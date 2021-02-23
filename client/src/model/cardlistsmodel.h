#ifndef CARDLISTSMODEL_H
#define CARDLISTSMODEL_H

#include <QAbstractListModel>
#include "model/cardsmodel.h"
#include <memory>

#define PARENT_CAST(parent, x) qobject_cast<parent *>(x)

class CardListsModel : public QAbstractListModel
{
    Q_OBJECT
    
    enum CardListsRole {
        TitleRole,
        ModelsRole,
        IdRole
    };
    struct Kanban {
        QString title;
        int id;
        std::shared_ptr<CardsModel> model;
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



    Q_INVOKABLE bool append(const QString &title, int id);

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    
    QHash<int, QByteArray> roleNames() const override;

    void clearAllLists();

    Kanban getKanbById(int listId) {
        for (auto& v : m_kanb)
            if (v.id == listId)
                return v;
        return {"", -1, nullptr};
    }

private:
    QVector<Kanban> m_kanb;
};

#endif // CARDLISTSMODEL_H
