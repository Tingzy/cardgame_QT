#pragma once
#include <QApplication>
#include <QWidget>
#include <QPushButton>

class myButton
{
    public:
        explicit myButton() = delete;
        explicit myButton(const QString& text, QWidget* buttonParent);
        ~myButton();
        QPushButton* getButton();
    private:
        QPushButton qButton;
};
