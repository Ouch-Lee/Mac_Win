function A = modified_DH(a, alpha, d, theta)
    % 修正后的DH参数的齐次变换矩阵
    A = [cos(theta), -sin(theta), 0, a;
         sin(theta)*cos(alpha), cos(theta)*cos(alpha), -sin(alpha), -d*sin(alpha);
         sin(theta)*sin(alpha), cos(theta)*sin(alpha), cos(alpha), d*cos(alpha);
         0, 0, 0, 1];
end
