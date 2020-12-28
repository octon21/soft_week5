#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "func.h"
//  qsort用
int compar(const void* a, const void* b) {
    if (((Sample*)a)->alt < ((Sample*)b)->alt){
        return 1;
    } else {
        return -1;
    }
}

int main(){
   FILE *fp;  
  if((fp=fopen("data.csv", "r"))==NULL){
    printf("File open failed");
    return EXIT_FAILURE;    
  }
  int num=14;
  Sample data[num];
  char str[num][100];
  
  for(int i=0; i<num;i++){
    fscanf(fp,"%[^,],%lf,%lf",str[i], &data[i].alt, &data[i].temp);
    data[i].loc=str[i];
  }

  const int dim = num;
  double *x = malloc(dim * sizeof(double));
  //a, bを初期化
  x[0]=10.0;//a
  x[1]=10.0;//b
  double alpha=0.01;
  // 最適化
  const int iter = optimize(alpha, dim, x, data,f_gradient, f_value);
  printf("Answer is :%lf\n", x[0]*3.776+x[1]); 

qsort(data, num, sizeof(Sample), compar);
for(int i=0;i<num;++i){
  
  printf("%s,%lf,%lf\n",data[i].loc,data[i].alt,data[i].temp);
}
}
