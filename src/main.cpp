#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "imageProcess.h"
using namespace std;



int main(int argc, char* argv[]){
  vector <Image::Pixel> vec;
  string lay1="input/layer1.tga"; 
  string pat1="input/pattern1.tga";
  Image img;
  Image::Header head;

  //task 1
  img.getHeader(lay1,head);
  img.Multiply(lay1,pat1, vec);
  img.Print("output/part1.tga",head, vec);

  //task 2
  vector <Image::Pixel> pic;
  Image::Header h;
  string lay2="input/layer2.tga"; 
  string file2="input/car.tga";
  img.getHeader(lay2,h);
  img.Subtract(lay2,file2, pic);
  img.Print("output/part2.tga",h, pic);

  //task 3 
  string pat2= "input/pattern2.tga";
  string f4="input/text.tga";
  Image::Header hd;
  vector <Image::Pixel> vc1, vc2;
  img.getHeader(lay1,hd);
  img.Multiply(lay1,pat2, vc1);
  img.Screen(f4,vc1,vc2);
  img.Print("output/part3.tga",hd,vc2);

  //task 4 pattern2 is f3
  string circle= "input/circles.tga";
  Image::Header he;
  vector <Image::Pixel> pc,pc2;
  img.getHeader(lay2,he);
  img.Multiply(lay2,circle,pc);
  img.SubtractAgain(pat2,pc,pc2);
  img.Print("output/part4.tga",he,pc2);

  //task5
  Image::Header h5;
  vector <Image::Pixel> vec3, vec4, vec5;
  img.getHeader(lay1,h5);
  img.Overlay(vec3, vec4, vec5);
  img.Print("output/part5.tga",h5,vec5);

  //task6
  string car="input/car.tga";
  Image::Header h6;
  vector <Image::Pixel> v6;
  img.getHeader(car,h6);
  img.AddGreen(car,200,v6);
  img.Print("output/part6.tga",h6,v6);

  //task7
  Image::Header h7;
  vector <Image::Pixel> v7;
  img.getHeader(car,h7);
  img.Scale(car, 4, v7);
  img.Print("output/part7.tga",h7,v7);

  //task8
  Image::Header h8;
  vector <Image::Pixel> v_r, v_b, v_g;
  img.getHeader(car,h8);
  img.RedChan(car, v_r);
  img.BlueChan(car, v_b);
  img.GreenChan(car, v_g);
  img.Print("output/part8_r.tga",h8,v_r);
  img.Print("output/part8_b.tga",h8,v_b);
  img.Print("output/part8_g.tga",h8,v_g);


  //task9- 
  string layr="input/layer_red.tga";
  string layg="input/layer_green.tga";
  string layb="input/layer_blue.tga";
  Image::Header h9;
  vector <Image::Pixel> v9;
  img.getHeader(layb,h9);
  img.Combine(layr,layg,layb,v9);
  img.Print("output/part9.tga",h9,v9);

  //task10 
  string txt2="input/text2.tga";
  Image::Header h10;
  vector <Image::Pixel> v10;
  img.getHeader(txt2,h10);
  img.Rotate("output/part10.tga",h10, v10);

////

return 0;

}