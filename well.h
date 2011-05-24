#ifndef WELL_H
#define WELL_H

#include "visual_object.h"
#include "curve.h"

class gxWell : public gxVisualObject
{
    Q_OBJECT
public:
    gxWell(gxTreeFolderObject *parent);

    virtual ~gxWell();

    QIcon getIcon();

    QMenu *getMenu();

    QString getMimeType() { return QString("geoix/well"); }

    void draw2D();
    void draw3D();

    void recalcSize();

    gxPoint3DList getPoint3DList() { return gxPoint3DList(); }

    void setData(gxPoint3DList newPoints) { data = newPoints; recalcSize();}
    bool hasData() { return data.size(); }

public slots:
    void importFromFile();
    void clearData(){}
    void options() {}

private:
    gxPoint3DList data;

    QList<gxCurve> curves;
};

#endif // WELL_H
