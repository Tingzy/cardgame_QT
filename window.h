#pragma once

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>

class mainWindow : public QWidget
{
Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

signals:
    void stateChanged();
public slots:
  void hideWindow();
};
