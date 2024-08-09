function T_final = compute_slave_T(D1, alpha2, Phi3, alpha4, Theta5)
    % 常数参数
    s1 = 10;
    s2 = 18;
    l = 6;

    % 计算 d2 和 d4
    if alpha2 == 0
        d2 = s1;
    else
        d2 =(2 * s1 / alpha2) * sin(alpha2 / 2); % 有个问题，这里 alpha2 不能是 0
    end

    if alpha4 == 0
        d4 = s2;
    else
        d4 = (2 * s2 / alpha4) * sin(alpha4 / 2);
    end


    % 定义 DH 参数表格
    dh_params = [
        0, 0, D1, 0;
        0, pi/2, 0, alpha2 / 2;
        0, -pi/2, d2, 0;
        0, pi/2, 0, alpha2 / 2;
        0, -pi/2, 0, Phi3;
        0, pi/2, 0, alpha4 / 2;
        0, -pi/2, d4, 0;
        0, pi/2, 0, alpha4 / 2;
        0, -pi/2, 0, -Phi3;
        0, 0, l, Theta5;
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


% 给定的参数
