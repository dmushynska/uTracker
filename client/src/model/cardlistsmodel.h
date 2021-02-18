#ifndef CARDLISTSMODEL_H
#define CARDLISTSMODEL_H

#include <QAbstractListModel>
#include "model/cardsmodel.h"

class CardListsModel : public QAbstractListModel
{
    Q_OBJECT
    
    enum CardListsRole {
        TitleRole,
        ModelsRole
    };
    struct Kanban {
        QString title;
        CardsModel *model;
    };

public:
    explicit CardListsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = TitleRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = TitleRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE bool append(QString title);

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<Kanban> m_kanb;
};

#endif // CARDLISTSMODEL_H
