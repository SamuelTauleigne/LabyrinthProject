#include "webcam.h"

Webcam::Webcam()
{
    webcam = new VideoCapture(0);
    // int width=webcam->get(CAP_PROP_FRAME_WIDTH);
    // int height=webcam->get(CAP_PROP_FRAME_HEIGHT);
    webcamImage = new Mat();
    webcamImageRGB = new Mat();
    grayWebcamImage = new Mat();
    img = new QImage();
    faceCascadeClassifier = new CascadeClassifier();
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
        cvtColor(*webcamImage, *webcamImageRGB, COLOR_BGR2RGB);
    }
    else
    {
        std::cerr << "Error";
    }
}

void Webcam::detectFaces()
{
    if (faceCascadeClassifier->load( "..\\Labyrinthe\\haarcascade_frontalface_alt.xml"))
    {
        std::vector<Rect> faces;
        // Converting to gray
        cv::cvtColor(*webcamImage, *grayWebcamImage, COLOR_BGR2GRAY);
        // Equalizing graylevels
        equalizeHist(*grayWebcamImage, *grayWebcamImage);
        // Detecting faces
        faceCascadeClassifier->detectMultiScale(*grayWebcamImage, faces, 1.1, 4, 0, Size(60, 60));
        if (faces.size()>0)
        {
            // Drawing green rectangle
            for (int i=0;i<(int)faces.size();i++)
                rectangle(*webcamImageRGB, faces[i], Scalar(0,255,0),2);
        }
    }
    else
    {
        std::cerr << "Error loading haarcascade_frontalface_alt.xml" << std::endl;
    }
}

QImage* Webcam::getImage()
{
    // Converting to Qt image
    *img = QImage((const unsigned char*)(webcamImageRGB->data), webcamImageRGB->cols, webcamImageRGB->rows, QImage::Format_RGB888);
    return img;
}
