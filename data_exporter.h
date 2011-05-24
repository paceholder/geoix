#ifndef DATAEXPORTER_H
#define DATAEXPORTER_H

#include "point3D.h"
#include "contour.h"

class gxSurfaceData;
class gxWell;

class gxDataExporter
{
public:
    /// Loads points' data from txt file
    static bool exportPointsData(gxPoint3DList* data);
    /// Loads surface's data from txt file
    static bool exportSurfaceData(gxSurfaceData* data);
    /// Loads lines' data from txt file
    static bool exportLinesData(gxContourList* data);

private:

    /// Opens text file and fill list. List must exist
    static void saveToTextFile(QStringList &list);
};

#endif // DATAEXPORTER_H
