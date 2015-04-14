#ifndef FILTER_H
#define FILTER_H

#include <opencv2/opencv.hpp>


using namespace cv;
class Filter
{
public:
    Filter();
    static void filterfun(cv::Mat img_src, Mat *img_lf, Mat *img_maskf);
};

#endif // FILTER_H
