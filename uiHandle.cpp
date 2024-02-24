#include "uiHandle.h"
#include <QApplication>
#include <QMessageBox>
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
    startWindow.setFixedSize(1200, 850);

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
    gameWindow.setFixedSize(1200, 850);

    gameLayout->addLayout(dealerCardLayout);
    gameLayout->addLayout(cardLayout);
    gameLayout->addLayout(playerCardLayout);
    gameLayout->addLayout(buttonLayout);

    // Empty widgets as card place holder.
    for (int i=0; i<9; i++)
    {
        cardWidgets[i] = new QStackedWidget;

        // Top row is for dealer.
        if(i == 0 || i == 1)
        {
            dealerCardLayout->addWidget(cardWidgets[i]);
        }
        // Last row is for player.
        else if (i == 2 || i == 3)
        {
            playerCardLayout->addWidget(cardWidgets[i]);
        }
        // Middle row.
        else
        {
            cardLayout->addWidget(cardWidgets[i]);
        }
    }

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
    endWindow.setFixedSize(1200, 850);
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
    if(cardCount <= 9)
    {
        Card* myCardObject = new Card(m_cardImage, m_cardName);
        int cardNumber = std::stoi(m_cardName.substr(4, 1));
        cardWidgets[cardNumber -1]->addWidget(myCardObject->getCardWidget());
        dealCards.push_back(myCardObject);
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","That's enough card.");
        messageBox.setFixedSize(500,250);
    }
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
    ++cardCount;
    std::string cardName = "card" + std::to_string(cardCount);
    if (cardCount == 1 || cardCount == 2)
    {
        cardImage = "backofcard";
    }
    else
    {
        cardImage = "aa";
    }
    emit cardCountChanged(cardImage, cardName);
}

uiHandle::~uiHandle()
{
    delete baseWindow;
    delete baseLayout;
    delete stackedLayout;

    delete gameLayout;
    delete buttonLayout;
    delete cardLayout;
    delete dealerCardLayout;
    delete playerCardLayout;

    for (int i=0; i<9; i++)
    {
        delete cardWidgets[i];
    }

    dealCards.clear();

}
