#include "card.h"

Card::Card(const std::string& m_cardImage, const std::string& m_cardName)
{
    const std::string cardStyle = "#" + m_cardName + " {border-image: url(resource/" + m_cardImage + ".png) 0 0 0 0 stretch stretch;}";
    cardWidget->setObjectName(QString::fromStdString(m_cardName));
    cardWidget->setStyleSheet(QString::fromStdString(cardStyle));
    cardWidget->setFixedSize(210, 250);
}

QWidget* Card::getCardWidget()
{
    return cardWidget;
}