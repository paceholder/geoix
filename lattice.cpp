#include "bspline.h"
#include "lattice.h"

/// конструктор
Lattice::Lattice(gxSize3D s)
    : size(s)
{
    double width  = size.getW();
    double height = size.getH();

    size.setSize(size.getMinX() - width,
                 size.getMinY() - height,
                 0,
                 size.getMaxX() + width,
                 size.getMaxY() + height,
                 0);

    step = 1; // set initial grid

    stepX = size.getW()/(double)(step+2);
    stepY = size.getH()/(double)(step+2);

    cgrid.resize(step+3);
    for (int i = 0; i < cgrid.size(); ++i)
    {
        cgrid[i].resize(step+3);
        for(int j = 0; j < cgrid.size(); ++j)
            cgrid[i][j].clear();
    }
}

Lattice::~Lattice()
{
    //
}

void Lattice::Refine()
{
    Grid temp;
    step *= 2;

	// изменяем размер ячейки
    stepX /= 2;
    stepY /= 2;

    // изменяем размер границ
    size.setSize(size.getMinX() + stepX,
                 size.getMinY() + stepY,
                 0,
                 size.getMaxX() - stepX,
                 size.getMaxY() - stepY,
                 0);

    //Изменяем размер сетки
    temp.resize(step+3);
    for (int i = 0; i < temp.size(); ++i)
        temp[i].resize(step + 3);

    // копируем старые коэффициенты в новую сетку с перерасчетом
    // что бы на новой уплотненной сетке строился тот же самый сплайн

    for (int i = 0; i<step/2+3-1; ++i)
        for (int j = 0; j<step/2+3-1; ++j)
        {

            // HARDCORE SCIENTIFIC PROGRAMMING BELOW =)

            temp[2*i][2*j].value = (cgrid[i][j].value + cgrid[i][j+1].value  +
                                  cgrid[i+1][j].value +  cgrid[i+1][j+1].value ) / 4;

            temp[2*i][2*j].delta = 0;
            temp[2*i][2*j].w = 0;

            if ((i!=0) && (j!=0))
            {
                temp[2*i-1][2*j-1].value = (cgrid[i-1][j-1].value + cgrid[i-1][j+1].value +
                                            cgrid[i+1][j-1].value + cgrid[i+1][j+1].value +
                                            6*(cgrid[i-1][j].value + cgrid[i][j-1].value +
                                               cgrid[i][j+1].value + cgrid[i+1][j].value) +
                                              36*cgrid[i][j].value) / 64;
                temp[2*i-1][2*j-1].delta = 0;
                temp[2*i-1][2*j-1].w = 0;
            }

            if (i!=0)
            {
                temp[2*i-1][2*j].value = (cgrid[i-1][j].value + cgrid[i-1][j+1].value +
                                          cgrid[i+1][j].value + cgrid[i+1][j+1].value +
                                          6*(cgrid[i][j].value +cgrid[i][j+1].value)) / 16;
                temp[2*i-1][2*j].delta = 0;
                temp[2*i-1][2*j].w = 0;
            }

            if (j!=0)
            {
                temp[2*i][2*j-1].value = (cgrid[i][j-1].value + cgrid[i][j+1].value +
                                          cgrid[i+1][j-1].value + cgrid[i+1][j+1].value +
                                          6*(cgrid[i][j].value + cgrid[i+1][j].value)) / 16;
                temp[2*i][2*j-1].delta = 0;
                temp[2*i][2*j-1].w = 0;
            }
        }

    // и заменяем на новую
    cgrid = temp;
}


// увеличивает размер сетки (x2)
void Lattice::Rescale()
{
    step *= 2;

	// change size of cell
    stepX /= 2;
    stepY /= 2;

    // изменяем размер границ
    size.setSize(size.getMinX() + stepX,
                 size.getMinY() + stepY,
                 0,
                 size.getMaxX() - stepX,
                 size.getMaxY() - stepY,
                 0);


    //resize grid
    cgrid.resize(step+3);
    for (int i = 0; i < step + 3; ++i)
    {
        cgrid[i].resize(step + 3);
        for(int j = 0; j < cgrid.size(); ++j)
            cgrid[i][j].clear();
    }

}


// возвращает z-значение точки
double Lattice::GetZ(const double X, const double Y) const
{
    double s = GetPartX(X);
    double t = GetPartY(Y);

    int xi =  GetIndexX(X) - 1;
    int yi =  GetIndexY(Y) - 1;

    if (xi > step + 2) { --xi; s = 1;}
    if (yi > step + 2) { --yi; t = 1;}

    if (xi < 0) { xi = 0; s = 0;}
    if (yi < 0) { yi = 0; t = 0;}

    double result = 0;
    for(int i = 0; i< 4; ++i )
        for(int j = 0; j< 4; ++j )
        {
            int m = xi + i;
            int n = yi + j;

            if (m > (cgrid.size()-1)) { --m; s =1; }
            if (n > (cgrid[m].size()-1)) { --n; t = 1; }

            result += W_ab(i,j,s,t) * (cgrid[m][n].value);
        }

    return result;
}


// суммирует две сетки
void Lattice::Add(const Lattice* src)
{
    int l = src->step+3;

    for (int i = 0; i<l; ++i)
        for (int j = 0; j<l; ++j)
        {
            this->cgrid[i][j].value += src->cgrid[i][j].value;
        }
}
