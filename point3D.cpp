#include "point3D.h"

#include "math.h"
#include "constants.h"


gxPoint3D::gxPoint3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

gxPoint3D& gxPoint3D::operator=(const gxPoint3D& p)
{
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;

    return *this;
}

bool gxPoint3D::operator==(gxPoint3D &p)
{
    return ((qAbs(this->x - p.x) < Gx::Eps) &&
            (qAbs(this->y - p.y) < Gx::Eps) &&
            (qAbs(this->z - p.z) < Gx::Eps) );
}

gxPoint3D &gxPoint3D::operator+=(gxPoint3D &p)
{
    this->x += p.x;
    this->y += p.y;
    this->z += p.z;

    return *this;
}

double gxPoint3D::distance2D(const gxPoint3D &point) const
{
    return sqrt(pow(x - point.x, 2) +
                pow(y - point.y, 2)/* +
                pow(z - point.z, 2)*/);
}

double gxPoint3D::distance2D(const double x,
                         const double y) const
{
    return sqrt(pow(this->x - x, 2) +
                pow(this->y - y, 2));
}

/// Comparison of x coordinate of points
bool gxPoint3D::pointXLessThan(const gxPoint3D &p1, const gxPoint3D &p2)
{
    return p1.x < p2.x;
}

/// Comparison of y coordinate of points
bool gxPoint3D::pointYLessThan(const gxPoint3D &p1, const gxPoint3D &p2)
{
    return p1.y < p2.y;
}
