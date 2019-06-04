#ifndef SQLDATABASE_H
#define SQLDATABASE_H


#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QJsonObject>


namespace tnk {
namespace sql{
typedef QList<QSqlRecord> SqlRecordList;

 QSqlDatabase setupSqlDatabase(const QString& name, const QJsonObject &data);

 void showSqlDebug(QSqlQuery *q);
 void showSqlDebug(QSqlDatabase *db);


 void createTable(const QSqlDatabase &db, const QString &tableName, QList<QSqlField> fields);
 void createTable(const QSqlDatabase &db, const QString &tableName, QMetaObject meta);

 void checkConnected(QSqlDatabase &db);
}
}


#endif // DATABASECONFIG_H
