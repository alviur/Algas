#include "algas.h"
#include "ui_algas.h"

Algas::Algas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Algas)
{
    ui->setupUi(this);
    img_line=Mat::zeros(img_src.size(),CV_8UC1);
    img_mask=Mat::zeros(img_src.size(),CV_8UC1);

}

Algas::~Algas()
{
    delete ui;
}





void Algas::on_pushButton_released()
{
    //ABRE VENTANA CARGA ARCHIVO
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Video"), ".",
    tr("Video Files(*.png *.jpg *.jpeg *.bmp *.tif)"));
    inputName=fileName.toStdString().c_str();
    img_src=imread(inputName);

    //MUESTRA IMAGEN EN INTERFAZ
    QImage img= QImage((const unsigned char*)(img_src.data),img_src.cols,img_src.rows,img_src.step,QImage::Format_RGB888);//extrae imagen
    ui->label->setPixmap(QPixmap::fromImage(img));//muestra en label el video

}




void Algas::on_pushButton_2_released()//process button
{


    ///Filter image
    Filter::filterfun(img_src,&img_line,&img_mask);//Extract background and clean image

//    namedWindow("Img Line",0);
//    imshow("Img Line",img_line);

//    namedWindow("Patata",0);
//    imshow("Patata",img_mask);



    ///Get lattice from image
    lattice1.lattice(img_line);
    qDebug()<<"Lattice listo";
   // cout<<lattice1.v<<endl;

    vector<vector<vector<Point> > > vector1;


    vector<vector<Point> > contoursBig;
    vector<Point>  positions;
    vector<vector<Point> > contoursBig2;
    vector1=ContoursSmall::contourSmallget(img_mask, img_src,contoursBig,positions);

    for(int a=0; a< positions.size();a++)
        qDebug()<<positions[a].x<<positions[a].y;


    // vector<vector<Point> > ContoursSmall::contourSmallget(vector<vector<Point> > contornos, cv::Mat img_src)


    ///Main cycle

    for(int i=0;i< vector1.size() -1;i++)
    {

        if(vector1[i].size()>0){


        qDebug()<<"Numero de contornos grandes" <<vector1.size() -1;


        qDebug()<<"Contorno grande: "<<i<<" "<<vector1[i].size();




        std::vector<int> angle2;
        std::vector<int> posiciones;
        vector<vector<Point> > contours_out;
        std::vector<int> angle(vector1[i].size());


       // qDebug()<<"Tamaño angle"<<angle.size();/////////////////////<------------------



        vector<vector<cv::Point> > a=vector1.at(i);
        for(int j=0;j< angle.size();j++)
        {



                //angle[j]=Alineation::fourierAlienation(a,j,img_src);
                img_src.setTo(cv::Scalar(0,0,0));
                cv::Mat img_Gray=img_src(cv::boundingRect(a[j]));
                cvtColor(img_Gray,img_Gray,cv::COLOR_BGR2GRAY);
                cv::drawContours(img_Gray,a,j,Scalar(255,255,255),2,8);


//                namedWindow("CONTORNO",0);
//                imshow("CONTORNO",img_Gray);
//                waitKey(0);


                //qDebug()<<"Oeeee";




                Fourier f;

                cv::Mat imgF;//imagen en frecuencia
                cv::Mat imgRotacion;//imagen para rotacion

                int tamanoVect=0;//numero de componentes frecuencia


                qDebug()<<"Imagen que entra a Fourier"<<img_Gray.rows<<img_Gray.cols;

//                                namedWindow("CONTORNO",0);
//                                imshow("CONTORNO",img_Gray);
//                                waitKey(0);


                if(img_Gray.rows >2 && img_Gray.cols>2){


                    imgF=f.getFourier(img_Gray);//obtiene transformada de fourier






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


    //                  qDebug()<<(imgF.cols-1)*lr.b + lr.a;
    //                  qDebug()<<(1)*lr.b + lr.a;


                      line(imgF,Point2f (1,(1)*lr.b + lr.a ), Point2f (imgF.cols-1,(imgF.cols-1)*lr.b + lr.a ), Scalar(255,255,255),1);



                        angle[j]=(atan(lr.b))*180/2*3.14;

                       qDebug()<<"Angulo pequeño:= "<<j<<" "<<angle[j];



                   // angle2=angle;



                }

                else
                {

                    angle[j]=0;

                }


        }





        std::vector<int> angle3(2);
        std::vector<vector<Point> > w;
        angle3[0]=1;
        angle3[1]=1;

        if(vector1[i].size()>0){
            checkup::checkupfc(vector1[i], angle3,&posiciones,  &contours_out );
            //qDebug()<<"Checkupfc listo";
        }
        else

            qDebug()<<"Hola";



    }


    }



    qDebug()<<"oe";
    ///Rules
    ///







    waitKey(0);






}
