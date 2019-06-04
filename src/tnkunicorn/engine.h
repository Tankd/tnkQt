#ifndef ENGINE_H
#define ENGINE_H


#include <QObject>
#include <QDebug>
#include <QMetaProperty>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>


#include "entity.h"

namespace unicorn {


class Error{
public:
    typedef enum Type{
        NONE,
        ERR_NOT_CONNECTED,
        ERR_SQL
    }Code;

    Type type = NONE;
    QString text;
    QString sqlText;
};

class  Engine : public QObject
{
    Q_OBJECT
public:    

    explicit Engine( QObject *parent = nullptr);


    void createTable(QMetaObject meta);
    void dropTable(const QString& tableName);

    void create(unicorn::Entity *entity);
    void create(QList<Entity *> *entities);

    void update(unicorn::Entity *entity);
    void update(QList<Entity *> *entities);



    template< class T = unicorn::Entity>
    T* get( QVariant id)
    {
        if( isConnected() == false)
        {
            setLastError( Error::ERR_NOT_CONNECTED, "Database not connected");
            return nullptr;
        }

        const QString tableName = getTableName(T::staticMetaObject.className());

        QSqlQuery q( _db);
        q.prepare( QString("SELECT * FROM %1 WHERE id = :id").arg( tableName));
        q.bindValue(":id", id);
        q.exec();

        if( findSqlError("Engine::get", q.lastError()))
            return nullptr;

        T* entity = nullptr;

        if( q.next())
        {
            entity = new T();

            for( int i=1; i<entity->metaObject()->propertyCount(); i++)
            {
                QMetaProperty prop = entity->metaObject()->property(i);
                if( QString(prop.typeName()).right(1) == "*")
                {

                    QVariant var = prop.read(entity);
                    auto sub = var.value<unicorn::Entity*>();
                    if(sub)
                        this->getInstancied( sub, q.record().value( prop.name()).toInt());
                }
                else
                    prop.write( entity, q.record().value( prop.name()));
            }
        }

        return entity;
    }

    template <class T = unicorn::Entity>
    QList<T*> getAll( const QString& condition)
    {

        QList<T*> results;

        if( isConnected() == false)
        {
            setLastError( Error::ERR_NOT_CONNECTED, "Database not connected");
            return results;
        }

        const QString tableName = getTableName(T::staticMetaObject.className());


        QSqlQuery q( _db);
        QString str = QString("SELECT * FROM %1 WHERE %2")
                   .arg( tableName)
                   .arg(condition);

        q.exec(str);

        if( findSqlError("Engine::get", q.lastError()))
            return results;


        //qDebug() << q.lastQuery() << q.boundValues();
        if( q.next())
        {
            T* entity = new T();
            for( int i=1; i<T::staticMetaObject.propertyCount(); i++)
            {
                auto prop = T::staticMetaObject.property(i);
                if( QString(prop.typeName()).right(1) == "*")
                {
                    QVariant var = prop.read(entity);
                    auto sub = var.value<unicorn::Entity*>();
                    if(sub)
                    {
                        this->getInstancied( sub, q.record().value( prop.name()).toInt());
                    }
                }
                else
                    prop.write( entity, q.record().value( prop.name()));
            }
            results << entity;
        }

        return results;
    }

    void remove(unicorn::Entity* entity);
    void remove(QList<unicorn::Entity*> *entities);

    template <class T = unicorn::Entity>
    void removeAll(const QString& condition)
    {
        if( isConnected() == false)
        {
            setLastError( Error::ERR_NOT_CONNECTED, "Database not connected");
            return;
        }

        const QString tableName = getTableName(T::staticMetaObject.className());

        getDb().transaction();
        QSqlQuery q(getDb());
        QString str = QString("DELETE FROM %1 WHERE %2")
                .arg( tableName)
                .arg( condition);

        q.exec(str);

        if( findSqlError("Engine::remove", q.lastError()))
            return;

        getDb().commit();
    }

    QSqlDatabase getDb() const;
    void setDb(const QSqlDatabase &db);
    Error getLastError() const;

    QString getTableNamePrefix() const;
    QString getTableName(const QString& className ) const {
        if( getTableNamePrefix().isEmpty() == false)
            return (getTableNamePrefix() + "_" + className.toLower());
        else
            return className.toLower();
    }


    bool isConnected()
    {
        if( _db.isValid() && _db.isOpen())
            return true;
        return false;
    }



    void setTableNamePrefix(const QString &tableNamePrefix);

protected:
    QSqlDatabase _db;
    QString _tableNamePrefix;
    Error _lastError;

    void getInstancied(unicorn::Entity *entity, int id);


    void setLastError( Error::Type type, const QString& text, const QString& sqlText = QString());
    bool findSqlError( const QString& text, const QSqlError& error);



};

}

#endif // ENGINE_H
