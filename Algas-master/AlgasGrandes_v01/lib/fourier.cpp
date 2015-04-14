#include "fourier.h"

Fourier::Fourier()
{
}


Fourier::~Fourier()
{
}


/**************************************************************************************************
Funciones
Autor: Alexander Gómez villa - German Diez Valencia - Sebastian Guzman Obando
Descripcion:Optiene transformada de fourier de la imagen
***************************************************************************************************/
Mat Fourier::getFourier(Mat img)
{

    //Mat img = imread("/home/lex/Cv/Images/Segmentacion Horizontal_screenshot_07.01.2014.png", CV_LOAD_IMAGE_GRAYSCALE);

    //////////////////////////////////////////////////////////
    /// \brief imgS
    ///
    ///
    ///
       cv::Mat imgS;


       cv::Sobel(img,imgS,CV_8U,1,0);

       threshold(imgS,imgS,100,255,0);



   //////////////////////////////////////////////////////////

       int M = getOptimalDFTSize( imgS.rows );
       int N = getOptimalDFTSize( imgS.cols );
       Mat padded;
       copyMakeBorder(imgS, padded, 0, M - imgS.rows, 0, N - imgS.cols, BORDER_CONSTANT, Scalar::all(0));

       Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
       Mat complexImg;
       merge(planes, 2, complexImg);

       dft(complexImg, complexImg);

       // compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))
       split(complexImg, planes);
       magnitude(planes[0], planes[1], planes[0]);
       Mat mag = planes[0];
       mag += Scalar::all(1);


       log(mag, mag);



       // crop the spectrum, if it has an odd number of rows or columns
       mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));



       int cx = mag.cols/2;
       int cy = mag.rows/2;

       // rearrange the quadrants of Fourier image
       // so that the origin is at the image center
       Mat tmp;
       Mat q0(mag, Rect(0, 0, cx, cy));
       Mat q1(mag, Rect(cx, 0, cx, cy));
       Mat q2(mag, Rect(0, cy, cx, cy));
       Mat q3(mag, Rect(cx, cy, cx, cy));

       q0.copyTo(tmp);
       q3.copyTo(q0);
       tmp.copyTo(q3);

       q1.copyTo(tmp);
       q2.copyTo(q1);
       tmp.copyTo(q2);




  cv::Mat mag2;

       normalize(mag, mag2, 0, 1,cv::NORM_MINMAX);///<<<----------error

       qDebug()<<"LLegue FOurier";


       cv::medianBlur(mag2,mag2,5);//elimina ruido sal y pimienta

       threshold(mag2,mag2,0.7,255,0);




   //////////////////////////////

       cv::Mat componentes;
       mag2.copyTo(componentes);

   //////////////////////////////

      return mag2;

}
