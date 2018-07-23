#ifndef POINT_H
#define POINT_H

class Point {
private:
    double x;
    double y;
    double z;
public:
    Point(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double get_x(){
        return this->x;
    }

    double get_y(){
        return this->y;
    }

    double get_z(){
        return this->z;
    }

    void set_x(double value){
        this->x = value;
    }

    void set_y(double value){
        this->y = value;
    }

    void set_z(double value){
        this->z = value;
    }
};

#endif // POINT_H
