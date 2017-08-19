#include "square.h"

Square::Square(int number, int x, int y)
{
    this->setNumber(number);
    this->setX(x);
    this->setY(y);

   /* std::cout << "Square constructor called" << std::endl;
    std::cout << "Number is " << this->getNumber() << std::endl;
    std::cout << " X is " << this->getX() << std::endl;
    std::cout << " Y is " << this->getY() << std::endl;
    std::cout << "_________"<< std::endl;*/
}

Square::Square(const Square & rhs)
{
     this->setNumber(rhs.getNumber());
     this->setX(rhs.getX());
     this->setY(rhs.getY());
}

Square &Square::operator=(const Square & rhs)
{
    this->setNumber(rhs.getNumber());
    this->setX(rhs.getX());
    this->setY(rhs.getY());
    return *this;
}

Square:: ~Square()
{
    //std::cout <<"Square dectructor called" << std::endl;
}

void    Square::setNumber(const int number)
{
    if (number >0 && number < 16)
        this->_number = number;
    else
        this->_number = -1;
}

int     Square::getNumber() const
{
    return this->_number;
}


void    Square::setX(const int x)
{
    if (x >=0 && x < 4)
        this->_x = x;
    else
        this->_x = -1;
}

int     Square::getX() const
{
    return this->_x;
}

void    Square::setY(const int y)
{
    if (y >=0 && y < 4)
        this->_y = y;
    else
        this->_y = -1;
}

int     Square::getY() const
{
    return this->_y;
}
