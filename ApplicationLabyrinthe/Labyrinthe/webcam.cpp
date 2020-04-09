#include "webcam.h"

Webcam::Webcam()
{
    // Setting a new camera object
    webcam = new cv::VideoCapture(0);
    webcam->set(cv::CAP_PROP_FRAME_WIDTH, frameWidth);
    webcam->set(cv::CAP_PROP_FRAME_HEIGHT, frameHeight);

}

Webcam::~Webcam()
{
    delete webcam;
    delete webcamImage;
    delete webcamImageRGB;
    delete grayWebcamImage;
    delete img;
    delete faceCascadeClassifier;
}

void Webcam::initializeMotionDetection()
{
    if(webcam->isOpened())
    {
        // Getting initialFrame
        *webcam >> *initialFrame;
        cv::flip(*initialFrame, *initialFrame, 1);
        cv::cvtColor(cv::Mat(*initialFrame, *workingRect), *initialFrameRect, cv::COLOR_BGR2GRAY);
        // imshow("Initial Frame", *initialFrame);

        // Creating the resultMatchTemplateImage image result
        int result_cols = initialFrameRect->cols-templateWidth  + 1;
        int result_rows = initialFrameRect->rows-templateHeight + 1;
        resultMatchTemplateImage->create(result_cols, result_rows, CV_32FC1);
    }
    else
    {
        std::cerr << "Error Opening Webcam" << std::endl;
    }
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
        cvtColor(*webcamImage, *webcamImageRGB, cv::COLOR_BGR2RGB);
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
        std::vector<cv::Rect> faces;
        // Converting to gray
        cv::cvtColor(*webcamImage, *grayWebcamImage, cv::COLOR_BGR2GRAY);
        // Equalizing graylevels
        equalizeHist(*grayWebcamImage, *grayWebcamImage);
        // Detecting faces
        faceCascadeClassifier->detectMultiScale(*grayWebcamImage, faces, 1.1, 4, 0, cv::Size(60, 60));
        if (faces.size()>0)
        {
            // Drawing green rectangle
            for (int i=0;i<(int)faces.size();i++)
                rectangle(*webcamImageRGB, faces[i], cv::Scalar(0,255,0),2);
        }
    }
    else
    {
        std::cerr << "Error loading haarcascade_frontalface_alt.xml" << std::endl;
    }
}

int Webcam::detectMotion()
{
    cv::Mat frameRect;

    // Extracting working rect in webcamImage and converting it to gray
    cv::cvtColor(cv::Mat(*webcamImage, *workingRect), frameRect, cv::COLOR_BGR2GRAY);

    // Extracting template image in initialFrame
    cv::Mat templateImage(*initialFrameRect, *templateRect);

    // Matching between the working rect and the templateImage in initialFrame
    matchTemplate(frameRect, templateImage, *resultMatchTemplateImage, cv::TM_CCORR_NORMED);
    // Localizing the best match with minMaxLoc
    double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
    minMaxLoc(*resultMatchTemplateImage, &minVal, &maxVal, &minLoc, &maxLoc);
    // Computing the translation vector between the origin and the matching rect
    cv::Point vect(maxLoc.x-templateRect->x,maxLoc.y-templateRect->y);

    // Drawing green rectangle and the translation vector
    rectangle(*webcamImageRGB, *workingRect, cv::Scalar( 0, 255, 0), 2);
    cv::Point p(workingCenter->x+vect.x,workingCenter->y+vect.y);
    arrowedLine(*webcamImageRGB, *workingCenter, p, cv::Scalar(255,255,255), 2);

    // Swaping matrixes
    // swap(*initialFrameRect, frameRect); // Commenter pour avoir deux modes de contrôle

    // Detecting direction
    std::cout << vect.x << " " << vect.y << std::endl;
    return move(vect.x, vect.y);
}

int Webcam::move(int x, int y)
{
    int thresholdH = 15;
    int thresholdL = 8;
    if (thresholdL < x && x < thresholdH && thresholdL < y && y < thresholdH)
    {
        if (x > y)
        {
            std::cout << "Droite" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Bas" << std::endl;
            return 3;
        }
    }
    else if (thresholdL < x && x < thresholdH && thresholdL < -y && -y < thresholdH)
    {
        if (x > -y)
        {
            std::cout << "Droite" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Haut" << std::endl;
            return 1;
        }
    }
    else if (thresholdL < -x && -x < thresholdH && thresholdL < y && y < thresholdH)
    {
        if (-x > y)
        {
            std::cout << "Gauche" << std::endl;
            return 2;
        }
        else
        {
            std::cout << "Bas" << std::endl;
            return 3;
        }
    }
    else if (thresholdL < -x && -x < thresholdH && thresholdL < -y && -y < thresholdH)
    {
        if (x < y)
        {
            std::cout << "Gauche" << std::endl;
            return 2;
        }
        else
        {
            std::cout << "Haut" << std::endl;
            return 1;
        }
    }
    else if (-thresholdL <= x && x <= thresholdL)
    {
        if (y > thresholdL)
        {
            std::cout << "Bas" << std::endl;
            return 3;
        }
        else if (y < -thresholdL)
        {
            std::cout << "Haut" << std::endl;
            return 1;
        }
        else
        {
            std::cout << "Neutre" << std::endl;
            return -1;
        }
    }
    else if (-thresholdL <= y && y <= thresholdL)
    {
        if (x > thresholdL)
        {
            std::cout << "Droite" << std::endl;
            return 0;
        }
        else if (x < -thresholdL)
        {
            std::cout << "Gauche" << std::endl;
            return 2;
        }
        else
        {
            std::cout << "Neutre" << std::endl;
            return -1;
        }
    }
    return -1;
}

QImage* Webcam::getImage()
{
    // Converting to Qt image
    *img = QImage((const unsigned char*)(webcamImageRGB->data), webcamImageRGB->cols, webcamImageRGB->rows, QImage::Format_RGB888);
    return img;
}
