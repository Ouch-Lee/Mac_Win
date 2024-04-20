% 这个脚本用于计算pinch部分拉簧的弹性系数等参数
L1 = 13.8; 
L2 = 18.5;
l0 = sqrt(L1^2 + L2^2); 

% 弹簧参数确定
l_spring_total = 20;
D_spring = 3;
l_spring = l_spring_total - D_spring; 

% 力矩长度
l1 = 58;
l2 = 33;

theta_i = 120 - rad2deg(atan2(L2,L1));
theta_f = theta_i - 30;
F_max = 400 * (l1 + l2); %tau: g*mm
F_spring_max = F_max / (2 * l0 * sind(theta_f));
delta_x = 2*l0*cosd(theta_f) - l_spring;
k = F_spring_max / delta_x;
disp('拉簧弹性系数：');
disp(k);