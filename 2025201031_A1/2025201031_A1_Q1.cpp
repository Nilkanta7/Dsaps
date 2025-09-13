#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using namespace cv;

int fun(char * str){
    int ans=0;
    bool flag=0;
    int i=0;
    if(str[i]=='-'){
        flag=1;
        i++;
    }

    while(str[i]!='\0'){
        if(str[i]<'0' || str[i]>'9'){
            cout<<"Error input"<<endl;
            return -1;
        }
        ans=(ans*10)+(str[i]-'0');
        i++;
    }
    if(flag)ans=-1*(ans);
    return ans;
}

//finding energy map
void computenergy(Mat &img,Mat &energy){

    Mat temp;
    if(img.channels()==3)cvtColor(img,temp,COLOR_BGR2GRAY);
    else temp=img.clone();

    Mat dx,dy;

    Sobel(temp,dx,CV_32F,1,0,3);//temp- input img dx-output img, cv-32f-32 bit floating pt number , 1- order of derivative in x, 0-odere of derivative in y, 3- kernel size
    Sobel(temp,dy,CV_32F,0,1,3);

    magnitude(dx,dy,energy);
    //energy(x,y)=sqrt(dx^2+dy^2)
}


//tabulation method to find the seam
void findverseam(Mat& energy,int *tracking){
    int row=energy.rows;
    int cols=energy.cols;

    float *prev=new float[cols],*curr=new float[cols];

    int *parent=new int[row*cols];

    //base condition
    //from (i,j) - (i,j-1),(i,j),(i,j+1)
    for(int j=0;j<cols;j++){
        prev[j]=energy.at<float>(0,j);
        parent[0*cols+j]=j;
    }

    for(int i=1;i<row;i++){
        for(int j=0;j<cols;j++){
            float maxi=prev[j];
            int ind=j;
            if(j>0 && prev[j-1]<maxi){
                maxi=prev[j-1];
                ind=j-1;
            }
            if(j+1<cols && prev[j+1]<maxi){
                maxi=prev[j+1];
                ind=j+1;
            }
            curr[j]=energy.at<float>(i,j)+maxi;
            parent[i*cols+j]=ind;
        }
        float *t=prev;
        prev=curr;
        curr=t;
    }

    int mini=0;
    double minval=prev[0];
    for(int j=1;j<cols;j++){
        if(prev[j]<minval){
            minval=prev[j];
            mini=j;
        }
    }

    //backtract to finding seam
    int indx=mini;
    for(int i=row-1;i>=0;i--){
        tracking[i]=indx;
        if(i>0){
            indx=parent[i*cols+indx];
        }
    }

    delete[] prev;
    delete[] curr;
    delete[] parent;
}


Mat removeverseam(Mat& img,int *seam){
    int row=img.rows;
    int cols=img.cols;

    //one size lesser size than input image
    Mat out(row,cols-1,img.type());

    for(int i=0;i<row;i++){
        int temp=seam[i];
        
        for(int j=0,k=0;j<cols;j++){
            if(j==temp)continue; //skip it
            out.at<Vec3b>(i,k)=img.at<Vec3b>(i,j);//copy pas
            k++;
        }
    }
    return out;
}

//showing thw seam by colouring the seam
Mat show(Mat &img,int *seam){
    Mat vis=img.clone();//make acopy 
    for(int i=0;i<vis.rows;i++){
        int temp=seam[i];
        if(temp>=0 && temp<vis.cols){
            Vec3b &p=vis.at<Vec3b>(i,temp);
            p[0]=0;
            p[1]=255;//green coloyr
            p[2]=0;
        }
    }
    //indicate seam and return it
    return vis;
}

void reduce(Mat& img,int target){
    int hei=img.rows;
    int wid=img.cols;

    int cnt=wid-target;

    if(cnt<=0)return;
    for(int i=0;i<cnt;i++){
        Mat energy;
        computenergy(img,energy);

        Mat temp;
        
        //ensuring flaot values
        if(energy.type()!=CV_32F)energy.convertTo(temp,CV_32F);
        else temp=energy;

        int *seam=new int[hei];
        findverseam(temp,seam);

        Mat vis=show(img,seam);
        imshow("Seam-Visualization",vis);
        waitKey(100);//wait for 0.1ms
        //destroyWindow("Seam-Visualization");

        Mat copy=removeverseam(img,seam);
        delete[] seam;
        img=copy;

        imshow("Carving Going On",img);
        waitKey(100);
        //destroyWindow("Carving Going On");
    }
}

void reduceheight(Mat& img,int targeth){
    Mat temp;
    transpose(img,temp);//transpose the image
    reduce(temp,targeth);//apply reduce function by width
    Mat res;
    transpose(temp,res);//angain transpose
    img=res;

}

int main(int argc,char ** argv){
    if(argc<5){
        cout<<"Throw error."<<" "<<"Error in giving input command"<<endl;
        return 0;
    }
    string ippath=argv[1];
    string oppath=argv[2];
    int targetw=fun(argv[3]);
    int targeth=fun(argv[4]);

    //cout<<targetw<<" "<<targeth<<endl;

    //stoting pixels image in 2D array in BGR format
    Mat imgMat=imread(ippath,IMREAD_COLOR);
    // for(int i=0;i<imgMat.rows;i++){
    //     for(int j=0;j<imgMat.cols;j++){
    //         Vec3b pixels=imgMat.at<Vec3b>(i,j);
    //         for(int k=0;k<3;k++){
    //             cout<<(int)pixels[i]<<" ";
    //         }
    //         cout<<endl;
    //     }
    //     cout<<endl;
    // }
    if(imgMat.empty()){
        cout<<"Throw Error"<<" "<<"Error in oopening input image"<<endl;
        return 0;
    }
    int imgcol=imgMat.cols,imgrow=imgMat.rows;
    if(imgcol<targetw || imgrow<targeth){
        cout<<"Throw Error"<<" "<<"Error in size input."<<endl;
        return 0;
    }
    reduce(imgMat,targetw);
    reduceheight(imgMat,targeth);


    imshow("Final-Result",imgMat);
    imwrite(oppath,imgMat);
    cout<<"image saved tp "<<oppath<<endl;
    cout<<"Finished"<<endl;
    waitKey(0);


    return 0;
}