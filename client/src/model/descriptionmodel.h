#ifndef DESCRIPTIONMODEL_H
#define DESCRIPTIONMODEL_H

#include <QAbstractListModel>

class DescriptionModel : public QAbstractListModel
{
    Q_OBJECT

    enum DescriptionRole {
        TaskTitleRole = Qt::UserRole,
        TaskDescriptionRole,
        TaskPointCheckRole,
        TaskPointDescriptionRole,
        TaskIdRole
    };

public:
    explicit DescriptionModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QPair<int, int> getStatus() {
        QPair<int, int> pair = {0, m_data.size()};
        for (const auto& data : m_data) {
            if (data.first)
                pair.first++;
        }
        return pair;
    }

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    void setTaskDescription(const QString &description){
        m_taskDescription = description;
    }
    void setTaskTitle(const QString &title){
        m_taskTitle = title;
    }
    void setTaskId(int id){
        m_taskId = id;
    }

    void setListId (int id) {
        m_listId = id;
    }

    Q_INVOKABLE QString getTaskDescription() const {
        return m_taskDescription;
    }
    Q_INVOKABLE QString getTaskTitle() const {
        return m_taskTitle;
    }
    Q_INVOKABLE int getTaskId() const {
        return m_taskId;
    }

    Q_INVOKABLE int getListId() const {
        return m_listId;
    }

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    Q_INVOKABLE void insert(const QString &pointDescription);
    Q_INVOKABLE void insert(const QPair<bool, QString> &pair);
    Q_INVOKABLE void append();

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    Q_INVOKABLE void clearAllData();

    QMap<QString, bool> toMap();

    QHash<int, QByteArray> roleNames() const override;

private:
    QString m_taskTitle;
    QString m_taskDescription;
    QVector<QPair<bool, QString>> m_data;
    int m_taskId{-1};
    int m_listId{-1};
};

#endif // DESCRIPTIONMODEL_H