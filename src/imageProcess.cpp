#include "imageProcess.h"
using namespace std;
#include <iostream>
#include <fstream>
#include <vector>


void Image:: ReadFile(string file,vector <Pixel>& pix_vec){
    ifstream data(file, ios_base:: binary);
    Header h;
    data.read(&h.idLength, 1);
    data.read(&h.colorMapType, 1);
    data.read(&h.dataTypeCode, 1);
    data.read((char*)&h.colorMapOrigin, 2);
    data.read((char*)&h.colorMapLength, 2);
    data.read(&h.colorMapDepth, 1);
    data.read((char*)&h.xOrigin, 2);
    data.read((char*)&h.yOrigin, 2);
    data.read((char*)&h.width, 2);
    data.read((char*)&h.height, 2);
    data.read(&h.bitsPerPixel, 1);
    data.read(&h.imageDescriptor, 1);

    int fullsize= h.width * h.height;
    Pixel pix;
    for(int i=0; i<fullsize;i++){
        data.read((char*)&pix.red,1);
        data.read((char*)&pix.blue,1);
        data.read((char*)&pix.green,1);
        pix_vec.push_back(pix);
    }
} 
unsigned char Image::clamp(int num){
    if(num>255){
        num=255;
    }
    else if(num<0){
        num=0;
        }
        unsigned char n=(unsigned char)num;
        return n;
    }

void Image::Print(string newFile, Header& h, vector <Pixel>& pix_vec){
    ofstream data(newFile, ios_base:: binary);
    data.write(&h.idLength, 1);
    data.write(&h.colorMapType, 1);
    data.write(&h.dataTypeCode, 1);
    data.write((char*)&h.colorMapOrigin, 2);
    data.write((char*)&h.colorMapLength, 2);
    data.write(&h.colorMapDepth, 1);
    data.write((char*)&h.xOrigin, 2);
    data.write((char*)&h.yOrigin, 2);
    data.write((char*)&h.width, 2);
    data.write((char*)&h.height, 2);
    data.write(&h.bitsPerPixel, 1);
    data.write(&h.imageDescriptor, 1);

    for(int i=0;i<pix_vec.size();i++){
         data.write((char*)&pix_vec.at(i).red,1);
         data.write((char*)&pix_vec.at(i).blue,1);
         data.write((char*)&pix_vec.at(i).green,1);
    }
}

void Image::getHeader(string file, Header& h){
    ifstream data(file, ios_base:: binary);
    data.read(&h.idLength, 1);
    data.read(&h.colorMapType, 1);
    data.read(&h.dataTypeCode, 1);
    data.read((char*)&h.colorMapOrigin, 2);
    data.read((char*)&h.colorMapLength, 2);
    data.read(&h.colorMapDepth, 1);
    data.read((char*)&h.xOrigin, 2);
    data.read((char*)&h.yOrigin, 2);
    data.read((char*)&h.width, 2);
    data.read((char*)&h.height, 2);
    data.read(&h.bitsPerPixel, 1);
    data.read(&h.imageDescriptor, 1);

}

void Image:: Multiply(string file1, string file2, vector <Pixel>& pix_vec){
   //pix_vec.clear();
   vector <Pixel> f1, f2;
    ReadFile(file1, f1);
    ReadFile(file2, f2);

    for(int i=0;i<f1.size();i++){
        float r1=f1.at(i).red / 255.0f;
        float b1=f1.at(i).blue / 255.0f;
        float g1=f1.at(i).green / 255.0f;

        float r2=f2.at(i).red / 255.0f;
        float b2=f2.at(i).blue / 255.0f;
        float g2=f2.at(i).green / 255.0f;

        Pixel pix;
        float red= (r1*r2*255)+0.5f;
        pix.red=clamp((unsigned char)red);
        float blue= (b1*b2*255)+0.5f;
        pix.blue=clamp((unsigned char)blue);
        float green= (g1*g2*255)+0.5f;
        pix.green=clamp((unsigned char)green);
        pix_vec.push_back(pix); //load onto vector
    }
}
    void Image::Subtract(string file1, string file2, vector <Pixel>& pix_vec){
    vector <Pixel> f1, f2;
    ReadFile(file1, f1);
    ReadFile(file2, f2);
     for(int i=0;i<f1.size();i++){
        int r1=int(f1.at(i).red );
        int b1=int(f1.at(i).blue );
        int g1=int(f1.at(i).green );

        int r2=int(f2.at(i).red );
        int b2=int(f2.at(i).blue );
        int g2=int(f2.at(i).green );

        Pixel pix;
        pix.red=clamp(r2-r1);
        pix.blue=clamp(b2-b1);
        pix.green=clamp(g2-g1);
        pix_vec.push_back(pix);
    }
}

void Image::Screen(string file, vector <Pixel>& pix_vec, vector <Pixel>& pix_vec2){
    vector <Pixel> f2;
    ReadFile(file, f2);
    for(int i=0;i<pix_vec.size();i++){
        float r1=float(pix_vec.at(i).red)/255 ;
        float b1=float(pix_vec.at(i).blue)/255 ;
        float g1=float(pix_vec.at(i).green)/255 ;

        float r2=float(f2.at(i).red)/255 ;
        float b2=float(f2.at(i).blue)/255 ;
        float g2=float(f2.at(i).green)/255 ;

        Pixel pix;
        float red= ((1-(1-r1)*(1-r2))*255)+0.5f;
        pix.red=clamp((unsigned char)red);
        float blue= ((1-(1-b1)*(1-b2))*255)+0.5f;
        pix.blue=clamp((unsigned char)blue);
        float green= ((1-(1-g1)*(1-g2))*255)+0.5f;
        pix.green=clamp((unsigned char)green);
        pix_vec2.push_back(pix); //load onto vec
    }
}

void Image::SubtractAgain(string f, vector <Pixel>& pv1, vector <Pixel>& pv2){
    vector <Pixel> fn;
    ReadFile(f, fn);
     for(int i=0;i<pv1.size();i++){
        int r1=int(pv1.at(i).red );
        int b1=int(pv1.at(i).blue );
        int g1=int(pv1.at(i).green );

        int r2=int(fn.at(i).red );
        int b2=int(fn.at(i).blue );
        int g2=int(fn.at(i).green );

        Pixel pix;
        pix.red=clamp(r1-r2);
        pix.blue=clamp(b1-b2);
        pix.green=clamp(g1-g2);
        pv2.push_back(pix);
    }
}
void Image:: Overlay(vector <Pixel>& pv1,vector <Pixel>& pv2,vector <Pixel>& pv3){
    string lay1="input/layer1.tga"; 
    string pat1="input/pattern1.tga";
    ReadFile(lay1,pv1);
    ReadFile(pat1,pv2);
    for(int i=0;i<pv1.size();i++){
        float r1=float(pv1.at(i).red)/255 ;
        float b1=float(pv1.at(i).blue)/255 ;
        float g1=float(pv1.at(i).green)/255 ;

        float r2=float(pv2.at(i).red)/255 ;
        float b2=float(pv2.at(i).blue)/255 ;
        float g2=float(pv2.at(i).green)/255 ;

        float red, blue, green;
        if(r2>0.5){
            red= ((1-(2*(1-r1)*(1-r2)))*255)+0.5f;
        }
        else{
            red=((2*(r1)*(r2))*255)+0.5f;
        }
        if(b2>0.5){
            blue= ((1-(2*(1-b1)*(1-b2)))*255)+0.5f;
        }
        else{
            blue=((2*(b1)*(b2))*255)+0.5f;
        }
        if(g2>0.5){
            green= ((1-(2*(1-g1)*(1-g2)))*255)+0.5f;
        }
        else{
            green=((2*(g1)*(g2))*255)+0.5f;
        }
        Pixel pix;
        pix.red=clamp((unsigned char)red);
        pix.blue=clamp((unsigned char)blue);
        pix.green=clamp((unsigned char)green);
        pv3.push_back(pix); //load onto vec
    }
    }
    void Image::AddGreen(string fn, float add,vector <Pixel>& pv1){
    vector <Pixel> pv;
    ReadFile(fn,pv);
    for(int i=0;i<pv.size();i++){
        float r1=float(pv.at(i).red);
        float b1=float(pv.at(i).blue) ;
        float g1=float(pv.at(i).green) ;
        float red=r1;
        float blue=b1+add; //to change green change blue
        float green=g1;

        Pixel pix;
        pix.red=clamp((int)red);
        pix.blue=clamp((int)blue);
        pix.green=clamp((int)green);
        pv1.push_back(pix); //load onto vec
    }
    }
   
    void Image::Scale(string fn, float scale, vector <Pixel>& pv1){
    vector <Pixel> pv;
    ReadFile(fn, pv);
     for(int i=0;i<pv.size();i++){
        float r1=float(pv.at(i).red);
        float b1=float(pv.at(i).blue) ;
        float g1=float(pv.at(i).green) ;
        float red=r1*0;
        float blue=b1; 
        float green=g1*scale;
        Pixel pix;
        pix.red=clamp((int)red);
        pix.blue=clamp((int)blue);
        pix.green=clamp((int)green);
        pv1.push_back(pix);
     }
    }
    void Image::ScaleBlue(string fn, float scale, vector <Pixel>& pv1){
    vector <Pixel> pv;
    ReadFile(fn, pv);
     for(int i=0;i<pv.size();i++){
        float r1=float(pv.at(i).red);
        float b1=float(pv.at(i).blue) ;
        float g1=float(pv.at(i).green) ;
        float red=r1*scale;
        float blue=b1; 
        float green=g1;
        Pixel pix;
        pix.red=clamp((int)red);
        pix.blue=clamp((int)blue);
        pix.green=clamp((int)green);
        pv1.push_back(pix);
     }
    }
    void Image::ScaleGreen(string fn, float scale, vector <Pixel>& pv1){
    vector <Pixel> pv;
    ReadFile(fn, pv);
     for(int i=0;i<pv.size();i++){
        float r1=float(pv.at(i).red);
        float b1=float(pv.at(i).blue) ;
        float g1=float(pv.at(i).green) ;
        float red=r1;
        float blue=b1*scale; 
        float green=g1;
        Pixel pix;
        pix.red=clamp((int)red);
        pix.blue=clamp((int)blue);
        pix.green=clamp((int)green);
        pv1.push_back(pix);
     }
    }
    

    short Image::getWid(string fn){
        ifstream data(fn, ios_base:: binary);
        Header h;
        data.read(&h.idLength, 1);
        data.read(&h.colorMapType, 1);
        data.read(&h.dataTypeCode, 1);
        data.read((char*)&h.colorMapOrigin, 2);
        data.read((char*)&h.colorMapLength, 2);
        data.read(&h.colorMapDepth, 1);
        data.read((char*)&h.xOrigin, 2);
        data.read((char*)&h.yOrigin, 2);
        data.read((char*)&h.width, 2);
        data.read((char*)&h.height, 2);
        data.read(&h.bitsPerPixel, 1);
        data.read(&h.imageDescriptor, 1);
        return h.width;
    }
    short Image::getHeight(string fn){
        ifstream data(fn, ios_base:: binary);
        Header h;
        data.read(&h.idLength, 1);
        data.read(&h.colorMapType, 1);
        data.read(&h.dataTypeCode, 1);
        data.read((char*)&h.colorMapOrigin, 2);
        data.read((char*)&h.colorMapLength, 2);
        data.read(&h.colorMapDepth, 1);
        data.read((char*)&h.xOrigin, 2);
        data.read((char*)&h.yOrigin, 2);
        data.read((char*)&h.width, 2);
        data.read((char*)&h.height, 2);
        data.read(&h.bitsPerPixel, 1);
        data.read(&h.imageDescriptor, 1);
        return h.height;
    }
    void Image::RedChan(string fn, vector <Pixel>& pv1){
    ReadFile(fn, pv1);
    string car="input/car.tga";
    int fullsize= getWid(car) * getHeight(car);
    for(int i=0;i<fullsize;i++){
        pv1.at(i).blue=pv1.at(i).green;
        pv1.at(i).red=pv1.at(i).green;
    }
}
void Image::BlueChan(string fn, vector <Pixel>& pv1){
    ReadFile(fn, pv1);
    string car="input/car.tga";
    int fullsize= getWid(car) * getHeight(car);
    for(int i=0;i<fullsize;i++){
        pv1.at(i).blue=pv1.at(i).red;
        pv1.at(i).green=pv1.at(i).red;
    }
}
void Image::GreenChan(string fn, vector <Pixel>& pv1){
    ReadFile(fn, pv1);
    string car="input/car.tga";
    int fullsize= getWid(car) * getHeight(car);
    for(int i=0;i<fullsize;i++){
        pv1.at(i).green=pv1.at(i).blue;
        pv1.at(i).red=pv1.at(i).blue;
    }
}
void Image::Combine(string r, string g, string b,vector <Pixel>& pv){
vector <Pixel> vr, vg, vb;
ReadFile(r,vr);
ReadFile(g,vg);
ReadFile(b,vb);
for(int i=0;i<vb.size();i++){
    Pixel pix;   
    pix.green=vr.at(i).red;                     
    pix.blue=vg.at(i).green;                
    pix.red=vb.at(i).blue; 
    pv.push_back(pix);
    }
}

void Image::Rotate(string fn, Header& h,vector <Pixel>& pix_vec ){
    ReadFile("input/text2.tga", pix_vec);
    ofstream data(fn, ios_base:: binary);
    data.write(&h.idLength, 1);
    data.write(&h.colorMapType, 1);
    data.write(&h.dataTypeCode, 1);
    data.write((char*)&h.colorMapOrigin, 2);
    data.write((char*)&h.colorMapLength, 2);
    data.write(&h.colorMapDepth, 1);
    data.write((char*)&h.xOrigin, 2);
    data.write((char*)&h.yOrigin, 2);
    data.write((char*)&h.width, 2);
    data.write((char*)&h.height, 2);
    data.write(&h.bitsPerPixel, 1);
    data.write(&h.imageDescriptor, 1);

    for(int i=pix_vec.size()-1;i>=0;i--){
         data.write((char*)&pix_vec.at(i).red,1);
         data.write((char*)&pix_vec.at(i).blue,1);
         data.write((char*)&pix_vec.at(i).green,1);
    }
    }




