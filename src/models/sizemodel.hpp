#ifndef SIZEMODEL_HPP
#define SIZEMODEL_HPP

#include <QObject>
#include <QAbstractListModel>

#include "size.hpp"


class SizeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(quint32 count READ rowCount NOTIFY countChanged)

public:
    enum SizeModelRoles
    {
        GuidRole = Qt::UserRole + 1,
        LabelRole,
        ScaleRole,
        WidthRole,
        HeightRole,
        ItemRole,
    };

    explicit SizeModel(QObject *parent = nullptr);
    ~SizeModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
    void sizesReset(const QList<Size*> size);
    void insertSize(Size *size);
    void deleteSize(const quint64 &guid, const qint32 &index);

signals:
    void countChanged(qint32 count);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Size*> m_sizes;

    void clearData();
};

#endif // SIZEMODEL_HPP
