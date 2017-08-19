#include "logic.h"

Logic::Logic(QObject *parent)
    : QAbstractListModel(parent),_data(new Data())
{
    //std::cout << "Logic constructor called" << std::endl;
    this->randomInitialise();
}

Logic::Logic(const Logic &rhs)
{
    this->_empty.x = rhs.getEmptyX();
    this->_empty.y = rhs.getEmptyY();
    this->_data->squares = rhs._data->squares;

}

Logic &Logic::operator=(const Logic &rhs)
{
    if (this == &rhs)
        return *this;

    this->_empty.x = rhs.getEmptyX();
    this->_empty.y = rhs.getEmptyY();
    this->deleteSquares();
    this->clear();
    this->_data->squares = rhs._data->squares;

    return *this;
}

Logic:: ~Logic()
{
    //std::cout <<"Logic dectructor called" << std::endl;
    this->deleteSquares();
    this->clear();
}

void       Logic::clear()
{
    beginResetModel();
    this->_data->squares.clear();
    endResetModel();
}

void       Logic::deleteSquares()
{
    for (int i(0); i < this->_data->squares.size(); ++i) {
        delete(this->_data->squares[i]);
        this->_data->squares[i] = NULL;
    }
}

void       Logic::refresh()
{
    this->mix();
}

void       Logic::initialise()
{
    int     i;

    i = 0;
    try{
        while (i++ < 15){
            this->_data->squares.append(new Square(i, (i - 1) % 4 , (i - 1) / 4));
        }
    }
    catch(std::bad_alloc&){
        std::cerr << "Bad allocation" << std::endl;
        exit(0);
    }
}

void       Logic::mix()
{
    int     i;
    int     fromX;
    int     fromY;
    int     random;
    int     toX;
    int     toY;

    i = 0;
    srand (time(NULL));
    while (i++ < 150){
        this->findEmpty();
        toX = this->getEmptyX();
        toY = this->getEmptyY();

        random = rand() % 4;
        if (random % 2){
            fromX = toX + random - 2;
            fromY = toY;
        }else{
            fromX = toX;
            if (random / 2)
                fromY = toY + random / 2;
            else
                fromY = toY - 1;
        }
        this->move(fromX, fromY, toX, toY);
    }
}


void       Logic::randomInitialise()
{
    this->initialise();
    this->mix();
}

int        Logic::rowCount(const QModelIndex &) const
{
    return this->_data->squares.size();
}


QVariant  Logic::data(const QModelIndex & modelIndex, int role) const
{
    if (!modelIndex.isValid()) {
        return QVariant();
     }

    int index = static_cast<int>(modelIndex.row());

    if (index >= this->_data->squares.size() || index < 0) {
       return QVariant();
    }

    Square & square = *(this->_data->squares[index]);

     switch (role) {
       case Roles::Number:    return square.getNumber();
       case Roles::PositionX: return square.getX();
       case Roles::PositionY: return square.getY();
     }
     return QVariant();
}

QHash<int, QByteArray>  Logic::roleNames() const
{
    QHash<int, QByteArray> names;
    names.insert(Roles::Number    , "number");
    names.insert(Roles::PositionX , "positionX");
    names.insert(Roles::PositionY , "positionY");
    return names;
}

int       Logic::findByPosition(int x, int y)
{
    for (int i(0); i < this->_data->squares.size(); ++i) {
        if (this->_data->squares[i]->getX() != x ||
            this->_data->squares[i]->getY() != y) {
                continue;
        }
        return i;
    }
    return -1;
}

bool        Logic::move(int fromX, int fromY, int toX, int toY)
{
    int     indexTo;
    int     indexFrom;

    indexTo = this->findByPosition(toX, toY);
    if (indexTo >=0)
        return false;
    indexFrom = this->findByPosition(fromX, fromY);
    if (indexFrom < 0)
        return false;
    if (toX < 0 || toX >= BOARD_SIZE || toY < 0 || toY >= BOARD_SIZE)
        return false;
    if(!(this->checkMove(fromX, fromY, toX, toY)))
        return false;

    this->_data->squares[indexFrom]->setX(toX);
    this->_data->squares[indexFrom]->setY(toY);
    QModelIndex topLeft = createIndex(indexFrom, 0);
    QModelIndex bottomRight = createIndex(indexFrom, 0);
    emit dataChanged(topLeft, bottomRight);

    return true;
}

bool        Logic::checkMove(int fromX, int fromY, int toX, int toY)
{
    int     dx;
    int     dy;

    dx = toX - fromX;
    dy = toY - fromY;

    if (dx && dy)
        return false;
    else if(abs(dx) > 1)
        return false;
    else if(abs(dy) > 1)
        return false;

    return true;
}

bool        Logic::checkWin()
{
    int     i;
    int     index;

    i = 0;
    while(i++ < 15){
        index = this->findByPosition((i - 1) % 4, (i - 1) / 4);
        if (index < 0 && i < 16)
            return false;
        if (this->_data->squares[index]->getNumber() != i)
            return false;
    }

    return true;
}

void         Logic::findEmpty()
{
    int     i;
    int     index;

    i = 0;
    while(i++ < 16){
        index = this->findByPosition((i - 1) % 4, (i - 1) / 4);
        if (index < 0){
            this->_empty.x = (i - 1) % 4;
            this->_empty.y = (i - 1) / 4;
            return;
        }
    }
}

int         Logic::getEmptyX() const
{
    return this->_empty.x;
}

int         Logic::getEmptyY() const
{
    return this->_empty.y;
}
