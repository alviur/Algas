#include "simage.h"


Simage::Simage()
{



}

Simage::~Simage()
{

}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Encuentra la intensidad mayor en la imagen  la coloca en inten,retorna código de error.

***************************************************************************************************/


int Simage::Pixval(const cv::Mat &image, int &inten)
{

    inten=0;
    int value=0;
    if(!image.data) //comprueba si la imagen se cargo correctamente
           return 0;

    for(int i=0;i< image.size().width;i++){//hasta el ancho de la imagen
            for(int j=0;j< image.size().height;j++){//hasta el alto de la imagen
                 value=image.at<uchar>(j,i);
                 if(inten < value)inten=value;

            }
        }

    return 1;


}




/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Encuentra el numero de pixeles que superan el umbral y lo comola en el entero #cambios,
retorna código de error.

***************************************************************************************************/

int Simage::Pixval(const cv::Mat &image, const float umbral, int &ncambios)
{

    int value=0;
    if(!image.data) //comprueba si la imagen se cargo correctamente
           return 0;

    for(int i=0;i< image.size().width;i++){//hasta el ancho de la imagen
            for(int j=0;j< image.size().height;j++){//hasta el alto de la imagen
                 value=image.at<uchar>(j,i);
                 if(value > umbral)ncambios++;

            }
        }

    return 1;




}


/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Encuentra el numero de pixeles que superan el umbral y lo comola en el entero #cambios,
retorna código de error.

***************************************************************************************************/

int Simage::Pixval(const cv::Mat &image, const int umbral, int &ncambios)
{



    int value=0;
    if(!image.data) //comprueba si la imagen se cargo correctamente
           return 0;

    for(int i=0;i< image.size().width;i++){//hasta el ancho de la imagen
            for(int j=0;j< image.size().height;j++){//hasta el alto de la imagen
                 value=image.at<uchar>(j,i);
                 if(value > umbral)ncambios++;

            }
        }

    return 1;

}



/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Encuentra la intensidad mayor en la imagen  la coloca en inten,retorna código de error.

***************************************************************************************************/


void Simage::whitePix(const cv::Mat &image,std::vector<double >& posicionesX,std::vector<double> &posicionesY)
{

    int inten=0;
    int value=0;




    for(int i=0;i< image.size().width;i++){//hasta el ancho de la imagen
            for(int j=0;j< image.size().height;j++){//hasta el alto de la imagen
                 value=image.at<uchar>(j,i);
                 if(value>0)
                 {
                     posicionesX[inten] =i;
                     posicionesY[inten]=j;
                     inten++;
                 }
            }
        }



}


/***************************************************************************************************
Metodos
Autor:
Descripcion: .

***************************************************************************************************/

void Simage::salt(cv::Mat &image, int n)
{
    for(int k=0; k<n ; k++)
    {
        //rand() is the MFC random number generator
        //try qrand with Qt
        int i= rand()%image.cols;
        int j= rand()%image.rows;

        if(image.channels()==1)
        {
            //if the image is gray-level
            image.at<uchar>(j,i)=255;
        }
        else if(image.channels()==3)
        {
            //if there are 3 chanels(color image)
             image.at<cv::Vec3b>(j,i)[0]=255;
             image.at<cv::Vec3b>(j,i)[1]=255;
             image.at<cv::Vec3b>(j,i)[2]=255;
        }
    }
}

/***************************************************************************************************
Metodos
Autor:
Descripcion: Encuentra el numero de pixeles que superan el umbral y lo comola en el entero #cambios,
retorna código de error.

***************************************************************************************************/
void Simage::salt2(cv::Mat &image, int n)
{

    for(int k=0; k<n ; k++)
    {
        //rand() is the MFC random number generator
        //try qrand with Qt
        int i= rand()%image.cols;
        int j= rand()%image.rows;

        if(image.channels()==1)
        {
            cv::Mat_<uchar> im2=image;
            //if the image is gray-level
            im2(j,i)=255;
        }
        else if(image.channels()==3)
        {
            cv::Mat_<cv::Vec3b> im2=image;
            //if there are 3 chanels(color image)
            im2(j,i)[0]=255;
            im2(j,i)[1]=255;
            im2(j,i)[2]=255;
        }
    }
}

/***************************************************************************************************
Metodos
Autor:
Descripcion:

***************************************************************************************************/
void Simage::colorReduce(cv::Mat &image, int div)
{
    int nl=image.rows;//numero de lineas
    int nc=image.cols*image.channels();//numero total de columnas = nc* numero de canales

    for(int j=0; j<nl ; j++)
    {
        uchar* data= image.ptr<uchar>(j);
        for(int i=0 ; i<nc ; i++)
        {
            data[i]= data[i]/div*div + div/2;
        }
    }
}

/***************************************************************************************************
Metodos
Autor:
Descripcion:

***************************************************************************************************/
void Simage::colorReduceEfficient(cv::Mat &image, int div)//para imagenes que no estan rellenas del todo
{
    int nl=image.rows;
    int nc=image.cols;

    if(image.isContinuous())
    {
        //then no padded pixels
        nc=nc*nl;
        nl=1;//it is now a 1D array
    }
    //this loop is executed only once in case of a continuous image
    for(int j=0; j<nl; j++)
    {
        uchar* data= image.ptr<uchar>(j);
        for(int i=0; i<nc; i++)
        {
            //process each pixel
            data[i]=data[i]/div*div +div/2;
            //end pixel processing
        }//end for
    }//end for

}

