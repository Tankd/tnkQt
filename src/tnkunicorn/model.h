#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>
#include <QVector>
namespace unicorn {

class  Model : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    int rowCount(const QModelIndex&) const override;
    QVariant data(const QModelIndex& index, int role) const override;

public slots:
    void insert(QObject* item);
    void remove(QObject* item);
    void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<QObject*> _items;
};

}

#endif // MODEL_H
