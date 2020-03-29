#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Set Up UI
    ui->setupUi(this);

    // Creating a new Webcam Object
    frontWebcam = new Webcam();

    // Creating a new QImage Object
    frontWebcamImage = new QImage();

    // Connecting the displayWebcamImage() method to the timeout of a timer
    /*
     * We display a new image when the timer times out.
     */
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayWebcamImage()));
    timer->start(timeout);

    chrono = new QTimer(this);
    connect(chrono, SIGNAL(timeout()), this, SLOT(addSecond()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayWebcamImage()
{
    // Updating the image caught by the webcam
    frontWebcam->updateImage();
    // If the game is running :
    if (isMoving)
    {
        // Detecting faces on the image
        frontWebcam->detectFaces();
        // Detecting motion
        frontWebcam->detectMotion();
    }
    // Getting this new image
    frontWebcamImage = frontWebcam->getImage();

    // Displaying on the label imageLabel_
    ui->imageLabel_->setPixmap(QPixmap::fromImage(*frontWebcamImage));
    // Resizing the label to fit the image
    ui->imageLabel_->resize(ui->imageLabel_->pixmap()->size());
}

void MainWindow::addSecond()
{
    timeElapsed++;
    ui->chronoLabel->setText(QString::fromStdString(std::to_string(timeElapsed) + " sec"));
}


void MainWindow::on_startPushButton_clicked()
{
    this->chrono->start(1000);
    this->haveToMove(true);
}

void MainWindow::on_resetPushButton_clicked()
{
    this->chrono->stop();
    this->haveToMove(false);
    timeElapsed = 0;
    ui->chronoLabel->setText(QString::fromStdString("Ready ?"));
}

void MainWindow::on_pausePushButton_clicked()
{
    this->chrono->stop();
    this->haveToMove(false);
}

void MainWindow::on_leavePushButton_clicked()
{
    this->close();
}
