#ifndef UTILS_FUNCTIONS_H
#define UTILS_FUNCTIONS_H

void t_calc(float* t, float tk, float tn, float* dt, int n);
void print_func(float* t, float* Uvx, float* Uvix, int n);
void Uvx_calc(float* Uvx, float* t, int n, float t1, float tn, float a, float b);
void Uvix_calc(float* Uvix, float* Uvx, int n, float Uvx1, float Uvx2, float U1, float U2);
void leading_edge(float* U, float Umin, float Umax, float* dlit, float dt, int n);
void print_file_func(float* t, float* Uvx, float* Uvix, int n);
void read_zast();
void min_max_U(float* U, float* Umin, float* Umax, int n);
#endif