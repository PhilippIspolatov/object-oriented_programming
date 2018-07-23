#ifndef TRANSF_COMMAND_H
#define TRANSF_COMMAND_H

#include "command.h"
#include "data.h"
#include <stdio.h>
#include "file.h"
#include "canvas.h"
#include "drawer.h"


class ScaleCommand : public Command<Model>
{
private:
   double kx, ky, kz;

public:
   ScaleCommand(Model *mdl, double kx, double ky, double kz){
       this->kx = kx;
       this->ky = ky;
       this->kz = kz;
       obj = mdl;

   }

   void Execute()
   {
      obj->scale(kx, ky, kz);
   }

};

class ShiftCommand : public Command<Model>
{
private:
   double dx, dy, dz;

public:
   ShiftCommand(Model *mdl, double dx, double dy, double dz){
       this->dx = dx;
       this->dy = dy;
       this->dz = dz;
       obj = mdl;
   }

   void Execute()
   {
      obj->shift(dx, dy, dz);
   }

};

class RotateCommand : public Command<Model>
{
private:
   double ax, ay, az;

public:
   RotateCommand(Model *mdl, double ax, double ay, double az){
       this->ax = ax;
       this->ay = ay;
       this->az = az;
       obj = mdl;
   }

   void Execute()
   {
      obj->rotate(ax, ay, az);
   }

};

class LoadModelCommand : public Command<File>
{
private:
    CarcaseModel *mdl;

public:
    LoadModelCommand(CarcaseModel *mdl, char *filename){
        this->mdl = mdl;
        obj = new File(filename);
   }

   void Execute()й
   {
      obj->parse(*mdl);
   }

};

class DrawCommand : public Command<Model>
{
private:
    Canvas<QGraphicsScene> *canvas;

public:
    DrawCommand(Model *mdl, Canvas<QGraphicsScene> *ptr){
        this->canvas = ptr;
        obj = mdl;
   }

   void Execute()
   {
      obj->draw(canvas);
   }

};


#endif // TRANSF_COMMAND_H
