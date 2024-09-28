function [xc,yc,u2,u3] = plannar_5_bar_fk(u1,u4) % 这里u4代表电机第二个检测角，也即五连杆第四个角
    % 以连接A,B,C,D,E 五个点
    l1 = 8;
    l2 = 8;
    l3 = 8;
    l4 = 8;
    l5 = 8;

    xb = l1 * cos(u1);
    yb = l1 * sin(u1);
    xd = l5 + l4 * cos(u4);
    yd = l4 * sin(u4);
    lbd = sqrt((xd - xb).^2 + (yd - yb).^2);
    
    u2_1 = acos((l2^2 + lbd^2 - l3^2) / (2*l2*lbd));  % 使用余弦定理求BC与BD之间的夹角
    u3_1 = acos((l3^2 + lbd^2 - l2^2) / (2*l3*lbd));  % CD 和 BD的夹角
    u2_2 = atan2(yd - yb, xd - xb);  % 求BD与水平线形成的夹角
    u3_2 = u2_2;
    u2 = u2_1 + u2_2; % 第二个角 = BC和水平线之间的夹角，不太符合机器人学
    u3_t = u3_1 - u3_2; 
    u3 = pi - u3_t; % 第三个角 = CD与水平线之间的夹角
    xc = xb + l2 * cos(u2);
    yc = yb + l2 * sin(u2);
end