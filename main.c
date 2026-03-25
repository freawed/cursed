#include "functions.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// chcp 65001 - для текста на русском в консоль



int main() {
    int choice = 0;
    float *t, *Uvx, *Uvix;
    int n;
    float dlit_vx = 0.0f, dlit_vix = 0.0f;
    float Uvx_max = -10000, Uvx_min = 10000, Uvix_max = -10000, Uvix_min = 10000; 
    float tn = 10, tk = 35, dt; // считать с клавиатуры потом
    float t1 = 22.5, a = 12, b = 12;
    float Uvx1 = 20, Uvx2 = 100, U1 = 20, U2 = 150;
                                  
    read_zast();
    printf("\n"); 

    printf("Введите кол-во точек для контрольного расчета: ");
    if (scanf("%d", &n) != 1 || n <= 1) {
        fprintf(stderr, "Ошибка: Некорректное количество точек.\n");
        return 1;
    }

    t = (float*)malloc((n + 50) * sizeof(float));
    Uvx = (float*)malloc((n + 50) * sizeof(float));
    Uvix = (float*)malloc((n + 50) * sizeof(float));

    if (t == NULL || Uvx == NULL || Uvix == NULL) {
        fprintf(stderr, "Ошибка: Не удалось выделить память.\n");
        return 1;
    }

    t_calc(t, tk, tn, &dt, n);   
    Uvx_calc(Uvx, t, n, t1, tn, a, b);
    Uvix_calc(Uvix, Uvx, n, Uvx1, Uvx2, U1, U2);

    min_max_U(Uvx, &Uvx_min, &Uvx_max, n);
    min_max_U(Uvix, &Uvix_min, &Uvix_max, n);

    leading_edge(Uvx, Uvx_min, Uvx_max, &dlit_vx, dt, n);
    leading_edge(Uvix, Uvix_min, Uvix_max, &dlit_vix, dt, n);
    
    while (choice != 5) {
        printf("\n");
		printf("======Меню======\n");
		printf("1. Вывод таблицы входного и выходного напряжения в терминал\n");
		printf("2. Вывод продолжительности переднего фронта в терминал\n");
		printf("3. Сохранение данных в файл\n");
		printf("4. Открытие графиков в программе wxMaxima\n");
        printf("5. Выход из программы\n");
    	printf("Выберите пункт меню: ");
    	scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            t_calc(t, tk, tn, &dt, n);   
            Uvx_calc(Uvx, t, n, t1, tn, a, b);
            Uvix_calc(Uvix, Uvx, n, Uvx1, Uvx2, U1, U2);
            print_func(t, Uvx, Uvix, n);
            break;
        case 2:
            printf("Длина переднего фронта для входного напряжения (Uvx): %f\n", dlit_vx);
            printf("Длина переднего фронта для выходного напряжения (Uvix): %f\n", dlit_vix);
            break;
        case 3:
            t_calc(t, tk, tn, &dt, 50);   
            Uvx_calc(Uvx, t, 50, t1, tn, a, b);
            Uvix_calc(Uvix, Uvx, 50, Uvx1, Uvx2, U1, U2);
            print_file_func(t, Uvx, Uvix, 50);
            printf("Данные успешно сохранены в файлы\n");
            break;
        case 4: 
            system("\"C:\\maxima-5.49.0\\bin\\wxmaxima.exe\" graf.wxmx");
            break;
        case 5:
            printf("Выход из программы\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    free(t);
    free(Uvx);
    free(Uvix);
    return 0;
}