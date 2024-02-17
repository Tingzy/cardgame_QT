#include <QApplication>
#include "uiHandle.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    mainWindow window;
    uiHandle myUiHandle;

 return app.exec();
}