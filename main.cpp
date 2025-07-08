/**
 * Typing Speed Test - C++ Qt Application
 * 
 * A comprehensive typing speed test and training application built with C++ and Qt,
 * featuring multiple difficulty levels, structured lessons, user profiles, and audio feedback.
 * 
 * @author Tolstoy Justin
 * @license MIT License
 * @version 1.0.0
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow window;
    window.show();
    
    return app.exec();
}