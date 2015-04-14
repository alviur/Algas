#include "checkup.h"



checkup::checkup()
{


}




void checkup::checkupfc(vector<vector<Point> > contours_in, std::vector<int> angulo, std::vector<int> *posiciones, vector<vector<Point> > *contours_out )
{

    int n;
    n=angulo.size();
    std::vector<int> tmp2(n,0);
    std::vector<int> tmp3(n,0);
    int tmp1=0;
    tmp1=angulo[0];

//    cout<<endl;
//    cout<<"Angulo original es: ";
//    for(int i=0; i<angulo.size(); i++){
//      // cout<<angulo[i]<<" ";
//    }

    for(int i=0;i<angulo.size();i++){
        if(abs(angulo[i]-tmp1)<=5)
            tmp2[i]=1;
        else
            tmp2[i]=angulo[i];
    }

   // cout<<endl;




 //   cout<<endl;
    for(int i=0;i<angulo.size();i++){
        if(tmp2[i]!=1){
            for(int k=0;k<angulo.size();k++){
                if(abs(angulo[k]-tmp2[i])<=5)
                    tmp3[k]=1;
                else
                    tmp3[k]=tmp2[i];
            }
        }
    }
//    cout<<endl;
//    for(int k=0;k<angulo.size();k++){
//        if(tmp2[k]==1)
//             cout<<"Igual en posicion tmp2: "<<k<<endl;
//    }
//    for(int k=0;k<angulo.size();k++){
//        if(tmp3[k]==1)
//          //   cout<<"Igual en posicion tmp3: "<<k<<endl;
//    }

    // Separar contornos
   // if(tmp)


}
