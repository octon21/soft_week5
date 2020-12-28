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
   FILE *fp;  
  if((fp=fopen("data.csv", "r"))==NULL){
    printf("File open failed");
    return EXIT_FAILURE;    
  }
  int num=14;
  Sample data[num];
  char str[100];
  
  for(int i=0; i<num;i++){
    fscanf(fp,"%[^,],%lf,%lf",str, &data[i].alt, &data[i].temp);
    data[i].loc=str;    
  }
  //sort(Sample)引数a[]
  //sort(data);
  const int dim = num;
  double *x = malloc(dim * sizeof(double));
  //a, bを初期化
  x[0]=10.0;//a
  x[1]=10.0;//b
  double alpha=0.01;
  // 最適化
  const int iter = optimize(alpha, dim, x, data,f_gradient, f_value);
  printf("%lf\n", x[0]*3.776+x[1]);  
}
