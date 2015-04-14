#include "contornoalgas.h"
#include "ui_contornoalgas.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include "checkup.h"


using namespace std;
using namespace cv;


ContornoALgas::ContornoALgas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContornoALgas)
{
    ui->setupUi(this);

}

ContornoALgas::~ContornoALgas()
{
    delete ui;
}

void ContornoALgas::on_pushButton_released()
{


    //ABRE VENTANA CARGA ARCHIVO
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Video"), ".",
    tr("Video Files(*.avi *.png *.jpg *.jpeg *.bmp *.tif)"));
    inputName=fileName.toStdString().c_str();
    img_src=imread(inputName);

    cv::Mat equalizado;


    cvtColor(img_src,img_srcRGB,cv::COLOR_BGR2RGB);//cambia de BRG a RGB

    //MUESTRA IMAGEN EN INTERFAZ
    QImage img= QImage((const unsigned char*)(img_srcRGB.data),img_srcRGB.cols,img_srcRGB.rows,img_srcRGB.step,QImage::Format_RGB888);//extrae imagen
    ui->label->setPixmap(QPixmap::fromImage(img));//muestra en label el video


    ////////////////////////




        // LLamado a la función
        //__ Declaracion de variables
        Mat imgS;
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        cvtColor(img_src,img_src,COLOR_RGB2GRAY); // Pasar a grises
        threshold(img_src,imgS,80,255,CV_THRESH_OTSU);
        imgS=255-imgS;

        findContours( imgS, contours, hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


        // Mostrar resultado del llamado
        Mat dst = Mat::zeros(img_src.rows, img_src.cols, CV_8UC3);
        for( int idx = 1; idx< contours.size(); idx++ )
        {
             Scalar color( rand()&255, rand()&255, rand()&255 );
             drawContours( dst, contours, idx, color, 1);

        }
        namedWindow( "Contornos Pequenos", 0);
        imshow( "Contornos Pequenos", dst );

        //Llamado a checkup
        std::vector<int> angle(10,30);
        std::vector<int>posiciones;
        vector<vector<Point> > contours_out;

       angle[2]=90;
       angle[4]=90;
       angle[6]=90;

        checkup::checkupfc(contours, angle,&posiciones,  &contours_out );

    }





void ContornoALgas::on_pushButton_2_released()
{

}
