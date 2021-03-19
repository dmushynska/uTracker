#ifndef CARD_H
#define CARD_H

#include <QObject>

class Card : public QObject
{
    Q_OBJECT
public:
    explicit Card(QObject *parent = nullptr);
    Card(const Card &card);
    Card &operator=(const Card &card);

    void doRequestForInfo() const {
//        emit (m_id);
    }
    // Title
    QString getTitle() const;
    void setTitle(const QString title);

    // Id
    Q_INVOKABLE int getId() const;
    void setId(int id) {
        m_id = id;
    }

    // List id
    int getListId() const {
        return m_listId;
    }
    void setListId(int id) {
        if (id != -1)
            m_listId = id;
    }

    // Status
    int getStatD() const {
        return m_statD;
    }
    void setStatD(int stat) {
        m_statD = stat;
    }

    int getCountD() const {
        return m_countD;
    }
    void setCountD(int count) {
        m_countD = count;
    }

private:
    QString m_title;
    int m_id;
    int m_listId = -1;
    int m_statD = 0;
    int m_countD = 0;
};

#endif // CARD_H
