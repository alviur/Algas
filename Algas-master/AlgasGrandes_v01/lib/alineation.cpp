#include "alineation.h"

Alineation::Alineation()
{
}




/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - German Diez Valencia
Descripcion: Alinea las letras verticalmente
***************************************************************************************************/
int fourierAlienation(std::vector<std::vector<cv::Point> >  contours,int indice,cv::Mat img)
{

    img.setTo(cv::Scalar(0,0,0));

    qDebug()<<"Tamaño"<<contours.size();
    cv::drawContours(img,contours,indice,Scalar(255,255,255),2,8);

    Fourier f;

    cv::Mat imgF;//imagen en frecuencia
    cv::Mat imgRotacion;//imagen para rotacion

    int tamanoVect=0;//numero de componentes frecuencia

    imgF=f.getFourier(img);//obtiene transformada de fourier


    //conversion imagen flotante a entera
    double minVal, maxVal;
    minMaxLoc(imgF, &minVal, &maxVal); //find minimum and maximum intensities
    imgF.convertTo(imgF, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));

    int a=0;

    Simage::Pixval(imgF,a,tamanoVect);//obtengo numero de componentes en frecuencia
    vector<double> posicionesX(tamanoVect);//posiciones X componentes frecuencia
    vector<double> posicionesY(tamanoVect);//posiciones Y componenetes frecuencia
    Simage::whitePix(imgF,posicionesX,posicionesY);//obtiene posiciones componentes frecuencia


    //Dibujo linea
    double* x = &posicionesX[0];
    double* y = &posicionesY[0];
     LinearRegression lr(x, y,tamanoVect);  // create with two arrays


      qDebug()<<(imgF.cols-1)*lr.b + lr.a;
      qDebug()<<(1)*lr.b + lr.a;


      line(imgF,Point2f (1,(1)*lr.b + lr.a ), Point2f (imgF.cols-1,(imgF.cols-1)*lr.b + lr.a ), Scalar(255,255,255),1);



      int angle=(atan(lr.b))*180/2*3.14;


      return angle;


}
