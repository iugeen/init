#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "stereocamera.h"
#include "stereovision.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void trace(QString str);
    Ui::MainWindow *ui;

private:
    StereoCamera camera;
    StereoVision* vision;
    QTimer timer;
    int sampleTimeout;
    CvMat* imageRectifiedPair;

    void displayOutput();
    void stereoVisionTest(QString image_path,int cornersX,int cornersY);

private slots:
//    void on_pushButtonSave_clicked();
//    void on_pushButtonLoad_clicked();
    void on_pushButtonCalibrate_clicked();
    void timeout();
};

#endif // MAINWINDOW_H
