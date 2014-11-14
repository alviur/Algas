#ifndef CONTORNOALGAS_H
#define CONTORNOALGAS_H


#include <QMainWindow>
#include "scontour.h"
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <QString>
#include <QDebug>
#include<QFileDialog>
#include "init_vector.h"
#include "checkup.h"

namespace Ui {
class ContornoALgas;
}

class ContornoALgas : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContornoALgas(QWidget *parent = 0);
    ~ContornoALgas();

    //images
   cv::Mat img_src;
   cv::Mat img_srcGray;
   cv::Mat img_srcRGB;
   cv::Mat img_srcTresh;
   cv::Mat img_muestra;


   cv::Mat img_ThreshOtsu;

   //PATHS
   string inputName;



   //contours
   std::vector<std::vector<cv::Point> > contours;
   std::vector<std::vector<cv::Point> > contoursMuestra;
   std::vector<cv::Point> contMuestra;


   //contadores
   int  int_one;
   int  int_two;
   int  int_three;
   int  int_four;
   int  int_five;
   int  int_six;
   int  int_seven;



private slots:
   void on_pushButton_released();

   void on_pushButton_2_released();

private:
    Ui::ContornoALgas *ui;
};

#endif // CONTORNOALGAS_H
