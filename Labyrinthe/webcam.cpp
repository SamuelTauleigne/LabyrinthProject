#include "webcam.h"

Webcam::Webcam()
{
    webcam = new VideoCapture(0);
    // int width=webcam->get(CAP_PROP_FRAME_WIDTH);
    // int height=webcam->get(CAP_PROP_FRAME_HEIGHT);
    webcamImage = new Mat();
    img = new QImage();
}

Webcam::~Webcam()
{
    delete webcam;
    delete webcamImage;
}

void Webcam::updateImage()
{
    // Checking if the webcam is opened
    if(webcam->isOpened())
    {
        // Reading an image
        webcam->read(*webcamImage);
        // Flipping the image to counter the mirror effect
        flip(*webcamImage, *webcamImage, 1);
        // Inverting Blue and Red color channels
        cvtColor(*webcamImage, *webcamImage, COLOR_BGR2RGB);
        // Converting to Qt image
        *img = QImage((const unsigned char*)(webcamImage->data), webcamImage->cols, webcamImage->rows, QImage::Format_RGB888);
    }
}

QImage* Webcam::getImage()
{
    return img;
}
