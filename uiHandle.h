#pragma once
#include "window.h"
#include "card.h"
#include <QLayout>
#include <QStackedLayout>
#include <QStackedWidget>

class uiHandle : public QObject
{
    Q_OBJECT
    public:
        int cardCount;
        explicit uiHandle();

        //Set background and main buttons for start window.
        void createStartWindow();
        //Set background and main buttons for in-game window.
        void createGameWindow();
        //Set background and main buttons for end window.
        void createEndWindow();

    private:
        //Base window is the application window. There is 1 base window for 1 app.
        QWidget *baseWindow = new QWidget;

        //Base layout is the application layout. 1 base layout for 1 app.
        QHBoxLayout *baseLayout = new QHBoxLayout(baseWindow);

        //Stacked layout is the layout inside baseLayout. Different view (start view, in game view, end view)
        //can be stacked in this layout, and each time there is 1 view to be shown on the window.
        QStackedLayout *stackedLayout = new QStackedLayout;

        //The 3 main views in this game.
        mainWindow startWindow;
        mainWindow gameWindow;
        mainWindow endWindow;

        //Layouts for the game window.
        //Game layout is the main layout.
        //Buttons layout is a horizontal layout that contains buttons.
        //cardLayout is the layout for the cards.
        QVBoxLayout *gameLayout = new QVBoxLayout(&gameWindow);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        QHBoxLayout *cardLayout = new QHBoxLayout();
        QHBoxLayout *dealerCardLayout = new QHBoxLayout();
        QHBoxLayout *playerCardLayout = new QHBoxLayout();

        QStackedWidget* cardWidgets[9];

        //Card vector.
        std::vector<Card*> dealCards;

        std::map<int, std::string> dealerCard;
        std::map<int, std::string> playerCard;
        std::map<int, std::string> sharedCard;

    private slots:
        //Slot to be connected to some signals, to show startWindow, in-game window or end window.
        void showStartWindow();
        void showGameWindow();
        void showEndWindow();

        //Test create a new card.
        void createCard(const std::string& m_cardImage, const std::string& m_cardName);

        // Slot that increase card count and emit cardCountChanged.
        void countNewCard();

        //Remove all cards.
        void removeCards();

        signals:
        void cardCountChanged(const std::string & cardImage, const std::string & cardName);
};
