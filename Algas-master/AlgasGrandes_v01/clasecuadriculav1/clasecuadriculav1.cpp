#include "clasecuadriculav1.h"


Clasecuadriculav1::Clasecuadriculav1()
{
}

void Clasecuadriculav1::lattice(cv::Mat img_line)
{

    int value=0;
    double prom_vert=0, prom_hor=0;
    int suma_vert=0, suma_hor=0;

    vector<double> V_vectIntegral(img_line.size().width);

    // Suma en X
     for(int i=0;i< img_line.size().width;i++){//hasta el ancho de la imagen
         for(int j=0;j< img_line.size().height;j++){//hasta el alto de la imagen
                value+=img_line.at<uchar>(j,i);
           }
        V_vectIntegral[i]=value;
        suma_vert=suma_vert+value/255;
        value=0;
     }
     prom_vert=suma_vert/ img_line.size().width;

     // Mostrar resultados
     vector<double> enx;
     vector<double> eny;
     Mat Proy=Mat::zeros(img_line.size(),img_line.type());

     enx=V_vectIntegral;

     for(int aux1=0;aux1<img_line.cols;aux1++)
     {
//             cout<< "---------en x-------" << enx[aux1]/255 << endl;
         if(enx[aux1]/255 > prom_vert+20)
         {
            for(int aux11=0;aux11<img_line.rows;aux11++)
            {
                Proy.at<uchar>(aux11,aux1)=255;
            }

         }
     }


     //_______________ Lineas Horizontales
     value=0;
     vector<double> V_vectIntegralh(img_line.size().height);

     // Suma en Y
      for(int i=0;i< img_line.size().height;i++){//hasta el ancho de la imagen
          for(int j=0;j< img_line.size().width;j++){//hasta el alto de la imagen
                 value+=img_line.at<uchar>(i,j);
            }
         V_vectIntegralh[i]=value;
         suma_hor=suma_hor+value/255;
         value=0;

      }
      prom_hor=suma_hor/ img_line.size().height;


      // Mostrar resultados

      Mat Proyh=Mat::zeros(img_line.size(),img_line.type());

      eny=V_vectIntegralh;
     // value=max(eny);

      for(int aux2=0;aux2<img_line.rows;aux2++)
      {
//            cout<< "---------en y-------" << enx[aux2]/255 << endl;
          if(eny[aux2]/255 > prom_hor+20)
          {
             for(int aux22=0;aux22<img_line.cols;aux22++)
             {
                 Proyh.at<uchar>(aux2,aux22)=255;

             }
          }
      }


      cv::morphologyEx(Proyh,Proyh, MORPH_CLOSE ,cv::getStructuringElement(cv::MORPH_RECT,cv::Size(1,15)));
      for(int iterax=0;iterax<2;iterax++)
      {
          cv::morphologyEx(Proyh,Proyh, MORPH_ERODE ,cv::getStructuringElement(cv::MORPH_RECT,cv::Size(1,15)));//*/

      }

      cv::morphologyEx(Proy,Proy, MORPH_CLOSE ,cv::getStructuringElement(cv::MORPH_RECT,cv::Size(15,1)));
      for(int iteray=0;iteray<2;iteray++)
      {
          cv::morphologyEx(Proy,Proy, MORPH_ERODE ,cv::getStructuringElement(cv::MORPH_RECT,cv::Size(15,1)));//*/

      }
      Mat ProyFinal; // prueba
      ProyFinal=Proy+Proyh;


      //-------------------------------posiciones de las lineas gruesas----------------------------------------------

      // Integrales de proyeccion

      //__________ Lineas Verticales


     // vector<double>


      int p=0;
      int iant=0;
      int jant=0;
      for(int i=0; i<img_line.size().height;i++)
      {
        for(int j=0; j<img_line.size().width;j++)
        {
            if(Proyh.at<uchar>(i,j)==255 && Proy.at<uchar>(i,j)==255)
            {
                if(i-iant>100 || j-jant>100)
                {

                  v.push_back(cv::Point(i,j));
                  p++;
                  iant=i;
                  jant=j;
                }


           }
        }
    }
}
