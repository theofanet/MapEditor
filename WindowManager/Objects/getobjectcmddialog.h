#ifndef GETOBJECTCMDDIALOG_H
#define GETOBJECTCMDDIALOG_H

#include <QDialog>
#include "Objects/object.h"

namespace Ui {
class GetObjectCmdDialog;
}

class GetObjectCmdDialog : public QDialog{
    Q_OBJECT

public:
    explicit GetObjectCmdDialog(Object *obj, QWidget *parent = 0);
    ~GetObjectCmdDialog();

signals:
    void cmdSelected(Object* obj, string cmd);

public slots:
    void cmdChoosed();

private:
    Ui::GetObjectCmdDialog *ui;

    Object *_object;
};

#endif // GETOBJECTCMDDIALOG_H
