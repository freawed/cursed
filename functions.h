#ifndef UTILS_FUNCTIONS_H
#define UTILS_FUNCTIONS_H

void t_calc(float* t, float tk, float tn, float* dt, int n);
void print_func(float* t, float* Uvx, float* Uvix, int n);
void Uvx_calc(float* Uvx, float* t, int n, float tn);
void Uvix_calc(float* Uvix, float* Uvx, int n);
void leading_edge(float* U, float Umin, float Umax, float* dlit, float dt, int n);
void print_file_func(float* t, float* Uvx, float* Uvix, int n);
void read_zast();
void min_max_U(float* U, float* Umin, float* Umax, int n);
double dlit_with_accuracy(float* t, float* Uvx, float* Uvix, double eps, float tn, float tk, int flag);
#endif