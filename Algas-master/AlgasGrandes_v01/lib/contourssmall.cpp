
#include "contourssmall.h"

ContoursSmall::ContoursSmall()
{
}

/***************************************************************************************************
Funciones
Descripcion: rota imagen
***************************************************************************************************/
//correccion de la posicion

cv::Mat rotacion(cv::Mat src,double angle){

cv::Point2f src2(src.cols/2.0F, src.rows/2.0F);
cv::Mat rot_mat;


    rot_mat = getRotationMatrix2D(src2,angle, 1.0);

cv::Mat dstrot;
cv::warpAffine(src, dstrot, rot_mat, src.size(), cv::INTER_CUBIC,
               cv::BORDER_CONSTANT,
               cv::Scalar(0,0,0));//ROTACION

return dstrot;

}


/***************************************************************************************************
Funciones
Descripcion: Entrega imagen rotada
***************************************************************************************************/


cv::Mat getRotatedImage(cv::Mat src,RotatedRect rect){

        // matrices we'll use
        cv::Mat M, rotated, cropped;
        // get angle and size from the bounding box
        float angle = rect.angle;
        Size rect_size = rect.size;
        // thanks to http://felix.abecassis.me/2011/10/opencv-rotation-deskewing/
        if (rect.angle < -45.) {
            angle += 90.0;
            swap(rect_size.width, rect_size.height);
        }
        // get the rotation matrix
        M = getRotationMatrix2D(rect.center, angle, 1.0);
        // perform the affine transformation
        warpAffine(src, rotated, M, src.size(), INTER_CUBIC);
        // crop the resulting image
        getRectSubPix(rotated, rect_size, rect.center, cropped);

        return cropped;
}


/**************************************************************************************************
Funciones
Descripcion:Ordena los contornos de menor a mayor
***************************************************************************************************/
// FUNCION DE COMPARACION
bool compareContourAreas ( std::vector<cv::Point> contour1, std::vector<cv::Point> contour2 ) {
    double i = fabs( contourArea(contour1) );
    double j = fabs( contourArea(contour2) );
    return ( i < j );
}


/**************************************************************************************************
Funciones
Descripcion:Extrae Contornos pequeños
***************************************************************************************************/
vector<vector<Point> > internalContours(cv::Mat  img_src)
{

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    cv::Mat imgS,imgS2;



    cv::Mat imgSB,imgS2B,img_src2;
    img_src.copyTo(img_src2);
    vector<vector<Point> > contoursB;



        // pyrMeanShiftFiltering(img_src, img_src, 5, 40, 2);
        cvtColor(img_src,imgS2,COLOR_RGB2GRAY); // Pasar a grises

        cvtColor(img_src,imgS2B,COLOR_RGB2GRAY); // Pasar a grises
        threshold(imgS2B,imgSB,80,255,cv::THRESH_OTSU);
        imgSB=255-imgSB;
        findContours( imgSB, contoursB, hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE, Point(0, 0));




        Simage::colorReduce(imgS2,64);


        namedWindow("src Discreta",0);
        imshow("src Discreta",imgS2);

        threshold(imgS2,imgS2,80,255,cv::THRESH_OTSU);


        namedWindow("discretizada binarizada",0);
        imshow("discretizada binarizada",imgS2);


        imgS=255-imgS;
        findContours( imgS2, contours, hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE, Point(0, 0));


        for(int m=0;m<contours.size();m++)
            drawContours(img_src,contours,m,cv::Scalar(255,0,0));


        for(int m=0;m<contoursB.size();m++)
            drawContours(img_src2,contoursB,m,cv::Scalar(255,0,0));


//double pointPolygonTest(InputArray contour, Point2f pt, bool measureDist)





        namedWindow("Contornos discretizada",0);
        imshow("Contornos discretizada",img_src);

        namedWindow("Contornos",0);
        imshow("Contornos",img_src2);

        //waitKey(0);


        return contours;
}


/**************************************************************************************************
Funciones
Descripcion:guarda la imagen
***************************************************************************************************/
void saveImage(cv::Mat src,String filename,int index)
{

QString path=filename.c_str();//Qstring para manejar nombres de rutas

path.append(QString("%1").arg(index));
path= path +".png";


vector<int> compression_params;//vector con parametros de imagenes para guardar
compression_params.push_back(cv::IMWRITE_PXM_BINARY);
compression_params.push_back(9);
imwrite(path.toUtf8().constData(), src, compression_params);

}

/**************************************************************************************************
Funciones
Descripcion:Extrae Contornos grandes
***************************************************************************************************/

vector<vector<Point> > externalContours(cv::Mat  img_src)
{
    vector<vector<Point> > contours;

    cv::Mat img_srcGray;

    cv::Mat img_srcTreshCopy;
    cv::Mat img_contours;
     cv::Mat hierarchy;
     cv::Mat img_subResult;
     cv::Mat img_forSub;
     cv::Mat img_srcTresh;


     int MaxArea=0;
     int Maxindice=0;
     int checkContours=0;

    cvtColor(img_src,img_srcGray,cv::COLOR_BGR2GRAY);



    img_src.copyTo(img_contours);
    cvtColor(img_src,img_srcGray,cv::COLOR_BGR2GRAY);//cambia imagen a escala de grises
    threshold(img_srcGray,img_srcTresh,30,255,cv::THRESH_OTSU);//realiza threshold en la imagen
    img_srcTresh.copyTo(img_forSub);
    threshold(img_srcTresh,img_srcTresh,30,255,cv::THRESH_BINARY_INV);

    dilate(img_srcTresh, img_srcTresh, Mat(), Point(-1, -1), 1, 1, 1);
    cv::absdiff(img_srcTresh,img_forSub,img_subResult);

    img_subResult.copyTo(img_srcTreshCopy);//realiza una copia de img_thresh




    Scontour::GetContourHierachy(img_srcTreshCopy,contours,hierarchy,30,cv::RETR_LIST,cv::CHAIN_APPROX_NONE);//Get contours form image
    //img_contours=Scontour::drawCont(img_src,contours);//Dibuja los contornos en la imagen

    for(int i=0;i < contours.size()-1;i++)
    {
        if(contourArea(contours[i])>MaxArea)
        {

             MaxArea=contourArea(contours[i]);
             Maxindice=i;
        }
    }



    cv::drawContours(img_contours,contours,Maxindice,Scalar(255,0,0),2,8);



//Chequeo por numero de contornos que cumplen
        for(int i=0;i < contours.size()-1;i++)
        {


                if ( (int)hierarchy.at<Vec4i>(0,i)[3] != -1  &&  (int)hierarchy.at<Vec4i>(0,i)[2] != -1)
                {
                    if ( (int)hierarchy.at<Vec4i>(0,i)[3] == Maxindice &&  (int)hierarchy.at<Vec4i>(0,i)[2] != -1)
                     {

                        checkContours++;


                    }

                }
           // }



         }

 //copia de contornos que cumplen

         vector<vector<Point> > ReturnedContours(checkContours);
         checkContours=0;

        for(int i=0;i < contours.size()-1;i++)
        {


                if ( (int)hierarchy.at<Vec4i>(0,i)[3] != -1  &&  (int)hierarchy.at<Vec4i>(0,i)[2] != -1)
                {
                    if ( (int)hierarchy.at<Vec4i>(0,i)[3] == Maxindice &&  (int)hierarchy.at<Vec4i>(0,i)[2] != -1)
                     {


                        ReturnedContours[checkContours]=contours[i];
                        checkContours++;

                    }

                }
           // }



         }


        for(int k=0; k< ReturnedContours.size() -1;k++)
        {

            approxPolyDP(ReturnedContours[k],ReturnedContours[k],4,false);
            RotatedRect recRot= minAreaRect(ReturnedContours[k]);
                        
            cv::Mat Contorno,contornoGray;



           // cv::drawContours(img_contours,ReturnedContours,k,Scalar(255,0,0),2,8);

           Contorno =getRotatedImage(img_contours,recRot);
           cvtColor(Contorno,contornoGray,cv::COLOR_BGR2GRAY);



           Simage::colorReduce(contornoGray,64);

            if(Contorno.data){
            namedWindow("imagenes individuales discretizadas",0);
            imshow("imagenes individuales discretizadas",contornoGray);





            /// guarda aqui
            saveImage(Contorno,"/home/german/Desktop/DANI/Algas-master/alga",k);
            qDebug()<<"Grabe!"<<k<<ReturnedContours.size();



            namedWindow("imagenes individuales",0);
            imshow("imagenes individuales",Contorno);

            //waitKey(0);
            }



         }



        //namedWindow("Contornos grandes",0);
        imshow("Contornos grandes",img_contours);

       // waitKey(0);





return ReturnedContours;


}



/**************************************************************************************************
MAIN
Descripcion:Extrae Contornos pequeños
***************************************************************************************************/

vector<vector<vector<Point> > > ContoursSmall::contourSmallget( cv::Mat img_src, cv::Mat img_srcColor, vector<vector<Point> > &contoursBig, vector<Point> &positions){


    cv::Mat mask2,mascara4;
    cv::Mat hierarchy, img_contours,img_cotoursMask;

    erode(img_src, mask2, Mat(), Point(-1, -1),1, 1, 1);
    mascara4=img_src - mask2;

    img_srcColor.copyTo(img_cotoursMask);


    img_cotoursMask = cv::Scalar(0,0,0);
    vector<vector<Point> > contours;


    Scontour::GetContourHierachy(mascara4,contours,hierarchy,30,cv::RETR_LIST,cv::CHAIN_APPROX_NONE);//Get contours form image
    std::sort(contours.begin(), contours.end(),compareContourAreas);//ordena los contornos por area de mayor a menor
    //img_contours=Scontour::drawCont(img_src,contours);//Dibuja los contornos en la imagen



 //Calculo de tamaño promedio de contornos
    int area=0;

 if ( !contours.empty() && !hierarchy.empty()) {//validation of contour an hierarcy existence
            for(int i=0;i < contours.size()-1;i++)
            {

                       area+=contourArea(contours[i]);

             }

            area=area/(contours.size());

   }


 //Dibujo de mascaras para completar contornos

 cv::Rect img_group;
 int alga=0;

 cv::Mat img_srcColor2;
 img_srcColor.copyTo(img_srcColor2);

if ( !contours.empty() && !hierarchy.empty()) {//validation of contour an hierarcy existence
           for(int i=0;i < contours.size()-1;i++)
           {

                      //qDebug()<<contourArea(contours[i]);
                      cv::drawContours(img_cotoursMask,contours,i,Scalar(255,255,255),1,8);//Dibuja la mascara


            }

  }


///Big contours extraction

cv::Mat img_checked;

img_checked= img_srcColor -img_cotoursMask;

contoursBig=externalContours(img_checked);//get external contours


///Small contours extraction

 vector<vector<vector<Point> > > vector_algas(contoursBig.size());//, vector<vector<Point> >(1000,std::vector<Point>(1000)));/// Arreglar despues



for(int i=0;i< contoursBig.size() -1; i++)
{


   cv::Point punto(img_group.x,img_group.y);

    img_group= boundingRect(contoursBig[i]);
    positions.push_back((cv::Point)punto);
    vector_algas[i]= internalContours(img_srcColor(img_group));//Extrae Contornos pequeños y los ingresa en el vector principal
}





int k=0;




        for(int i=0;i<vector_algas.size() -1; i++ )
        {

          //qDebug()<<vector_algas[i][40][1].x;


//            cv::Mat a;

//            img_group= boundingRect(contoursBig[100]);
//            cv::drawContours(a,vector_algas[100],i,Scalar(255,0,0),2,8);

//            namedWindow("Ventana",0);
//            imshow("Ventana",a);
//            waitKey(0);
        }








    return vector_algas;

}
