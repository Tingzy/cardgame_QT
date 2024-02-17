#include "button.h"

myButton::myButton(const QString& text, QWidget* buttonParent)
{
    qButton.setParent(buttonParent);
    qButton.setText(text);
}

QPushButton* myButton::getButton()
{
    return &qButton;
}