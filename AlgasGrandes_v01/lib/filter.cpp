#include "filter.h"

Filter::Filter()
{
}

void Filter::filterfun(cv::Mat img_src, cv::Mat * img_lf,  cv::Mat * img_maskf){
    // Variables Auxiliares
    int smallest_area=1000000;
    int largest_area=0,areas_mayores[100]={0}, areas_menores[100]={0};
    int total=0,i=0,o=0,suma=0,sumam=0;
    double media=0,prom_areas_mayores=0;//prom_areas_menores=0;

    // Imagenes Auxiliares
    Mat img_algas,img_res,img_mask,dst,cdst;//imagenes auxiliares
    Mat img_src2=img_src.clone();
    Mat img_src3=img_src.clone();
    Mat img_src4=img_src.clone();


    for(int i=19;i<=69;i=i+2){ // for para variar size del filtro
           GaussianBlur(img_src2, img_src2, Size(i,i-2), 0, 0);// Aplicar un filtro pasabajas
           img_res=50*(img_src-img_src2); // Restar funcion original con la suavizada

           Mat element = getStructuringElement( MORPH_ELLIPSE,Size( 1, 1 ),Point( 0,0 ) );//elemento estructurante dilate
           erode( img_res, img_res, element);//dilatacion de segmentacion conseguida
          // QImage qimgPro((uchar*)img_res.data, img_res.cols, img_res.rows, img_res.step, QImage::Format_RGB888);
          // ui->label_2->setPixmap(QPixmap::fromImage(qimgPro));
           //ui->label_2->setScaledContents(true);
          // ui->label_2->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    }

    img_mask=50*(img_src-img_src2);

    dst=img_mask.clone();
    Mat img_algasclean= Mat::zeros(dst.size(),dst.type());

    //--- Rellenar Algas--------------------------------------------
    img_mask=255-img_mask;
    cv::Mat edgesNeg = img_mask.clone();
    cv::floodFill(edgesNeg, cv::Point(0,0), Scalar(255,255,255));
    bitwise_not(edgesNeg, edgesNeg);
    img_mask = (edgesNeg | img_mask);

    cv::Mat bwalgas= img_mask.clone(); // Imagen para la deteccion de cuadricula

    Mat destino = Mat::zeros(img_mask.rows, img_mask.cols, CV_8UC1);
    img_mask=img_mask >1;

    std::vector<std::vector<Point> > contours;
     std::vector<Vec4i> hierarchy;

    cvtColor(img_mask,img_mask,cv::COLOR_BGR2GRAY);

   // namedWindow("Rellenas",0);
   // imshow("Rellenas",img_mask);
    img_mask.copyTo((*img_maskf));

    findContours( img_mask, contours, hierarchy,cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0,0));

    for (int j=0;j>=0;j=hierarchy[j][0])
    {
         Scalar color(rand()&255, rand()&255, rand()&255); // RGB aleatorio
         drawContours(destino,contours,j,color,cv::FILLED);
    }

    Mat destino_eliminados = Mat::zeros(img_mask.rows, img_mask.cols, CV_8UC1);


    for (size_t sizet = 0; sizet<contours.size(); sizet++){
         double a=contourArea(contours[sizet],false); // Retorna el valor absoluto del area si el seg argumento da false
         total=a+total;
         if(a>largest_area){
             largest_area=a;
             i++;
                areas_mayores[i]=largest_area;
         }
         else{
             if((a<smallest_area) & (a!=0)){
                smallest_area = a;
                o++;
                areas_menores[o]=smallest_area;
             }
         }
     }
     media=total/contours.size();

     for(int e=0;e<=i;e++)
           suma=suma+areas_mayores[e];
     for(int e=0;e<=o;e++)
           sumam=sumam+areas_menores[e];
     prom_areas_mayores=suma/i;



     for (size_t sizet = 0; sizet<contours.size(); sizet++){
         double a=contourArea(contours[sizet],false);
         if (a >= media-100 && a< areas_mayores[i]-prom_areas_mayores+100) // Umbral 350-200
            drawContours(destino_eliminados,contours,sizet,255,cv::FILLED);//,8,hierarchy);
     }
     cvtColor(destino_eliminados,destino_eliminados,cv::COLOR_GRAY2BGR);


     // Algas originales sin ruido

     for(int i=0; i<img_src.rows;i++){
        for(int j=0;j<img_src.cols;j++){
               for(int c=0; c<3;c++){
                   if(destino_eliminados.at<Vec3b>(i,j)[c]==255)
                       img_algasclean.at<Vec3b>(i,j)[c]=dst.at<Vec3b>(i,j)[c];
                   else
                       img_algasclean.at<Vec3b>(i,j)[c]=255;
               }
           }
       }


     Mat img_line=Mat::zeros(img_res.size(),img_res.type());
     Mat img_line2=Mat::zeros(img_res.size(),img_res.type());
     GaussianBlur(img_src4, img_src4, Size(19,17), 0, 0);// Aplicar un filtro pasabajas
     img_res=50*(img_src-img_src4);
     Mat se = getStructuringElement( MORPH_ELLIPSE,Size( 17, 17),Point( -1,-1 ) );//elemento estructurante dilate
     dilate( bwalgas, bwalgas, se);//dilatacion de segmentacion conseguida


     for(int i=0; i<img_src4.rows;i++){
         for(int j=0;j<img_src4.cols;j++){
             for(int c=0; c<3;c++){
                 if(bwalgas.at<Vec3b>(i,j)[1]==255 && img_res.at<Vec3b>(i,j)[c]==255){
                    img_line.at<Vec3b>(i,j)[c]=0;
                 }
                 else
                    img_line.at<Vec3b>(i,j)[c]=img_res.at<Vec3b>(i,j)[c];
               }
            }
     }

     cvtColor(img_line,img_line,cv::COLOR_RGB2GRAY);
     Mat se2 = getStructuringElement( MORPH_ELLIPSE,Size( 3, 3),Point( -1,-1 ) );
     erode( img_line, img_line, se2);
     medianBlur(img_line,img_line,3);

     //namedWindow("Algas negras",0);
     //imshow("Algas negras",img_line);
     img_line.copyTo((*img_lf));

}
