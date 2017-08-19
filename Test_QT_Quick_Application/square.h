#ifndef SQUARE_H
#define SQUARE_H
#include <QList>
#include <iostream>

class Square
{
public:
    Square(int number, int x, int y);
    Square(const Square &);
    Square &operator=(const Square &);
    virtual ~Square();
    void     setNumber(int const type);
    int      getNumber() const;
    void     setX(int const x);
    int      getX() const;
    void     setY(int const y);
    int      getY() const;
private:
    Square   ();
    int      _number;
    int      _x;
    int      _y;
};

struct Data
{
    QList<Square*> squares;
};


#endif // SQUARE_H
