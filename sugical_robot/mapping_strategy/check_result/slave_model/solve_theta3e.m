function theta_3e = solve_theta3e(px, theta1, theta3, theta4)
    s1 = 6;
    s2 = 12;
    l = 3;
    A = theta1 + theta3;
    alpha2 = theta1;
    d2 = (2*s1/alpha_2) 
    % 定义方程的匿名函数
    equation = @(theta3e) d2 * sin((A - theta3e) / 2) + ...
               d4 * sin(acos(cos(theta3e) * cos(theta4)) / 2) * ...
               cos(acos(cos(theta4) * sin(theta3e) / sqrt(1 - (cos(theta3e) * cos(theta4))^2))) * cos(A - theta3e) + ...
               l * cos(theta3e) * cos(theta4) * ...
               cos(acos(cos(theta4) * sin(theta3e) / sqrt(1 - (cos(theta3e) * cos(theta4))^2))) * cos(A - theta3e) + ...
               l * sqrt(1 - (cos(theta3e) * cos(theta4))^2) * cos(A - theta3e) - px;

    % 初始猜测
    initial_guess = 0;

    % 使用fsolve进行数值求解
    options = optimoptions('fsolve', 'Display', 'off');
    theta_3e = fsolve(equation, initial_guess, options);
end

% 示例使用
px = 1; % 给定的 px 值
A = pi / 3;
d2 = 1;
d4 = 1;
l = 1;
theta4 = pi / 6;

theta_3e = solve_theta3e(px, A, d2, d4, l, theta4);
disp(['The solved theta_3^e is: ', num2str(theta_3e), ' radians']);
