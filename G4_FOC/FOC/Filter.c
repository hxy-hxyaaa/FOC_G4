#include "Filter.h"
#include "stm32g4xx.h"                  // Device header
#include  <math.h>
#include "main.h"
#include "arm_math.h"
float speed1,speed2,speedt,speeda,speedf;





typedef struct {
    float a0, a1, a2;  // 分子系数
    float b1, b2;      // 分母系数
    float x1, x2;      // 输入历史
    float y1, y2;      // 输出历史
} LowPassFilter;

void init_low_pass_filter(LowPassFilter* filter, float sample_rate, float cutoff_freq, float damping_ratio)
{
    float omega = 2.0f * PI * cutoff_freq / sample_rate;
    float sn = sinf(omega);
    float cs = cosf(omega);
    float alpha = sn / (2.0f * damping_ratio);

    float a0_inv = 1.0f / (1.0f + alpha);

    // 计算滤波器系数
    filter->a0 = (1.0f - cs) * 0.5f * a0_inv;
    filter->a1 = (1.0f - cs) * a0_inv;
    filter->a2 = (1.0f - cs) * 0.5f * a0_inv;
    filter->b1 = -2.0f * cs * a0_inv;
    filter->b2 = (1.0f - alpha) * a0_inv;

    // 初始化历史值
    filter->x1 = filter->x2 = 0.0f;
    filter->y1 = filter->y2 = 0.0f;
}

float apply_low_pass_filter(LowPassFilter* filter, float input)
{
    // 应用滤波器
    float output = filter->a0 * input + filter->a1 * filter->x1 + filter->a2 * filter->x2
                   - filter->b1 * filter->y1 - filter->b2 * filter->y2;

    // 更新历史值
    filter->x2 = filter->x1;
    filter->x1 = input;
    filter->y2 = filter->y1;
    filter->y1 = output;

    return output;
}


//LowPassFilter my_fittle;


//void my_Filteriniy(void)
//{
//init_low_pass_filter(&my_fittle, 1000,  10,0.5f);





//}
//void my_Filterrun(void)
//{
//	speedt+=0.001f;
//if(speedt>=1000.0f)speedt-=1000.0f;
//	speed1=speeda+arm_sin_f32(speedf*2*3.141592654f*speedt);

//	speed2=apply_low_pass_filter(&my_fittle,speed1);
//	
//}





typedef struct {
    float a0, a1, a2;  // 分子系数
    float b1, b2;      // 分母系数
    float x1, x2;      // 输入历史
    float y1, y2;      // 输出历史
} NotchFilter;

void init_notch_filter(NotchFilter* filter, float sample_rate, float notch_freq, float bandwidth, float damping_ratio)
{
    float omega = 2.0f * PI * notch_freq / sample_rate;
    float alpha = sinf(omega) / (2.0f * damping_ratio);
    float beta = cosf(omega) * sinhf(logf(2.0f) / 2.0f * bandwidth * omega / sinf(omega));

    // 计算滤波器系数
    float a0 = 1.0f + alpha;
    filter->a0 = 1.0f;
    filter->a1 = -2.0f * cosf(omega);
    filter->a2 = 1.0f;
    filter->b1 = -2.0f * cosf(omega) / a0;
    filter->b2 = (1.0f - alpha) / a0;

    // 初始化历史值
    filter->x1 = filter->x2 = 0.0f;
    filter->y1 = filter->y2 = 0.0f;
}

float apply_notch_filter(NotchFilter* filter, float input)
{
    // 应用滤波器
    float output = filter->a0 * input + filter->a1 * filter->x1 + filter->a2 * filter->x2
                   - filter->b1 * filter->y1 - filter->b2 * filter->y2;

    // 更新历史值
    filter->x2 = filter->x1;
    filter->x1 = input;
    filter->y2 = filter->y1;
    filter->y1 = output;

    return output;
}


//NotchFilter my_fittle;

//void my_Filteriniy(void)
//{
//init_notch_filter(&my_fittle, 1000,  40, 5, 0.707);





//}


//void my_Filterrun(void)
//{
//	speedt+=0.001f;
//if(speedt>=1000.0f)speedt-=1000.0f;
//	speed1=speeda+arm_sin_f32(speedf*2*3.141592654f*speedt);

//	speed2=apply_notch_filter(&my_fittle,speed1);
//	
//}

typedef struct {
    float a0, a1, a2;  // 分子系数
    float b1, b2;      // 分母系数
    float z1, z2;      // 中间变量（延迟线）
} HighPassFilter;

void init_high_pass_filter(HighPassFilter* filter, float sample_rate, float cutoff_freq, float damping_ratio)
{
    float omega = 2.0f * PI * cutoff_freq / sample_rate;
    float sn = sinf(omega);
    float cs = cosf(omega);
    float alpha = sn / (2.0f * damping_ratio);

    float a0_inv = 1.0f / (1.0f + alpha);

    // 计算滤波器系数
    filter->a0 = a0_inv * (1.0f + cs) / 2.0f;
    filter->a1 = a0_inv * (-1.0f - cs);
    filter->a2 = filter->a0;
    filter->b1 = a0_inv * (-2.0f * cs);
    filter->b2 = a0_inv * (1.0f - alpha);

    // 初始化延迟线
    filter->z1 = filter->z2 = 0.0f;
}

float apply_high_pass_filter(HighPassFilter* filter, float input)
{
    // 应用滤波器
    float output = filter->a0 * input + filter->z1;
    filter->z1 = filter->a1 * input + filter->z2 - filter->b1 * output;
    filter->z2 = filter->a2 * input - filter->b2 * output;

    return output;
}


//HighPassFilter my_fittle;

//void my_Filteriniy(void)
//{
//init_high_pass_filter(&my_fittle, 1000,  40,  0.707);





//}
//void my_Filterrun(void)
//{
//	speedt+=0.001f;
//if(speedt>=1000.0f)speedt-=1000.0f;
//	speed1=speeda+arm_sin_f32(speedf*2*3.141592654f*speedt);

//	speed2=apply_high_pass_filter(&my_fittle,speed1);
//	
//}

typedef struct {
    float a0, a1, a2;  // 分子系数
    float b1, b2;      // 分母系数
    float z1, z2;      // 中间变量（延迟线）
} BiquadFilter;

void init_biquad_band_pass_filter(BiquadFilter* filter, float sample_rate, float center_freq, float bandwidth, float damping_ratio)
{
    float omega = 2.0f * PI * center_freq / sample_rate;
    float sn = sinf(omega);
    float cs = cosf(omega);
    float alpha = sn * sinhf(logf(2.0f) / 2.0f * bandwidth * omega / sn) / (2.0f * damping_ratio);

    float a0_inv = 1.0f / (1.0f + alpha);

    // 计算滤波器系数
    filter->a0 = alpha * a0_inv;
    filter->a1 = 0.0f;
    filter->a2 = -alpha * a0_inv;
    filter->b1 = -2.0f * cs * a0_inv;
    filter->b2 = (1.0f - alpha) * a0_inv;

    // 初始化延迟线
    filter->z1 = filter->z2 = 0.0f;
}

float apply_biquad_filter(BiquadFilter* filter, float input)
{
    // 应用滤波器
    float output = filter->a0 * input + filter->z1;
    filter->z1 = filter->a1 * input + filter->z2 - filter->b1 * output;
    filter->z2 = filter->a2 * input - filter->b2 * output;

    return output;
}


//BiquadFilter my_fittle;

//void my_Filteriniy(void)
//{
//init_biquad_band_pass_filter(&my_fittle, 1000,  20, 5, 0.707);



//}

//void my_Filterrun(void)
//{
//	speedt+=0.001f;
//if(speedt>=1000.0f)speedt-=1000.0f;
//	speed1=speeda+arm_sin_f32(speedf*2*3.141592654f*speedt);

//	speed2=apply_biquad_filter(&my_fittle,speed1);
//	
//}


typedef struct {
    float a0, a1, a2;  // 分子系数
    float b1, b2;      // 分母系数
    float z1, z2;      // 中间变量（延迟线）
    float sample_rate;
    float cutoff_freq;
    float damping_ratio;
} AdaptiveLowPassFilter;

void init_adaptive_low_pass_filter(AdaptiveLowPassFilter* filter, float sample_rate, float cutoff_freq, float damping_ratio)
{
    filter->sample_rate = sample_rate;
    filter->cutoff_freq = cutoff_freq;
    filter->damping_ratio = damping_ratio;
    filter->z1 = filter->z2 = 0.0f;

    // 初始化滤波器系数
    float omega = 2.0f * PI * cutoff_freq / sample_rate;
    float sn = sinf(omega);
    float cs = cosf(omega);
    float alpha = sn / (2.0f * damping_ratio);
    float a0_inv = 1.0f / (1.0f + alpha);

    filter->a0 = a0_inv * (1.0f - cs) / 2.0f;
    filter->a1 = a0_inv * (1.0f - cs);
    filter->a2 = a0_inv * (1.0f - cs) / 2.0f;
    filter->b1 = a0_inv * (-2.0f * cs);
    filter->b2 = a0_inv * (1.0f - alpha);
}

void update_filter_coefficients(AdaptiveLowPassFilter* filter, float new_cutoff_freq)
{
    filter->cutoff_freq = new_cutoff_freq;

    // 更新滤波器系数
    float omega = 2.0f * PI * new_cutoff_freq / filter->sample_rate;
    float sn = sinf(omega);
    float cs = cosf(omega);
    float alpha = sn / (2.0f * filter->damping_ratio);
    float a0_inv = 1.0f / (1.0f + alpha);

    filter->a0 = a0_inv * (1.0f - cs) / 2.0f;
    filter->a1 = a0_inv * (1.0f - cs);
    filter->a2 = a0_inv * (1.0f - cs) / 2.0f;
    filter->b1 = a0_inv * (-2.0f * cs);
    filter->b2 = a0_inv * (1.0f - alpha);
}

float apply_adaptive_low_pass_filter(AdaptiveLowPassFilter* filter, float input)
{
    // 应用滤波器
    float output = filter->a0 * input + filter->z1;
    filter->z1 = filter->a1 * input + filter->z2 - filter->b1 * output;
    filter->z2 = filter->a2 * input - filter->b2 * output;

    return output;
}




AdaptiveLowPassFilter my_fittle;

void my_Filteriniy(void)
{
init_adaptive_low_pass_filter(&my_fittle, 1000,  100,0.507f);



}

	float data;
void my_Filterrun(void)
{
	speedt+=0.001f;
if(speedt>=1000.0f)speedt-=1000.0f;
	speeda=10*arm_sin_f32(speedt*speedf);
	speed1=speeda+0.1*speeda*arm_sin_f32(0.1*speeda*2*3.141592654f*speedt);

	if(speeda>=0)data=speeda;
	else data=-speeda;
//    adapt_cutoff_frequency(&my_fittle, speed1, threshold);  // 自适应调整截止频率
    update_filter_coefficients(&my_fittle,data+10);
	speed2 = apply_adaptive_low_pass_filter(&my_fittle, speed1);
 

	
}
