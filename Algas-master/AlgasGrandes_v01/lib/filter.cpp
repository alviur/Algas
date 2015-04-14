#include "filter.h"

Filter::Filter()
{
}

void color_reduce(cv::Mat &input, cv::Mat &output, size_t div)
{
    if(input.data != output.data){
        output.create(input.size(), input.type());
    }

    uchar buffer[256];
    for(size_t i = 0; i != 256; ++i){
        buffer[i] = i / div * div + div / 2;
    }
    cv::Mat table(1, 256, CV_8U, buffer, sizeof(buffer));
    cv::LUT(input, table, output);
}

void Filter::filterfun(cv::Mat img_src, cv::Mat * img_lf,  cv::Mat * img_maskf){

    /* Obtener imagen con solo algas.
     1.	Ajuste del contraste de la imagen
     2.	Conversion a grises.
     3.	Posterizacion con n=3
     4.	Obtener mascara binaria de las algas.
     */

  //  cv::Size GridSize;
    Mat img_linea;
    Mat img_gris;
    Mat img_soloalgas;
    Mat img_maskalgas;
    Mat img_srcProcessed;
    int clipLimit=220;

    cvtColor(img_src,img_gris,cv::COLOR_RGB2GRAY);
    img_linea=img_gris.clone();

    color_reduce(img_linea, img_soloalgas, 128);
    threshold(img_soloalgas,img_maskalgas,80,255,cv::THRESH_OTSU);

    img_maskalgas=255-img_maskalgas;
   // namedWindow("Solo Algas",0);
   // imshow("Solo Algas",img_maskalgas);
    img_maskalgas.copyTo((*img_maskf));

    //____________________________________________________________________________
    /*
         Obtener imagen con solo cuadricula
           1.	Convertir a grises
           2.	Aplicar CLAHE no me acuerdo con q parámetros…los finales quedaron en el pc de German.
    */


    cvtColor(img_src,img_gris,cv::COLOR_RGB2GRAY);

    //____________ Clahe ___________________
    Ptr<cv::CLAHE> clahe=cv::createCLAHE();
    clahe->setClipLimit(clipLimit);
    clahe->apply(img_gris,img_srcProcessed);


    Mat se = getStructuringElement( MORPH_ELLIPSE,Size( 10, 10),Point( -1,-1 ) );//elemento estructurante dilate
    dilate( img_maskalgas, img_maskalgas, se);//dilatacion de segmentacion conseguida
    Mat img_resta;
    img_resta=img_srcProcessed-img_maskalgas;
    threshold(img_resta,img_resta,220,255,cv::THRESH_BINARY);
    //namedWindow("restaB",0);
    //imshow("restaB",img_resta);

    Mat se2 = getStructuringElement( MORPH_RECT,Size( 2,2),Point( -1,-1 ) );//elemento estructurante dilate
    erode( img_resta, img_resta, se2);//dilatacion de segmentacion conseguida
    img_resta.copyTo((*img_lf));


}
