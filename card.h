#pragma once
#include <string>
#include <QWidget>

class Card : public QWidget
{
Q_OBJECT
public:
    explicit Card(const std::string& m_cardImage, const std::string& m_cardName);
    QWidget* getCardWidget();

    private:
        QWidget* cardWidget = new QWidget;
        int cardValue;
};