#ifndef DOMAINS_H_INCLUDED
#define DOMAINS_H_INCLUDED


#include "size.h"
#include "point3D.h"


// some definitions below
enum gxDomainLongSide {Length, Width};

/// Comparison of x coordinate of points
static bool pointXLessThan(const gxPoint3D &p1, const gxPoint3D &p2)
{
    return p1.x < p2.x;
}

/// Comparison of y coordinate of points
static bool pointYLessThan(const gxPoint3D &p1, const gxPoint3D &p2)
{
    return p1.y < p2.y;
}


static const int defaulfDomainCapacity = 500;


//------------------------------------------------------------------------------


class gxRBFDomain
{
public:
    /// size of domain, vector of points
    gxRBFDomain(gxDomainLongSide parentLongSide,
                const gxSize3D &s,
                gxPoints3DList p);
    ~gxRBFDomain();

    /// points belonging to this domain
    gxPoints3DList points;

    gxRBFDomain *leftDomain, *rightDomain; // children

    /// returns z-value at point with x and y coords
    double getValue(const double x, const double y);

    /// special smoothin function
    inline double V(const double x, const double y)
    {
        double d;
        if ( inRange(x,y) )
        {
            if ( longSide == Width )
                d = 1 - 4*(x - size.getMinX())*(size.getMaxX() - x)/(size.getW() * size.getW());
            else
                d = 1 - 4*(y - size.getMinY())*(size.getMaxY() - y)/(size.getH() * size.getH());
        }
        else
            d = 1;

        double d2 = d*d;
        return  2*d2*d -3 * d2 + 1;
    }

    static void setMaxLeafCapacity(int capacity)
    {
        gxRBFDomain::maxLeafCapacity = capacity;
    }
private:
    static int maxLeafCapacity;

    gxSize3D size;

    /// density of points.
    /// It regulates value of domains' overlapping
    double density;

    /// area of domain
    double area;

    /// longest side of domain
    gxDomainLongSide longSide;

    /// coefficients of spline
    QVector<double> coeff;

    /// creates subdomains' tree
    void buildTree();

    /// create coefficients of spline (just for Leafs)
    bool buildSpline();

    /// Checks if point is in range of domain
    inline bool inRange(double x, double y)
    {
        return (! (x < size.getMinX() || x > size.getMaxX() ||
                   y < size.getMinY() || y > size.getMaxY()));
    }

    /// Distance function
    inline double Df(const double x, const double y)
    {
        double s = area*area;


        /// \todo reread the article
        return (1 - 16 * (x - size.getMinX() ) * (size.getMaxX() - x) *
                         (y - size.getMinY() ) * (size.getMaxY() - y)/s);
    }


    /// if this domain is leaf
    inline bool isLeaf()
    {
        return ((leftDomain == NULL) || (rightDomain == NULL));
    }
};




#endif // DOMAINS_H_INCLUDED
