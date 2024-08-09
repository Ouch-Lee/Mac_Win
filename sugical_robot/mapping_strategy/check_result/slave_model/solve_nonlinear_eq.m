function x = solve_nonlinear_eq(px, theta_1, theta_3, theta_4)

    % 常数参数
    s1 = 10;
    s2 = 18;
    l = 6;

    % 计算 A 和 c_4
    A = theta_1 + theta_3;
    c_4 = cos(theta_4);

    % 定义非线性方程
    function F = nonlinear_eq(x)
        % 计算 α_2 和 α_4
        alpha_2 = A - x;
        alpha_4 = acos(cos(x) * c_4);
        % 计算 Φ_3
        Phi_3 = acos(c_4 * sin(x) / sin(alpha_4));
        % 计算 d_2 和 d_4
        d_2 = (2 * s1 / alpha_2) * sin(alpha_2 / 2);
        d_4 = (2 * s2 / alpha_4) * sin(alpha_4 / 2);
        % 定义方程 p_x
        F = px - (-d_2 * sin(alpha_2 / 2) - d_4 * (sin(alpha_4 / 2) * cos(Phi_3) * cos(alpha_2) + cos(alpha_4 / 2) * sin(alpha_2)) - l * (sin(alpha_4) * cos(Phi_3) * cos(alpha_2) + cos(alpha_4) * sin(alpha_2)));
    end
    % 初始猜测值
    x0 = 1;
    % 使用fsolve求解非线性方程
    options = optimoptions('fsolve', 'Display', 'iter');
    x = fsolve(@nonlinear_eq, x0, options);

end
