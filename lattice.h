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


/// ����� ������������ ����� �����,
/// � ������� ������������� ������������ B-�������
class Lattice
{
public:
    /// �����������
    Lattice(gxSize3D s);
    /// ����������
    ~Lattice();

    /// ���������� [X]/stepX
    inline int GetIndexX(const double X) const
    { return int((X - size.getMinX()) / stepX); }

    inline int GetIndexY(const double Y) const
    { return int((Y - size.getMinY()) / stepY); }

    /// ���������� X-[X]
    /*!
      [X] �������� ����������� ��  stepX
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

    /// ����� ���� �����
    void Add (const Lattice* src);

    /// ������� �������� ������� � ����� (X,Y)
    double GetZ(const double X, const double Y) const;

	/// �������� ������ ����� � �������������� ������� ��� ��������� ��������
    void Refine();

    /// �������� ������ ����� ��� ����������� �������������
    void Rescale();

    Grid cgrid;
    int step; // ������ ������� �����
    double stepX, stepY;

    gxSize3D size;
};


#endif // LATTICE_H_INCLUDED
