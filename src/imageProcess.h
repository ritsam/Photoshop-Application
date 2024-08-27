#include <iostream>
#pragma once
#include <fstream>
#include <vector>
using namespace std;

class Image{
public:
 struct Pixel{
    unsigned char red;
    unsigned char blue;
    unsigned char green;
 };
public:
struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth; 
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};
    //int length;
    unsigned char clamp(int num);
    void getHeader(string file, Header& h);
    void ReadFile(string file, vector <Pixel>& pix_vec);
    void Print(string newFile,Header& h, vector <Pixel>& pix_vec); 
    void Multiply(string file1, string file2, vector <Pixel>& pix_vec);
    void Subtract(string file1, string file2, vector <Pixel>& pix_vec);
    void Screen(string file, vector <Pixel>& pix_vec, vector <Pixel>& pix_vec2 );
    void SubtractAgain(string f, vector <Pixel>& pv1, vector <Pixel>& pv2);
    void Overlay(vector <Pixel>& pv1,vector <Pixel>& pv2,vector <Pixel>& pv3);
    void AddGreen(string fn, float add,vector <Pixel>& pv1);
    void Scale(string fn, float scale, vector <Pixel>& pv1);
    void ScaleBlue(string fn, float scale, vector <Pixel>& pv1);
    void ScaleGreen(string fn, float scale, vector <Pixel>& pv1);
    short getWid(string fn);
    short getHeight(string fn);
    void RedChan(string fn, vector <Pixel>& pv1);
    void BlueChan(string fn, vector <Pixel>& pv1);
    void GreenChan(string fn, vector <Pixel>& pv1);
    void Combine(string r, string g, string b,vector <Pixel>& pv);
    void Rotate(string fn, Header& h,vector <Pixel>& pix_vec );
};
    
 

