#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
// chcp 65001 - для текста на русском в консоль



int main() {
    int choice = 0;
    int n;
    int file_size = 50;
    float dlit_vx = 0.0f, dlit_vix = 0.0f;
    float Uvx_max = -10000, Uvx_min = 10000, Uvix_max = -10000, Uvix_min = 10000; 
    float tn = 10, tk = 35, dt; // считать с клавиатуры потом
    // float t1 = 22.5, a = 12, b = 12;
    // float Uvx1 = 20, Uvx2 = 100, U1 = 20, U2 = 150;
                                  
    read_zast();
    printf("\n"); 

    printf("Введите кол-во точек для контрольного расчета: ");
    if (scanf("%d", &n) != 1 || n <= 1) {
        fprintf(stderr, "Ошибка: Некорректное количество точек.\n");
        return 1;
    }

    float *t, *Uvx, *Uvix;
    
    while (choice != 5) {
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

        switch (choice)
        {
        case 1:
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
            
            t_calc(t, tk, tn, &dt, n);   
            Uvx_calc(Uvx, t, n, tn);
            Uvix_calc(Uvix, Uvx, n);
            
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

            t_calc(t, tk, tn, &dt, file_size);   
            Uvx_calc(Uvx, t, file_size, tn);
            Uvix_calc(Uvix, Uvx, file_size);
            print_file_func(t, Uvx, Uvix, file_size);
            printf("Данные успешно сохранены в файлы\n");

            free(t);
            free(Uvx);
            free(Uvix);            
            break;
        case 4: 
            system("\"C:\\maxima-5.49.0\\bin\\wxmaxima.exe\" graf.wxmx");
            break;
        case 5:
            float eps;
            printf("Задайте начальную погрешность: ");
            scanf("%f", &eps);
            printf("\n");
            double dlit_Uvx = dlit_with_accuracy(t, Uvx, Uvix, eps, tn, tk, 0);
            double dlit_Uvix = dlit_with_accuracy(t, Uvix, Uvix, eps, tn, tk, 1);

            printf("Длительность переднего фронта для Uvx с погрешностью %f: %f\n", eps, dlit_Uvx);
            printf("Длительность переднего фронта для Uvix с погрешностью %f: %f\n", eps, dlit_Uvix);
        case 6:
            printf("Выход из программы\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    return 0;
}