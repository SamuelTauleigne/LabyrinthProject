/*
 * Class MainWindow
 *
 * Author = Samuel Tauleigne
 *
 * This Class MainWindow is inherited from QMainWindow.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QTimer>
using namespace std;

#include "webcam.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*
UI will be accessed only through the MainWindow Class.
Moreover, UI can be access only in the main thread.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
    Webcam* frontWebcam;
    QImage* frontWebcamImage;
    int *timeElapsed;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void displayWebcamImage();
    void addSecond();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
