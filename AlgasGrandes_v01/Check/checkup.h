#ifndef CHECKUP_H
#define CHECKUP_H

#include <opencv2/opencv.hpp>
#include <qdebug.h>
#include <stdio.h>
#include <QString>
#include "contornoalgas.h"

#include <sstream>
#include <string>
#include<QFileDialog>

using namespace cv;
using namespace std;

class checkup
{

public:
    checkup();
   static void checkupfc(vector<vector<Point> > contours_in, std::vector<int>angulo, std::vector<int> *posiciones, vector<vector<Point> > *contours_out );

};

#endif // CHECKUP_H
