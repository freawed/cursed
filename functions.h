#ifndef UTILS_FUNCTIONS_H
#define UTILS_FUNCTIONS_H

void t_calc(float* t, float tk, float tn, float* dt, int n);
void Uvx_calc(float* Uvx, float* Uvx_max, float* Uvx_min, float* t, int n, float t1, float tn, float a, float b);
void Uvix_calc(float* Uvix, float* Uvx, int n, float Uvx1, float Uvx2, float U1, float U2, float* Uvix_max, float* Uvix_min);
void leading_edge(float* Uvx, float* Uvix, float Uvx_min, float Uvix_min, float Uvx_max, float Uvix_max, float* dlit_vx, float* dlit_vix, float dt, int n);

#endif