#include <QApplication>
#include "CameraApp.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CameraApp cameraApp;
    cameraApp.show();
    return app.exec();
}