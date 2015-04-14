#ifndef FOURIER_H
#define FOURIER_H

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <qdebug.h>

//namespace
using namespace cv;
using namespace std;



class Fourier
{
public:
    Fourier();
    ~Fourier();


    cv::Mat getFourier(cv::Mat input);

};

#endif // FOURIER_H
