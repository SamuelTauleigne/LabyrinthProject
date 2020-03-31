#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Set Up UI
    ui->setupUi(this);
    // ui->chronoLabel->setStyleSheet("QLabel {color : white;}");
    ui->chronoLabel->setText(QString::fromStdString("Ready ?"));

    ui->gridLayout->addWidget(glwidget);

    // Labyrinthe 3D
    // MyGLWidget* labyrinth3D = new MyGLWidget();
    // ui->openGLWidget = labyrinth3D;
    // ui->openGLWidget->setLayout(labyrinth3D->layout());
    // labyrinth3D->show();
    // ui->openGLWidget->show();

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

    glTimer = new QTimer(this);
    connect(glTimer, SIGNAL(timeout()), this->glwidget, SLOT(paintGL()));
    glTimer->start(glTimeout);
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

/*
 * The method addSecond() increments timeElapsed and displays the new value in the corresponding label.
 */
void MainWindow::addSecond()
{
    timeElapsed++;
    ui->chronoLabel->setText(QString::fromStdString(std::to_string(timeElapsed) + " sec"));
}



/*
 * Push Buttons slots :
 *  - Start makes the chronometer start and enables moves
 *  - Reset makes the chronometer stop, resets it and disables moves
 *  - Pause stops the chronometer and disable the moves
 *  - Leave closes the window and leaves the application
 */

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


// Fonction de gestion d'interactions clavier
void MainWindow::keyPressEvent(QKeyEvent * event){
    if (isMoving)
    {
        this->glwidget->keyPressEvent(event);
    }
}
