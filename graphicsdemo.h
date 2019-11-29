#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>
using namespace std;
struct coor
{
    int x ;
    int y ;
};
struct linkPrint
{
    coor c;
    string name;
};

const coor c00 =  {205, 290};                                      
const coor c01 =  {265, 290};                                      
const coor c02 =  {325, 290};                                      
const coor c03 =  {385, 290};                                      
const coor c04 =  {445, 290};                                      
const coor c05 =  {505, 290};                                      
const coor c06 =  {565, 290};                                      
const coor c07 =  {625, 290};                                      
                                                                   
const coor c10 =  {205, 350};                                      
const coor c11 =  {265, 350};                                      
const coor c12 =  {325, 350};                                      
const coor c13 =  {385, 350};                                      
const coor c14 =  {445, 350};                                      
const coor c15 =  {505, 350};                                      
const coor c16 =  {565, 350};                                      
const coor c17 =  {625, 350};                                      
                                                                   
const coor c20 =  {205, 410};                                      
const coor c21 =  {265, 410};                                      
const coor c22 =  {325, 410};                                      
const coor c23 =  {385, 410};                                      
const coor c24 =  {445, 410};                                      
const coor c25 =  {505, 410};                                      
const coor c26 =  {565, 410};                                      
const coor c27 =  {625, 410};                                      
                                                                   
const coor c30 =  {205, 470};                                      
const coor c31 =  {265, 470};                                      
const coor c32 =  {325, 470};                                      
const coor c33 =  {385, 470};                                      
const coor c34 =  {445, 470};                                      
const coor c35 =  {505, 470};                                      
const coor c36 =  {565, 470};                                      
const coor c37 =  {625, 470};                                      
                                                                   
const coor c40 =  {205, 530};                                      
const coor c41 =  {265, 530};                                      
const coor c42 =  {325, 530};                                      
const coor c43 =  {385, 530};                                      
const coor c44 =  {445, 530};                                      
const coor c45 =  {505, 530};                                      
const coor c46 =  {565, 530};                                      
const coor c47 =  {625, 530};                                      
                                                                   
const coor c50 =  {205, 590};                                      
const coor c51 =  {265, 590};                                      
const coor c52 =  {325, 590};                                      
const coor c53 =  {385, 590};                                      
const coor c54 =  {445, 590};                                      
const coor c55 =  {505, 590};                                      
const coor c56 =  {565, 590};                                      
const coor c57 =  {625, 590};

const coor c60 =  {205, 650};                                      
const coor c61 =  {265, 650};                                      
const coor c62 =  {325, 650};                                      
const coor c63 =  {385, 650};                                      
const coor c64 =  {445, 650};                                      
const coor c65 =  {505, 650};                                      
const coor c66 =  {565, 650};                                      
const coor c67 =  {625, 650};                                      
                                                                   
const coor c70 =  {205, 710};                                      
const coor c71 =  {265, 710};                                      
const coor c72 =  {325, 710};                                      
const coor c73 =  {385, 710};                                      
const coor c74 =  {445, 710};                                      
const coor c75 =  {505, 710};                                      
const coor c76 =  {565, 710};                                      
const coor c77 =  {625, 710}; 

  // for the download section P1
  string P1DownData;
  string P1DownComma = " ,  ";
  string P1DownVirus;
  // for the download section P2
  string P2DownData;
  string P2DownComma = " ,  ";
  string P2DownVirus;

  // for the abilities section P1
  string P1Abilites;
  // for the abilities section P2
  string P2Abilites;

  //for the revealed of p1 links
  string p1a;
  string p1b;
  string p1c;
  string p1d;
  string p1e;
  string p1f;
  string p1g;
  string p1h;
  // for the revealed of p1 links
  string p2A;
  string p2B;
  string p2C;
  string p2D;
  string p2E;
  string p2F;
  string p2G;
  string p2H;




// std::vector<std::vector<coor>> coors{ {c00, c01, c02, c03, c04, c05, c06, c07},
//                     {c10, c11, c12, c13, c14, c15, c16, c17},
//                     {c20, c21, c22, c23, c24, c25, c26, c27},
//                     {c30, c31, c32, c33, c34, c35, c36, c37},
//                     {c40, c41, c42, c43, c44, c45, c46, c47},
//                     {c50, c51, c52, c53, c54, c55, c56, c57},
//                     {c60, c61, c62, c63, c64, c65, c66, c67},
//                     {c70, c71, c72, c73, c74, c75, c76, c77}};

// int getX(coor cel) const;
// int getY(coor cel) const;

#endif