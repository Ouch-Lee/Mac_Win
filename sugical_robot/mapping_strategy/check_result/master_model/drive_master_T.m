syms theta1 d2 theta3 theta4 theta5 h l
% 定义 DH 参数表格


dh_params = [
    0, pi/2, 0, theta1; 
    0, -pi/2, d2, 0; 
    0, pi/2, h, theta3 + pi/2; 
    0, pi/2, 0, theta4 + pi/2; 
    0, pi/2, l, theta5 + pi/2; 
];

A = cell(1, size(dh_params, 1));
for i = 1:size(dh_params, 1)
    a = dh_params(i, 1);
    alpha = dh_params(i, 2);
    d = dh_params(i, 3);
    theta = dh_params(i, 4);
    A{i} = modified_DH(a, alpha, d, theta);
end

% 计算最终的齐次变换矩阵
T_final = eye(4);
for i = 1:length(A)
    T_final = T_final * A{i};
end


% 输出最终的齐次变换矩阵
disp('最终的齐次变换矩阵 T_final = ');
disp(T_final);