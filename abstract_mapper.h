#ifndef ABSTRACT_MAPPER_H
#define ABSTRACT_MAPPER_H

#include <QtCore>

#include "point3D.h"
#include "size.h"

class gxAbstractMapper : public QObject
{
    Q_OBJECT
public:
    gxAbstractMapper(QString splineName)
        : name(splineName)
    {}
    /// abstract function which is reimplemented in
    /// subclasses
    virtual bool calcSurface(const gxPoints3DList points,
                             const gxSize3D size,
                             const int nx, const int ny,
                             QVector<double> &result) = 0;

    QString getName() { return name; }

    /// returns widget which is embedded in
    /// mapping window
    virtual QWidget *getSettingsWidget(QWidget *parent) = 0;
protected:
    QString name;
};


#endif // ABSTRACT_MAPPER_H
