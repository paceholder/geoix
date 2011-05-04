#ifndef DOMAINS_H_INCLUDED
#define DOMAINS_H_INCLUDED


#include "size.h"
#include "point3D.h"

//------------------------------------------------------------------------------


class gxRBFDomain
{
public:
    enum DomainLongSide {Length, Width};


    /// size of domain, vector of points
    gxRBFDomain(DomainLongSide parentLongSide,
                const gxSize3D &s,
                gxPoint3DVector p);
    ~gxRBFDomain();



    /// points belonging to this domain
    gxPoint3DVector points;

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
    DomainLongSide longSide;

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
