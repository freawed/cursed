#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
// chcp 65001



int main() {
    int choice = 0;
    int n = 0;
    int file_size = 50;
    float eps;
    float dlit_vx = 0.0f, dlit_vix = 0.0f;
    float Uvx_max = -10000, Uvx_min = 10000, Uvix_max = -10000, Uvix_min = 10000; 
    float tn, tk, dt;
    // tn = 10, tk = 35
          
    read_zast();
    printf("\n"); 
    
    input_params(&n, &tn, &tk);
    float *t, *Uvx, *Uvix;
      
    while (choice != 6 ) {
        printf("\n");
		printf("======Меню======\n");
		printf("1. Вывод таблицы входного и выходного напряжения в терминал\n");
		printf("2. Вывод продолжительности переднего фронта в терминал\n");
		printf("3. Сохранение данных в файл\n");
		printf("4. Открытие графиков в программе wxMaxima\n");
        printf("5. Расчет параметра с заданной погрешностью\n");
        printf("6. Выход из программы\n");
    	printf("Выберите пункт меню: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода! Введите число.\n");
            while (getchar() != '\n');
            continue;
        }
        printf("\n");

        switch (choice) {
        case 1:
            t = (float*)malloc(n * sizeof(float));
            Uvx = (float*)malloc(n * sizeof(float));
            Uvix = (float*)malloc(n* sizeof(float));

            if (t == NULL || Uvx == NULL || Uvix == NULL) {
                fprintf(stderr, "Ошибка: Не удалось выделить память.\n");
                return 1;
            }   
            calc_all(t, Uvx, Uvix, tn, tk, &dt, n);
            print_func(t, Uvx, Uvix, n);

            free(t);
            free(Uvx);
            free(Uvix);
            break;

        case 2:
            Uvx_max = -10000, Uvx_min = 10000;
            Uvix_max = -10000, Uvix_min = 10000;
            
            t = (float*)malloc(n * sizeof(float));
            Uvx = (float*)malloc(n * sizeof(float));
            Uvix = (float*)malloc(n* sizeof(float));

            if (t == NULL || Uvx == NULL || Uvix == NULL) {
                fprintf(stderr, "Ошибка: Не удалось выделить память.\n");
                return 1;
            }
            
            calc_all(t, Uvx, Uvix, tn, tk, &dt, n);

            min_max_U(Uvx, &Uvx_min, &Uvx_max, n);
            min_max_U(Uvix, &Uvix_min, &Uvix_max, n);

            leading_edge(Uvx, Uvx_min, Uvx_max, &dlit_vx, dt, n);
            leading_edge(Uvix, Uvix_min, Uvix_max, &dlit_vix, dt, n);

            printf("Длина переднего фронта для входного напряжения (Uvx): %f\n", dlit_vx);
            printf("Длина переднего фронта для выходного напряжения (Uvix): %f\n", dlit_vix);

            free(t);
            free(Uvx);
            free(Uvix);            
            break;

        case 3:
            t = (float*)malloc(file_size * sizeof(float));
            Uvx = (float*)malloc(file_size * sizeof(float));
            Uvix = (float*)malloc(file_size * sizeof(float));

            if (t == NULL || Uvx == NULL || Uvix == NULL) {
                fprintf(stderr, "Ошибка: Не удалось выделить память.\n");
                return 1;
            }

            calc_all(t, Uvx, Uvix, tn, tk, &dt, file_size);
            print_file_func(t, Uvx, Uvix, file_size);
            printf("Данные успешно сохранены в файл\n");

            free(t);
            free(Uvx);
            free(Uvix);            
            break;

        case 4: 
            system("\"C:\\maxima-5.49.0\\bin\\wxmaxima.exe\" graf.wxmx");
            break;
            
        case 5:
            printf("Задайте начальную погрешность: ");
            scanf("%f", &eps);
            if (eps <= 0) {
                printf("Ошибка: eps должен быть > 0\n");
                break;
            }
            printf("\n");
            printf("Расчет параметра с погрешностью для Uvx:\n");
            dlit_with_accuracy(eps, tn, tk, 0);
            printf("\n");
            printf("Расчет параметра с погрешностью для Uvix:\n");
            dlit_with_accuracy(eps, tn, tk, 1);
            break;
                 
        case 6:
            printf("Выход из программы\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    return 0;
}
