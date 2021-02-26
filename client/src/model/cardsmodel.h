#ifndef CARDSMODEL_H
#define CARDSMODEL_H

#include <QAbstractListModel>
#include <Components/src/card.h>

class CardsModel : public QAbstractListModel
{
    Q_OBJECT

    enum CardsRole {
        TitleRole,
        IdRole,
        ParentIdRole
    };

public:
    explicit CardsModel(QObject *parent = nullptr, int parentID = -1);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = TitleRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = TitleRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void setParentId(int id);

    Q_INVOKABLE bool append(const QString &title, int id, int parentID);
    Q_INVOKABLE bool append(const Card &card);
    Q_INVOKABLE int parentId() const;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Card *findById(int id, int *indx = nullptr);
    void removeById(int id);

    QHash<int, QByteArray> roleNames() const override;

    static std::shared_ptr<CardsModel> creatCardsModel(const QJsonObject &array, QObject *parent = nullptr, int parentID = -1);

signals:
    void taskAppended();
private:
    QVector<Card> m_cards;
    int m_parentId;
};

#endif // CARDSMODEL_H
