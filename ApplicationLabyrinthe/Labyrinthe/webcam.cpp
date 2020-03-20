#include "webcam.h"

Webcam::Webcam()
{
    // Setting a new camera object
    webcam = new VideoCapture(0);
    webcam->set(CAP_PROP_FRAME_WIDTH, frameWidth);
    webcam->set(CAP_PROP_FRAME_HEIGHT, frameHeight);

    // Initializing motion Detection
    initializeMotionDetection();

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
        cv::cvtColor(Mat(*initialFrame, *workingRect), *initialFrame, COLOR_BGR2GRAY);
        // imshow("Initial Frame", *initialFrame);

        // Creating the resultMatchTemplateImage image result
        int result_cols = initialFrame->cols-templateWidth  + 1;
        int result_rows = initialFrame->rows-templateHeight + 1;
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

void Webcam::detectMotion()
{
    Mat frameRect;

    // Extracting working rect in webcamImage and converting it to gray
    cv::cvtColor(Mat(*webcamImage, *workingRect), frameRect, COLOR_BGR2GRAY);

    // Extracting template image in initialFrame
    Mat templateImage(*initialFrame, *templateRect);

    // Matching between the working rect and the templateImage in initialFrame
    matchTemplate(frameRect, templateImage, *resultMatchTemplateImage, TM_CCORR_NORMED);
    // Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    minMaxLoc(*resultMatchTemplateImage, &minVal, &maxVal, &minLoc, &maxLoc);
    // Computing the translation vector between the origin and the matching rect
    Point vect(maxLoc.x-templateRect->x,maxLoc.y-templateRect->y);

    // Drawing green rectangle and the translation vector
    rectangle(*webcamImageRGB, *workingRect, Scalar( 0, 255, 0), 2);
    Point p(workingCenter->x+vect.x,workingCenter->y+vect.y);
    arrowedLine(*webcamImageRGB, *workingCenter, p, Scalar(255,255,255), 2);

    // Detecting direction
    // std::cout << vect.x << " " << vect.y << std::endl;
    move(vect.x, vect.y);

    // Swaping matrixes
    swap(templateImage, frameRect);
}

void Webcam::move(int x, int y)
{
    int thresholdH = 15;
    int thresholdL = 3;
    if (thresholdL < x && x < thresholdH && thresholdL < y && y < thresholdH)
    {
        if (x > y)
            std::cout << "Droite" << std::endl;
        else
            std::cout << "Bas" << std::endl;
    }
    else if (thresholdL < x && x < thresholdH && thresholdL < -y && -y < thresholdH)
    {
        if (x > -y)
            std::cout << "Droite" << std::endl;
        else
            std::cout << "Haut" << std::endl;
    }
    else if (thresholdL < -x && -x < thresholdH && thresholdL < y && y < thresholdH)
    {
        if (-x > y)
            std::cout << "Gauche" << std::endl;
        else
            std::cout << "Bas" << std::endl;
    }
    else if (thresholdL < -x && -x < thresholdH && thresholdL < -y && -y < thresholdH)
    {
        if (x < y)
            std::cout << "Gauche" << std::endl;
        else
            std::cout << "Haut" << std::endl;
    }
    else if (-thresholdL <= x && x <= thresholdL)
    {
        if (y > thresholdL)
            std::cout << "Bas" << std::endl;
        else if (y < -thresholdL)
            std::cout << "Haut" << std::endl;
        else
            std::cout << "Neutre" << std::endl;
    }
    else if (-thresholdL <= y && y <= thresholdL)
    {
        if (x > thresholdL)
            std::cout << "Droite" << std::endl;
        else if (x < -thresholdL)
            std::cout << "Gauche" << std::endl;
        else
            std::cout << "Neutre" << std::endl;
    }
}

QImage* Webcam::getImage()
{
    // Converting to Qt image
    *img = QImage((const unsigned char*)(webcamImageRGB->data), webcamImageRGB->cols, webcamImageRGB->rows, QImage::Format_RGB888);
    return img;
}
