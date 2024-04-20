clear all;
clc;
% 定义曲柄长度和连杆长度的数组
OA_values = linspace(5, 6, 11);
AB_values = linspace(9, 10, 11);

% 定义最小行程和最大值
min_stroke = 3; % 行程达到3mm
max_stroke = 13.5; % 最大值不超过13mm

% 定义角度步长
% angle_step = pi/180; % 1度

% 初始化满足条件的曲柄长度和连杆长度组合
delta_x = [];
satisfying_OA = [];
satisfying_AB = [];

% 遍历曲柄长度和连杆长度组合
for i = 1:length(OA_values)
    for j = 1:length(AB_values)
        OA = OA_values(i);
        AB = AB_values(j);
        
        % 计算最小角度和最大角度
        theta_i = acos((-AB^2 + OA^2 + max_stroke^2)/(2*max_stroke*OA));
        theta_f = theta_i + pi/6;
        
        % % 计算对应的时间范围
        % t_range = linspace(theta_i, theta_f, ceil((theta_f - theta_i)/angle_step));
        
        % 计算滑块位移
        % xSlide = OA*cos(10*t_range) + (AB^2 - OA^2*sin(10*t_range).^2).^0.5;
        xSlide_max = OA*cos(theta_i) + (AB^2 - OA^2*sin(theta_i)^2)^0.5;
        xSlide_min = OA*cos(theta_f) + (AB^2 - OA^2*sin(theta_f)^2)^0.5;
        delta_x_tmp = xSlide_max - xSlide_min;
        
        % 判断是否满足条件
        if xSlide_max - xSlide_min >= min_stroke
            satisfying_OA = [satisfying_OA, OA];
            satisfying_AB = [satisfying_AB, AB];
            delta_x = [delta_x, delta_x_tmp];
        end
    end
end

% 显示满足条件的曲柄长度和连杆长度组合
disp('满足条件的曲柄长度和连杆长度组合：');
disp('曲柄长度 (OA)    连杆长度 (AB)');
disp([satisfying_OA; satisfying_AB]);
