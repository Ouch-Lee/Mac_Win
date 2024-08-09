% 再一次验证CCP方法的正确性
% 同时尝试使用Modified DH方法对连续体建模
function T = end_effector_transform(phi, ks, s)
    % 定义 DH 表中的参数
    theta1 = phi;
    theta2 = ks / 2;
    d3 = (2 * s / ks) * sin(ks / 2);
    theta4 = ks / 2;
    theta5 = -phi;

    % 计算各关节的齐次变换矩阵
    A1 = standard_DH(0, -pi/2, 0, theta1);
    A2 = standard_DH(0, pi/2, 0, theta2);
    A3 = standard_DH(0, -pi/2, d3, 0);
    A4 = standard_DH(0, pi/2, 0, theta4);
    A5 = standard_DH(0, 0, 0, theta5);

    % 计算末端齐次变换矩阵
    T = A1 * A2 * A3 * A4 * A5;
end

