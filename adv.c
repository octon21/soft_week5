#include<stdio.h>
#include<stdlib.h>

typedef struct
{
  char *loc;   // location name
  double alt;  // altitude (km)
  double temp; // temperature (centigrade)
} Sample;

int main(){
  int ex_val=2;
  int i,j,k,n;
  int N=10;//?

  double **x,**xx,*xy,*y,*b,**trans_x, **inv_x;
  double buf;

  x=(double**)malloc(n);
  y=(double*)malloc(n);
  for(i = 0; i < N; i++) x[i] =(double*)malloc(ex_val+1);
  
  FILE *fp;  
  if((fp=fopen("data.csv", "r"))==NULL){
    printf("File open failed");
    return EXIT_FAILURE;    
  }
  int num=10;
  
  for(int i=0; i<num;i++){

    x[i][0]=1.0;
    fscanf(fp,"%lf %lf %lf", &y[i],&x[i][2],&x[i][1]);
  }

n=ex_val+1;

trans_x=(double**)malloc(n);

for(i=0;i<n;i++)trans_x[i]=(double*)malloc(N);
for(i=0; i<N;i++){
  for(j=0;j<n;j++)trans_x[j][i]=x[i][j];
}
for(i=0; i<N; i++){
  for(j=0;j<n;j++)printf("%lf\n", trans_x[i][j]);
  
}
//xとtrans_x積
xx=(double**)malloc(n);
for(i=0;i<n;i++)xx[i]=(double*)malloc(n);

for(i=0; i<n;i++){
  for(j=0; j<n; j++){

    xx[i][j]=0.0;
    for(k=0;k<N;k++)xx[i][j]+=trans_x[i][k]*x[k][j];
  }
}
//逆行列計算
inv_x=(double**)malloc(n);
for(i=0; i<n;i++)inv_x[i]=(double*)malloc(n);

for(i=0;i<n;i++){
  for(j=0;j<n;j++){
    if(i==j)inv_x[i][j]=1.0;
    else inv_x[i][j]=0.0;
  }
}

for(i=0;i<n;i++){
  if(-1e-5<x[i][i]&&x[i][i]<1e-5){
    printf("cannot calculate invers matrix\n");
    exit(1);
  }
}
for(i = 0; i < n; i++){
  buf = 1.0 / xx[i][i];
  for(j = 0; j < n; j++){
    xx[i][j] += buf;
    inv_x[i][j] *= buf;
  }

  for(j = 0; j < n; j++){
    if(i != j){
      buf = xx[j][i];
      for(k = 0; k < n; k++){
        xx[j][k] -= xx[i][k] * buf;
        inv_x[j][k] -= inv_x[i][k] * buf;
      }
    }
  }
}
  // 逆行列inverse_xと目的変数yの積 
  xy=(double*)malloc(n);
  for(i=0;i<n;i++){
    xy[i]=0.0;
    for(j=0;j< N;j++)xy[i]+=trans_x[i][j]*y[j];
  }
  b=(double*)malloc(n);

  for(i = 0; i < n; i++){
    b[i] = 0.0;
    for(j = 0; j < n; j++) b[i] += inv_x[i][j] * xy[j];
  }
  printf("fin mul regression\n");

    // 係数の表示 
    for(i = 0; i < n; i++) printf("b%d : %lf, ", i, b[i]);
    printf("\n");

    for(i = 0; i < N; i++) free(x[i]);
    free(x);

    for(i = 0; i < n; i++) free(trans_x[i]);
    free (trans_x);

    for(i = 0; i < n; i++) free(xx[i]);
    free(xx);

    for(i = 0; i < n; i++) free(inv_x[i]);
    free(inv_x);

    free(xy);
    free(b);
    free(y);

    return 0;

}
