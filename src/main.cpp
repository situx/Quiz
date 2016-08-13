#include <QApplication>
#include "../include/Window.hpp"
#include "../include/Editor.hpp"
/*! \mainpage Quiz Documentation
 *\image html screenshot.png
 *
 */
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QFile *err = new QFile("error.log");
    err->remove();
    delete(err);
    Window window;
    return app.exec();
}
