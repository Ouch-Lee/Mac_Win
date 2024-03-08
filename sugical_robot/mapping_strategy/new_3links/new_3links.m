TIME_STEP = 10;
systime = 0.0;   %秒计时器

%========================================= 参数区
kp = 100;
%========================================= device 初始化

joint0 =wb_robot_get_device('Joint_0');
joint1 =wb_robot_get_device('Joint_1');
joint2 =wb_robot_get_device('Joint_2');

wb_motor_set_position(joint0, pi/6);
wb_motor_set_position(joint1, -pi/3);
wb_motor_set_position(joint2, pi/3);
  
pos0 = wb_robot_get_device('Sensor_0');
pos1 = wb_robot_get_device('Sensor_1');
pos2 = wb_robot_get_device('Sensor_2');

wb_position_sensor_enable(pos0, TIME_STEP);
wb_position_sensor_enable(pos1, TIME_STEP);
wb_position_sensor_enable(pos2, TIME_STEP);

%=========================================运动学

Jacobian1 =zeros(2,3); 
L=0.7;


% main loop:
% perform simulation steps of TIME_STEP milliseconds
% and leave the loop when Webots signals the termination
%
while wb_robot_step(TIME_STEP) ~= -1
 

 theta_1 = wb_position_sensor_get_value(pos0);
 theta_2 = wb_position_sensor_get_value(pos1);
 theta_3 = wb_position_sensor_get_value(pos2);
 theta_12=theta_1+theta_2;
 theta_123=theta_12+theta_3;
%%%%%%define the Jacobian Matrix%%%
 Jacobian1(1,1) = -sin(theta_1) -sin(theta_12)-sin(theta_123);
 Jacobian1(1,2) =  -sin(theta_12)-sin(theta_123);
 Jacobian1(1,3) = -sin(theta_123);

Jacobian1(2,1) = cos(theta_1) +cos(theta_12) +cos(theta_123);
Jacobian1(2,2) = cos(theta_12) +cos(theta_123);
Jacobian1(2,3) = cos(theta_123);
Jacobian2 =L*Jacobian1;
%%%%%%get the angular velocity at next T
q_=[theta_1; theta_2; theta_3];
T=0.01;
H=2*T^2*diag([1 1 1]);
f=2*T*q_;
Aeq=Jacobian2;
beq=zeros(2,1);
x0 = [0;0;0];
options = optimoptions('quadprog','Algorithm','active-set');
result =quadprog(H,f,[],[],Aeq,beq,[],[],x0,options);
q1_dot1=result(1);
q2_dot2=result(2);
q3_dot3=result(3);

% systime
% systime = systime +0.01;
% contreller
theta_1 =theta_1 +result(1)*0.001;
theta_2 =theta_2 +result(2)*0.001;
theta_3 =theta_3 +result(3)*0.001;

  % wb_motor_set_position(joint0, theta_1);
  % wb_motor_set_position(joint1, theta_2);
  % wb_motor_set_position(joint2, theta_3);
    wb_motor_set_position(joint0, 0);
  wb_motor_set_position(joint1, pi/2);
  wb_motor_set_position(joint2, pi/6);
%   wb_motor_set_velocity(joint0,result(1));
%   wb_motor_set_velocity(joint1,result(2));
%   wb_motor_set_velocity(joint2,result(3));

  % if your code plots some graphics, it needs to flushed like this:
  drawnow;


end