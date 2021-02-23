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
    int getId() const;
    void setId(int id) {
        m_id = id;
    }


private:
    QString m_title;
    int m_id;
};

#endif // CARD_H
