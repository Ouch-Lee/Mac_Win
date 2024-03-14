
% 数据准备
data_x_1 = averageArray(:,1);
data_y_1 = averageArray(:,2);
data_z_1 = averageArray(:,3);

data_x_2 = P_avg_KF(:,1);
data_y_2 = P_avg_KF(:,2);
data_z_2 = P_avg_KF(:,3);

% 设置颜色
color_x = [0.8500, 0.3250, 0.0980];
color_y = [0, 0.4470, 0.7410];
color_z = [0.4660, 0.6740, 0.1880];

% 创建图像
figure('Position', [100, 100, 800, 600]);

% 绘制 x 方向
subplot(3,1,1);
plot(data_x_1, 'Color', color_x, 'LineWidth', 1.5);
hold on;
plot(data_x_2, '--', 'Color', color_x, 'LineWidth', 1.5);
hold off;
ylabel('x position (mm)', 'FontSize', 12);
xlabel('Time', 'FontSize', 12);
title('X Position', 'FontSize', 14);
legend('initial\_data', 'after\_KF');
grid on;

% 绘制 y 方向
subplot(3,1,2);
plot(data_y_1, 'Color', color_y, 'LineWidth', 1.5);
hold on;
plot(data_y_2, '--', 'Color', color_y, 'LineWidth', 1.5);
hold off;
ylabel('y position (mm)', 'FontSize', 12);
xlabel('Time', 'FontSize', 12);
title('Y Position', 'FontSize', 14);
legend('initial\_data', 'after\_KF');
grid on;

% 绘制 z 方向
subplot(3,1,3);
plot(data_z_1, 'Color', color_z, 'LineWidth', 1.5);
hold on;
plot(data_z_2, '--', 'Color', color_z, 'LineWidth', 1.5);
hold off;
ylabel('z position (mm)', 'FontSize', 12);
xlabel('Time', 'FontSize', 12);
title('Z Position', 'FontSize', 14);
legend('initial\_data', 'after\_KF');
grid on;

% 调整子图间距
sgtitle('Tremor Tracking Comparison', 'FontSize', 16);
