#ifndef COMMAND_H
#define COMMAND_H

#include "base_data.h"

template <class T>

class Command
{
protected:
   T *obj;
public:
   virtual ~Command() {}
   virtual void Execute() = 0;

//   void setObj(T *obj){
//       this->obj = obj;
//   }
};

class ModelCommand{
private:
    Base_Model *mdl;
public:
    virtual ~ModelCommand() {}
    virtual void Execute() = 0;
}

#endif // COMMAND_H
