#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
    cout<<"OpenCV version: "<<CV_VERSION<<endl;
    Mat image=imread("../TestOpenCV/lena.jpg");
    namedWindow("My Image");
    imshow("My Image",image);
    waitKey(0);


    return 0;
}
