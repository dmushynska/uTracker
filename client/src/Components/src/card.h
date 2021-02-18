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
//    Card(Card &&card);

    void doRequestForInfo() const {}
    // Title
    QString getTitle() const;
    void setTitle(const QString title);
    // Id
    int getId() const;

private:
    QString m_title;
    int m_id;
};

#endif // CARD_H
