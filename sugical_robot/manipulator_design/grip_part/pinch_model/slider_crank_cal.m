% 用于绘制曲柄滑块末端与theta之间的关系
clear all;
OA = 10; % 曲柄长度 mm
AB = 15;% 连杆长度 mm
omega = 10; % 曲柄角速度 rad/s
detaTime = 0.005;% 时间间隔s
t = 0:detaTime:(pi/omega);% 时间 s
n = length(t);% 数据个数
thetas = zeros(1,n);% 曲柄转角
xSlide = zeros(1,n);% 滑块位移 mm
for iterTime = 1:n
    thetas(iterTime) = omega*t(iterTime);
    theta = thetas(iterTime);
    xSlide(iterTime) = OA*cos(theta) + (AB*AB - OA*OA*sin(theta)*sin(theta))^0.5;   
end

plot(thetas, xSlide, 'LineWidth', 2);
xlabel('\theta (degrees)');
ylabel('x');
title('x as a function of \theta');
grid on;

