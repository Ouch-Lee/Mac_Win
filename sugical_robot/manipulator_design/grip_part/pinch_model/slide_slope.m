% 计算斜率
slope = diff(xSlide) ./ diff(t);

% 绘制 xSlide 图像
figure;
plot(t, xSlide, 'b');
xlabel('时间 (s)');
ylabel('滑块位移 (mm)');
title('滑块位移随时间变化');

% 绘制 xSlide 图像的斜率
figure;
plot(t(1:end-1), slope, 'r');
xlabel('时间 (s)');
ylabel('斜率');
title('滑块位移斜率随时间变化');
