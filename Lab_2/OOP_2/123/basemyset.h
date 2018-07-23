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

    virtual bool isEmpty() const;
    virtual int getSize() const;
};



#endif // BASEMYSET_H
