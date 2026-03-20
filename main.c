#include "functions.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//chcp 65001 - для текста на русском в консоль



int main() {
    int choice = 0;
    float *t, *Uvx, *Uvix;
    int n, i;
    float dlit_vx = 0.0f, dlit_vix = 0.0f;
    float Uvx_fr1, Uvix_fr1, Uvx_fr2, Uvix_fr2;
    float Uvx_max = -10000, Uvx_min = 10000, Uvix_max = -10000, Uvix_min = 10000; 
    float tn = 10, tk = 35, dt;
    float t1 = 22.5, a = 12, b = 12;
    float Uvx1 = 20, Uvx2 = 100, U1 = 20, U2 = 150;
  
    printf("Введите кол-во точек для контрольного расчета: ");
    if (scanf("%d", &n) != 1 || n <= 1) {
        fprintf(stderr, "Ошибка: Некорректное количество точек.\n");
        return 1;
    }

    t = (float*)malloc(n * sizeof(float));
    Uvx = (float*)malloc(n * sizeof(float));
    Uvix = (float*)malloc(n * sizeof(float));

    if (t == NULL || Uvx == NULL || Uvix == NULL) {
        fprintf(stderr, "Ошибка: Не удалось выделить память.\n");
        return 1;
    }

    while (choice != 4) {

    t_calc(t, tk, tn, &dt, n);   

    Uvx_calc(Uvx, &Uvx_max, &Uvx_min, t, n, t1, tn, a, b);

    Uvix_calc(Uvix, Uvx, n, Uvx1, Uvx2, U1, U2, &Uvix_max, &Uvix_min);

    print_func(t, Uvx, Uvix, n);

    leading_edge(Uvx, Uvix, Uvx_min, Uvix_min, Uvx_max, Uvix_max, &dlit_vx, &dlit_vix, dt, n);

    printf("Длина пререднего фронта для входного напряжения (Uvx): %f\n", dlit_vx);
    printf("Длина пререднего фронта для выходного напряжения (Uvix): %f\n", dlit_vix);
    
    free(t);
    free(Uvx);
    free(Uvix);
    printf("\nНажмите Enter для завершения...");
    while (getchar() != '\n');
    getchar();
    return 0;
    }
}