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


void Uvx_calc(float* Uvx, float* t, int n, float t1, float tn, float a, float b) {
    for (int i = 0; i < n; i++) {
        if (t[i] <= t1) {
            Uvx[i] = a * (t[i] - tn);
        } else {
            Uvx[i] = a * (t1 - tn) - b * (t[i] - t1);
        }
    }
}


void Uvix_calc(float* Uvix, float* Uvx, int n, float Uvx1, float Uvx2, float U1, float U2) {
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