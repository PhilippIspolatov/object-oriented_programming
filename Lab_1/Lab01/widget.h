#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

#include "entrypoint.h"



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private slots:
    void on_openButton_clicked();

    void on_scaleButton_clicked();

    void on_rotateButton_clicked();

    void on_setRotateButton_clicked();

    void on_shiftButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::Widget *ui;
    sCanvasContainer *scene;  // render.h
    uChangeData change;

};

#endif // WIDGET_H
