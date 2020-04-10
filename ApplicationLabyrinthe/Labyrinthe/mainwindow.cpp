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

    ui->gridLayout_4->addWidget(carte);

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
    delete carte;
    delete glwidget;
}

void MainWindow::manageLabyrinth()
{
    this->carte->setLabyrinthe(this->glwidget->getLabyrinthe());
    this->carte->paintGL();
    this->glwidget->paintGL();
    if (this->glwidget->getLabyrinthe()->terminer()){
        // The player found the exit.
        QMessageBox::information(this, tr("And the winner is ..."), QString::fromStdString("You won in " + std::to_string(timeElapsed) + " seconds !"));

        on_resetPushButton_clicked();

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
        int moveToDo = frontWebcam->detectMotion();
        moveTo(moveToDo);
        // processMove(moveToDo);

        if (moveToDo == -1)
        {
            carte->setFixedWidth(280);
        }
        else
        {
            carte->setFixedWidth(25);
        }

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
    // Initializing motion Detection
    this->frontWebcam->initializeMotionDetection();
}

void MainWindow::on_resetPushButton_clicked()
{
    this->chrono->stop();
    this->haveToMove(false);
    timeElapsed = 0;
    ui->chronoLabel->setText(QString::fromStdString("Ready ?"));
    this->frontWebcam->initializeMotionDetection();
    int width = min(ui->heightEdit->text().toUInt(), ui->widthEdit->text().toUInt());
    int height = max(ui->heightEdit->text().toUInt(), ui->widthEdit->text().toUInt());
    glwidget->setLabyrinthe(new Labyrinthe(width, height));
    glwidget->genererLabyrinthe();
    carte->setLabyrinthe(glwidget->getLabyrinthe());
    glwidget->update();
    carte->setFixedWidth(280);
    carte->update();
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

void MainWindow::on_setSizePushButton_clicked()
{
    int width = min(ui->heightEdit->text().toUInt(), ui->widthEdit->text().toUInt());
    int height = max(ui->heightEdit->text().toUInt(), ui->widthEdit->text().toUInt());
    glwidget->setLabyrinthe(new Labyrinthe(width, height));
    glwidget->genererLabyrinthe();
    carte->setLabyrinthe(glwidget->getLabyrinthe());
    glwidget->update();
    carte->setFixedWidth(280);
    carte->update();
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
    carte->update();

}

void MainWindow::moveTo(int moveToDo)
{
    float pas = 0.125;
    switch (moveToDo){
        case 1:
            glwidget->deplacerCamera(pas, glwidget->getLabyrinthe()->getJoueur().getOrientation(), true);
            glwidget->getLabyrinthe()->deplacerJoueur(pas, true);
            if (glwidget->getLabyrinthe()->collision()){
                glwidget->deplacerCamera(pas, glwidget->getLabyrinthe()->getJoueur().getOrientation(), false);
                glwidget->getLabyrinthe()->deplacerJoueur(pas, false);
            }
            break;
        case 3 :
            glwidget->deplacerCamera(pas, glwidget->getLabyrinthe()->getJoueur().getOrientation(), false);
            glwidget->getLabyrinthe()->deplacerJoueur(pas, false);
            if (glwidget->getLabyrinthe()->collision()){
                glwidget->deplacerCamera(pas, glwidget->getLabyrinthe()->getJoueur().getOrientation(), true);
                glwidget->getLabyrinthe()->deplacerJoueur(pas, true);
            }
            break;
        case 0 :
            glwidget->pivoterCamera(glwidget->getLabyrinthe()->getJoueur().getOrientation(), false);
            glwidget->getLabyrinthe()->pivoterJoueur(false);
            break;
        case 2 :
            glwidget->pivoterCamera(glwidget->getLabyrinthe()->getJoueur().getOrientation(), true);
            glwidget->getLabyrinthe()->pivoterJoueur(true);
            break;
    }
    glwidget->update();
    carte->update();
}

void MainWindow::processMove(int moveToDo)
{
    if (lastMove == moveToDo)
    {
        countSameMoves++;
    }
    else
    {
        countSameMoves = 0;
    }
    if (countSameMoves >= 2)
    {
        if (lastMoveDone == -1 || lastMoveDone == moveToDo) // Comment second part
        {
            moveTo(moveToDo);
            lastMoveDone = moveToDo;
        }
        else
        {
            if (moveToDo == -1)
            {
                lastMoveDone = -1;
            }
        }
    }
    lastMove = moveToDo;
}
