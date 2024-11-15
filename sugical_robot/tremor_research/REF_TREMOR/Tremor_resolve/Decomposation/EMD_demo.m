% % 设置参数
Fs = 100;  % 采样频率
% t = 0:1/Fs:10;  % 时间范围，从0到10秒
% frequency_base = 0.5;  % 基波频率
% amplitude_base = 5;  % 基波幅值
% phase_base = 0;  % 基波相位
% 
% % 生成基波信号
% base_wave = amplitude_base * sin(2 * pi * frequency_base * t + phase_base);
% 
% % 生成噪声
% frequency_noise = 10;  % 噪声频率
% amplitude_noise = 0.5;  % 噪声幅值
% random_signal = 0.5 * rand(1, length(t)); % 生成随机信号
% 
% % 将随机信号中每4个样本中的3个设为0
% for i = 1:length(random_signal)
%     if mod(i, 4) ~= 1
%         random_signal(i) = 0;
%     end
% end
% 
% noise = amplitude_noise * sin(2 * pi * frequency_noise * t) + random_signal;
% 
% % 合成信号
% synthetic_signal = base_wave + noise;

synthetic_signal = myData(2,:);
N = length(synthetic_signal);
t = linspace(0, 0.01 * (1800 - 1), 1800);
% 使用EEMD进行分解
% 请确保已安装并添加相关包（如 EMD）
imfs = emd(synthetic_signal);  % EMD分解 (确保安装了EEMD的MATLAB版本)
[n_rows, n_cols] = size(imfs);
% 绘制结果
figure('Position', [100, 100, 800, 600]);

% 第一张图为合成信号
subplot(n_cols + 1, 1, 1);  
plot(t, synthetic_signal, 'b');
title('Synthetic Signal');
xlabel('Time [s]');
ylabel('Amplitude');
grid on;

% 绘制IMFs
for i = 1:n_cols
    subplot(n_cols + 1, 1, i + 1);
    plot(t(1:length(imfs(:, i))), imfs(:, i));  % 修改为 imfs(:, i)以获取第i列
    title(['Intrinsic Mode Function ', num2str(i)]);
    xlabel('Time [s]');
    ylabel('Amplitude');
    grid on;
end

% 调整布局
% tight_layout();
