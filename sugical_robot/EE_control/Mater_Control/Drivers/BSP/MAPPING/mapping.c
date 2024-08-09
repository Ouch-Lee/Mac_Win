#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "./BSP/MAPPING/mapping.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/sys/sys.h"
#include "./Inc/DataTransmission.h"
#include "./BSP/KEY/key.h"


// define varibles
//float motor_angles[10] = {2* PI/3, PI/3, PI/6, PI/6, 5*PI/6, 4* PI/5, PI/2, PI/6, -PI/6, PI/3};
float motor_angles[10] = {0, 0, 0, 0, 0, 0.988733621083509f,	1.27483296840274f,	-1.17185547762446f,	1.29865855281773f,	0.415818835576429f};
float joint_angles[10];  // rad not degree
float slave_joint_angles[10]; // rad
float slave_unit_joint_angles[10]; //rad 
extern float motor_anlge_offset[10];


void Mapping_ABS(float the_motor_angles[])  // the_motor_angles为传入的测量值，长度为10
{
		mapping_master_drive_joints(the_motor_angles, ABS_MODE); // 从电机角度到等效主端关节空间
		mapping_joints_master_slave(joint_angles); // 从主关节空间到从关节空间
		mapping_slave_segment_section(slave_joint_angles); // 从关节空间到单元空间
		for(int i=0; i<10; i++)
			{
					if(i==0||i==5)
					{
						continue;
					}
					slave_unit_joint_angles[i] = radians_to_degrees(slave_unit_joint_angles[i]);
			}
}

void Mapping_INCREMENT(float the_motor_angles[])
{
	mapping_master_drive_joints(the_motor_angles, INCREMENT_MODE); // 先得到主端关节空间，然后让关节看空间和从端电机一一对应
	
}
/**
* 这个函数用于计算平面五连杆给定两个驱动关节角度 u1, u5 后
* 末端点平面上坐标和第四个（被动）关节角度 u4
* input : u1, u5两个驱动关节角度
* output: 存放平面五连杆参数的struct类型
*/

Plannar5BarFKResult plannar_5_bar_fk(float u1, float u5) {
		// 先把 u1，u5转换成弧度制
		u1 = degrees_to_radians(u1);
		u5 = degrees_to_radians(u5);
    float xb = l1 * cos(u1);
    float yb = l1 * sin(u1);
    float xd = l5 + l4 * cos(u5);
    float yd = l4 * sin(u5);
    float lbd = sqrt(pow(xd - xb, 2) + pow(yd - yb, 2));


    Plannar5BarFKResult result;

    float u2_1 = acos((pow(l2, 2) + pow(lbd, 2) - pow(l3, 2)) / (2 * l2 * lbd));
    float u3_1 = acos((pow(l3, 2) + pow(lbd, 2) - pow(l2, 2)) / (2 * l3 * lbd));
    float u2_2 = atan2(yd - yb, xd - xb);
    float u3_2 = u2_2;
    float u2 = u2_1 + u3_2;
    float u3_t = u3_1 - u3_2;
    float u3 = PI - u3_t;

    result.xc = xb + l2 * cos(u2);
    result.yc = yb + l2 * sin(u2);
    result.u4 = u3;
    return result;
}

/**
* 作用：将主端驱动空间的角度也即电机编码器角
* 度转化为等效构型关节空间角度并存于joint_angles中
* input : motor_angles[] 长度为10的float数组存编码器测量角度
* output: void
*/

void calculate_joint_angles(float the_cja_motor_angles[], int offset, int this_control_mode)
{
	Plannar5BarFKResult fkResult = plannar_5_bar_fk(the_cja_motor_angles[offset], the_cja_motor_angles[offset + 1]);
	float xc = fkResult.xc;
	float yc = fkResult.yc;
	float u4 = fkResult.u4;

	if (this_control_mode) // 
	{ // 增量模式使用deg
		joint_angles[offset] = atan2((0.5f * l5 - xc), yc); // 弧度制
		joint_angles[offset + 1] = sqrt(pow((xc - 0.5f * l5), 2) + pow(yc, 2));
		joint_angles[offset + 2] =degrees_to_radians(the_cja_motor_angles[offset + 2]) - (joint_angles[offset] + (PI - u4) - 0.2f * PI);
		joint_angles[offset] = radians_to_degrees(joint_angles[offset]);
		joint_angles[offset + 2] = radians_to_degrees(joint_angles[offset + 2]);
		joint_angles[offset + 3] =the_cja_motor_angles[offset + 3];
		joint_angles[offset + 4] =the_cja_motor_angles[offset + 4];
	}else
	{ // 绝对模式为了后续计算使用rad
		joint_angles[offset] = atan2((0.5f * l5 - xc), yc); // 弧度制
		joint_angles[offset + 1] = sqrt(pow((xc - 0.5f * l5), 2) + pow(yc, 2));
		joint_angles[offset + 2] =degrees_to_radians(the_cja_motor_angles[offset + 2]) - (joint_angles[offset] + (PI - u4) - 0.2f * PI);
		joint_angles[offset + 3] =degrees_to_radians(the_cja_motor_angles[offset + 3]);
		joint_angles[offset + 4] =degrees_to_radians(the_cja_motor_angles[offset + 4]);
	}
	


}


void mapping_master_drive_joints(float the_motor_angles[], int this_control_mode)
{	
//	printf("left: \r\n");
	calculate_joint_angles(the_motor_angles, 0, this_control_mode);  // left hand
//	state_lr = 1;
	calculate_joint_angles(the_motor_angles, 5, this_control_mode);  // right hand
//	state_lr = 0;
}

/**
* 作用：将主端关节空间角度转换为从端关节空间
* 并存于slave_joint_angles中
* input : joint_angles[] 长度为10的float数组存编码器测量角度
* output: void
*/
void calculate_slave_joint_angles(float the_csja_joint_angles[], int offset)
{		
		float theta1 = the_csja_joint_angles[offset];
		float d2 = the_csja_joint_angles[offset + 1];
		float theta3 = the_csja_joint_angles[offset+2];
		float theta4 = the_csja_joint_angles[offset+3];
		float theta5 = the_csja_joint_angles[offset+4];
		float px = -L_m * cos(theta4) * sin(theta3 + theta1) - d2 * sin(theta1);
		float pz = d2 * cos(theta1) + L_m * cos(theta4) * cos(theta3 + theta1);
		float initial_guess = 1.0;
    float tolerance = 1e-4;
    int max_iterations = 400;
		float theta_3e = newton_method(px, theta1, theta3, theta4, initial_guess, tolerance, max_iterations);

		
		float alpha2 = theta1 + theta3 - theta_3e;
    float alpha4 = acos(cos(theta_3e) * cos(theta4));
    // 取 theta3, theta4 的正负号
    float sign_3 = (theta_3e > 0) ? 1 : (theta_3e < 0) ? -1 : 0;
    float sign_4 = (theta4 > 0) ? 1 : (theta4 < 0) ? -1 : 0;
    // 计算 Phi3
    float Phi3 = sign_4 * acos(cos(theta4) * sin(theta_3e) / sin(alpha4));
    // 计算 Delta_x
    float Delta_x = sign_3 * acos(cos(theta_3e) * sin(Phi3)) + Phi3 - PI / 2;
    // 计算 Theta5
    float Theta5 = theta5 + Delta_x;
		/*需要你补齐的代码: 计算pz_s*/
		float pz_s = (S1_s * sin(alpha2) / alpha2)
               + (S2_s / alpha4) * (sin(alpha4) * cos(alpha2) - (1 - cos(alpha4)) / 2 * sin(alpha2) * cos(Phi3))
               + L_s * (cos(alpha4) * cos(alpha2) - sin(alpha4) * sin(alpha2) * cos(Phi3)); // TODO
		float D1 = pz - pz_s;
		// 填充 slave_joint_angles 数组
		slave_joint_angles[offset] = D1;
		slave_joint_angles[offset+1] = alpha2;
		slave_joint_angles[offset+2] = Phi3;
		slave_joint_angles[offset+3] = alpha4;
		slave_joint_angles[offset+4] = Theta5;

}

void mapping_joints_master_slave(float the_joint_angles[])
{
		calculate_slave_joint_angles(the_joint_angles, 0);
		calculate_slave_joint_angles(the_joint_angles, 5);
}

/* 牛顿迭代法神中神，用于求解theta3_e */
#include <math.h>
#include <stdio.h>

#define S1_s 10
#define S2_s 18
#define L_s 6

float newton_method(float px, float theta1, float theta3, float theta4, float initial_guess, float tolerance, int max_iterations) {
    float x = initial_guess;
    float s1 = S1_s;
    float s2 = S2_s;
    float l = L_s;
    float A = theta1 + theta3;
    float c4 = cos(theta4);
    float fx, dfx;
    int iteration = 0;

    while (iteration < max_iterations) {
        // 计算函数值
        float alpha2 = A - x;
        float alpha4 = acos(cos(x) * c4);
        float Phi3 = acos(c4 * sin(x) / sin(alpha4));
        float d2 = (2 * s1 / alpha2) * sin(alpha2 / 2);
        float d4 = (2 * s2 / alpha4) * sin(alpha4 / 2);

        fx = px - (-d2 * sin(alpha2 / 2) - d4 * (sin(alpha4 / 2) * cos(Phi3) * cos(alpha2) + cos(alpha4 / 2) * sin(alpha2)) - l * (sin(alpha4) * cos(Phi3) * cos(alpha2) + cos(alpha4) * sin(alpha2)));

        // 计算导数值（使用中央差分法近似导数）
        float h = 1e-6;
        float x_h1 = x + h;
        float x_h2 = x - h;

        // 计算函数值变化
        float alpha2_h1 = A - x_h1;
        float alpha4_h1 = acos(cos(x_h1) * c4);
        float Phi3_h1 = acos(c4 * sin(x_h1) / sin(alpha4_h1));
        float d2_h1 = (2 * s1 / alpha2_h1) * sin(alpha2_h1 / 2);
        float d4_h1 = (2 * s2 / alpha4_h1) * sin(alpha4_h1 / 2);

        float fx_h1 = px - (-d2_h1 * sin(alpha2_h1 / 2) - d4_h1 * (sin(alpha4_h1 / 2) * cos(Phi3_h1) * cos(alpha2_h1) + cos(alpha4_h1 / 2) * sin(alpha2_h1)) - l * (sin(alpha4_h1) * cos(Phi3_h1) * cos(alpha2_h1) + cos(alpha4_h1) * sin(alpha2_h1)));

        float alpha2_h2 = A - x_h2;
        float alpha4_h2 = acos(cos(x_h2) * c4);
        float Phi3_h2 = acos(c4 * sin(x_h2) / sin(alpha4_h2));
        float d2_h2 = (2 * s1 / alpha2_h2) * sin(alpha2_h2 / 2);
        float d4_h2 = (2 * s2 / alpha4_h2) * sin(alpha4_h2 / 2);

        float fx_h2 = px - (-d2_h2 * sin(alpha2_h2 / 2) - d4_h2 * (sin(alpha4_h2 / 2) * cos(Phi3_h2) * cos(alpha2_h2) + cos(alpha4_h2 / 2) * sin(alpha2_h2)) - l * (sin(alpha4_h2) * cos(Phi3_h2) * cos(alpha2_h2) + cos(alpha4_h2) * sin(alpha2_h2)));

        dfx = (fx_h1 - fx_h2) / (2 * h);

        // 更新 x
        if (fabs(dfx) < 1e-6) {
            printf("Warning: Derivative too small, stopping iteration.\n");
            break;
        }

        x = x - fx / dfx;

        // 检查收敛性
        if (fabs(fx) < tolerance) {
            break;
        }

        iteration++;
    }

    if (iteration == max_iterations) {
        printf("Warning: Newton's method did not converge within the maximum number of iterations.\n");
    }

    return x;
}


/**
* 作用：将从端关节空间角度转换为从端单元关节角度
* 并slave_unit_joint_angles
* input : slave_joint_angles[] 长度为10的float数组存从端关节空间角度
* output: void
*/

void mapping_slave_segment_section(float the_msss_slave_joint_angles[])
{
		calculate_unit_joints(the_msss_slave_joint_angles, 0);
		calculate_unit_joints(the_msss_slave_joint_angles, 5);
}

void calculate_unit_joints(float the_cuj_slave_joint_angles[], int offset)
{
	    // 根据给定的关系式计算β2, β3, β4
    float alpha_2 = the_cuj_slave_joint_angles[offset + 1];
    float alpha_4 = the_cuj_slave_joint_angles[offset + 3];
    float Phi_3 = the_cuj_slave_joint_angles[offset + 2];
    
    // 参数n_p和n_d
    const uint8_t n_p = 8;
    const uint8_t n_d = 6;

    // 计算β2, β3, β4
    float beta_2 = alpha_2 / n_p;
    float beta_3 = atan(tan(alpha_4 / n_d) * cos(Phi_3));
    float beta_4 = -asin(sin(alpha_4 / n_d) * sin(Phi_3));

    // 将计算结果赋值给对应的slave_unit_joint_angles
		slave_unit_joint_angles[offset] = the_cuj_slave_joint_angles[offset];
    slave_unit_joint_angles[offset + 1] = beta_2;
    slave_unit_joint_angles[offset + 2] = beta_3;
    slave_unit_joint_angles[offset + 3] = beta_4;
		slave_unit_joint_angles[offset + 4] = the_cuj_slave_joint_angles[offset + 4];
}

float radians_to_degrees(float radians) {
    return radians * (180.0 / PI);
}

float degrees_to_radians(float degrees) {
    return degrees * (PI / 180.0);
}


void test_change_arr(int cnt)
{
		received_data[0] = cnt * 1.1;
}

//void test_mapping_master_drive_joints(float arr[])
//{
//		int length = 5; 	
//		    // 遍历输入数组，将每个元素乘以2，存储到新数组
//    for (int i = 0; i < length; ++i) {
//        after_map[i] = arr[i] * 2;
//    }	
//}
