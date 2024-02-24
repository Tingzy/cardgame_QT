#include "card.h"
#include <map>

/*std::map<std::string, int> cardVal
{
    {"a2", 1}, // 2 spade.
    {"b2", 2}, // 2 club.
    {"c2", 3}, // 2 diamond.
    {"d2", 4}, // 2 heart.
    {"a3", 5}, // 3 spade.
    {"b3", 6}, // 3 club.
    {"c3", 7}, // 3 diamond.
    {"d3", 8}, // 3 heart.
    {"a4", 9}, // 4 spade.
    {"b4", 10}, // 4 club.
    {"c4", 11}, // 4 diamond.
    {"d4", 12}, // 4 heart.
    {"a5", 13}, // 5 spade.
    {"b5", 14}, // 5 club.
    {"c5", 15}, // 5 diamond.
    {"d5", 16}, // 5 heart.
    {"a6", 17}, // 6 spade.
    {"b6", 18}, // 6 club.
    {"c6", 19}, // 6 diamond.
    {"d6", 20}, // 6 heart.
    {"a7", 6},
    {"a8", 7},
    {"a9", 2},
    {"a10", 2},
    {"aj", 2},
    {"aq", 2},
    {"ak", 2},
    {"aa", 2}
}*/
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

Card::~Card()
{
    delete cardWidget;
}
