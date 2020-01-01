#ifndef LATTICE_H_INCLUDED
#define LATTICE_H_INCLUDED

#include <QtCore>
#include "size.h"

// define lattice for b-spline control point
struct grid_elem
{
    grid_elem(double value_ = 0, double delta_ = 0, double w_ = 0)
        : value(value_),
        delta(delta_),
        w(w_)
    {}

    void clear()
    {
        value = 0;
        delta = 0;
        w = 0;
    }

    double value, delta, w;
};

typedef QVector<QVector<grid_elem> > Grid;


/// Класс представляет собой сетку,
/// в которой накапливаются коэффициенты B-сплайна
class Lattice
{
public:
    /// Конструктор
    Lattice(gxSize3D s);
    /// Деструктор
    ~Lattice();

    /// возвращаем [X]/stepX
    inline int GetIndexX(const double X) const
    { return int((X - size.getMinX()) / stepX); }

    inline int GetIndexY(const double Y) const
    { return int((Y - size.getMinY()) / stepY); }

    /// возвращает X-[X]
    /*!
      [X] означает округленная до  stepX
    */
    inline double GetPartX(const double X) const
    {
        double xi = GetIndexX(X);
        return ((X - size.getMinX())/stepX - xi);
    }

    inline double GetPartY(const double Y) const
    {
        double yi = GetIndexY(Y);
        return ((Y - size.getMinY())/stepY - yi);
    }

    /// сумма двух сеток
    void Add (const Lattice* src);

    /// считает значение сплайна в точке (X,Y)
    double GetZ(const double X, const double Y) const;

	/// Изменяет размер сетки с коэффициентами сплайна для следующей итерации
    void Refine();

    /// Изменяет размер сетки без перерасчета коэффициентов
    void Rescale();

    Grid cgrid;
    int step; // размер текущей сетки
    double stepX, stepY;

    gxSize3D size;
};


#endif // LATTICE_H_INCLUDED
