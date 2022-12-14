#include <iostream>
#include "classdef.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <string>/* time */
#include <sstream>
using namespace std;


string gameboard[8][8];
int mines[8][2];
string hidden[8][8];
string lib = "abcdefgh";
int cint(char input){
  stringstream ss;
  int conv;
  ss << input;
  ss >> conv;
  return conv;
}
char cchar(int input){
  stringstream ss;
  char conv;
  ss << input;
  ss >> conv;
  return conv;
}
void genmines(){
    for(int u = 0;u<8;u++){
    for(int p = 0;p<2;p++){
    mines[u][p] = rand()%8;
    }  
    }
}
bool minecheck(int ycheck, int xcheck){
  for(int t = 0;t<8;t++){
    if(ycheck == mines[t][0] && xcheck == mines[t][1]){
      return true;
    }
  
    }
  return false;
}
char num(int yguess, int xguess){
  bool minecount[8];
  int totcount = 0;
  for(int i = 0; i<8;i++){
    switch(i){
      case 0:
        if(minecheck(yguess-1,xguess)== true){
          minecount[0] = true;
        }else{
          minecount[0] = false;
        }
      case 1:
        if(minecheck(yguess-1,xguess+1) == true){
          minecount[1] = true;
        }else{
          minecount[1] = false;
        }
      case 2:
        if(minecheck(yguess, xguess+1) == true){
          minecount[2] = true;
        } else{
          minecount[2] = false;
        }
      case 3:
        if(minecheck(yguess+1, xguess + 1) == true){
          minecount[3] = true;
        }else{
          minecount[3] = false;
        }
      case 4:
        if(minecheck(yguess+1, xguess) == true){
          minecount[4] = true;
        }else{
          minecount[4] = false;
        }
      case 5:
        if(minecheck(yguess+1, xguess-1) == true){
          minecount[5] = true;
        } else{
          minecount[5] = false;
        }
      case 6:
        if(minecheck(yguess, xguess-1) == true){
          minecount[6] = true;
        }else{
          minecount[6] = false;
        }
      case 7:
        if(minecheck(yguess-1, xguess-1) == true){
          minecount[7] = true;
        }else{
          minecount[7] = false;
        }
    }
  }
  for(int k=0;k<8;k++){
     if (minecount[k] == true){totcount++;}
  }
  return totcount;
}
void reveal(int y, int x){
      hidden[y][x] = gameboard[y][x];
}
/*(void zerochain(int y, int x){
  for(int i = 0; i<8;i++){
    switch(i){
      case 0:
        if(minecheck(y-1,x) == false){
          if(y-1>=0){
          reveal(y-1,x);
          if(gameboard[y-1][x] == "0"){
            zerochain(y-1,x);
          }
          }
        }
      case 1:
        if(minecheck(y-1,x+1) == false){
          if(y-1>=0&&x+1<8){
          reveal(y-1,x+1);
          if(gameboard[y-1][x+1] == "0"){
            zerochain(y-1,x+1);
          }
          }
        }
      case 2:
        if(minecheck(y,x+1) == false){
          if(x+1<8){
          reveal(y,x+1);
          if(gameboard[y][x+1] == "0"){
            zerochain(y,x+1);
          }
          }
        }
      case 3:
        if(minecheck(y+1,x+1) == false){
          if(y+1<8&&x+1<8){
          reveal(y+1,x+1);
          if(gameboard[y+1][x+1] == "0"){
            zerochain(y+1,x);
          }
          }
        }
      case 4:
        if(minecheck(y+1,x) == false){
          if(y+1<8){
          reveal(y+1,x);
          if(gameboard[y+1][x] == "0"){
            zerochain(y+1,x);
          }
          }
        }
      case 5:
        if(minecheck(y+1,x-1) == false){
          if(y+1<8&&x-1>=0){
          reveal(y+1,x-1);
          if(gameboard[y+1][x-1] == "0"){
            zerochain(y+1,x-1);
          }
          }
        } 
      case 6:
        if(minecheck(y,x-1) == false){
        if(x-1>=0){
          reveal(y,x-1);
          if(gameboard[y][x-1] == "0"){
            zerochain(y,x-1);
          }
          }
        }
      case 7:
        if(minecheck(y-1,x-1) == false){
          if(y-1>=0&&x-1>=0){
          reveal(y-1,x-1);
          if(gameboard[y-1][x-1] == "0"){
            zerochain(y-1,x-1);
          }
          }
        }
    }
}
    }
  */
void generate(){
  srand(time(NULL));
  genmines();
  for (int i = 0;i<8;i++){
    for(int j = 0;j<8;j++){
      gameboard[i][j] = cchar(num(i,j));
      gameboard[mines[j][0]][mines[j][1]] = '#';
      hidden[i][j] = "*";
    }
  }
}



void play(){
  string userinput;
  int guessx;
  int guessy;
  for(int i = 0;i<8;i++){
    for(int j = 0;j<8;j++){
      cout << hidden[i][j] << "  ";
    }
    cout << "\n";
  }
  cout << "Please Enter Your Value:";
  cin >> userinput;
  guessy = cint(userinput[0]);
  guessx = cint(userinput[1]);
  if(minecheck(guessy,guessx) == true){
    cout << "Game Over!";
    exit(0);
    }
  else if(minecheck(guessy, guessx) == false){
    reveal(guessy, guessx);
    play();
  }
  
}
int main(){
  generate();
  
  for(int i=0;i<8;i++){
    for(int j=0;j<2;j++){
      cout << mines[i][j];
    }
    cout << "\n";
  }
  play();
  return 0;
}