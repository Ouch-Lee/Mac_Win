% 定义连杆长度
L1 = 1; % 第一个连杆长度
L2 = 1; % 第二个连杆长度

% 定义关节角度范围
theta1_min = -pi; % 关节1的最小角度
theta1_max = pi;   % 关节1的最大角度
theta2_min = -pi; % 关节2的最小角度
theta2_max = pi;   % 关节2的最大角度

% 创建角度网格
theta1 = linspace(theta1_min, theta1_max, 100);
theta2 = linspace(theta2_min, theta2_max, 100);
[Theta1, Theta2] = meshgrid(theta1, theta2);

% 计算末端执行器的坐标
x = (L1 * cos(Theta1) + L2 * cos(Theta1 + Theta2));
y = (L1 * sin(Theta1) + L2 * sin(Theta1 + Theta2));

% 绘制工作空间
figure;
surf(x, y, zeros(size(x)), 'EdgeColor', 'none', 'FaceColor', [0.8, 0.8, 0.8]);
hold on;
grid on;
xlabel('X');
ylabel('Y');
zlabel('Z');
title('2-Link Robot Workspace');
axis equal; % 保持坐标轴比例一致
view(2); % 2D视图