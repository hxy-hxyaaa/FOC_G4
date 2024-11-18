#ifndef _FOC_USE_H
#define _FOC_USE_H

#include "main.h"

void foc_transform_cp(foc_para_t *foc);
void foc_inverse_pc(foc_para_t *foc);

void sin_cos_val(foc_para_t *foc);

void clarke_transform(foc_para_t *foc);
void inverse_clarke(foc_para_t *foc);

void park_transform(foc_para_t *foc);
void inverse_park(foc_para_t *foc);
void svpwm_midpoint(foc_para_t *foc);

#endif
