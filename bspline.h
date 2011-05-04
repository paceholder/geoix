#ifndef BSPLINE_H_INCLUDED
#define BSPLINE_H_INCLUDED

#include <math.h>
#include <vector>

typedef double (*B)(double);

// basis cubic functions
extern B Bfunct[4];

// ������� ������������ 2� ������� �������
inline double W_ab(const int k, const int l, const double s, const double t)
{
    return Bfunct[k](s)*Bfunct[l](t);
}

// ������������� � ������������.
inline double Summ_w_ab(const double s,const double t)
{
    double summ = 0;
    for (int i = 0; i<4; ++i)
        for (int j = 0; j<4; ++j)
        {
            summ += W_ab(i,j,s,t);
        }
    return  summ;
}

#endif // BSPLINE_H_INCLUDED
