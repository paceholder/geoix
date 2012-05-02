#ifndef ABSTRACT_MAPPER_H
#define ABSTRACT_MAPPER_H

#include <QtCore>

#include "point_nd.h"
#include "size.h"
#include "matrix.h"

class gxAbstractMapper : public QObject
{
    Q_OBJECT
public:
    gxAbstractMapper(QString splineName)
        : name(splineName)
    {}
    /// abstract function which is reimplemented in
    /// subclasses
    virtual bool calcSurface(const gxPoint3DList points,
                             const gxSize3D size,
                             const int nx, const int ny,
                             std::vector<double> &result) = 0;

    QString getName() { return name; }

    /// returns widget which is embedded in
    /// mapping window
    virtual QWidget *getSettingsWidget(QWidget *parent = 0) = 0;
protected:
    QString name;

    void removeEqualPoints(gxPoint3DList &points);

    gxPoint3D average(gxPoint3DList &toBeAveraged);

    std::vector<double> leastSquare(gxPoint3DList &points);

};


#endif // ABSTRACT_MAPPER_H
