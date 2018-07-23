
#ifndef MYSET_H
#define MYSET_H

#include <iostream>
#include "basemyset.h"
#include <memory>
#include <ctime>
#include "my_exceptions.h"

template<typename T>
class MySet: public BaseMySet
{
protected:
    std::unique_ptr<std::shared_ptr<T>[]> data;

public:
    MySet();
    explicit MySet(const MySet<T> &origin);
    MySet(MySet&& origin);
    MySet(std::initializer_list<T> list);
    ~MySet();


    // Перегруженные операторы
    MySet<T> &operator = (const MySet<T>& right);
    MySet<T> &operator = (MySet<T>&& other);
    const T &operator [](int i) const;
    bool operator == (const MySet<T>& with) const;
    bool operator != (const MySet<T>& with) const;

    // Очистка контейнера
    void clear();

    // Операции обьединения, пересечения, разности
    MySet<T> unite(const MySet<T> &other) const;
    MySet<T> intersect(const MySet<T> &other) const;
    MySet<T> subtract(const MySet<T> &other) const;

    template<typename U>
    friend MySet<U> operator + (const MySet<U> & left, const MySet<U> & right);

    template<typename U>
    friend MySet<U> operator & (const MySet<U> & left, const MySet<U> & right);

    template<typename U>
    friend MySet<U> operator - (const MySet<U> & left, const MySet<U> & right);

    MySet<T> &operator += (const MySet<T> & right);
    MySet<T> &operator &= (const MySet<T> & right);
    MySet<T> &operator -= (const MySet<T> & right);

    /// Методы получения и добавления значений
    bool contains(const T &val) const;
    bool contains(const MySet<T> &right) const;
    bool operator < (const MySet<T> & right) const;

    bool add(const T &val);
    bool remove(const T &val);

    // Итератор и методы множества его возвращающие
    template <typename U>
    class MySetIterator
    {
    private:
        //std::weak_ptr<MySet<U>> set;
       	std::weak_ptr<std::shared_ptr<U>> set;
        int index;

        int getIndex() const;
        MySet<U> *getSet();

    public:

        MySetIterator(MySet<U> *s)
        {
            index = 0;
            set = s;
        }
        MySetIterator(const MySet<U> &s)
        {
            index = s.getSize();
            set = s;
        }

        bool check()
        {
            if (index != set->getSize())
            {
                std::weak_ptr<U> cur = set->data[index];
                if (cur.lock()) return true;
            }
            return false;
        }

        MySetIterator<U> operator++ (int)
        {
            MySetIterator<U> temp = *this;
            ++*this;
            return temp;
        }
        MySetIterator<U> operator-- (int)
        {
            MySetIterator<U> temp = *this;
            --*this;
            return temp;
        }
        MySetIterator<U> &operator++ ()
        {
        	if (!check())
        	{
	            index++;
	            return *this;
        	}
        	else
        	{

        		cEIteratorException ex("myset.hpp", "MySetIterator", __LINE__, "Testing");
        		throw ex;
        	}
        }
        MySetIterator<U> &operator-- ()
        {
            index--;
            return *this;
        }

        bool operator!= (const MySetIterator<U>& it)
        {
            if (set != it.getSet() && index != it.getIndex()) return true;
            else return false;
        }
        bool operator== (const MySetIterator<U>& it)
        {
            if (set == it.getSet() || index == it.getIndex()) return true;
            else return false;
        }

        const U& operator* ()
        {
            std::weak_ptr<U> cur = set->data[index];
            if (cur.lock()) { return *(set->data[index]); }
            else
            {

                cEIteratorException ex("myset.hpp", "MySetIterator", __LINE__, "Testing");
                throw ex;
            }
        }
        const shared_ptr<U> operator-> ()
        {
            std::weak_ptr<U> cur = set->data[index];
            if (cur.lock()) { return set->data[index]; }
            else
            {

                cEIteratorException ex("myset.hpp", "MySetIterator", __LINE__,"Testing");
                throw ex;
            }
        }
    };


    /// Вывод в стандартый поток
    template<typename S>
    friend std::ostream& operator << (std::ostream& stream, const MySet<S> &set);

    MySetIterator<T> createIterator() { return MySetIterator<T>(this); }
    bool remove(MySetIterator<T> pos);
};

#include "myset.hpp"

#endif // MYSET_H

