#ifndef CLASECUADRICULAV1_H
#define CLASECUADRICULAV1_H
#include <iostream>

#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class  Clasecuadriculav1
{

public:
    Clasecuadriculav1();
    std::vector<cv::Point> v;//
    void lattice(cv::Mat img_line);
};

#endif // CLASECUADRICULAV1_H
