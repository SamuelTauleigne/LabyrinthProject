/*
 * Class Webcam
 *
 * Author = Samuel Tauleigne
 *
 * This Class Webcam manages the webcam : saving images, processing images, etc.
 */

#ifndef WEBCAM_H
#define WEBCAM_H

#include <QWidget>
#include <QLabel>
#include "opencv2/opencv.hpp"
using namespace cv;


class Webcam
{
    int frameWidth=320;
    int frameHeight=240;
    int subImageWidth=100;
    int subImageHeight=100;
    int templateWidth=25;
    int templateHeight=25;
    Rect* workingRect = new Rect((frameWidth-subImageWidth)/2,frameHeight/2-subImageHeight/2,subImageWidth,subImageHeight);
    Rect* templateRect = new Rect((workingRect->width-templateWidth)/2,(workingRect->height-templateHeight)/2,templateWidth,templateHeight);
    Point* workingCenter = new Point(workingRect->x+subImageWidth/2,workingRect->y+subImageHeight/2);
    Mat* initialFrame = new Mat();
    Mat* initialFrameRect = new Mat();
    Mat* resultMatchTemplateImage = new Mat();

    VideoCapture* webcam;
    Mat* webcamImage = new Mat();
    Mat* webcamImageRGB = new Mat();
    Mat* grayWebcamImage = new Mat();
    QImage* img = new QImage();
    CascadeClassifier* faceCascadeClassifier = new CascadeClassifier();

public:
    Webcam();
    ~Webcam();
    void initializeMotionDetection();
    void updateImage();
    void detectFaces();
    void detectMotion();
    QImage* getImage();
};

#endif // WEBCAM_H
