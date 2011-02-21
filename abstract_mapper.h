#ifndef ABSTRACT_MAPPER_H
#define ABSTRACT_MAPPER_H

#include <QtCore>

class gxAbstractMapper : public QObject
{
    Q_OBJECT
public:
    gxAbstractMapper(QString splineName)
        : name(splineName)
    {}
    /// abstract function which is reimplemented in
    /// subclasses
    virtual bool calcSurface(const double *x, const double *y, const double *z,
                     const double minx, const double miny,
                     const double maxx, const double maxy,
                     const int nx, const int ny,
                     double *result) = 0;

    QString getName() { return name; }

    /// returns widget which is embedded in
    /// mapping window
    virtual QWidget *getSettingsWidget(QWidget *parent) = 0;
protected:
    QString name;
};


#endif // ABSTRACT_MAPPER_H
