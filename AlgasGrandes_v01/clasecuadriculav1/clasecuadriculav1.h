#ifndef CLASECUADRICULAV1_H
#define CLASECUADRICULAV1_H

#include "clasecuadriculav1_global.h"
#include <opencv2/opencv.hpp>
class CLASECUADRICULAV1SHARED_EXPORT Clasecuadriculav1
{

public:
    Clasecuadriculav1();
    std::vector<cv::Point> v;//
    void lattice(cv::Mat img_line);
};

#endif // CLASECUADRICULAV1_H
