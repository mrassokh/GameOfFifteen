#ifndef LOGIC_H
#define LOGIC_H

#include <QAbstractListModel>
#include <QObject>
#include <QQuickItem>
#include <QList>
#include <memory>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include "square.h"

struct  Empty
{
    int     x;
    int     y;
};

class Logic: public QAbstractListModel
{
    Q_OBJECT
public:

    enum GlobalConstants {
        BOARD_SIZE = 4
    };

    enum Roles {
        Number = Qt::UserRole,
        PositionX,
        PositionY,
     };

    explicit Logic(QObject *parent = 0);
    Logic(const Logic &);
    Logic &operator=(const Logic &);
    virtual ~Logic();
    Q_INVOKABLE bool        move(int fromX, int fromY, int toX, int toY);
    Q_INVOKABLE void        refresh();
    Q_INVOKABLE bool        checkWin();
    Q_INVOKABLE void        findEmpty();
    Q_INVOKABLE int         getEmptyX() const;
    Q_INVOKABLE int         getEmptyY() const;

private:

    int                     rowCount(const QModelIndex & parent) const override;
    QVariant                data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray>  roleNames() const override;
    void                    randomInitialise();
    void                    initialise();
    void                    mix();
    bool                    checkMove(int fromX, int fromY, int toX, int toY);
    int                     findByPosition(int x, int y);
    void                    clear();
    void                    deleteSquares();

    Empty                   _empty;
    std::unique_ptr<Data>   _data;
 };

#endif // LOGIC_H
