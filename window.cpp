#include "window.h"
#include "button.h"
#include <iostream>

mainWindow::mainWindow(QWidget *parent) :
QWidget(parent)
{

}

void mainWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void mainWindow::hideWindow()
{
    emit stateChanged();
    this->hide();
    
}

void stateChanged()
{
    
}
