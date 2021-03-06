#ifndef SQLTABLEMODEL_H
#define SQLTABLEMODEL_H

#include <QtSql/QSqlRelationalTableModel>

namespace tnk {
namespace sql{
class  TableModel: public QSqlRelationalTableModel
{
    Q_OBJECT

private:
    QHash<int, QByteArray> roles;
    void generateRoleNames();
public:
    TableModel(const QSqlDatabase &database, QObject *parent = nullptr);

    virtual QHash<int, QByteArray> roleNames() const;

   Q_INVOKABLE QVariant data ( const QModelIndex & index, int role ) const;

    // QSqlTableModel interface
public slots:
    virtual bool select() override;
};

}
}
#endif // SQLTABLEMODEL_H
