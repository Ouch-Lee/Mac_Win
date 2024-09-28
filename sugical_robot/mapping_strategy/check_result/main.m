% 用于验证主端驱动空间到关节空间的映射是否正确
% 这里手动输入一组电机的角度
clc;
clear all;
beta_1 =  deg2rad(108);
beta_2 =  deg2rad(72);
beta_3 =  deg2rad(0);
beta_4 =  deg2rad(0);
beta_5 =  deg2rad(0);
l1 = 8; l2 =8; l3 =8; l4 =8; l5 = 8;
[xc, yc, u3] = plannar_5_bar_fk(beta_1, beta_2);