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


void Uvx_calc(float* Uvx, float* Uvx_max, float* Uvx_min, float* t, int n, float t1, float tn, float a, float b) {

    for (int i = 0; i < n; i++) {
        if (t[i] <= t1) {
            Uvx[i] = a * (t[i] - tn);
        } else {
            Uvx[i] = a * (t1 - tn) - b * (t[i] - t1);
        }

        if (Uvx[i] > *Uvx_max) {
            *Uvx_max = Uvx[i];
        }
        if (Uvx[i] < *Uvx_min) {
            *Uvx_min = Uvx[i];
        }
    }
}


void Uvix_calc(float* Uvix, float* Uvx, int n, float Uvx1, float Uvx2, float U1, float U2, float* Uvix_max, float* Uvix_min) {

    for (int i = 0; i < n; i++) {
        if (Uvx[i] < Uvx1) {
            Uvix[i] = U1;
        } else if (Uvx[i] <= Uvx2) {
            Uvix[i] = U1 + (((U2 - U1) * pow(Uvx[i] - Uvx1, 2)) /
                            pow(Uvx2 - Uvx1, 2));
        } else {
            Uvix[i] = U2;
        }

        if (Uvix[i] > *Uvix_max) {
            *Uvix_max = Uvix[i];
        }
        if (Uvix[i] < *Uvix_min) {
            *Uvix_min = Uvix[i];
        }
    }
}


void leading_edge(float* Uvx, float* Uvix, float Uvx_min, float Uvix_min, float Uvx_max, float Uvix_max, float* dlit_vx, float* dlit_vix, float dt, int n) {

    float Uvx_fr1 = Uvx_min + 0.9 * (Uvx_max - Uvx_min);
    float Uvix_fr1 = Uvix_min + 0.9 * (Uvix_max - Uvix_min);
    float Uvx_fr2 = Uvx_min + 0.1 * (Uvx_max - Uvx_min);
    float Uvix_fr2 = Uvix_min + 0.1 * (Uvix_max - Uvix_min);

    for (int i = 0; i < n - 1; i++)
        if (Uvx[i] > Uvx_fr2 && Uvx[i] < Uvx_fr1 && Uvx[i + 1] > Uvx[i]) {
            *dlit_vx += dt;
        }

    for (int i = 0; i < n - 1; i++)
        if (Uvix[i] > Uvix_fr2 && Uvix[i] < Uvix_fr1 && Uvix[i + 1] > Uvix[i]) {
            *dlit_vix += dt;
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

    fprintf(f1, "t\n");
    fprintf(f2, "Uvx\n");
    fprintf(f3, "Uvix\n");

    for (int i=0;i<n;i++) { 
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