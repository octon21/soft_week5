#include<stdio.h>
#include<stdlib.h>
#include "func.h"

int main(){
  int num=14;
  //Sample *data=(Sample)malloc(sizeof(Sample));
  Sample data[num];

  FILE *fp;
  
  if((fp=fopen("data.csv", "r"))==NULL){
    printf("File open failed");
    return EXIT_FAILURE;    
  }

  char  Loc[10];
  double Alt;
  double Temp;
  for(int i=0; i<num;i++){
    fscanf(fp,"%[^,],%lf,%lf",data[i].loc, &data[i].alt, &data[i].temp);
  //fscanf(fp,"%s %f %f",data[i].loc, &data[i].alt, &data[i].temp);
  }
  //sort(Sample)引数a[]
  sort(data);



  estimate(data);//最小2zyouhou
}


