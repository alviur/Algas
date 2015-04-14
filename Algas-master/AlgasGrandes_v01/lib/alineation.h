#ifndef ALINEATION_H
#define ALINEATION_H
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <QString>
#include <QDebug>
#include "fourier.h"
#include "simage.h"
#include "linearregretion.h"



class Alineation
{
public:
    Alineation();
    ~Alineation();

    static int fourierAlienation(std::vector<std::vector<cv::Point> >  contours,int indice,cv::Mat img);




};

#endif // ALINEATION_H
