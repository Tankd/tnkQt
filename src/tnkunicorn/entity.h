#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>


#include <QJsonObject>
#include <QMetaProperty>
#include <QDateTime>

#define UC_PROPERTY(type, name, defaultValue) \
    Q_SIGNALS: \
    void name##Changed(); \
    public:                          \
    Q_PROPERTY(type name READ get_##name() WRITE set_##name NOTIFY name##Changed)  \
    type get_##name() const { return m_##name; } \
    void set_##name( type value) { m_##name = value; emit  name##Changed(); } \
    private: \
    type m_##name = defaultValue;


class QSqlRecord;

namespace unicorn {

class  Entity : public QObject
{
    Q_OBJECT
public:
    explicit Entity(QObject* parent = nullptr);
    Entity( const Entity& other);

    QJsonObject toJsonObject();

    UC_PROPERTY( QVariant, id, QVariant())
    UC_PROPERTY( QDateTime, created, QDateTime::currentDateTime())
    UC_PROPERTY( QDateTime, updated, QDateTime::currentDateTime())
};

}

#endif // ENTITY_H
