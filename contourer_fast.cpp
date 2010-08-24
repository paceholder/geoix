//------------------------------------------------------------------------
//    This file is part of Geoix.
//
//    Copyright (C) 2010 Dmitriy Pinaev
//
//    Geoix is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Geoix is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------


#include "contourer_fast.h"

#include "surface_data.h"
#include "surface_data_iterator.h"


//---------------------------------------------------
//                         gxContourer

gxContourer::gxContourer(double step)
    : QObject()
{
    this->step = step;
    this->curcont = NULL;
}

void gxContourer::run(gxSurfaceData* data, gxFlatContours* contours)
{
    this->data = data;
    this->contours = contours;

    this->edges.resize(data->values.size());


    double minz = data->getSize()->getMinZ();
    double maxz = data->getSize()->getMaxZ();

    if (abs(maxz - minz) < step)
        curz = minz +data->getSize()->getD()/2.0;
    else
        curz = minz + step/2.0;

    // check every minz + step*n depth
    while (curz < maxz)
    {
        resetEdges();
        markEdges(curz);

        runEdges();

        curz += step;
    }
}

void gxContourer::markEdges(double curz)
  {
      gxSurfaceDataIterator it(this->data);

      double z;
      int pos;
      int x, y;
      while(it.goNext())
      {
          pos = it.getPos();

          x = it.getX(); y = it.getY();

          bool b = (data->values[pos] >= curz);

          // horisontal
          if (x < data->nx - 1)
          {
              z = data->values[pos + 1];
              if (z == Gx::BlankDouble) continue;

              Q_ASSERT(y * data->nx + x < data->values.count());

              if (b != (z >= curz))
                  edges[y * data->nx + x] |= 1;
          }

          // vertical
          if (y < data->ny - 1)
          {
              z = data->values[pos + data->nx];
              if (z == Gx::BlankDouble) continue;

              Q_ASSERT(y * data->nx + x < data->values.count());

              if (b != (z >= curz))
                  edges[y * data->nx + x] |= 2;
          }

          // diagonal
          if ((x < data->nx - 1) &&
              (y < data->ny - 1))
          {
              z = data->values[pos + data->nx + 1];
              if (z == Gx::BlankDouble) continue;

              Q_ASSERT(y * data->nx + x < data->values.count());

              if (b != (z >= curz))
                  edges[y * data->nx + x] |= 4;
          }

      }
  }


void gxContourer::runEdges()
   {
       gxSurfaceDataIterator it(this->data);

       int pos;
       while(it.goNext())
       {
           pos = it.getPos();

           // no marked edges
           if (edges[pos] == 0) continue;

           QQueue<gxEdge> runedges;

           // horizontal edge
           if (edges[pos] & 1)
           {
               //edges[pos] &= ~1; // delete mark;

               runedges.clear();
               runedges.append(gxEdge(pos, pos + 1, +1));
               runedges.append(gxEdge(pos + 1, pos, -1));

               walkEdge(runedges);

               if (curcont->count())
                   contours->append(curcont);
               else
                   delete curcont;
           }

           // vertical edge
           if (edges[pos] & 2)
           {
               //edges[pos] &= ~2;
               runedges.append(gxEdge(pos, pos + data->nx, +1));
               runedges.append(gxEdge(pos + data->nx, pos, -1));

               walkEdge(runedges);

               if (curcont->count())
                   contours->append(curcont);
               else
                   delete curcont;
           }

           // diagonal edge
           if (edges[pos] & 4)
           {
               //edges[pos] &= ~4;

               runedges.append(gxEdge(pos, pos + data->nx + 1, +1));
               runedges.append(gxEdge(pos + data->nx + 1, pos, -1));

               walkEdge(runedges);

               if (curcont->count())
                   contours->append(curcont);
               else
                   delete curcont;
           }
       }
   }


void gxContourer::addPoint(int pos, int vector, int direction)
{
    Q_ASSERT(pos >=0 );

    double x1, y1, x2, y2, z1, z2;
    double d;
    int x = pos % data->nx;
    int y = pos / data->nx;

    int nextpos = 0;

    z1 = data->values[pos];
    x1 = data->getX(x);
    y1 = data->getY(y);

    switch(vector)
    {
    case 1: nextpos = pos + 1; break;
    case 2: nextpos = pos + data->nx; break;
    case 4: nextpos = pos + data->nx + 1; break;
    }

    Q_ASSERT(nextpos < data->nx*data->ny);
    Q_ASSERT(nextpos > 0);

    x = nextpos % data->nx;
    y = nextpos / data->nx;

    z2 = data->values[nextpos];
    x2 = data->getX(x);
    y2 = data->getY(y);

    d = (curz - z1)/(z2 - z1);

    gxPoint2D p(x1 + (x2 - x1) * d,
                y1 + (y2 - y1) * d);

    if (direction > 0)
        curcont->addPointFront(p);
    else
        curcont->addPointBack(p);
}


// A piece of shit below
void gxContourer::walkEdge(QQueue<gxEdge>& runedges)
{
    // creating of new contour
    curcont = new gxFlatContour(curz);

    while ( runedges.count() > 0 )
    {
        gxEdge edge = runedges.takeFirst();


        Q_ASSERT(edge.knot1 >=0 );
        Q_ASSERT(edge.knot1 < data->values.count() );
        Q_ASSERT(edge.knot2 >=0 );
        Q_ASSERT(edge.knot2 < data->values.count() );

        int d = edge.knot2 - edge.knot1;
        int m = qMin(edge.knot1, edge.knot2);
        // horizontal edges
        if (qAbs(d) == 1)
        {
            if (d > 0)
            {
                // building upper triangle
                if (edge.knot1 / data->nx < data->ny - 1) // not last row
                {
                    //     /_|
                    if (edges[edge.knot1] & 4) // diaglonal
                    {
                        runedges.append(gxEdge(edge.knot1, edge.knot1 + data->nx + 1, edge.direction));
                    }

                    if (edges[edge.knot2] & 2) // vertical
                    {
                        runedges.append(gxEdge(edge.knot2 + data->nx , edge.knot2, edge.direction));
                    }
                }
            }
            else
            {
                if (edge.knot1 / data->nx > 0)
                {
                    //     _
                    //    |/

                    if (edges[edge.knot2 - data->nx]  & 2) // vertical
                    {
                        runedges.append(gxEdge(edge.knot2 - data->nx, edge.knot2, edge.direction));
                    }

                    if (edges[edge.knot2 - data->nx]  & 4) // diagonal
                    {
                        runedges.append(gxEdge(edge.knot1, edge.knot2 - data->nx, edge.direction));
                    }

                }
            }

            if (edges[m] & 1) addPoint(m, 1, edge.direction);

            //if (!isLastAdded(m, 1))
                edges[m] &= ~1; //demark edge                     todo:
        }


        // vertical edge
        else if (qAbs(d) == data->nx)
        {
            if (d > 0)
            {
                if (edge.knot1 % data->nx > 0) // not first element in row
                {
                    if (edges[edge.knot1 - 1] & 4) // diagonal
                    {
                        runedges.append(gxEdge(edge.knot1 - 1, edge.knot2, edge.direction));
                    }

                    if (edges[edge.knot1 - 1] & 1) // horizontal
                    {
                        runedges.append(gxEdge(edge.knot1, edge.knot1 - 1, edge.direction));
                    }
                }
            }
            else
            {
                if (edge.knot1 % data->nx < data->nx -1 )
                {

                    if (edges[edge.knot2] & 4) // diagonal
                    {
                        runedges.append(gxEdge(edge.knot1 + 1, edge.knot2, edge.direction));
                    }

                    if (edges[edge.knot1] & 1) // horizontal
                    {
                        runedges.append(gxEdge(edge.knot1, edge.knot1 + 1, edge.direction));
                    }
                }
            }

            if (edges[m] & 2) addPoint(m, 2, edge.direction);

           // if (!isLastAdded(m, 2))
                edges[m] &= ~2; //demark edge
        }


        // diagonal edge
        else if (qAbs(d) == data->nx + 1)
        {

            // denote direction of edge
            if (d > 0)
            {
                if (edges[edge.knot1] & 2) // vertical
                {
                    runedges.append(gxEdge(edge.knot1, edge.knot1 + data->nx, edge.direction));
                }

                if (edges[edge.knot1 + data->nx] & 1) // horizontal
                {
                    runedges.append(gxEdge(edge.knot1 + data->nx, edge.knot2, edge.direction));
                }
            }
            else
            {
                if (edges[edge.knot2] & 1) // horizontal
                {
                    runedges.append(gxEdge(edge.knot2 +1, edge.knot2, edge.direction));
                }

                if (edges[edge.knot1 - data->nx] & 2) // vertical
                {
                    runedges.append(gxEdge(edge.knot1, edge.knot1 -data->nx, edge.direction));
                }
            }

            if (edges[m] & 4) addPoint(m, 4, edge.direction);

            //if (!isLastAdded(m, 4))
                edges[m] &= ~4; //demark edge
        }


    }
}
