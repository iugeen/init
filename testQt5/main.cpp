//#include "mainwindow.h"
//#include <QApplication>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();

    //read an image
     cv::Mat image = cv::imread("/home/imocanu/Downloads/opencv-2.4.8/samples/cpp/fruits.jpg");
     //check an image
     if(image.empty()){
         std::cout << "!!!Failed imread(): image not found" << std::endl;
         return 1;
     }
     //create image window name “My image”
     cv::namedWindow("My image", CV_WINDOW_AUTOSIZE);
     //show the image on window
     cv::imshow("My image",image);
     //wait key for 5000ms
     cv::waitKey(5000);
}
