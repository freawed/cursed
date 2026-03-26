#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void t_calc(float* t, float tk, float tn, float* dt, int n) {
    *dt = (tk - tn) / (n - 1);
    for (int i = 0; i < n; i++) {
        t[i] = tn + i * *dt;
    } 
}


void Uvx_calc(float* Uvx, float* t, int n, float tn) {
    float t1 = 22.5, a = 12, b = 12;
    for (int i = 0; i < n; i++) {
        if (t[i] <= t1) {
            Uvx[i] = a * (t[i] - tn);
        } else {
            Uvx[i] = a * (t1 - tn) - b * (t[i] - t1);
        }
    }
}


void Uvix_calc(float* Uvix, float* Uvx, int n) {
    float Uvx1 = 20, Uvx2 = 100, U1 = 20, U2 = 150;
    for (int i = 0; i < n; i++) {
        if (Uvx[i] < Uvx1) {
            Uvix[i] = U1;
        } else if (Uvx[i] <= Uvx2) {
            Uvix[i] = U1 + (((U2 - U1) * pow(Uvx[i] - Uvx1, 2)) /
                            pow(Uvx2 - Uvx1, 2));
        } else {
            Uvix[i] = U2;
        }
    }
}


void leading_edge(float* U, float Umin, float Umax, float* dlit, float dt, int n) {
    *dlit = 0;
    float U_fr1 = Umin + 0.9 * (Umax - Umin);
    float U_fr2 = Umin + 0.1 * (Umax - Umin);

    for (int i = 0; i < n - 1; i++) {
        if (U[i] > U_fr2 && U[i] < U_fr1 && U[i + 1] > U[i]) {
            *dlit += dt;
        }
    }
}


void print_func(float* t, float* Uvx, float* Uvix, int n) {
    printf("\n");
    printf("+-----+----------+----------+----------+\n");
    printf("|  i  |    t     |   Uvx    |   Uvix   |\n");
    printf("+-----+----------+----------+----------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %3d | %8.3f | %8.3f | %8.3f |\n",
               i, t[i], Uvx[i], Uvix[i]);
    }
    printf("+-----+----------+----------+----------+\n");
}


void print_file_func(float* t, float* Uvx, float* Uvix, int n) {
    FILE *f1,*f2,*f3; 		 
    f1=fopen("massiv_t.txt","w");
    f2=fopen("massiv_Uvx.txt", "w"); 
    f3=fopen("massiv_Uvix.txt", "w");

    if (!f1 || !f2 || !f3) {
        printf("Ошибка открытия файла\n");
        exit(1);
    }
    for (int i=0;i < n; i++) { 
        fprintf(f1,"%6.3f\n",t[i]);
        fprintf(f2,"%6.3f\n", Uvx[i]);        
        fprintf(f3,"%6.3f\n",Uvix[i]);
    }
    fclose(f1);
    fclose(f2);                         
    fclose(f3);
}


void read_zast() {
    FILE *f=fopen("zast.txt","r"); 
    if (!f) {
        printf("Ошибка открытия файла zast.txt\n");
        return;
    }
    char ch;
    while (!feof(f)) {
        fscanf(f,"%c",&ch);            
       printf("%c",ch);
    }
    fclose(f);                                 
}


void min_max_U(float* U, float* Umin, float* Umax, int n) {
    for (int i = 0; i < n; i++) {
        if (U[i] > *Umax) {
            *Umax = U[i];
        }
        if (U[i] < *Umin) {
            *Umin = U[i];
        }
    }
}


double dlit_with_accuracy(float* t, float* Uvx, float* Uvix, double eps, float tn, float tk, int flag) {
    int n = 11;
    double p = 1;
    double par = 1e+10;
    float par1 = 0;
    float dt;
    
    while (p > eps) {
        float Uvx_max = -10000, Uvx_min = 10000;
        float Uvix_max = -10000, Uvix_min = 10000;
        
        t = (float*)malloc(n * sizeof(float));
        Uvx = (float*)malloc(n * sizeof(float));
        Uvix = (float*)malloc(n* sizeof(float));

        if (t == NULL || Uvx == NULL || Uvix == NULL) {
            fprintf(stderr, "Ошибка: Не удалось выделить память.\n");
            return 1;
        }     
        
        t_calc(t, tk, tn, &dt, n);   
        Uvx_calc(Uvx, t, n, tn);
        Uvix_calc(Uvix, Uvx, n);

        min_max_U(Uvx, &Uvx_min, &Uvx_max, n);
        min_max_U(Uvix, &Uvix_min, &Uvix_max, n);
        if (flag == 0) {
            leading_edge(Uvx, Uvx_min, Uvx_max, &par1, dt, n);
        } else {
            leading_edge(Uvix, Uvix_min, Uvix_max, &par1, dt, n);
        }
        
        if (par1 == 0) break;
        p = fabs(par - par1) / par1;

        par = par1;
        n = 2 * n;

        free(t);
        free(Uvx);
        free(Uvix);
    }
    return par;
}