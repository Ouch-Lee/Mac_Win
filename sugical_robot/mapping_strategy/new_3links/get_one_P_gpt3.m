function one_P = get_one_P_gpt3(five_DH_para)
% 给出5个关节变量，求解末端位置

d1 = five_DH_para(1);
a2 = five_DH_para(2);
theta3 = five_DH_para(3);
theta4 = five_DH_para(4);
theta5 = five_DH_para(5);

% DH参数
DH = [0, 0, d1, 0;
      pi/2, 0, 0, 0;
      0, a2, 0, theta3;
      pi/2, 0, 90, theta4;
      0, 0, -40, theta5];

% 计算齐次变换矩阵
T = eye(4);
for i = 1:size(DH, 1)
    alpha = DH(i, 1);
    a = DH(i, 2);
    d = DH(i, 3);
    theta = DH(i, 4);
    
    % 构造单个关节的齐次变换矩阵
    A = [cos(theta), -sin(theta)*cos(alpha), sin(theta)*sin(alpha), a*cos(theta);
         sin(theta), cos(theta)*cos(alpha), -cos(theta)*sin(alpha), a*sin(theta);
         0, sin(alpha), cos(alpha), d;
         0, 0, 0, 1];
    
    % 累积齐次变换矩阵
    T = T * A;
end
disp(T)
% 提取末端位置
one_P = T(1:3, 4)';

end
