#ifndef JSONCONFIG_H
#define JSONCONFIG_H

#include <QJsonValue>
#include <QJsonObject>


namespace tnk {

class  JsonObject
{
public:
    JsonObject();
    JsonObject( const QJsonValue& value);


    QByteArray toString() const;
    void fromData( const QByteArray &data);
    void fromValue( const QJsonValue& value);
    void load( const QString& fileName);
    void save( const QString& fileName);


    void loadConfig();
    void saveConfig();

    QJsonValue value(const QString &path);


    void setValue(const QString &path, const QJsonValue& value);

    bool isValid() const;
    QJsonObject data() const;



private:
    QJsonObject m_data;

    void setValue(QJsonObject *object, const QString& path, const QJsonValue& value); //no array
};

}
#endif // JSONCONFIG_H
