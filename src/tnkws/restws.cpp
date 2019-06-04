#include "restws.h"

#include <QAuthenticator>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonArray>

#include <QEventLoop>



namespace tnk {
namespace ws{

RestWs::RestWs( QObject *parent) : QNetworkAccessManager(parent)
{
    connect( this, &QNetworkAccessManager::authenticationRequired, this, &RestWs::on_authenticationRequired);
}

RestWs::RestWs(const QString &host, const QString &user, const QString &password, QObject *parent)
    :QNetworkAccessManager(parent),
      m_host( host), m_user( user), m_password( password)
{
    connect( this, &QNetworkAccessManager::authenticationRequired, this, &RestWs::on_authenticationRequired);
}


QNetworkReply *RestWs::get(const QString &path, const QUrlQuery& query)
{
    QUrl url(m_host+path);
    url.setQuery( query);



    return QNetworkAccessManager::get( QNetworkRequest(url));

}

QNetworkReply *RestWs::post(const QString &path, const QJsonObject &object)
{
    QByteArray ba = QJsonDocument( object).toJson();
    QUrl url(m_host+path);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, ba.size());
    request.setRawHeader("Accept", "application/json");

    return QNetworkAccessManager::post( request, ba);
}

QNetworkReply *RestWs::put(const QString &path, const QJsonObject &object)
{
    QByteArray ba = QJsonDocument( object).toJson();
    QUrl url(m_host+path);
    QNetworkRequest request(url);
    if(ba.isEmpty() == false)
    {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::ContentLengthHeader, ba.size());
    }
    request.setRawHeader("Accept", "application/json");

    return QNetworkAccessManager::put( request, ba);
}

QNetworkReply *RestWs::del(const QString &path)
{
    QUrl url(m_host+path);
    return QNetworkAccessManager::deleteResource( QNetworkRequest(url));
}

void RestWs::waitForFinished(QNetworkReply *reply)
{
    QEventLoop loop;
    connect( reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
}

QJsonValue RestWs::waitJson(QNetworkReply *reply)
{
    waitForFinished(reply);
    return toJson( reply);
}

QJsonValue RestWs::getJson(const QString &path, const QUrlQuery& query)
{
    auto reply = this->get(path, query);

    waitForFinished( reply);
    return this->toJson(reply);
}

QJsonValue RestWs::toJson(QNetworkReply *reply)
{

    if( reply->error() == QNetworkReply::NoError)
    {
        return toJson(reply->readAll());
    }

    return QJsonValue();


}

QJsonValue RestWs::toJson( const QByteArray& data)
{
    const QJsonDocument& doc = QJsonDocument::fromJson( data);
    if( doc.isArray())
        return doc.array();

    return doc.object();
}

void RestWs::on_authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED( reply)
    authenticator->setUser( m_user);
    authenticator->setPassword( m_password);
}

}
}
