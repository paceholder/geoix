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
//    along with Geoix. If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------


#ifndef KRIGING_PARAMS_H
#define KRIGING_PARAMS_H


struct gxKrigingParams2D
{
    /// Type of RBF function
    enum VariogramModel { Exponential, Gaussian, Spherical};

    VariogramModel variogramModel;

    // ellips parameters
    double rangex;
    double rangey;

    // ellips rotation
    double anglez;

    double sill; // top
    double nugget;  // bottom



    gxKrigingParams2D(VariogramModel v, double rx, double ry, double az, double s, double n)
        : variogramModel(v), rangex(rx), rangey(ry), anglez(az), sill(s), nugget(n)
    {}
};




struct gxKrigingParams3D
{
    /// Type of RBF function
    enum VariogramModel { Exponential, Gaussian, Spherical};

    VariogramModel variogramModel;

    // ellips parameters
    double rangex;
    double rangey;
    double rangez;

    // ellips rotation
    double anglex;
    double angley;
    double anglez;

    double sill; // top
    double nugget;  // bottom



    gxKrigingParams3D(VariogramModel v,
                      double rx, double ry, double rz,
                      double ax, double ay, double az,
                      double s, double n)
        : variogramModel(v),
        rangex(rx), rangey(ry), rangez(rz),
        anglex(ax), angley(ay), anglez(az),
        sill(s), nugget(n)
    {}
};

#endif // KRIGING_PARAMS_H
