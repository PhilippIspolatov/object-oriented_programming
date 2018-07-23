#include "basemyset.h"

//конструктор по умолчанию
BaseMySet::BaseMySet() : size(0)
{}

//конструктор создания
BaseMySet::BaseMySet(int s) : size(s)
{}

//конструктор копирования
BaseMySet::BaseMySet(BaseMySet &origin) : size(origin.size)
{}


//проверка массива на пустоту
bool BaseMySet::isEmpty() const
{	return (size == 0);	}

//получение размера массива
int BaseMySet::getSize() const
{	return size;	}
