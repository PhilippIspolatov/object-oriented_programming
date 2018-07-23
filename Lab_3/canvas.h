#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
template <typename T>

class Canvas{
private:
    T *ptr;
public:

    Canvas() = default;
    Canvas(T *canvas){
        this->ptr = canvas;
    }
    ~Canvas(){}

//    void setScene(T *scene){
//        this->ptr = scene;
//    }

    T * scene(){
        return this->ptr;
    }

    void drawLine(double xn, double yn, double xk, double yk){
        ptr->addLine(xn, -yn, xk, -yk);
    }

    void sceneClear(){
        ptr->clear();
    }

};

#endif // CANVAS_H
