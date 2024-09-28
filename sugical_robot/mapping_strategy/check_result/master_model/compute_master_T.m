function T_final = compute_master_T(theta1, d2, theta3, theta4, theta5)

    % 固定参数
    h = 15; %15
    l = 24;
    % d2 = 10 +- 5

    % 定义 DH 参数表格
    dh_params = [
        0, pi/2, 0, theta1; 
        0, -pi/2, d2, 0; 
        0, pi/2, h, theta3 + pi/2; 
        0, pi/2, 0, theta4 + pi/2; 
        0, pi/2, l, theta5 + pi/2; 
    ];

    % 初始化最终的齐次变换矩阵
    T_final = eye(4);

    % 计算每个关节的齐次变换矩阵并相乘
    for i = 1:size(dh_params, 1)
        a = dh_params(i, 1);
        alpha = dh_params(i, 2);
        d = dh_params(i, 3);
        theta = dh_params(i, 4);
        
        % 计算齐次变换矩阵
        A = modified_DH(a, alpha, d, theta);
        
        % 乘积更新最终的齐次变换矩阵
        T_final = T_final * A;
    end
end

