/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - German Diez Valencia
Descripcion:
***************************************************************************************************/


#ifndef ALGAS_H
#define ALGAS_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <QString>
#include <QDebug>
#include<QFileDialog>
#include"lib/fourier.h"
#include"lib/linearregretion.h"
#include"lib/simage.h"
#include "lib/contourssmall.h"
#include "lib/alineation.h"
#include "lib/filter.h"
#include "lib/clasecuadriculav1.h"
#include "lib/checkup.h"


using namespace cv;
using namespace std;

namespace Ui {
class Algas;
}

class Algas : public QMainWindow
{
    Q_OBJECT

public:
    explicit Algas(QWidget *parent = 0);
    ~Algas();

    //images
    cv::Mat img_src;//source image
    cv::Mat img_line;//image for lattice
    cv::Mat img_mask;//image for contours

    //PATHS
    string inputName;//path to image


    //Objects
     Clasecuadriculav1 lattice1;


    //

public slots:




private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

private:
    Ui::Algas *ui;
};

#endif // ALGAS_H
