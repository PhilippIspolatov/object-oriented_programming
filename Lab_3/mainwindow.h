#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvas.h"
#include <QGraphicsScene>
#include "receiver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();

    void on_scale_button_clicked();

    void on_rotate_button_clicked();

    void on_transfer_button_clicked();

private:
    Ui::MainWindow *ui;
    MyViewer viewer;
    Canvas<QGraphicsScene> canvas = new QGraphicsScene();
};

#endif // MAINWINDOW_H
