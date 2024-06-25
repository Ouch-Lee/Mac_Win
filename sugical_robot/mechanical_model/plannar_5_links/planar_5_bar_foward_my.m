function [check_para, xc, yc, xb, yb, xd, yd] = planar_5_bar_foward_my(u1, u4, l1, l2, l3, l4, l5)
    xb = l1 * cos(u1);
    yb = l1 * sin(u1);
    xd = l5 + l4 * cos(u4);
    yd = l4 * sin(u4);
    lbd = sqrt((xd - xb).^2 + (yd - yb).^2);
    
    if lbd > l2 + l3 
        check_para = 0;
        xc = NaN;
        yc = NaN;
        return;
    end
    
    check_para = 1;
    u2_1 = acos((l2^2 + lbd^2 - l3^2) / (2*l2*lbd));  % 使用余弦定理求BC与BD之间的夹角
    u3_1 = acos((l3^2 + lbd^2 - l2^2) / (2*l3*lbd)); 
    u2_2 = atan2(yd - yb, xd - xb);  % 求BD与水平线形成的夹角
    u3_2 = u2_2;
    u2 = u2_1 + u2_2;
    u3 = pi - (u3_1 - u3_2);

    xc = xb + l2 * cos(u2);
    yc = yb + l2 * sin(u2);
    % xc_2 = xd + l3 * cos(u3);
    % yc_2 = yb + l3 * sin(u2);
end