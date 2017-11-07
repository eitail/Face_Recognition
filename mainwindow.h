/*-------------------------------------------------
*
* Project created by QtCreator 2017-11-03T01:20:33
*
* author:Leo
*
* url:http://www.linuxkiss.com
*
-------------------------------------------------*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cv.h>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        void        Face_recognition();
        void        Pic2Gray(Mat camerFrame,Mat &gray);

    private:
        Ui::MainWindow *ui;
        string face_cascade_name;
        CascadeClassifier face_cascade;

    private slots:
        void        openCamara();

};

#endif // MAINWINDOW_H
