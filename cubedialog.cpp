#include "cubedialog.h"
#include "ui_cubedialog.h"

#include "tree_abstract_object.h"
#include "visual_object.h"

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

/*

 bool MainWindow::eventFilter(QObject *obj, QEvent *event)
 {
     if (obj == textEdit) {
         if (event->type() == QEvent::KeyPress) {
             QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
             qDebug() << "Ate key press" << keyEvent->key();
             return true;
         } else {
             return false;
         }
     } else {
         // pass the event on to the parent class
         return QMainWindow::eventFilter(obj, event);
     }
 }

*/
