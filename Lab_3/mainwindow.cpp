#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <QString>
#include "receiver.h"
#include <QGraphicsScene>
#define PI 3.14159265

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Lab_03");



    ui->graphicsView->centerOn(0, 0);
    ui->graphicsView->setScene(canvas.scene());
    canvas.scene()->setSceneRect(-1000, -1000, 2000, 2000);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this);
    if (file_name.isEmpty()) return;

    QByteArray byte_name = file_name.toLatin1();
    char *filename = byte_name.data();

    //std::cout << filename << std::endl;

    // Test
    viewer.LoadModel(filename);
    viewer.DrawModel(&canvas);
}

void MainWindow::on_scale_button_clicked()
{
    double kx, ky, kz;
    kx = ui->kx_lineEdit->text().toDouble();
    ky = ui->ky_lineEdit->text().toDouble();
    kz = ui->kz_lineEdit->text().toDouble();
    viewer.Scale(kx, ky, kz);
    viewer.DrawModel(&canvas);
}

void MainWindow::on_rotate_button_clicked()
{
    double ax, ay, az;
    ax = ui->angle_x_lineEdit->text().toDouble() / 180 * PI;
    ay = ui->angle_y_lineEdit->text().toDouble() / 180 * PI;
    az = ui->angle_z_lineEdit->text().toDouble() / 180 * PI;
    viewer.Rotate(ax, ay, az);
    viewer.DrawModel(&canvas);
}

void MainWindow::on_transfer_button_clicked()
{
    double dx, dy, dz;
    dx = ui->dx_lineEdit->text().toDouble();
    dy = ui->dy_lineEdit->text().toDouble();
    dz = ui->dz_lineEdit->text().toDouble();
    viewer.Shift(dx, dy, dz);
    viewer.DrawModel(&canvas);
}
