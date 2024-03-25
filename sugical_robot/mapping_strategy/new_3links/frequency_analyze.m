
P_avg_x = P_avg(:,1);


% 假设你已经将数据加载到名为 'P_avg_x' 的向量中

% 计算采样率
total_samples = 2628;
recorded_time = 60; % 秒
sampling_rate = total_samples / recorded_time;

% 绘制时间序列图
time = (0:total_samples-1) / sampling_rate;
figure;
plot(time, P_avg_x);
title('Time Series Plot');
xlabel('Time (s)');
ylabel('Amplitude');

% 进行傅里叶变换
Y = fft(P_avg_x);
L = length(P_avg_x);
P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f = sampling_rate*(0:(L/2))/L;

% 绘制频谱图
figure;
plot(f,P1);
title('Single-Sided Amplitude Spectrum');
xlabel('Frequency (Hz)');
ylabel('|Y(f)|');

% 计算自相关函数
acf = xcorr(P_avg_x);

% 绘制自相关函数图
lags = (-(total_samples-1):(total_samples-1)) / sampling_rate;
figure;
plot(lags, acf);
title('Autocorrelation Function');
xlabel('Lag (s)');
ylabel('Autocorrelation');
