#ifndef CUBEDIALOG_H
#define CUBEDIALOG_H

#include <QDialog>

namespace Ui {
    class gxCubeDialog;
}

class gxCubeDialog : public QDialog {
    Q_OBJECT
public:
    gxCubeDialog(QWidget *parent = 0);
    ~gxCubeDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::gxCubeDialog *ui;
};

#endif // CUBEDIALOG_H
