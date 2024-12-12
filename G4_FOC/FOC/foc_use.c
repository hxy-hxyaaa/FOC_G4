#include "foc_use.h"
#include "main.h"
#include "math.h"
#include "arm_math.h"
/*
�ǶȲ��û���ֵ
*/


/**
***********************************************************************
* @brief:      foc_inverse_pc(foc_para_t *foc,float IQ,float ID,float ang)
* @param[in]:  foc  FOC�����ṹ��ָ��
* @retval:     void
* @details:    FOC�㷨����Ҫ���������任 
***********************************************************************
**/
void foc_transform_cp(foc_para_t *foc)
{
	  clarke_transform(foc);//CLARKE
	  park_transform(foc);//PACK
}

/**
***********************************************************************
* @brief:      foc_transform_cp(foc_para_t *foc,float IQ,float ID,float ang)
* @param[in]:  foc  FOC�����ṹ��ָ��
* @retval:     void
* @details:    FOC�㷨����Ҫ��������任
***********************************************************************
**/
void foc_inverse_pc(foc_para_t *foc)
{

    inverse_park(foc);//PARK��
	  //inverse_clarke(foc);//CLARKE��
	
}

/**
***********************************************************************
* @brief:      sin_cos_val(foc_para_t *foc)
* @param[in]:  foc  FOC�����ṹ��ָ��
* @retval:     void
* @details:    �����Ƕ� theta ��Ӧ�� sin �� cos ֵ
***********************************************************************
**/
void sin_cos_val(foc_para_t *foc)
{
    foc->sin_val = arm_sin_f32(foc->theta); 
    foc->cos_val = arm_cos_f32(foc->theta); 
}

/**
***********************************************************************
* @brief:      clarke_transform(foc_para_t *foc)
* @param[in]:  foc  FOC�����ṹ��ָ��
* @retval:     void
* @details:    Clarke�任���������ת��Ϊ Alpha-Beta ����ϵ�µĵ��� 
***********************************************************************
**/
    void clarke_transform(foc_para_t *foc)
{
    foc->i_alpha = foc->i_a-(foc->i_a + foc->i_b + foc->i_c)*ONE_BY_3;
    foc->i_beta = (foc->i_b - foc->i_c) * ONE_BY_SQRT3;
}

/**
***********************************************************************
* @brief:      inverse_clarke(foc_para_t *foc)
* @param[in]:  foc  FOC�����ṹ��ָ��
* @retval:     void
* @details:    ��Clarke�任�� Alpha-Beta ����ϵ�µĵ�ѹת��Ϊ�����ѹ 
***********************************************************************
**/
void inverse_clarke(foc_para_t *foc)
{
    foc->v_a = foc->v_alpha;
    foc->v_b = -0.5f * foc->v_alpha + SQRT3_BY_2 * foc->v_beta;
    foc->v_c = -0.5f * foc->v_alpha - SQRT3_BY_2 * foc->v_beta;
}

/**
***********************************************************************
* @brief:      void park_transform(foc_para_t *foc)
* @param[in]:  foc  FOC�����ṹ��ָ��
* @retval:     void
* @details:    Park�任�� Alpha-Beta ����ϵ�µĵ���ת��Ϊ dq ����ϵ�µĵ��� 
***********************************************************************
**/
void park_transform(foc_para_t *foc)
{
  	foc->i_d = foc->i_alpha * foc->cos_val + foc->i_beta  * foc->sin_val;
    foc->i_q = foc->i_beta  * foc->cos_val - foc->i_alpha * foc->sin_val;
}

/**
***********************************************************************
* @brief:      inverse_park(foc_para_t *foc)
* @param[in]:  foc  FOC�����ṹ��ָ��
* @retval:     void
* @details:    ��Park�任�� dq ����ϵ�µĵ�ѹת��Ϊ Alpha-Beta ����ϵ�µĵ�ѹ 
***********************************************************************
**/
void inverse_park(foc_para_t *foc)
{
    foc->v_alpha = (foc->v_d * foc->cos_val - foc->v_q * foc->sin_val);
    foc->v_beta  = (foc->v_d * foc->sin_val + foc->v_q * foc->cos_val);
}



void svpwm_midpoint(foc_para_t *foc)
{
	float va = foc->v_alpha;
	float vb = -0.5f * foc->v_alpha + SQRT3_BY_2 * foc->v_beta;
	float vc = -0.5f * foc->v_alpha - SQRT3_BY_2 * foc->v_beta;

	float vmax = max(max(va, vb), vc);
	float vmin = min(min(va, vb), vc);

	float vcom = (vmax + vmin) * 0.5f;

	foc->v_a = -(vcom - va) - 0.5f;
	foc->v_b = -(vcom - vb) - 0.5f;
	foc->v_c = -(vcom - vc) - 0.5f;
}  



	
