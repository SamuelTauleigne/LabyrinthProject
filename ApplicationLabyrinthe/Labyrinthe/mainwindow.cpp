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

    // Initializing timer
    *timeElapsed = 0;

    // Connecting the displayWebcamImage() method to the timeout of a timer
    /*
     * We display a new image when the timer times out.
     */
    int timeout = 5;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayWebcamImage()));
    timer->start(timeout);
    QTimer *chrono = new QTimer(this);
    connect(chrono, SIGNAL(timeout()), this, SLOT(addSecond()));
    chrono->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayWebcamImage()
{
    // Updating the image caught by the webcam
    frontWebcam->updateImage();
    // Detecting faces on the image
    frontWebcam->detectFaces();
    // Detecting motion
    frontWebcam->detectMotion();
    // Getting this new image
    frontWebcamImage = frontWebcam->getImage();

    // Displaying on the label imageLabel_
    ui->imageLabel_->setPixmap(QPixmap::fromImage(*frontWebcamImage));
    // Resizing the label to fit the image
    ui->imageLabel_->resize(ui->imageLabel_->pixmap()->size());
}

void MainWindow::addSecond()
{
    (*timeElapsed)++;
    ui->chronoLabel->setText(QString::fromStdString(std::to_string(*timeElapsed) + " sec"));
}
