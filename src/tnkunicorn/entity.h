#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>


#include <QJsonObject>
#include <QMetaProperty>
#include <QDateTime>

#include "tnkcommon.h"


class QSqlRecord;

namespace unicorn {

class  Entity : public QObject
{
    Q_OBJECT
public:
    explicit Entity(QObject* parent = nullptr);
    Entity( const Entity& other);

    QJsonObject toJsonObject();

    PROPERTY( QVariant, id, QVariant())
    PROPERTY( QDateTime, created, QDateTime::currentDateTime())
    PROPERTY( QDateTime, updated, QDateTime::currentDateTime())
};

}

#endif // ENTITY_H
