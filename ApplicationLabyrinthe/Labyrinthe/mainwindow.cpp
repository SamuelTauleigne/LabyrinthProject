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
    connect(glTimer, SIGNAL(timeout()), this, SLOT(manageLabyrinth()));
    glTimer->start(glTimeout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete frontWebcam;
    delete frontWebcamImage;
    delete timer;
    delete chrono;
    delete glTimer;
    delete glwidget;
}

void MainWindow::manageLabyrinth()
{
    this->glwidget->paintGL();
    if (this->glwidget->getLabyrinthe()->terminer()){
        // The player found the exit.
        QMessageBox::information(this, tr("And the winner is ..."), QString::fromStdString("You won in " + std::to_string(timeElapsed) + " seconds !"));
        // this->glwidget = new MyGLWidget();
        delete this;
        this->close();
    }
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
    float pas = 0.125;
    switch (event->key()){
        case Qt::Key_Z :
            glwidget->deplacerCamera(pas, glwidget->getLabyrinthe()->getJoueur().getOrientation(), true);
            glwidget->getLabyrinthe()->deplacerJoueur(pas, true);
            if (glwidget->getLabyrinthe()->collision()){
                glwidget->deplacerCamera(pas, glwidget->getLabyrinthe()->getJoueur().getOrientation(), false);
                glwidget->getLabyrinthe()->deplacerJoueur(pas, false);
            }
            break;
        case Qt::Key_S :
            glwidget->deplacerCamera(pas, glwidget->getLabyrinthe()->getJoueur().getOrientation(), false);
            glwidget->getLabyrinthe()->deplacerJoueur(pas, false);
            if (glwidget->getLabyrinthe()->collision()){
                glwidget->deplacerCamera(pas, glwidget->getLabyrinthe()->getJoueur().getOrientation(), true);
                glwidget->getLabyrinthe()->deplacerJoueur(pas, true);
            }
            break;
        case Qt::Key_D :
            glwidget->pivoterCamera(glwidget->getLabyrinthe()->getJoueur().getOrientation(), false);
            glwidget->getLabyrinthe()->pivoterJoueur(false);
            break;
        case Qt::Key_Q :
            glwidget->pivoterCamera(glwidget->getLabyrinthe()->getJoueur().getOrientation(), true);
            glwidget->getLabyrinthe()->pivoterJoueur(true);
            break;
    }
    // Acceptation de l'événement et mise a jour de la scene
    event->accept();
    glwidget->update();

}
/*
// Fonction de gestion d'interactions clavier
void MainWindow::keyPressEvent(QKeyEvent * event){
    if (isMoving)
    {
        switch (event->key()){
        case Qt::Key_Z :
            if (this->glwidget->getFixX() == this->glwidget->getCamX()+1){
                this->glwidget->setCamX(this->glwidget->getCamX()+1);
                this->glwidget->setFixX(this->glwidget->getFixX()+1);
                this->moveTo(0.1,0);
            } else if (this->glwidget->getFixY() == this->glwidget->getCamY()-1){
                this->glwidget->setCamY(this->glwidget->getCamY()-1);
                this->glwidget->setFixY(this->glwidget->getFixY()-1);
                this->moveTo(0,-0.1);
            } else if (this->glwidget->getFixX() == this->glwidget->getCamX()-1){
                this->glwidget->setCamX(this->glwidget->getCamX()-1);
                this->glwidget->setFixX(this->glwidget->getFixX()-1);
                this->moveTo(-0.1,0);
            } else if (this->glwidget->getFixY() == this->glwidget->getCamY()+1){
                this->glwidget->setCamY(this->glwidget->getCamY()+1);
                this->glwidget->setFixY(this->glwidget->getFixY()+1);
                this->moveTo(0,0.1);
            }
            break;
        case Qt::Key_S :
            if (this->glwidget->getFixX() == this->glwidget->getCamX()+1){
                this->glwidget->setCamX(this->glwidget->getCamX()-1);
                this->glwidget->setFixX(this->glwidget->getFixX()-1);
                this->moveTo(-0.1,0);
            } else if (this->glwidget->getFixY() == this->glwidget->getCamY()-1){
                this->glwidget->setCamY(this->glwidget->getCamY()+1);
                this->glwidget->setFixY(this->glwidget->getFixY()+1);
                this->moveTo(0,0.1);
            } else if (this->glwidget->getFixX() == this->glwidget->getCamX()-1){
                this->glwidget->setCamX(this->glwidget->getCamX()+1);
                this->glwidget->setFixX(this->glwidget->getFixX()+1);
                this->moveTo(0.1,0);
            } else if (this->glwidget->getFixY() == this->glwidget->getCamY()+1){
                this->glwidget->setCamY(this->glwidget->getCamY()-1);
                this->glwidget->setFixY(this->glwidget->getFixY()-1);
                this->moveTo(0,-0.1);
            }
            break;
        case Qt::Key_D :
            if (this->glwidget->getFixX() == this->glwidget->getCamX()+1){
                this->glwidget->setFixX(this->glwidget->getFixX()-1);
                this->glwidget->setFixY(this->glwidget->getFixY()-1);
            } else if (this->glwidget->getFixY() == this->glwidget->getCamY()-1){
                this->glwidget->setFixX(this->glwidget->getFixX()-1);
                this->glwidget->setFixY(this->glwidget->getFixY()+1);
            } else if (this->glwidget->getFixX() == this->glwidget->getCamX()-1){
                this->glwidget->setFixX(this->glwidget->getFixX()+1);
                this->glwidget->setFixY(this->glwidget->getFixY()+1);
            } else if (this->glwidget->getFixY() == this->glwidget->getCamY()+1){
                this->glwidget->setFixX(this->glwidget->getFixX()+1);
                this->glwidget->setFixY(this->glwidget->getFixY()-1);
            }
            break;
        case Qt::Key_Q :
            if (this->glwidget->getFixX() == this->glwidget->getCamX()+1){
                this->glwidget->setFixX(this->glwidget->getFixX()-1);
                this->glwidget->setFixY(this->glwidget->getFixY()+1);
            } else if (this->glwidget->getFixY() == this->glwidget->getCamY()-1){
                this->glwidget->setFixX(this->glwidget->getFixX()+1);
                this->glwidget->setFixY(this->glwidget->getFixY()+1);
            } else if (this->glwidget->getFixX() == this->glwidget->getCamX()-1){
                this->glwidget->setFixX(this->glwidget->getFixX()+1);
                this->glwidget->setFixY(this->glwidget->getFixY()-1);
            } else if (this->glwidget->getFixY() == this->glwidget->getCamY()+1){
                this->glwidget->setFixX(this->glwidget->getFixX()-1);
                this->glwidget->setFixY(this->glwidget->getFixY()-1);
            }
            break;
        }
        // Acceptation de l'événement et mise a jour de la scene
        event->accept();
        // update();
        this->glwidget->update();
    }
}
*/

void MainWindow::moveTo(float x, float y)
{
    this->glwidget->getLabyrinthe()->deplacerJoueur(x, y);
}
