#ifndef VARIANCE_MODEL_H
#define VARIANCE_MODEL_H

#include <QtCore>

#include "matrix.h"

#include "math.h"

inline double grad_to_rad(double grad)
{
        return ( grad * M_PI ) / 180.0;
}


//------------------------------------------------------------------------------


class gxVariogramModel2D
{
public:
    QVector<double> createTransformation3D(double rangex,
                                           double rangey,
                                           double rangez,
                                           double rotx   = 0, // grads
                                           double roty   = 0,
                                           double rotz   = 0)
    {

        math::matrix<double> scale(3, 3);
        math::matrix<double> rotate_z(3, 3);
        math::matrix<double> rotate_y(3, 3);
        math::matrix<double> rotate_x(3, 3);

        scale(0, 0) = 1.0;
        scale(1, 1) = rangesx/rangesy;
        scale(2, 2) = rangesx/rangesz;

        rotate_x(2, 2) =  cos(grad_to_rad(rotz));
        rotate_x(3, 3) =  cos(grad_to_rad(rotz));
        rotate_x(2, 3) =  sin(grad_to_rad(rotz));
        rotate_x(3, 2) = -sin(grad_to_rad(rotz));
        rotate_x(1, 1) = 1;

        rotate_y(1, 1) =  cos(grad_to_rad(roty));
        rotate_y(3, 3) =  cos(grad_to_rad(roty));
        rotate_y(1, 3) = -sin(grad_to_rad(roty));
        rotate_y(3, 1) =  sin(grad_to_rad(roty));
        rotate_y(2, 2) =  1;

        rotate_z(1, 1) = cos(grad_to_rad(rotz));
        rotate_z(2, 2) = cos(grad_to_rad(rotz));
        rotate_z(1, 2) = sin(grad_to_rad(rotz));
        rotate_z(2, 1) = -sin(grad_to_rad(rotz));
        rotate_z(3, 3) = 1;
    }

    QVector<double> createTransformation2D(double rangex,
                                           double rangey,
                                           double rotx = 0)
    {
        math::matrix<double> scale(3, 3);
        math::matrix<double> rotate_z(3, 3);

        scale(0, 0) = 1.0;
        scale(1, 1) = rangesx/rangesy;
        scale(2, 2) = 1.0;

        rotate_z(1, 1) = cos(grad_to_rad(rotz));
        rotate_z(2, 2) = cos(grad_to_rad(rotz));
        rotate_z(1, 2) = sin(grad_to_rad(rotz));
        rotate_z(2, 1) = -sin(grad_to_rad(rotz));
        rotate_z(3, 3) = 1
    }

private:
    QVector<double> transformation;
};

#endif // VARIANCE_MODEL_H
