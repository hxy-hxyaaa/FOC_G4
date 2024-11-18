#ifndef __OBSERVER_H_
#define __OBSERVER_H_
#include "observer.h"

#define UTILS_IS_NAN(x)		((x) != (x))
#define UTILS_NAN_ZERO(x)	(x = UTILS_IS_NAN(x) ? 0.0 : x)

void  utils_norm_angle_rad(float *angle);

typedef struct {
	float x1;         //a轴观测磁链
	
	float x2;         //b轴观测磁链
	
	float dt;
	
	float motore_ia;
	
	float motore_ib;	
	
	float motore_va;
	
	float motore_vb;		
	    
	float motore_l;        //电感
	
	float motore_l_dq_diff;//电感差
	
	float motore_r;	       //电阻
	
	float motore_lambda;    //永磁体磁链
	
	float motore_gamma;     //增益
	
	float motore_ang;       //观测角度

	
} observer_state;


typedef struct {
  float motor_angle_pu;//输入角度
	
	float pll_phase;//单位化角度
	
  float	pll_phase_var;//输出角度
	
	float pll_delta_theta;//角度误差
	
	float pll_speed_ver;//输出速度
	
	float pll_dt;
	
	float pll_kp;
	
	float pll_ki;
	
	float pll_bw;
} PLL_EASY ;

typedef struct {

	float pll_dt;
	
	float pll_kp;
	
	float pll_ki;
	
	float pll_bw;
	
	float pll_sin_data;
	
	float pll_cos_data;	
	
	float pll_err;	
	
	float pll_speeed;		

  float pll_e_speeed;	
	
  float pll_ang;	
	
} PLL_ang ;


typedef struct {
  float set;
	float real;
	float err;	
	float KP;
	float KI;	
	float KP_DATA;		
	float KI_DATA;			
	float OUT_DATA;			
  float KI_MAX;
	float OUT_MAX;
	
} PID_PI ;

#define SQ(x)				((x) * (x))


void  FOC_observer_init(observer_state *observer,float lq,float ld,float r,float flux,float g,float dt);
void  FOC_observer_set(observer_state *observer,float ia,float ib,float va,float vb);
void  FOC_observer_run(observer_state *observer);
float FOC_observer_get(observer_state *observer);



void   PLL_ESAY_init(PLL_EASY*pll,float dt,float bw);
void   PLL_ESAY_set(PLL_EASY*pll ,float ang);
void   PLL_ESAY_run(PLL_EASY*pll);
float  PLL_ESAY_get(PLL_EASY*pll);

void   PLL_ang_init(PLL_ang*pll,float dt,float bw);
void   PLL_ang_set (PLL_ang*pll ,float sin_data,float cos_data);
void   PLL_ang_run (PLL_ang*pll);
float  PLL_ang_get (PLL_ang*pll);


void   PI_init(PID_PI*PID , float dt,float bw,float L,float R,float V ,float I_MAX);
void   PI_set (PID_PI*PID , float set ,float real);
void   PI_run (PID_PI*PID);
float  PI_get (PID_PI*PID);

#endif

