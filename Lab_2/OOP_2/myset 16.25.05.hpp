#ifndef MYSET_HPP
#define MYSET_HPP

#include "myset.h"
#include "my_exceptions.h"
#include <iostream>
#include <memory>
#include <ctime>

#define DEBUG 0

using namespace std;

//конструктор по умолчанию
template<typename T>
MySet<T>::MySet() : BaseMySet(0)
{
    data = std::make_unique<std::shared_ptr<T> []>(0);
}

//конструктор копирования
template<typename T>
MySet<T>::MySet(const MySet &origin)
{
    if (DEBUG)
        std::cout << "In MySet(const MySet&). Copying resource." << std::endl;

    size = origin.size;
    data = std::make_unique<std::shared_ptr<T> []>(size);
    for (int i = 0; i < size; i++)
        data[i] = std::make_shared<T>(*(origin.data[i]));
}

template<typename T>
MySet<T>::MySet(MySet&& origin)
{
    if (DEBUG)
        std::cout << "In MySet(MySet&&). Moving resource." << std::endl;

    size = origin.size;
    data = std::move(origin.data);

    origin.size = 0;
}

template<typename T>
MySet<T>& MySet<T>::operator = (MySet<T>&& other)
{
    if (DEBUG)
        std::cout << "In operator=(MySet<T>&&). Moving resource." << std::endl;

    if (this != &other)
    {
       size = other.size;
       data = std::move(other.data);

       other.size = 0;
    }
    return *this;
}

template<typename T>
MySet<T>::MySet(std::initializer_list<T> list)
{
    auto it = list.begin();
    while (it != list.end())
    {
        add(*it);
        ++it;
    }
}

//деструктор
template<typename T>
MySet<T>::~MySet()
{
    data.reset();
}


// Очищение контейнера
template<typename T>
void MySet<T>::clear()
{
    if (data)
    {
        data.reset();
        size = 0;
    }
}


/// Методы получения и добавления значений

// содержится ли элемент val во множестве?
template<typename T>
bool MySet<T>::contains (const T &val) const
{
    for(int i = 0; i < size; i++)
    {
        if(val == *(data[i]))
            return true;
    }

    return false;
}

template<typename T>
bool MySet<T>::contains (const MySet<T> &right) const
{
    for(int i = 0; i < right.size; i++)
        if(!contains(*(right.data[i])))
            return false;

    return true;
}


template<typename T>
bool MySet<T>::add(const T& val)
{
    if(contains(val))
        return false;

    size += 1;
    auto Ndata = std::make_unique<std::shared_ptr<T> []>(size);
    for(int i=0; i < size; i++)
        Ndata[i] = std::make_shared<T>(0);

    if (!Ndata)
    {
        time_t t;
        t = time(NULL);
        cEMemoryException ex("myset.hpp","MySet",__LINE__, "Testing");
        throw ex;
    }

    // Находим индекс в который поставим val
    int index = size - 1;
    for (int i = 0; i < size - 1; i++)
    {
        if (val < *(data[i]))
        {
            index = i;
            break;
        }
    }

    // Копируем элементы в новый массив
    for (int i=0; i < index; i++) Ndata[i] = std::make_shared<T>(*(data[i]));
    Ndata[index] = std::make_shared<T>(val);
    for (int i=index + 1; i<size; i++) Ndata[i] = std::make_shared<T>(*(data[i - 1]));

    data = std::move(Ndata);

    return true;
}

// удалить элемент
template<typename T>
bool MySet<T>::remove(const T &val)
{
    if(!contains(val))
        return false;

    size -= 1;
    auto Ndata = std::make_unique<std::shared_ptr<T> []>(size);
    for(int i=0; i < size; i++)
        Ndata[i] = std::make_shared<T>(0);

    // Находим индекс элемента который удаляем
    int index = 0;
    for(int i = 0; i < size + 1; i++)
    {
        if (val == *(data[i]))
        {
            index = i;
            break;
        }
    }

    //копируем элементы в новый массив
    for (int i=0; i < index; i++) Ndata[i] = std::make_shared<T>(*(data[i]));
    for (int i=index; i < size; i++) Ndata[i] = std::make_shared<T>(*(data[i + 1]));

    data = std::move(Ndata);

    return true;
}


template<typename T>
bool MySet<T>::remove(MySetIterator<T> pos)
{
    T val = *pos;
    if(contains(val))
    {
        size -= 1;
        auto Ndata = std::make_unique<std::shared_ptr<T> []>(size);
        for(int i=0; i < size; i++)
            Ndata[i] = std::make_shared<T>(0);

        // Находим индекс элемента который удаляем
        int index = 0;
        for(int i = 0; i < size + 1; i++)
        {
            if (*pos == *(data[i]))
            {
                index = i;
                break;
            }
        }

        //копируем элементы в новый массив
        for (int i=0; i < index; i++) Ndata[i] = std::make_shared<T>(*(data[i]));
        for (int i=index; i < size; i++) Ndata[i] = std::make_shared<T>(*(data[i + 1]));

        data = std::move(Ndata);

        return true;
    }

    return false;
}



/// Операции обьединения, пересечения, разности

template<typename T>
MySet<T> MySet<T>::unite(const MySet<T>& other) const
{
    MySet<T> res;
    for (int i = 0; i < size; i++)
        res.add(*(data[i]));
    for (int i = 0; i < other.getSize(); i++)
        res.add(*(other.data[i]));

    return res;
}

template<typename T>
MySet<T> MySet<T>::intersect(const MySet<T>& other) const
{
    MySet<T> res;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (*(data[i]) == *(other.data[j]))
                res.add(*(data[i]));

    return res;
}

template<typename T>
MySet<T> MySet<T>::subtract(const MySet<T>& other) const
{
    MySet<T> res(*this);
    for (int i = 0; i < other.getSize(); i++)
        res.remove(*(other.data[i]));

    return res;
}

/// Перегруженные операторы
template<typename T>
const T &MySet<T>::operator [](int i) const
{
    if (i<0 || i>=size)
    {
        //time_t t;
        //t = time(NULL);
        cEIndexException ex("myset.hpp", "MySet", __LINE__, "Testing");
        throw ex;
    }
    return *(data[i]);
}

template<typename T>
MySet<T> &MySet<T>::operator = (const MySet<T>& right)
{
    if (DEBUG)
        std::cout << "In operator=(const MySet&). Copying resource." << std::endl;

    if (this != &right)
    {
        size = right.size;
        data = std::make_unique<std::shared_ptr<T> []>(size);
        if (!data)
        {
            time_t t;
            t = time(NULL);
            cEMemoryException ex("myset.hpp","MySet",__LINE__, "Testing");
            throw ex;
        }

        for (int i = 0; i < size; i++)
            data[i] = std::make_shared<T>(*(right.data[i]));
    }
    return *this;
}

template<typename T>
bool MySet<T>::operator == (const MySet<T>& with) const
{
    if (size != with.size)
        return false;

    for (int i=0; i<size; i++)
    {
        if (*(data[i]) != *(with.data[i]))
            return false;
    }

    return true;
}

template<typename T>
bool MySet<T>::operator != (const MySet<T>& with) const
{
    if (*this == with) return false;
    else return true;
}


template<typename T>
MySet<T> operator + (const MySet<T> & left, const MySet<T> & right)
{
    MySet<T> res(left.unite(right));
    return res;
}

template<typename T>
MySet<T> operator & (const MySet<T> & left, const MySet<T> & right)
{
    MySet<T> res(left.intersect(right));
    return res;
}

template<typename T>
MySet<T> operator - (const MySet<T> & left, const MySet<T> & right)
{
    MySet<T> res(left.subtract(right));
    return res;
}

template<typename T>
MySet<T> &MySet<T>::operator += (const MySet<T> &right)
{
    MySet<T> res(unite(right));
    size = res.size;
    data = std::move(res.data);
    return *this;
}

template<typename T>
MySet<T> &MySet<T>::operator &= (const MySet<T> &right)
{
    MySet<T> res(intersect(right));
    size = res.size;
    data = std::move(res.data);
    return *this;
}

template<typename T>
MySet<T> &MySet<T>::operator -= (const MySet<T> &right)
{
    MySet<T> res(subtract(right));
    size = res.size;
    data = std::move(res.data);
    return *this;
}

template<typename T>
std::ostream &operator << (std::ostream &stream, const MySet<T> &set)
{
    if (set.isEmpty())
        stream << "Set is empty!" << endl;
    else
    {
        int size = set.getSize();
        stream << "MySet(";
        for (int i = 0; i < size; i++)
        {
            if (i == size - 1)
            {
                stream << " " << set[i] << " )" << endl;
                break;
            }
            stream << " " << set[i] << ",";
        }
    }

   return stream;
}


#endif // MYSET_HPP
