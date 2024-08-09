
#define PI  3.14159265358979f

// ���������˲���
#define l1 8.0f
#define l2 8.0f
#define l3 8.0f
#define l4 8.0f
#define l5 8.0f

// ���������˲���
#define L_m 24
#define H_m 15

// �Ӷ˳��Ȳ���
#define S1_s 10
#define S2_s 18
#define L_s 6

// һ����ƽ����������ز���	
typedef struct {
    double xc;
    double yc;
    double u4;
}Plannar5BarFKResult;

// ����һ���ṹ���ӳ����������нǶȰ�
typedef struct {
		float motor_angles[10]; 
		float master_joint_angles[10];
		float slave_joint_angles[10];
		float slave_drive_angels[10];
}AngleSpace;


// 
extern float motor_angles[10];
extern float joint_angles[10];
extern float slave_joint_angles[10];
extern float slave_unit_joint_angles[10];

/*************API************/
void Mapping_ABS(float the_motor_angles[]);
void Mapping_INCREMENT(float the_motor_angles[]);
Plannar5BarFKResult plannar_5_bar_fk(float u1, float u5);
void calculate_joint_angles(float motor_angles[], int offset, int this_control_mode);
void mapping_master_drive_joints(float the_motor_angles[], int this_control_mode);
void test_change_arr(int cnt);
void test_mapping_master_drive_joints(float arr[]);
void calculate_slave_joint_angles(float joint_angles[], int offset);
void mapping_joints_master_slave(float joint_angles[]);
float newton_method(float px, float theta1, float theta3, float theta4, float initial_guess, float tolerance, int max_iterations);
void mapping_slave_segment_section(float slave_joint_angles[]);
void calculate_unit_joints(float slave_joint_angles[], int offest);
float radians_to_degrees(float radians);
float degrees_to_radians(float degrees);


