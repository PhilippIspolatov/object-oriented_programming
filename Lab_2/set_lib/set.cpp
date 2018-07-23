#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <memory>

#define DEBUG 1

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// errors.h

class erBaseException : public std::exception
{
public:
    virtual const char* what()
    {
        return "my base exception";
    }
};
class erIndexException : public erBaseException
{
public:
    const char* what()
    {
        return "Array index is out of range!";
    }
};

class erMemoryException : public erBaseException
{
public:
    const char* what()
    {
        return "Couldn't allocate memory for array data!";
    }
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//base.h
class set_base
{
protected:
	int size;

public:
	// Конструктор 
	set_base();
	// Конструктор создания
	set_base(int s);
	// Конструктор копирования
	set_base(set_base &origin);
	// Получение размера
	int getSize() const;
	// Проверка на пустоту
	bool Empty() const;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//base.hpp
//#include "base.h"

set_base::set_base(){

}

set_base::set_base(int s){
	size = s;
}

set_base::set_base(set_base &origin){
	size = origin.size;
}

int set_base::getSize() const{
	return size;
}

bool set_base::Empty() const{
	return (size == 0);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//set.h


template <typename type>
class set : public set_base
{
protected:
	//type *data;
	//std::unique_ptr<type[]> data;
    std::unique_ptr<std::shared_ptr<type>[]> data;

public:
	set();
	set(int n);
	set(const set<type> &origin);
	set(set<type>&& origin);
	set(std::initializer_list<type> list);

	~set();

	void clear();

	bool is(const type &val) const;
	set<type>& operator<< (const type &val);
	void Insert(const type &el);
	void Del(const type &el);

	set<type> Unite(const set<type> &other) const;
    set<type> Intersect(const set<type> &other) const;
    set<type> Diff(const set<type> &other) const;


    set<type> &operator = (set<type>&& origin);
    set<type> &operator = (const set<type>& origin);
    const type &operator [](int i) const;
    bool operator == (const set<type>& with) const;


    template<typename T>
    friend set<T> operator + (const set<T> & left, const set<T> & right);

    template<typename T>
    friend set<T> operator & (const set<T> & left, const set<T> & right);

    template<typename T>
    friend set<T> operator - (const set<T> & left, const set<T> & right);

	
};

template <typename type>
set<type>::set(){
	size = 0;
	data = nullptr;
}

template <typename type>
set<type>::set(int n){
	if (n < 0)
	{
		//cESizeException ex;
		//throw ex;
	}
	size = n;
	//auto data = std::make_shared<type[]>(size);
	//data = std::make_unique<type[]>(size);
    auto data = std::unique_ptr<std::shared_ptr<type>[]>(new std::shared_ptr<type>[this->size]);
	//data = new type [n];

	if (!data)
	{
		erMemoryException ex;
		throw ex;
	}
} 

template<typename type>
set<type>::set(set<type>&& origin)
{
    if (DEBUG)
        std::cout << "In set(set&&). Moving resource." << std::endl;

    size = origin.size;
    data = std::move(origin.data);

    origin.size = 0;
    origin.data = nullptr;

}



template <typename type>
set<type>::set(const set<type> &origin)
{
	size = origin.size;
    auto data = std::unique_ptr<std::shared_ptr<type>[]>(new std::shared_ptr<type>[this->size]);

	if (!data)
	{
		erMemoryException ex;
		throw ex;
	}

	for (auto i = 0; i < size; i++)
	{
        this->data[i] = std::shared_ptr<type>(new type);
		*(this->data[i]) = origin[i];
	}
}

template<typename type>
set<type>::set(std::initializer_list<type> list)
{
    auto it = list.begin();
    while (it != list.end())
    {
        Insert(*it);
        ++it;
    }
}


template <typename type>
set<type>::~set()
{
	//data.reset;
}


template<typename type>
void set<type>::clear()
{
    if (data)
    {
        data.reset();
        size = 0;
    }
}


// добавить элемент
template<typename type>
set<type>& set<type>::operator<< (const type &val)
{
    Insert(val);
    return *this;
}

// содержится ли элемент val во множестве?
template<typename type>
bool set<type>::is (const type &val) const
{
    for(int i = 0; i < size; i++)
        if(val == *data.get()[i])
            return true;


    return false;
}


template<typename type>
void set<type>::Insert(const type& val)
{
    if(is(val))
        return;

    size += 1;
    auto Ndata = std::unique_ptr<std::shared_ptr<type>[]>(new std::shared_ptr<type>[this->size]);
    if (!Ndata)
    {
        erMemoryException ex;
        throw ex;
    }

    for (auto i = 0; i < size; i++)
        Ndata[i] = std::shared_ptr<type>(new type);

    
    int index = size - 1;
    for (int i = 0; i < size - 1; i++)
    {
        if (val < *data.get()[i])
        {
            index = i;
            break;
        }
    }

    
    for (int i = 0; i < index; i++) 
    	*Ndata[i] = *data[i];

    *Ndata[index] = val;

    for (int i = index + 1; i < size; i++) 
    	*Ndata[i] = *data[i-1];

    data = std::move(Ndata);
}

template<typename type>
void set<type>::Del(const type &val)
{
    if(!is(val))
        return;

    size -= 1;
    auto Ndata = std::unique_ptr<std::shared_ptr<type>[]>(new std::shared_ptr<type>[this->size]);

    for (auto i = 0; i < size; i++)
        Ndata[i] = std::shared_ptr<type>(new type);

    int index = 0;
    for(int i = 0; i < size + 1; i++)
    {
        if (val == *data[i])
        {
            index = i;
            break;
        }
    }

    for (int i = 0; i < index; i++) 
    	*Ndata[i] = *data[i];
    for (int i = index; i < size; i++) 
    	*Ndata[i] = *data[i + 1];

    data = std::move(Ndata);
}

template<typename type>
set<type> set<type>::Unite(const set<type>& other) const
{
    set<type> res;
    for (int i = 0; i < size; i++)
        res.Insert(*data[i]);
    for (int i = 0; i < other.getSize(); i++)
        res.Insert(other[i]);

    return res;
}

template<typename type>
set<type> set<type>::Intersect(const set<type>& other) const
{
    set<type> res;
    for (int i = 0; i < this->size; i++)
        for (int j = 0; j < other.size; j++)
            if (data[i] == other.data[j])
                res.Insert(*other.data[j]);

    return res;
}

template<typename type>
set<type> set<type>::Diff(const set<type>& other) const
{
    set<type> res(*this);
    for (int i = 0; i < other.getSize(); i++)
        res.Del(other[i]);

    return res;
}




template<typename type>
const type &set<type>::operator [](int i) const
{
    if (i < 0 || i >= size)
    {
        erIndexException ex;
        throw ex;
    }
    return *data[i];
}

template<typename type>
set<type> &set<type>::operator = (const set<type>& origin)
{
    if (DEBUG)
        std::cout << "In operator=(const set&). Copying resource." << std::endl;

    if (this != &origin)
    {

        // size = right.size;
        // data = std::move(right.elem);
        data = std::unique_ptr<std::shared_ptr<type>[]>(new std::shared_ptr<type>[this->size]);
        if (!data)
        {
            erMemoryException ex;
            throw ex;
        }

        for (int i = 0; i < size; i++)
        {
            // *data[i] = right.data[i];
            this->data[i] = std::shared_ptr<type>(new type);
            *data[i] = origin[i];
        }

        // right.data = nullptr;
        // right.size = 0;
    }
    return *this;
}

template<typename type>
set<type>& set<type>::operator = (set<type>&& origin)
{
    //this->size = origin.size();
    size = origin.size;
    data = std::move(origin.data);
    origin.data = nullptr;
    origin.size = 0;

    return *this;
}

template<typename type>
bool set<type>::operator == (const set<type>& with) const
{
    if (size != with.size)
        return false;

    for (int i = 0; i < size; i++)
    {
        if (data[i] != with[i])
            return false;
    }

    return true;
}



template<typename type>
set<type> operator + (const set<type> & left, const set<type> & right)
{
    const set<type> res = left.Unite(right);
    return res;
}

template<typename type>
set<type> operator & (const set<type> & left, const set<type> & right)
{
    const set<type> res = left.Intersect(right);
    return res;
}

template<typename type>
set<type> operator - (const set<type> & left, const set<type> & right)
{
    const set<type> res = left.Diff(right);
    return res;
}



int main(void)
{
	set<int> ptr1{1, 2, 3, 4, 5, 6, 7, 8};
	set<int> ptr2{7, 8, 9, 10, 11};
	set<int> res1(ptr1);
    set<int> res2;
    set<int> res3;
	
    //ptr.Del(5);

    //res1(ptr1);
    //ptr2 = move(ptr);

    int size1 = ptr2.getSize();
    std::cout << size1 << std::endl;

    //res1 = ptr1 + ptr2; // не перегружается


	int size = res1.getSize();
    std::cout << size << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << res1[i] << std::endl;
	}

	//res = ptr + ptr2;

	// size = res.getSize();
	// for (int i = 0; i < size; i++) {
	// 	std::cout << res[i] << std::endl;
	// }

	return 0;
}

// Перемещение / Итератор  / 


