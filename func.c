#include <stdio.h>
#include<stdlib.h>

typedef struct
{
  char *loc;   // location name
  double alt;  // altitude (km)
  double temp; // temperature (centigrade)
} Sample;

int f_dimension(Sample *data){
  int n = 0;
  while (data[n].loc != NULL){
    n++;
  }
  return n ;
}


double f_value(const double x[], const Sample sample[], const int n)
{
  double sum = 0;
  for (int i = 0; i < n; i++){  // nはデータの数．x[0]がa, x[1]がb
    sum += (sample[i].temp - x[0] * sample[i].alt - x[1]) * (sample[i].temp - x[0] * sample[i].alt - x[1]);
  }
  return sum;
}


void f_gradient(const double x[], double g[], const Sample sample[], const int n)
{
  double sum0 = 0;
  double sum1 = 0;
  for (int i = 0; i < n; i++){
    sum0 += (-2) * sample[i].alt * (sample[i].temp - x[0] * sample[i].alt - x[1]);
  }
  for (int i = 0; i < n; i++){
    sum1 += (-2) * (sample[i].temp - x[0] * sample[i].alt - x[1]);
  }
  // 代入
  g[0] = sum0;
  g[1] = sum1;
}


/*int optimize(const double alpha, const int dim, double x[], 
             void (*calc_grad)(const double [], double []))
{
  // 勾配ベクトルを記録する領域を確保
  double *g = malloc(dim * sizeof(double));

  int iter = 0;
  while (++iter < 10000) {

    // 引数で渡された関数を使って勾配ベクトルを計算
    (*calc_grad)(x, g);

    // 勾配ベクトルのノルムを評価
    const double norm = calc_norm(dim, g);
    printf("%3d norm = %7.4f", iter, norm);
    for (int i = 0; i < dim; i++) {
      printf(", x[%d] = %7.4f", i, x[i]);
    }
    printf("\n");

    if (norm < 0.01) break;

    // 最急降下法による更新
    for (int i = 0; i < dim; i++) {
      x[i] -= alpha * g[i];
    }
  }

  free(g);

  return iter;
}*/

int optimize(const double alpha, const int dim, double x[],Sample sample[],int n, void (*calc_grad)(const double x[], double g[], const Sample sample[], const int n),
double (*calc_value)(const double x[], const Sample sample[], const int n))
{
    // 勾配ベクトル（今回は二次元ベクトル）を確保
    double *g = malloc(dim * sizeof(double));
    int iter = 0;
    while(++iter < 100) {
        (*calc_grad)(x, g, sample, n);
        // 平均二乗誤差
        const double err = (*calc_value)(x, sample, n) / n;
        // 表示
        printf("%3d mean_squared_error = %7.4f", iter, err);
        for (int i = 0; i < dim; i++) {
            printf(", x[%d] = %7.4f", i, x[i]);
        }
        for (int i = 0; i < dim; i++) {
            printf(", g[%d] = %7.4f", i, g[i]);
        }
        printf(",  f(x) = %f\n", (*calc_value)(x, sample, n));
        // 終了条件
        if (err < 0.0001) {
            break;
        }
        // 最急降下法
        for (int i = 0; i < dim; i++){
            x[i] -= alpha * g[i];
        }
    }
    free(g);
    return iter;
}
