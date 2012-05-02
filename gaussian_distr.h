#ifndef GAUSSIAN_DISTR_H
#define GAUSSIAN_DISTR_H


#include <math.h>

#include "cumulative_distribution.h"

/// Gaussian (normal) distribution function
class gxGaussianCDF : public gxAbstractCDF
{
public:
    /// Constructor creates cummulative distribution
    gxGaussianCDF(double m = 0, double v  = 1)
        : mean(m), var(v)
    {}

    /// Returns probability corresponding to the given value (x)
    double probability(double value) const
    {
        return (1 + erf((value - mean)/sqrt(2 * var)))/2.0;
    }

    /// Returns value corresponding to the given probability (rho)
    /// Here equation phi(x) - prob = 0 is solved
    double value(double prob) const
    {
        double a = mean - 10 * var;
        double b = mean + 10 * var;


        while (true)
        {
            double x1 = a;
            double x2 = b;

            double y1 = probability(x1) - prob;
            //double y2 = probability(x2) - prob;

            /// we should have wider interval
            //if (y1 * y2 > 0) return 0;

            double mm = (x1 + x2) / 2.0;

            double ym = probability(mm) - prob;

            if (ym == 0) break;

            if (y1 * ym < 0)
                b = mm;
            else
                a = mm;


            if (abs(a - b) < 0.00001) break;
        }

        return (a + b)/2.0;
    }

private:
    double mean;
    double var;


};

#endif // GAUSSIAN_DISTR_H
