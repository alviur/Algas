/**************************************************************************************************
Función: Esta clase encuentra los contornos pequeños de la imagen con algas.
Recibe los contornos de algas mayores. Retorna un vector de contornos.

Autor: Alexander Gómez - Germán Díez - Daniela Sánchez
***************************************************************************************************/

#ifndef CONTOURSSMALL_H
#define CONTOURSSMALL_H

#include <opencv2/opencv.hpp>
#include <qdebug.h>
#include "scontour.h"


using namespace cv;

class ContoursSmall
{
private:

public:
    ContoursSmall();
    static vector<vector<vector<Point> > > contourSmallget(Mat img_src, Mat img_srcColor, vector<vector<Point> > &contoursBig);

};

#endif // CONTOURSSMALL_H
