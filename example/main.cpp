//#include "indicator.h"
//#include "mainwindow.h"
#include "dialog.h"

#include <QApplication>
#include <QtDebug>
#include <QLabel>

#define EXAMPLE_DEBUG

#include "../import/IODriverLib/includes/iodriverlib.h"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include <exception>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog dlg;
    dlg.show();

    return a.exec();
}
