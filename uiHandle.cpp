#include "uiHandle.h"
#include <QStackedWidget>
#include <QApplication>
#include <unistd.h>
#include "window.h"
#include "button.h"

uiHandle::uiHandle()
{
    cardCount = 0;
    //Add stacked layout to the main base lauouy, and set base layout as the layout for base window.
    baseLayout->addLayout(stackedLayout);
    baseWindow->setLayout(baseLayout);

    //Create the 3 views.
    createStartWindow();
    createGameWindow();
    createEndWindow();
    
    // Add the 3 vviews to stacked layout.
    stackedLayout->addWidget(&startWindow);
    stackedLayout->addWidget(&gameWindow);
    stackedLayout->addWidget(&endWindow);

    // Show base winow.
    baseWindow->show();
    

}

void uiHandle::createStartWindow()
{
    startWindow.setObjectName("startWindow");
    startWindow.setStyleSheet("#startWindow {border-image: url(resource/startBG.png);}");
    startWindow.setFixedSize(1200, 600);

    //Creat a button with no text, background image2, child of startWindow.
    QPushButton *startButton = new QPushButton("", &startWindow);
    startButton->setGeometry(10, 10, 160, 70);
    startButton->setObjectName("startButton");
    startButton->setStyleSheet("#startButton {border-image: url(resource/startButton.png);}");

    //When button click, hide widow, which in turn shows the next window.
    connect(startButton, &QPushButton::released, &startWindow, &mainWindow::hideWindow);
    connect(startButton, &QPushButton::released, this, &uiHandle::showGameWindow);
}

void uiHandle::createGameWindow()
{
    gameWindow.setObjectName("gameWindow");
    gameWindow.setStyleSheet("#gameWindow {border-image: url(resource/gameBG.png);}");
    gameWindow.setFixedSize(1200, 600);

    gameLayout->addLayout(cardLayout);
    cardLayout->setSizeConstraint(QLayout::SetMaximumSize);
    gameLayout->addLayout(buttonLayout);

    QPushButton *restartButton = new QPushButton("Restart");
    restartButton->setFixedSize(80, 30);
    connect(restartButton, &QPushButton::released, &gameWindow, &mainWindow::hideWindow);
    connect(restartButton, &QPushButton::released, this, &uiHandle::showStartWindow);
    connect(restartButton, &QPushButton::released, this, &uiHandle::removeCards);

    QPushButton *dealButton = new QPushButton("Deal");
    dealButton->setFixedSize(80, 30);
    //connect(dealButton, &QPushButton::released, this, [this]{ createCard("aa", "card1"); });
    connect(dealButton, &QPushButton::released, this, &uiHandle::countNewCard);
    connect(this, &uiHandle::cardCountChanged, this, &uiHandle::createCard);

    buttonLayout->addWidget(restartButton);
    buttonLayout->addWidget(dealButton);
    
}


void uiHandle::createEndWindow()
{
    endWindow.setObjectName("endWindow");
    endWindow.setStyleSheet("#endWindow {border-image: url(resource/endBG.png);}");
    endWindow.setFixedSize(1200, 600);
}

void uiHandle::showGameWindow()
{
    gameWindow.show();
}

void uiHandle::showEndWindow()
{
    endWindow.show();
}

void uiHandle::showStartWindow()
{
    startWindow.show();
}

void uiHandle::createCard(const std::string& m_cardImage, const std::string& m_cardName)
{
    Card* myCardObject = new Card(m_cardImage, m_cardName);
    cardLayout->addWidget(myCardObject->getCardWidget());
    dealCards.push_back(myCardObject);
}

// not yet working.
void uiHandle::removeCards()
{
    for (Card* card : dealCards)
    {
        cardLayout->removeWidget(card->getCardWidget());
        delete card;
    }
}

void uiHandle::countNewCard()
{
    std::string cardImage;
    std::string cardName;
    ++cardCount;
    if(cardCount == 1)
    {
        cardImage = "aa";
        cardName = "card1";
    }
    else
    {
        cardImage = "ak";
        cardName = "card2";
    }
    emit cardCountChanged(cardImage, cardName);
}
