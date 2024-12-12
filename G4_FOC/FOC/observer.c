#include "observer.h"
#include "stm32g4xx.h"                  // Device header
#include  <math.h>
#include "main.h"

#include "arm_math.h"
   void utils_norm_angle_rad(float *angle) {
	while (*angle < - M_PI)  { *angle += 2.0 * M_PI;  }
	while (*angle >=  M_PI)  { *angle -= 2.0 * M_PI;  }
}



void FOC_observer_init(observer_state *observer,float lq,float ld,float r,float flux,float g,float dt )
	
{
	observer->motore_l=(lq+ld)*0.5f;
	observer->motore_l_dq_diff=ld-lq;
  observer->motore_r=r;
	observer->motore_lambda=flux;
	observer->motore_gamma=g;
  observer->dt=dt;

}

void FOC_observer_set(observer_state *observer,float ia,float ib,float va,float vb)
	
{  
	observer->motore_ia=ia;
	observer->motore_ib=ib;
  observer->motore_va=va;
  observer->motore_vb=vb;	

}

void FOC_observer_run(observer_state *observer)
	
{
float l_ia=observer->motore_l*observer->motore_ia;//电流产生的磁链
float l_ib=observer->motore_l*observer->motore_ib;	

float r_ia=observer->motore_r*observer->motore_ia;//电阻产生的电压
float r_ib=observer->motore_r*observer->motore_ib;	
	
float gamma_half=	observer->motore_gamma*0.5f;    //半增益
	
float err=SQ(observer->motore_lambda)-(SQ(observer->x1-l_ia)+SQ(observer->x2-l_ib));//误差
	
	if(err>0)err=0;
	
	//观测器更新
	float x1_dot=observer->motore_va-r_ia+gamma_half*(observer->x1-l_ia)*err;
	float x2_dot=observer->motore_vb-r_ib+gamma_half*(observer->x2-l_ib)*err;	
	
	observer->x1+=x1_dot*observer->dt;
	observer->x2+=x2_dot*observer->dt;
	
	UTILS_NAN_ZERO(observer->x1);
  UTILS_NAN_ZERO(observer->x2);
	
  observer->motore_cos_data = (observer->x1 - l_ia)/observer->motore_lambda;
	observer->motore_sin_data	= (observer->x2 - l_ib)/observer->motore_lambda;	
	/*反切获取角度  实现*/
	observer->motore_ang=atan2f(observer->motore_cos_data ,observer->motore_sin_data ) ;

	
}



float FOC_observer_get(observer_state *observer)
	
{
return observer->motore_ang;
}




void PLL_ESAY_init(PLL_EASY*pll,float dt,float bw)
{
 
  pll->pll_dt=dt;
  pll->pll_bw=bw;
  pll->pll_kp = pll->pll_bw * 8.9f * pll->pll_dt;
  pll->pll_ki =
	      (pll->pll_bw * 8.9f * pll->pll_bw * 8.9f) / 2.0f *
         pll->pll_dt;
}

void PLL_ESAY_set(PLL_EASY*pll ,float ang)
{
pll->motor_angle_pu=ang;
}

void PLL_ESAY_run(PLL_EASY*pll)
{
	UTILS_NAN_ZERO(pll->pll_phase_var);//nan判断
	
        pll->pll_phase = pll->motor_angle_pu ;          //转换为弧度制   
	      pll->pll_delta_theta =                          //计算角度误差
            pll->pll_phase -
            (pll->pll_phase_var +
             pll->pll_dt * pll->pll_speed_ver);
	
  utils_norm_angle_rad(&pll->pll_delta_theta);    
  UTILS_NAN_ZERO(pll->pll_speed_ver); //nan判断

	      pll->pll_phase_var +=                          //计算输出角度
            (pll->pll_speed_ver * pll->pll_dt +
             pll->pll_kp * pll->pll_delta_theta);
	
  utils_norm_angle_rad(&pll->pll_phase_var);  	
	
        pll->pll_speed_ver +=                          //计算速度
            pll->pll_ki * pll->pll_delta_theta;
}

float  PLL_ESAY_get(PLL_EASY*pll)
{
return pll->pll_speed_ver;
}


void PLL_ang_init(PLL_ang*pll,float dt,float bw)
{
	
  pll->pll_dt=dt;
  pll->pll_bw=bw;
  pll->pll_kp = pll->pll_bw * 8.9f * pll->pll_dt;
  pll->pll_ki =
	      (pll->pll_bw * 8.9f * pll->pll_bw * 8.9f) / 2.0f *
         pll->pll_dt;
}

void PLL_ang_set(PLL_ang*pll ,float sin_data,float cos_data)
{
pll->pll_sin_data=sin_data;
pll->pll_cos_data=cos_data;
}

void PLL_ang_run(PLL_ang*pll)
{

	UTILS_NAN_ZERO(pll->pll_ang); //nan判断
pll->pll_err=pll->pll_sin_data*cosf(pll->pll_ang+pll->pll_speeed*pll->pll_dt)-pll->pll_cos_data*sinf(pll->pll_ang+pll->pll_speeed*pll->pll_dt);//sin(a-b)=sin(a)cos(b)-cos(a)sin(b)
 
	
utils_norm_angle_rad(&pll->pll_err);    


  UTILS_NAN_ZERO(pll->pll_speeed); //nan判断
pll->pll_ang += (pll->pll_speeed * pll->pll_dt + pll->pll_kp * pll->pll_err);    //计算输出角度
           
utils_norm_angle_rad(&pll->pll_ang);                                                    //-pi~pi             
	
pll->pll_speeed+=pll->pll_ki*pll->pll_err;                  //pi
	

	
}

float PLL_ang_get(PLL_ang*pll)
{
return pll->pll_ang;
}

////    // 设置ID默认PI
////    // 使用电机参数计算  连续时间下 Kp = 2*pi*f_c*L / U_scale; Ki = R / L;
//    float32_t RoverLs_d = m1_motor_param_data.motor_rs / m1_motor_param_data.motor_ls_d;
//    float32_t Kp = 2.0f * PI * m1_motor_param_data.motor_ls_d *
//         (m1_motor_param_data.current_ctrl_loop_id_bw /
//          m1_motor_param_data.motor_rated_voltage_v);           // TODO:200.0代表的是带宽?
//    float32_t Ki = RoverLs_d * rst_ctrl_loop_proc.motor1.ctrl_period_sec; // TODO:0.25代表?
//    float32_t kd = 0.0f;

void   PI_init(PID_PI*PID , float dt,float bw,float L,float R,float V,float I_MAX)

{
PID->KP=2*M_PI*bw*L/V;
PID->KI=(R/L)*dt;
PID->OUT_MAX=V;
PID->KI_MAX=I_MAX;
}
void   PI_set (PID_PI*PID , float set ,float real)
	
{
PID->set=set;
PID->real=real;
}
void   PI_run (PID_PI*PID)
	
{
	PID->err=PID->set-PID->real;
	PID->KP_DATA=PID->KP*PID->err;
	PID->KI_DATA+=PID->KP_DATA;
	if(PID->KI_DATA>= PID->KI_MAX)PID->KI_DATA= PID->KI_MAX;
	if(PID->KI_DATA<=-PID->KI_MAX)PID->KI_DATA=-PID->KI_MAX;	
	PID->OUT_DATA=PID->KP_DATA+PID->KI_DATA;
  if(PID->OUT_DATA>= PID->OUT_MAX)PID->OUT_DATA= PID->OUT_MAX;
  if(PID->OUT_DATA<=-PID->OUT_MAX)PID->OUT_DATA=-PID->OUT_MAX;	
}
	
float  PI_get (PID_PI*PID)
{
return PID->OUT_DATA;
}
