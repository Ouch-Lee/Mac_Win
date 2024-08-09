% 用于验证主端驱动空间到关节空间的映射是否正确
% 输入一组驱动空间变量
clc;
clear all;
beta_1 =  deg2rad(108);
beta_2 =  deg2rad(72);
beta_3 =  deg2rad(0);
beta_4 =  deg2rad(0);
beta_5 =  deg2rad(0);
l1 = 8; l2 =8; l3 =8; l4 =8; l5 = 8;
[xc, yc, u3] = plannar_5_bar_fk(beta_1, beta_2);
beta_4_t = pi - u3;
%% 计算实际平面五连杆末端的齐次变换矩阵
DH_para_1 = [0, 0, 0, beta_2;
            l4, 0, 0, beta_4 - beta_2;
            l3, 0, 0, beta_3 - 0.3*pi - pi/2];
% 初始化最终的齐次变换矩阵
T_final_1 = eye(4);

% 计算每个关节的齐次变换矩阵并相乘
for i = 1:size(DH_para_1, 1)
    a = DH_para_1(i, 1);
    alpha = DH_para_1(i, 2);
    d = DH_para_1(i, 3);
    theta = DH_para_1(i, 4);
    
    % 计算齐次变换矩阵
    A = modified_DH(a, alpha, d, theta);
    
    % 乘积更新最终的齐次变换矩阵
    T_final_1 = T_final_1 * A;
end

%% 计算经变换后等效三连杆末端的齐次变换矩阵
theta_1 = atan((0.5*l5 - xc) / yc);
d_2 = sqrt((xc - 0.5*l5)^2 + yc^2);
delta_3 = (theta_1 + beta_4_t - 0.2*pi);
theta_3 = beta_3 - delta_3;
DH_para_2 = [0, 0, 0, theta_1;
             0, -pi/2, d_2, 0;
            0, pi/2, 0, theta_3];

% 初始化最终的齐次变换矩阵
T_final_2 = eye(4);

% 计算每个关节的齐次变换矩阵并相乘
for i = 1:size(DH_para_2, 1)
    a = DH_para_2(i, 1);
    alpha = DH_para_2(i, 2);
    d = DH_para_2(i, 3);
    theta = DH_para_2(i, 4);
    
    % 计算齐次变换矩阵
    A = modified_DH(a, alpha, d, theta);
    
    % 乘积更新最终的齐次变换矩阵
    T_final_2 = T_final_2 * A;
end
