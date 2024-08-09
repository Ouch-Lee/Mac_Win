function [beta, Phi_2] = calculate_angles_Phi(theta3, theta4)
    % 计算 cos 和 sin 值
    c3 = cos(theta3);
    s3 = sin(theta3);
    c4 = cos(theta4);
    s4 = sin(theta4);
    
    % 计算投影向量的 x 和 y 分量
    vx = c4 * s3;
    vy = s4;
    
    % 计算投影向量的长度
    v_length = sqrt(vx^2 + vy^2);
    
    % 计算投影向量与 x 轴的夹角 beta
    beta = acos(vx / v_length);
    
    % 计算 ks_2
    ks_2 = acos(c3 * c4);
    
    % 计算 Phi_2
    Phi_2 = acos((c4 * s3) / sin(ks_2));
end

