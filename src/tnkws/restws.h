#ifndef RESTWS_H
#define RESTWS_H


#include <QNetworkAccessManager>
#include <QJsonObject>

#include <TnkCommon/utils.h>
#include <QUrlQuery>

class QNetworkReply;
class QAuthenticator;
namespace tnk {
namespace ws{
class  RestWs : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit RestWs(QObject *parent = nullptr);
    RestWs(const QString& host,
                    const QString& user = QString(),
                    const QString& password = QString(), QObject *parent = nullptr);

    typedef enum  REQUESTTYPE{
        GET,
        POST,
        PUT,
        DEL
    }REQUESTTYPE;

signals:

public slots:
    QNetworkReply *get(const QString& path, const QUrlQuery &query = QUrlQuery());
    QNetworkReply *post(const QString& path, const QJsonObject &object);
    QNetworkReply *put(const QString& path, const QJsonObject &object = QJsonObject());
    QNetworkReply *del(const QString& path);

public:

    QJsonValue getJson(const QString &path, const QUrlQuery &query = QUrlQuery());


    static void waitForFinished( QNetworkReply *reply);
    static QJsonValue waitJson( QNetworkReply *reply);
    static QJsonValue toJson( QNetworkReply* reply);
    static QJsonValue toJson(const QByteArray &data);

private slots:

    void on_authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);


private:
    PROPERTY(QString, host, QString())
    PROPERTY(QString, user, QString())
    PROPERTY(QString, password, QString())

};
}
}
#endif // RESTWS_H
