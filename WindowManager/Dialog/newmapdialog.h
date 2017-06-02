#ifndef NEWMAPDIALOG_H
#define NEWMAPDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class NewMapDialog;
}

class NewMapDialog : public QDialog{
    Q_OBJECT

public:
    explicit NewMapDialog(QWidget *parent = 0);
    ~NewMapDialog();

    QString getMapName();
    int     getMapWidth();
    int     getMapHeight();
    QString getTilesetFilePath();
    int     getTileWidth();
    int     getTileHeight();

signals:
    void createSignal(NewMapDialog *dialog);

private slots:
    void createSlot();
    void loadTilesetFile();

private:
    Ui::NewMapDialog *ui;
};

#endif // NEWMAPDIALOG_H
