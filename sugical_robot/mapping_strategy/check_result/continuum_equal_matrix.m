a = 30;
a = deg2rad(a); % 将角度转换为弧度
Rx = @(a) [1, 0, 0; 0, cos(a), -sin(a); 0, sin(a), cos(a)];
Ry = @(a) [cos(a), 0, sin(a); 0, 1, 0; -sin(a), 0, cos(a)];
Rxy =  Rx(a) * Ry(a);