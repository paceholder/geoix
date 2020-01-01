//#include <algorithm>

#include "rbf_domain.h"
#include "rbf_core.h"


/// default overlapping ratio
const double OVERLAP = 0.2f;

int gxRBFDomain::maxLeafCapacity = 300;



//------------------------------------------------------------------------------



gxRBFDomain::gxRBFDomain(DomainLongSide pLongSide,
                         const gxSize3D &s,
                         gxPoint3DVector p)
    :
     points(p),
     leftDomain(0),
     rightDomain(0),
     size(s),
     density(p.size() / s.area()),
     parentLongSide(pLongSide)
{
    area = size.area();

    this->buildTree();
}


gxRBFDomain::~gxRBFDomain()
{
    if (leftDomain) delete leftDomain;
    if (rightDomain) delete rightDomain;
}

//---------------------------------------------------------------------------//


void gxRBFDomain::buildTree()
{
    int n = points.size();

    DomainLongSide longSide = size.getW() > size.getH() ? Width : Length;

    if ( n > gxRBFDomain::maxLeafCapacity ) // we still can create two branches
    {
        if (longSide == Width )
            qSort(points.begin(), points.end(), gxPoint3D::pointXLessThan);
        else
            qSort(points.begin(), points.end(), gxPoint3D::pointYLessThan);

        double overlap = OVERLAP;

        // overlapping depends on density ?
        // ?? is it equalls 1.0 ?
        overlap = OVERLAP * density / (points.size() / area) ;

        /// number of common points
        int n0 = OVERLAP * n; // + 1 ?

        // number of points in 1st subdomain
        int n1 = (n - n0) / 2 ;
        // number of points in 2ng subdomain
        int n2 = (n - n1 - n0);

        // prepare left subdomain
        gxPoint3DVector left_points;

        left_points.resize(n1+n0);
        qCopy(points.begin(), points.begin() + n1 + n0, left_points.begin());

        // let's change the size of domain
        gxSize3D left_size(size);

        if (longSide == Width)
            left_size.setMaxX(left_points.last().x());
        else
            left_size.setMaxY(left_points.last().y());

        leftDomain = new gxRBFDomain(longSide, left_size, left_points);

        // prepare right subdomain

        gxPoint3DVector right_points;
        right_points.resize(n2 + n0);
        qCopy(points.end() - (n2 + n0), points.end(), right_points.begin());


        // let's change the size of domain
        gxSize3D right_size(size);

        if (longSide == Width)
            right_size.setMinX(right_points.first().x());
        else
            right_size.setMinY(right_points.first().y());

        rightDomain = new gxRBFDomain(longSide, right_size, right_points);
    }
    else // no more subfomains let's create spline!
        buildSpline();
}

//-----------------------------------------------------------------------//

bool gxRBFDomain::buildSpline()
{
    return gxRBFCore::calculate(this->points, this->coeff);
}

//--------------------------------------------------------------------------//

double gxRBFDomain::getValue(const double x, const double y)
{
    // if point out of range
    if ( ! inRange(x, y) )
        return 0;


    double result = 0;
    if ( this->isLeaf() ) // calculate spline
    {
        int l = coeff.size();
        for (int i = 0; i < l - 3; ++i)
            result += gxRBFCore::coreFunction(points[i].distance2D(x, y)) * coeff[i];
        result += coeff[l-3] + coeff[l-2] * x + coeff[l-1] * y;
    }

    else // obtain value from children
    {
        double v1 = this->leftDomain->V(x,y);
        double v2 = this->rightDomain->V(x,y);

        double l = leftDomain->getValue(x,y);
        double r = rightDomain->getValue(x,y);

        if (v1 + v2 == 0.0)
            result = l+r;
        else
            result = (l * v1 + r * v2)/(v1 + v2);
    }
    return result;
}

