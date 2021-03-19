#include "card.h"

Card::Card(QObject *parent) : QObject(parent)
{

}

Card::Card(const Card &card)
{
    m_title = card.m_title;
    m_id = card.m_id;
    m_countD = card.m_countD;
    m_statD = card.m_statD;
}

Card &Card::operator=(const Card &card)
{
    m_title = card.m_title;
    m_id = card.m_id;
    m_countD = card.m_countD;
    m_statD = card.m_statD;
    return *this;
}

QString Card::getTitle() const
{
    return m_title;
}

void Card::setTitle(const QString title)
{
    // request to server "change card's title"
    m_title = title;
}

int Card::getId() const
{
    return m_id;
}
