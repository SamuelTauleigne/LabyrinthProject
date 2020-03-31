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
#include "myglwidget.h"

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
    int timeout = 5;
    int timeElapsed = 0;
    int glTimeout = 5;
    QTimer *timer;
    QTimer *chrono;
    QTimer *glTimer;
    bool isMoving = false; // Tells if we should move or not.
    MyGLWidget *glwidget = new MyGLWidget();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void haveToMove(bool movingOrNotMoving) {isMoving = movingOrNotMoving;}

protected:
    void keyPressEvent(QKeyEvent * event);

public slots:
    void displayWebcamImage();
    void addSecond();


private slots:
    void on_startPushButton_clicked();

    void on_resetPushButton_clicked();

    void on_pausePushButton_clicked();

    void on_leavePushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
