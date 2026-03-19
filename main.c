#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
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

    dt = (tk - tn) / (n - 1);
    for (i = 0; i < n; i++) {
        t[i] = tn + i * dt;
    }    



    for (i = 0; i < n; i++) {
        if (t[i] <= t1) {
            Uvx[i] = a * (t[i] - tn);
        } else {
            Uvx[i] = a * (t1 - tn) - b * (t[i] - t1);
        }
        
        
        if (Uvx[i] > Uvx_max) {
            Uvx_max = Uvx[i];
        }
        if (Uvx[i] < Uvx_min) {
            Uvx_min = Uvx[i];
        }
    }



    for (i = 0; i < n; i++) {
        if (Uvx[i] < Uvx1) {
            Uvix[i] = U1;
        } else if (Uvx[i] <= Uvx2) {
            Uvix[i] = U1 + (((U2 - U1) * pow((Uvx[i] - Uvx1), 2)) / pow((Uvx2 - Uvx1), 2));
        } else {
            Uvix[i] = U2;
        }
        

        if (Uvix[i] > Uvix_max) {
            Uvix_max = Uvix[i];
        }
        if (Uvix[i] < Uvix_min) {
            Uvix_min = Uvix[i];
        }
    }


    
    printf("\n");
    printf("-------------------------------------------------\n");
    printf("|  №  |    t   |   Uvx   |   Uvix  |\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("  %3d   %6.3f    %6.3f    %6.3f  \n", i, t[i], Uvx[i], Uvix[i]);
    }
    printf("-------------------------------------------------\n");



    Uvx_fr1 = Uvx_min + 0.9 * (Uvx_max - Uvx_min);
    Uvix_fr1 = Uvix_min + 0.9 * (Uvix_max - Uvix_min);
    Uvx_fr2 = Uvx_min + 0.1 * (Uvx_max - Uvx_min);
    Uvix_fr2 = Uvix_min + 0.1 * (Uvix_max - Uvix_min);

    for (int i=0; i<n-1; i++)
        if (Uvx[i]>Uvx_fr2 && Uvx[i]<Uvx_fr1 && Uvx[i+1]>Uvx[i]) {
            dlit_vx+=dt; 
        }
    for (int i=0; i<n-1; i++)
        if (Uvix[i]>Uvix_fr2 && Uvix[i]<Uvix_fr1 && Uvix[i+1]>Uvix[i]) {
            dlit_vix+=dt; 
        }

    printf("Длина пререднего фронта для входного напряжения (Uvx): %f\n", dlit_vx);
    printf("Длина пререднего фронта для выходного напряжения (Uvix):%f\n", dlit_vix);
    


    free(t);
    free(Uvx);
    free(Uvix);
    printf("\nНажмите Enter для завершения...");
    while (getchar() != '\n');
    getchar();
    return 0;
}