#include "widget.h"
#include "ui_widget.h"

#include "entrypoint.h"
#include "render.h"

#include "math.h"
#include <string.h>

#include <QMessageBox>
#include <QString>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("OOP Lab1");
    this->resize(700,350);
    this->setFixedSize(700,350);

    scene = new sCanvasContainer;
    scene->pb = new QGraphicsScene();  // render.h
    change.canvas  = scene;

    ui->graphicsView->centerOn(0,0);
    ui->graphicsView->setScene(scene->pb);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->pb->setSceneRect(-99999,-99999,99999*2,99999*2);

    ui->scaleKoeffSpin->setValue(1);
}

Widget::~Widget()
{
    Apply(caDelete, &change);
    delete ui;
}

void Widget::on_openButton_clicked()
{
    QString str1 = QFileDialog::getOpenFileName(this, tr("Open model"), "D:\\Labs 4 semestr\\OOP\\Lab01");
    if (str1.isEmpty())
        return;

    QByteArray ba = str1.toLatin1();
    char *filename = ba.data();
    change.filename = filename;

    eCodeFile result = Apply(caLoad, &change);

    if (result == cfNotFound)
    {
        QMessageBox msg;
        msg.setText("File isn't found!");
        msg.exec();
    }
    else if (result == cfOutOfMemory)
    {
        QMessageBox msg;
        msg.setText("Error of allocate memory!");
        msg.exec();
    }

    result = Apply(caDraw, &change);
}

void Widget::on_saveButton_clicked()
{
    QString str1 = QFileDialog::getSaveFileName(this, tr("Save model"), "D:\\Labs 4 semestr\\OOP\\Lab01");
    if (str1.isEmpty())
        return;

    QByteArray ba = str1.toLatin1();
    char *filename = ba.data();
    change.filename = filename;

    Apply(caSave, &change);
    Apply(caDraw, &change);
}

void Widget::on_scaleButton_clicked()
{
    change.scale = ui->scaleKoeffSpin->value();

    Apply(caScale, &change);
    Apply(caDraw, &change);
}

void Widget::on_rotateButton_clicked()
{
    sMove move;
    move.dx = ui->doubleSpinBox_2->value() / 180.0 * M_PI;
    move.dy = ui->doubleSpinBox_3->value() / 180.0 * M_PI;
    move.dz = ui->doubleSpinBox_4 ->value()/ 180.0 * M_PI;
    change.move = move;

    Apply(caRotate, &change);
    Apply(caDraw, &change);
}

void Widget::on_setRotateButton_clicked()
{
    sMove move;
    move.dx = ui->doubleSpinBox_2->value() / 180.0 * M_PI;
    move.dy = ui->doubleSpinBox_3->value() / 180.0 * M_PI;
    move.dz = ui->doubleSpinBox_4->value() / 180.0 * M_PI;
    change.move = move;

    Apply(caSetRot, &change);
    Apply(caDraw, &change);
}

void Widget::on_shiftButton_clicked()
{
    sMove move;
    move.dx = ui->doubleSpinBox_5->value();
    move.dy = ui->doubleSpinBox_6->value();
    move.dz = ui->doubleSpinBox_7->value();   
    change.move = move;

    Apply(caShift, &change);
    Apply(caDraw, &change);
}



