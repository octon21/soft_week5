#include <stdio.h>
#include<stdlib.h>

typedef struct
{
  char *loc;   // location name
  double alt;  // altitude (km)
  double temp; // temperature (centigrade)
} Sample;

double f_value(const double x[], const Sample data[], const int n)
{
  double sum = 0;
  for (int i = 0; i < n; i++){//データ数n
    sum +=(data[i].temp -x[0] * data[i].alt - x[1]) * (data[i].temp - x[0] * data[i].alt - x[1]);
  }
  return sum;
}


void f_gradient(const double x[], double g[], const Sample data[], const int n)
{
  double sum0 = 0;
  double sum1 = 0;
  for (int i = 0; i < n; i++){
    sum0 += (-2) *data[i].alt * (data[i].temp - x[0] * data[i].alt - x[1]);
  }
  for (int i = 0; i < n; i++){
    sum1 += (-2) * (data[i].temp - x[0] *data[i].alt - x[1]);
  }
  g[0] = sum0;
  g[1] = sum1;
}

int optimize(const double alpha, const int dim, double x[],Sample data[], void (*calc_grad)(const double x[], double g[], const Sample data[], const int dim),
double (*calc_value)(const double x[], const Sample data[], const int dim))
{
  // 勾配ベクトル（今回は二次元ベクトル）を確保
  double *g = malloc(dim * sizeof(double));
  int iter = 0;
  while(++iter < 10000) {
    (*calc_grad)(x, g, data, dim);
    // 平均二乗誤差
    const double err = (*calc_value)(x, data, dim) / dim;

    // 終了条件
    if (err < 0.01)break;
    // 最急降下法
    for (int i = 0; i < 2; i++){
      x[i] -= alpha * g[i];
    }
  }
  free(g);
  return iter;
}
