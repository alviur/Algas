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

    qDebug()<<"1.Filtro listo";

    namedWindow("Img Line",0);
    imshow("Img Line",img_line);

    namedWindow("Patata",0);
    imshow("Patata",img_mask);


    ///Get lattice from image
    lattice1.lattice(img_line);
    qDebug()<<"Lattice listo";
   // cout<<lattice1.v<<endl;

    vector<vector<vector<Point> > > vector1;


    vector<vector<Point> > contoursBig;
    vector<Point>  positions;
    vector<vector<Point> >contoursBig2;
    vector1=ContoursSmall::contourSmallget(img_mask, img_src,contoursBig,positions);
    qDebug()<<"3.Contorno listo";

    for(int a=0; a< positions.size();a++)
        qDebug()<<a<<"/"<<positions.size()<<"_"<<positions[a].x<<positions[a].y;


    // vector<vector<Point> > ContoursSmall::contourSmallget(vector<vector<Point> > contornos, cv::Mat img_src)


    ///Main cycle

    for(int i=0;i< vector1.size() -1;i++)
    {

        if(vector1[i].size()>0){

        qDebug()<<"Numero de contornos grandes" <<vector1.size() -1;
        qDebug()<<"Contorno grande: "<<i<<" "<<vector1[i].size();


        }


    }



    qDebug()<<"oe";
    ///Rules
    ///







    waitKey(0);



}
