#include "cubedialog.h"
#include "ui_cubedialog.h"

#include "tree_abstract_object.h"
#include "visual_object.h"
#include "surface.h"


gxCubeDialog::gxCubeDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowStaysOnTopHint),
    ui(new Ui::gxCubeDialog)
{
    ui->setupUi(this);

    QStringList list;
    list << "Top" << "Bottom";
    ui->cbBaseGrid->addItems(list);

    list.clear();
    list << "From top" << "From bottom" << "Proportional";
    ui->cbSedimentationModel->addItems(list);

    QIntValidator *validator = new QIntValidator(this);
    validator->setBottom(1);
    ui->lineNumberOfSublayers->setValidator(validator);

    /// setting up event filter
    ui->dropWidgetTop->installEventFilter(this);
    ui->dropWidgetBottom->installEventFilter(this);

    ui->dropWidgetTop->setAcceptDrops(true);
    ui->dropWidgetBottom->setAcceptDrops(true);

}

gxCubeDialog::~gxCubeDialog()
{
    delete ui;
}

void gxCubeDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



//------------------------------------------------------------------------------


bool gxCubeDialog::eventFilter(QObject *object, QEvent *event)
{
    if (!(object == ui->dropWidgetTop || object == ui->dropWidgetBottom))
        return QDialog::eventFilter(object, event);

    switch (event->type())
    {
    case QEvent::DragEnter:
        {
            QDragEnterEvent *eventEnter = static_cast<QDragEnterEvent*>(event);
            return handleDragEnterEvent(eventEnter);
        }
    case QEvent::Drop:
        {
            QDropEvent *dropEvent = static_cast<QDropEvent*>(event);
            return handleDropEvent(object, dropEvent);
        }
    default: break;
    }
    return false;
}


//------------------------------------------------------------------------------


bool gxCubeDialog::handleDragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/surface"))
    {
        event->setDropAction(Qt::CopyAction);
        event->accept();
        return true;
    }
    else
    {
        event->ignore();
        return false;
    }
}



//------------------------------------------------------------------------------


bool gxCubeDialog::handleDropEvent(QObject *object, QDropEvent *event)
{
    event->setDropAction(Qt::CopyAction);
    event->accept();

    foreach(QString format, event->mimeData()->formats())
    {
        const QMimeData *mimeData = event->mimeData();
        QByteArray encodedData = mimeData->data(format);

        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        while (!stream.atEnd())
        {
            quint64 pointer;
            stream >> pointer;

            gxTreeAbstractObject *abstractObject = reinterpret_cast<gxTreeAbstractObject*>(pointer);

            if (object == ui->dropWidgetTop)
                this->topSurface = abstractObject->getSharedPointer();
            else
                this->bottomSurface = abstractObject->getSharedPointer();

            QLabel *label = static_cast<QLabel*>(object);

            label->setText(abstractObject->getName());
        }
    }

    return true;
}


//------------------------------------------------------------------------------


void gxCubeDialog::createCube()
{
    gxSurface *topSurf = static_cast<gxSurface*>(topSurface.data());
    gxSurface *botSurf = static_cast<gxSurface*>(bottomSurface.data());
    gxSurface *baseSurface = ui->cbBaseGrid->currentIndex() == 0 ? topSurf : botSurf;

    /// intersection of sizes of two surfaces
    gxSize3D size = topSurf->getSize().intersect(botSurf->getSize());

    if (size.volume() < 0) return;
}
