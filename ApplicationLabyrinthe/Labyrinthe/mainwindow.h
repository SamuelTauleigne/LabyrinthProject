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
#include <QMessageBox>
using namespace std;

#include "webcam.h"
#include "myglwidget.h"
#include "carteWidget.h"

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
    int timeout = 180; // 5
    int timeElapsed = 0;
    int glTimeout = 5;
    QTimer *timer;
    QTimer *chrono;
    QTimer *glTimer;
    bool isMoving = false; // Tells if we should move or not.
    carteWidget* carte = new carteWidget();
    MyGLWidget *glwidget = new MyGLWidget();
    int lastMove = -1;
    int countSameMoves = 0;
    int lastMoveDone = -1;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void haveToMove(bool movingOrNotMoving) {isMoving = movingOrNotMoving;}
    // void moveTo(float x, float y);
    void moveTo(int moveToDo);
    void processMove(int moveToDo);

protected:
    void keyPressEvent(QKeyEvent * event);

public slots:
    void manageLabyrinth();
    void displayWebcamImage();
    void addSecond();


private slots:
    void on_startPushButton_clicked();

    void on_resetPushButton_clicked();

    void on_pausePushButton_clicked();

    void on_leavePushButton_clicked();

    void on_setSizePushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
