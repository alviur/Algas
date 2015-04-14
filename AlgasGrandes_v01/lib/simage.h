#ifndef SIMAGE_H
#define SIMAGE_H

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>

class  Simage
{
public:
    Simage();
    ~Simage();

    static int Pixval(const cv::Mat &image, int  &inten);
    static int Pixval(const cv::Mat &image, const float umbral, int &ncambios);
    static int Pixval(const cv::Mat &image, const int umbral, int &ncambios);
    static void salt(cv::Mat& image, int n);//metodo estatico,esta presente en la ejecucion de todo el programa que agrega ruido tipo sal a una imagen en su interir usa el metodo "at" para acceder a los pixeles.
    static void salt2(cv::Mat& image, int n);//metodo estatico,esta presente en la ejecucion de todo el programa que agrega ruido tipo sal a una imagen , en su interior usa un objeto tipo "cv::Mat_ "  que tiene unos metodos extra para acceder a un pixel.
    static void colorReduce(cv::Mat &image,int div=64);
    static void whitePix(const cv::Mat &image, std::vector<double > &posicionesX, std::vector<double> &posicionesY);
    static void colorReduceEfficient(cv::Mat &image, int div=64);


};

#endif // SIMAGE_H
