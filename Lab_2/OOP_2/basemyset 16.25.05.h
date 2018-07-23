#ifndef BASEMYSET_H
#define BASEMYSET_H


class BaseMySet
{
protected:
    int size;
public:
    BaseMySet();
    BaseMySet(int s);
    BaseMySet(BaseMySet &origin);

    bool isEmpty() const;
    int getSize() const;
    virtual void vt();
};



#endif // BASEMYSET_H
