#include "uiHandle.h"
#include <QApplication>
#include <QMessageBox>
#include <unistd.h>
#include <stdlib.h>
#include "window.h"
#include "button.h"

std::map<int, std::string> cardVal
{
    {1, "a2"}, // 2 spade.
    {2, "b2"}, // 2 club.
    {3, "c2"}, // 2 diamond.
    {4, "d2"}, // 2 heart.
    {5, "a3"}, // 3 spade.
    {6, "b3"}, // 3 club.
    {7, "c3"}, // 3 diamond.
    {8, "d3"}, // 3 heart.
    {9, "a4"}, // 4 spade.
    {10, "b4"}, // 4 club.
    {11, "c4"}, // 4 diamond.
    {12, "d4"}, // 4 heart.
    {13, "a5"}, // 5 spade.
    {14, "b5"}, // 5 club.
    {15, "c5"}, // 5 diamond.
    {16, "d5"}, // 5 heart.
    {17, "a6"}, // 6 spade.
    {18, "b6"}, // 6 club.
    {19, "c6"}, // 6 diamond.
    {20, "d6"}, // 6 heart.
    {21, "a7"}, // 7 spade.
    {22, "b7"}, // 7 club.
    {23, "c7"}, // 7 diamond.
    {24, "d7"}, // 7 heart.
    {25, "a8"}, // 8 spade.
    {26, "b8"}, // 8 club.
    {27, "c8"}, // 8 diamond.
    {28, "d8"}, // 8 heart.
    {29, "a9"}, // 9 spade.
    {30, "b9"}, // 9 club.
    {31, "c9"}, // 9 diamond.
    {32, "d9"}, // 9 heart.
    {33, "a10"}, // 10 spade.
    {34, "b10"}, // 10 club.
    {35, "c10"}, // 10 diamond.
    {36, "d10"}, // 10 heart.
    {37, "aj"}, // J spade.
    {38, "bj"}, // J club.
    {39, "cj"}, // J diamond.
    {40, "dj"}, // J heart.
    {41, "aq"}, // Q spade.
    {42, "bq"}, // Q club.
    {43, "cq"}, // Q diamond.
    {44, "dq"}, // Q heart.
    {45, "ak"}, // K spade.
    {46, "bk"}, // K club.
    {47, "ck"}, // K diamond.
    {48, "dk"}, // K heart.
    {49, "aa"}, // A spade.
    {50, "ba"}, // A club.
    {51, "ca"}, // A diamond.
    {52, "da"} // A heart.
};

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
    int cardNumber;
    ++cardCount;
    srand((unsigned int)time(NULL));
    cardNumber = rand()% 52 + 1;
    while (dealerCard.count(cardNumber) || playerCard.count(cardNumber) || sharedCard.count(cardNumber))
    {
        cardNumber = rand()% 52 + 1;
    }
    printf("card number %d\n", cardNumber);
    std::string cardName = "card" + std::to_string(cardCount);
    if (cardCount == 1 || cardCount == 2)
    {
        cardImage = "backofcard";
        dealerCard.insert({cardNumber, cardImage});
    }
    else
    {
        cardImage = cardVal[cardNumber];
        if (cardCount == 3 || cardCount == 4)
        {
            playerCard.insert({cardNumber, cardImage});
        }
        else
        {
            sharedCard.insert({cardNumber, cardImage});
        }
    }
    emit cardCountChanged(cardImage, cardName);
}

