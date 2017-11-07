#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //****** 这个路径自行修改 ******
    face_cascade_name = "../opencvDemo/haarcascade_frontalface_alt2.xml";
    connect(ui->open, SIGNAL(clicked()), this, SLOT(openCamara()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * @brief 打开本机摄像头，开始人脸识别
 *
 */
void MainWindow::openCamara()
{
    /*
     * 人脸检测器（快速的Haar）:haarcascade_frontalface_alt2.xml,需要先加载这个，在进行人脸识别
     */
    qDebug() << "openCamara ... ";
    if (!face_cascade.load(face_cascade_name)){
        qDebug() << "级联分类器错误，可能未找到文件，拷贝该文件到工程目录下！ ";
        return;
    }

      Face_recognition();
}



void MainWindow::Face_recognition()
{
    //打开摄像头
    VideoCapture camera(0);
    while (true)
    {
        Mat camerFrame;
        camera >> camerFrame;
        if (camerFrame.empty())
        {
            std::cerr << "无法获取摄像头图像" << std::endl;
            getchar();
            exit(1);
        }
        Mat displayedFrame(camerFrame.size(),CV_8UC3);


        //人脸检测只试用于灰度图像
        Mat gray;
        Pic2Gray(camerFrame, gray);

        //直方图均匀化(改善图像的对比度和亮度)
        Mat equalizedImg;
        equalizeHist(gray, equalizedImg);
       // int flags = CASCADE_FIND_BIGGEST_OBJECT|CASCADE_DO_ROUGH_SEARCH;    //只检测脸最大的人
        int flags = CASCADE_SCALE_IMAGE;  //检测多个人
        Size minFeatureSize(30, 30);
        float searchScaleFactor = 1.1f;
        int minNeighbors = 4;
        std::vector<Rect> faces;

        //选择最终的人脸分类器后，若想在这个基础上继续优化，那就试试这个detectMultiScale函数.
        face_cascade.detectMultiScale(equalizedImg, faces, searchScaleFactor, minNeighbors, flags, minFeatureSize);

        //画矩形框
        cv::Mat face;
        cv::Point text_lb;
        for (size_t i = 0; i < faces.size(); i++)
        {
            if (faces[i].height > 0 && faces[i].width > 0)
            {
                face = gray(faces[i]);
                text_lb = cv::Point(faces[i].x, faces[i].y);
                cv::rectangle(equalizedImg, faces[i], cv::Scalar(255, 0, 0), 1, 8, 0);
                cv::rectangle(gray, faces[i], cv::Scalar(255, 0, 0), 1, 8, 0);
                cv::rectangle(camerFrame, faces[i], cv::Scalar(255, 0, 0), 1, 8, 0);
                qDebug() << "这是个脸";
            }
        }


        imshow("直方图均匀化", equalizedImg);
        imshow("灰度化", gray);
        imshow("原图", camerFrame);

        waitKey(20);
    }

}

void MainWindow::Pic2Gray(Mat camerFrame,Mat &gray)
{
    //普通台式机3通道BGR,移动设备为4通道
    if (camerFrame.channels() == 3)
    {
        cvtColor(camerFrame, gray, CV_BGR2GRAY);
    }
    else if (camerFrame.channels() == 4)
    {
        cvtColor(camerFrame, gray, CV_BGRA2GRAY);
    }
    else
        gray = camerFrame;
}


