#ifndef CUMULATIVE_DISTRIBUTION_H
#define CUMULATIVE_DISTRIBUTION_H

#include "point3D.h"

#include <QtCore>
#include <QtAlgorithms>
#include <QtGui>

/// Abstract Cumulative Distribution Function
class gxAbstractCDF
{
public:
    /// Returns probability corresponding to the given value (x)
    virtual double probability(double value) const = 0;

    /// Returns value corresponding to the given probability (rho)
    /// Here equation phi(x) - prob = 0 is solved
    virtual double value(double prob) const = 0;


    /// Trasformation of random function values
    /// from one distribution to another one
    static void transform(QVector<double> &values,
                          const gxAbstractCDF *from_cdf,
                          const gxAbstractCDF *to_cdf)
    {
        QMutableVectorIterator<double> it(values);

        while(it.hasNext())
        {
            double prob = from_cdf->probability(it.peekNext());
            double value = to_cdf->value(prob);
            it.next() = value;
        }
    }

    static void transform(gxPoint3DList &points,
                          const gxAbstractCDF *from_cdf,
                          const gxAbstractCDF *to_cdf)
    {
        QVector<double> values;
        foreach(gxPoint3D point, points)
            values.append(point.z);

        gxAbstractCDF::transform(values, from_cdf, to_cdf);

        for(int i = 0; i < points.size(); ++i)
        {
            points[i].z = values[i];
        }
    }
};

//------------------------------------------------------------------------------

// Custom cumulative distibution
class gxCDF : public gxAbstractCDF
{
public:
    /// Constructor
    gxCDF(gxPoint3DVector vector)
    {
        QMap<double, int> hash;
        foreach(gxPoint3D point, vector)
        {
            if (hash.contains(point.z))
            {
                hash[point.z] += 1;
            }
            else
                hash.insert(point.z, 1);
        }

        summation(hash);
    }


    /// Constructor
    gxCDF(QVector<double> vector)
    {
        QMap<double, int> hash;
        foreach(double value, vector)
        {
            if (hash.contains(value))
                hash[value] += 1;
            else
                hash.insert(value, 1);
        }

        summation(hash);
    }


    /// Returns probability corresponding to the given value (x)
    double probability(double value) const
    {
        if (value < cdf.first().first)
            return cdf.first().first;

        if (value > cdf.last().first)
            return cdf.last().first;


        QVectorIterator<QPair<double, double> > it(cdf);

        while(it.hasNext() &&
              (it.peekNext().first < value))
            it.next();

        double dx = it.peekNext().second - it.peekPrevious().second;
        double dy = it.peekNext().first - it.peekPrevious().first;

        return (value - it.peekPrevious().first)/dy * dx + it.peekPrevious().second;
    }


    /// Returns value corresponding to the given probability (rho)
    /// Here equation phi(x) - prob = 0 is solved
    double value(double prob) const
    {
        if (prob < cdf.first().second)
            return cdf.first().second;

        if (prob > cdf.last().second)
            return cdf.last().second;

        QVectorIterator<QPair<double, double> > it(cdf);

        while(it.hasNext() &&
              (it.peekNext().second < prob))
            it.next();

        double dx = it.peekNext().second - it.peekPrevious().second;
        double dy = it.peekNext().first - it.peekPrevious().first;

        return (prob - it.peekPrevious().second)/dx * dy + it.peekPrevious().first;
    }

private:
    QVector<QPair<double, double> > cdf;

    void summation(QMap<double, int> &hash)
    {
        // 1) move data from map to cdf

        cdf.clear();

        QMapIterator<double, int> it_hash(hash);

        int count = 0;
        while(it_hash.hasNext())
        {
            cdf.append(QPair<double, double>(it_hash.peekNext().key(),
                                             it_hash.peekNext().value()));

            count += it_hash.peekNext().value();

            it_hash.next();
        }

        // 2) sorting

        sortCDF();

        // 3) summation

        QMutableVectorIterator<QPair<double, double> > it_cdf(cdf);

        if (it_cdf.hasNext()) it_cdf.next(); // skip first element
        while(it_cdf.hasNext())
        {
            it_cdf.peekNext().second += it_cdf.peekPrevious().second;
            it_cdf.next();
        }

        // 4) normalization

        it_cdf.toFront();

        while(it_cdf.hasNext())
        {
//            it_cdf.next().second /= cdf.last().second; // possible division by zero *trollface*
            it_cdf.next().second /= count;
        }
    }


    void sortCDF()
    {
        qSort(cdf.begin(), cdf.end(), gxCDF::lessThan);
    }

    /// Functor for CDF sorting
    static bool lessThan(const QPair<double, double> &pair1,
                         const QPair<double, double> &pair2)
    {
        return pair1.first < pair2.first;
    }
};

#endif // CUMULATIVE_DISTRIBUTION_H
