#ifndef ADDTILESETDIALOG_H
#define ADDTILESETDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class AddTilesetDialog;
}

class AddTilesetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTilesetDialog(QWidget *parent = 0);
    ~AddTilesetDialog();

    QString getTilesetFilePath();
    int     getTileWidth();
    int     getTileHeight();

signals:
    void createSignal(AddTilesetDialog *dialog);

private slots:
    void createSlot();
    void loadTilesetFile();

private:
    Ui::AddTilesetDialog *ui;
};

#endif // ADDTILESETDIALOG_H
