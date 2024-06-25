% 这个文档是用于确定手肘装置中连杆长度等参数
clear all;
clc;
l1 = 12; % 连杆长度
l2 = 25; % 曲柄长度
D = 25;  % 滑块与曲柄转轴之间的距离
N = 20;  % 采样点数
theta = linspace(0, pi/3, N); % 定义theta的范围和采样点

% 初始化数组
Y = zeros(N, 1);
y = zeros(N, 1);

% 计算Y和y的值
for i = 1:N
    Y(i) = sqrt(l2^2 - (D - l1 * sin(theta(i)))^2);
    y(i) = l1 * cos(theta(i)) - Y(i);
end

% 绘制 y 关于 theta 的函数图
figure(1);
plot(theta, y, 'o-');
title('Position of the Slider Block (y) vs. Crank Angle (theta)');
xlabel('Crank Angle (radians)');
ylabel('Position (y)');

% 计算 y 关于 theta 的导数
dy = diff(y) ./ diff(theta);  % 导数的近似值
% dy = [dy, dy(end)]; % 补齐数组长度，注意这里使用单引号来保持行向量的形式

% 绘制 y 的导数图
figure(2);
plot(theta(1:end-1), dy, 'o-');
title('Derivative of Position of the Slider Block with respect to Crank Angle (dy/dtheta)');
xlabel('Crank Angle (radians)');
ylabel('Derivative (dy/dtheta)');