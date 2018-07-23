#include <iostream>
#include <GLUT/glut.h>
#include "main.h"
#include <math.h>
#include <fstream>
#include </Library/glui-2.35/src/include/GL/glui.h>

#define ANGLE 0.017453

using namespace std;

#define OK 0

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations" // в оболочку


//~~~~~~~~~MATHEMATIC'S PART~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int right()
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i].x += 5;
    }

    return OK;
}

int left()
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i].x -= 5;
    }

    return OK;
}

int up()
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i].y += 5;
    }

    return OK;
}

int down()
{
    for (int i = 0; i < points.size(); i++) {
        points[i].y -= 5;
    }

    return OK;
}

int pl()
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i].y *= 1.1;
        points[i].x *= 1.1;
    }
    return OK;
}

int mn()
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i].y *= 0.9;
        points[i].x *= 0.9;
    }
    return OK;
}

int rotate_x()
{
    double tmp_y;
    double tmp_z;

    for (int i = 0; i < points.size(); i++) 
    {
        tmp_y = points[i].y;
        tmp_z = points[i].z;
        points[i].x = points[i].x;
        points[i].y = tmp_y * cos(ANGLE) + tmp_z * sin(ANGLE);
        points[i].z = -tmp_y * sin(ANGLE) + tmp_z * cos(ANGLE);
    }

    return 1;
}

int rotate_y()
{
    double tmp_x;
    double tmp_z;

    for (int i = 0; i < points.size(); i++)
    {
        tmp_x = points[i].x;
        tmp_z = points[i].z;
        points[i].x = tmp_x * cos(ANGLE) + tmp_z * sin(ANGLE);
        points[i].y = points[i].y;
        points[i].z = -tmp_x * sin(ANGLE) + tmp_z * cos(ANGLE);
    }

    return 1;
    
}

int rotate_z()
{
    double tmp_x;
    double tmp_y;

    for (int i = 0; i < points.size(); i++)
    {
        tmp_x = points[i].x;
        tmp_y = points[i].y;

        points[i].x = tmp_x * cos(ANGLE) - tmp_y * sin(ANGLE);
        points[i].y = tmp_x * sin(ANGLE) + tmp_y * cos(ANGLE);
        points[i].z = points[i].z; 
    }

    return 1;
}

// Read to file

void parser(ifstream &data) {
    int vertices;
    int lines;

    data >> vertices;
    data >> lines;

    for (int i = 0; i < vertices; i++) { 
        struct point point;
        data >> point.x;
        data >> point.y;
        data >> point.z;
        points.push_back(point);
    }

    for (int i = 0; i < lines; i++) {
        struct connection connection;
        data >> connection.start;
        data >> connection.end;
        connections.push_back(connection);
    }
}

void Keyboard(int key, int x, int y) {
    glClear(GL_COLOR_BUFFER_BIT);
    switch(key)
    {
        case GLUT_KEY_LEFT:
            left();
            break;
        case GLUT_KEY_RIGHT:
            right();
            break;
        case GLUT_KEY_UP:
            up();
            break;
        case GLUT_KEY_DOWN:
            down();
            break;
        case GLUT_KEY_F1:
            mn();
            break;
        case GLUT_KEY_F2:
            pl();
            break;
        case GLUT_KEY_F3:
            rotate_x();
            break;
        case GLUT_KEY_F4:
            rotate_y();
            break;
        case GLUT_KEY_F5:
            rotate_z();
            break;

    }
    glutPostRedisplay();
}

//~~~~~~~~~~GUI PART~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


int my_print(int i){

    glEnable(GL_LINE_STIPPLE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_LINES);
    glColor3b(0, 0, 100);

    glVertex3d(points[connections[i].start].x, points[connections[i].start].y, points[connections[i].start].z);
    glVertex3d(points[connections[i].end].x, points[connections[i].end].y, points[connections[i].end].z);

    glEnd();

    return 0;
}
void figure()
{

    for (int i = 0; i < connections.size(); i++) {
        my_print(i);
    }


}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    figure();
    glFlush();
}

void GLinit(int main_win)
{

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Объектно-ориентрованное программирование");

    glClearColor(255, 255, 255, 1.0);
    glOrtho(-400, 400, -300, 300, -300, 300);

    glutDisplayFunc(display);
    glutSpecialFunc(Keyboard);


}

//~~~~~~~~~~MAIN PART~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char **argv) {

    int main_win;
    ifstream data;
    data.open("cube.txt");
    parser(data);
    glutInit(&argc, argv);
    GLinit(main_win);
    //GLUI *subwin = GLUI_Master.create_glui_subwindow(main_win, GLUI_SUBWINDOW_RIGHT );

    //subwin->set_main_gfx_window( window_id );
    glutMainLoop();

    return OK;
}




#pragma clang diagnostic pop