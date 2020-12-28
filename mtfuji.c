#include<stdio.h>
#include<stdlib.h>
#include "func.h"

typedef struct
{
  char *loc;   // location name
  double alt;  // altitude (km)
  double temp; // temperature (centigrade)
} data;


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
  char buf[100];
  char str[100];
  
  for(int i=0; i<num;i++){
    fscanf(fp,"%[^,],%lf,%lf",str, &data[i].alt, &data[i].temp);
    data[i].loc=str;    
    //printf("%s,%lf,%lf\n",data[i].loc,data[i].alt,data[i].temp);
  }

  //sort(Sample)引数a[]
  //sort(data);
   const int dim = f_dimension();
    double *x = malloc(dim * sizeof(double));
    // 適当な値でa, bを初期化
    x[0] = 10.0;
    x[1] = 10.0;
    double alpha=0.1;
    printf("alpha = %f\n", alpha);
    // 最適化する関数を動かす
    const int iter = optimize(alpha, dim, x, data, 2,f_gradient, f_value);
}
