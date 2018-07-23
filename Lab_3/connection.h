#ifndef CONNECTION_H
#define CONNECTION_H

class Connection {
private:
    int begin;
    int end;
public:
    Connection(int bg, int end)
    {
        this->begin = bg;
        this->end = end;
    }

    int get_begin(){
        return this->begin;
    }

    int get_end(){
        return this->end;
    }
};

#endif // CONNECTION_H
