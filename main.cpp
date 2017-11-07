#include "mainwindow.h"
#include <QApplication>

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//using namespace cv;

int main(int argc, char *argv[])
{

//    IplImage *img = 0;
//    img = cvLoadImage("/root/Desktop/h3.jpg",-1);    //tong.bmp在所建工程的目录下
//    cvNamedWindow("tong", 1);
//    cvShowImage("tong", img);
//    cvWaitKey(0);
//    return 0;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();


}

