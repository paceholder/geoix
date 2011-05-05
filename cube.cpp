#include "cube.h"


#include "logger.h"

gxCube::gxCube(gxTreeFolderObject *parent)
    : gxVisualObject(parent)
{
    name = tr("New 3D Cube");

    // some initialization

    // end initialization

    gxLogger::instance()->logEvent("3d cube '" + name + "' created");
}




gxCube::~gxCube()
{

}


void gxCube::setRestrictingSurfaces(gxSurface *top,
                                    gxSurface *bottom,
                                    gxCube::GridSurface gridDefiningSurface,
                                    gxCube::SedimentationModel sedimentationModel)
{
    Q_UNUSED(top);
    Q_UNUSED(bottom);
    Q_UNUSED(gridDefiningSurface);
    Q_UNUSED(sedimentationModel);
}

