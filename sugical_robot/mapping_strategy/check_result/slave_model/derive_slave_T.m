syms D1 alp2 d2 Phi3 alp4 d4 Theta5 l

% 定义每个连杆的DH参数
DH_params = [
    0, 0, D1, 0;
    0, pi/2, 0, alp2/2;
    0, -pi/2, d2, 0;
    0, pi/2, 0, alp2/2;
    0, -pi/2, 0, Phi3;
    0, pi/2, 0, alp4/2;
    0, -pi/2, d4, 0;
    0, pi/2, 0, alp4/2;
    0, -pi/2, 0, -Phi3;
    0, 0, l, Theta5;
];

A = cell(1, size(DH_params, 1));
for i = 1:size(DH_params, 1)
    a = DH_params(i, 1);
    alpha = DH_params(i, 2);
    d = DH_params(i, 3);
    theta = DH_params(i, 4);
    A{i} = modified_DH(a, alpha, d, theta);
end

% % 输出每个变换矩阵
% for i = 1:length(A)
%     % fprintf('A{%d} = \n', i);
%     % disp(A{i});
% end

% 计算最终的齐次变换矩阵
T_final = eye(4);
for i = 1:length(A)
    T_final = T_final * A{i};
end


% 输出最终的齐次变换矩阵
disp('最终的齐次变换矩阵 T_final = ');
disp(T_final);



