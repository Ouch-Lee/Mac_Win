% 在给定主端关节空间的条件下，求解了关于theta_3e的非线性方程。由它出发可以得到从端的所有工作空间
% 通过编写一个整体函数，验证这个非线性方程求解是否正确

% 给定一组主端关节空间
% clc;
% clear all;
s1 = 10;
s2 = 18;
l = 6;

% 先运行 check_plannar_5_bar_mapping 文件
% joints_master = [pi/12, 10, pi/6, pi/6, 0]; % theta1, d2, theta3, theta4, theta5
joints_master = [theta_1, d_2, theta_3, beta_4, beta_5]; % theta1, d2, theta3, theta4, theta5
T_master = compute_master_T(joints_master(1), joints_master(2), joints_master(3), joints_master(4), joints_master(5));
px = T_master(1,4);
pz = T_master(3,4);

theta_3e = solve_nonlinear_eq(px, joints_master(1), joints_master(3), joints_master(4));
alpha2 = (joints_master(1) + joints_master(3) - theta_3e);  
alpha4 = acos(cos(theta_3e) * cos(joints_master(4)));

% 取 theta3, theta4 的正负号
sign_3 = sign(theta_3e);
sign_4 = sign(joints_master(4));

Phi3 = sign_4 * acos(cos(joints_master(4)) *sin(theta_3e) / sin(alpha4)) ;  % 分情况讨论
Delta_x = sign_3 * acos(cos(theta_3e) * sin(Phi3)) + Phi3 - pi/2;
Theta5 = joints_master(5) + Delta_x;

pz_s = s1 * sin(alpha2) / alpha2 + (s2/alpha4) * ( sin(alpha4)*cos(alpha2) - (1-cos(alpha4))/2 *sin(alpha2)*cos(Phi3) ) + l * (cos(alpha4)*cos(alpha2) - sin(alpha4)*sin(alpha2)*cos(Phi3));
d2 = (2*s1)/alpha2 *sin(alpha2/2); 
d4 = (2*s2)/alpha4 *sin(alpha4/2);
alp4 = alpha4;
% pz_s2 = d4*(cos(alp4/2)*(cos(alp2/2)^2 - sin(alp2/2)^2) - 2*cos(alp2/2)*sin(alp2/2)*sin(alp4/2)*cos(Phi3)) + d2*cos(alp2/2) +
% l*(cos(alp4/2)*(cos(alp4/2)*(cos(alp2/2)^2 - sin(alp2/2)^2) - 2*cos(alp2/2)*sin(alp2/2)*sin(alp4/2)*cos(Phi3)) 
% - sin(alp4/2)*(sin(alp4/2)*(cos(alp2/2)^2 - sin(alp2/2)^2) + 2*cos(alp2/2)*cos(alp4/2)*sin(alp2/2)*cos(Phi3)));
T_slave_1 = compute_slave_T(0, alpha2, Phi3, alpha4, Theta5);
D1 = pz - T_slave_1(3,4);

T_slave = modified_DH(0,0,D1,0) * T_slave_1;
% T_slave = compute_slave_T(D1, alpha2, Phi3, alpha4, 0); % 这里可以简化就是在T_slave_1基础上乘以一个D1的平移
disp('master transformation matrix:');
disp(T_master);
disp('slave transformation matrix:');
disp(T_slave);

fprintf("D1 = %d, alpha2 = %d, Phi3 = %d, alpha4 = %d, Theta5 = %d\n", D1, alpha2, Phi3, alpha4, Theta5);