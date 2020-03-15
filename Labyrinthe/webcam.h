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
    VideoCapture* webcam;
    Mat* webcamImage;
    QImage* img;

public:
    Webcam();
    ~Webcam();
    void updateImage();
    QImage* getImage();
};

#endif // WEBCAM_H