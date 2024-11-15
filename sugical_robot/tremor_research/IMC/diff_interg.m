% 设置参数
fs = 100; % 采样频率 (Hz)
T_sample = 1 / fs; % 采样间隔
t = 0:T_sample:10; % 时间从 0 到 10 秒

% 创建原始信号（例如正弦波）
original_signal = 0.1 * (t.^2) - t + 2; % 二次函数

% 计算一阶导数
first_derivative = zeros(size(original_signal));
first_derivative(2:end-1) = (original_signal(3:end) - original_signal(1:end-2)) / (2 * T_sample); % 中心差分
first_derivative(1) = first_derivative(2);
first_derivative(1001) = first_derivative(1000);
% 计算二阶导数
second_derivative = zeros(size(original_signal));
second_derivative(2:end-1) = (first_derivative(3:end) - first_derivative(1:end-2)) / (2 * T_sample); % 二阶导数的中心差分
second_derivative(2) = second_derivative(1);
second_derivative(1001) = second_derivative(1000);
% 进行第一个积分（恢复一阶导数）
first_integral = cumtrapz(t, second_derivative) * T_sample; % 第一次积分

% 进行第二次积分（恢复原始信号）
second_integral = cumtrapz(t, first_integral) * T_sample; % 第二次积分



% 绘制结果
figure;
subplot(4, 1, 1);
plot(t, original_signal, 'b');
title('Original Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(4, 1, 2);
plot(t, first_derivative, 'o-r');
title('First Derivative');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(4, 1, 3);
plot(t, second_derivative, 'r');
title('Second Derivative');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(4, 1, 4);
plot(t, second_integral, 'g');
title('Recovered Signal from Second Derivative');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;
