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


class Webcam
{
    int frameWidth=320;
    int frameHeight=240;
    int subImageWidth=100;
    int subImageHeight=100;
    int templateWidth=25;
    int templateHeight=25;
    cv::Rect* workingRect = new cv::Rect((frameWidth-subImageWidth)/2,frameHeight/2-subImageHeight/2,subImageWidth,subImageHeight);
    cv::Rect* templateRect = new cv::Rect((workingRect->width-templateWidth)/2,(workingRect->height-templateHeight)/2,templateWidth,templateHeight);
    cv::Point* workingCenter = new cv::Point(workingRect->x+subImageWidth/2,workingRect->y+subImageHeight/2);
    cv::Mat* initialFrame = new cv::Mat();
    cv::Mat* initialFrameRect = new cv::Mat();
    cv::Mat* resultMatchTemplateImage = new cv::Mat();

    cv::VideoCapture* webcam;
    cv::Mat* webcamImage = new cv::Mat();
    cv::Mat* webcamImageRGB = new cv::Mat();
    cv::Mat* grayWebcamImage = new cv::Mat();
    QImage* img = new QImage();
    cv::CascadeClassifier* faceCascadeClassifier = new cv::CascadeClassifier();

public:
    Webcam();
    ~Webcam();
    void initializeMotionDetection();
    void updateImage();
    void detectFaces();
    int detectMotion();
    int move(int x, int y);
    QImage* getImage();
};

#endif // WEBCAM_H
