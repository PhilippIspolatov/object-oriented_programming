#ifndef RECEIVER_H
#define RECEIVER_H

#include <vector>
#include "command.h"
#include "transf_command.h"
#include "file.h"

//using namespace std;

class MyViewer{
private:
   CarcaseModel mdl;

   Command<File>* command;
   //Command<Model>* m_command;
   ModelCommand *m_command;


public:
   MyViewer() {
       mdl = Model();
   }

   void Scale(double kx, double ky, double kz){
      m_command = new ScaleCommand(&mdl, kx, ky, kz);
      m_command->Execute();
   }

   void Shift(double dx, double dy, double dz){
      m_command = new ShiftCommand(&mdl, dx, dy, dz);
      m_command->Execute();
   }

   void Rotate(double ax, double ay, double az){
      m_command = new RotateCommand(&mdl,ax, ay, az);
      m_command->Execute();
   }

   void LoadModel(char *filename){
      command = new LoadModelCommand(&mdl, filename);
      std::cout << "command created" << std::endl;
      command->Execute();
   }

   void DrawModel(Canvas<QGraphicsScene> *canvas){
      m_command = new DrawCommand(&mdl, canvas);
      std::cout << mdl.getPoints().size() << std::endl;
      m_command->Execute();
   }
};


#endif // RECEIVER_H
