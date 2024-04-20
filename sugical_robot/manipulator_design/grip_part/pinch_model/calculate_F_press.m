% 用于计算给定角度时操纵者需要提供多大的 合力矩
mu = 0.5;   % mu 常数值
Fpress = 10; % Fpress 常数值
L1 = 13.8;
L2 = 18.5;
k = 50;      % k 常数值
l0 = sqrt(L1^2 + L2^2);     % l0 常数值
theta_i = 120 - rad2deg(atan2(L2,L1));


% 定义 theta 范围
theta_range = theta_i - 30 :0.1: theta_i;
n = length(theta_range);
% theta_range_1 = theta_range(1:)
F1_values = zeros(1,n);
% 计算对应 theta 值下的 F1
for i = 1:length(theta_range)
    F1_values(i) = calculate_F1(theta_i, theta_range(i), k, l0, mu, Fpress);
end

% F1_values = ones(1,n) - F1_values;

% F1_values = calculate_F1(theta_range, k, l0, mu, Fpress, L1);

% 绘制图像
plot(theta_range, F1_values, 'LineWidth', 2);
xlabel('\theta (degrees)');
ylabel('F_1');
title('F_1 as a function of \theta');
grid on;
 