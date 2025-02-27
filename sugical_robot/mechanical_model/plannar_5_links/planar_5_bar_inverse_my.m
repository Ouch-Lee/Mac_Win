function [u1_solutions, u4_solutions] = planar_5_bar_inverse_my(xc, yc, l1, l2, l3, l4, l5)
    % 给定末端位置
    x = xc;
    y = yc;

    % 杆长
    a1 = l1;
    a2 = l2;
    a3 = l3;
    a4 = l4;
    a5 = l5;

    % 计算P1和P2
    P1_x = x + a5/2;
    P1_y = y ;
    P2_x = x - a5/2;
    P2_y = y ;

    % 使用二连杆逆向运动学求解u1和u4
    u1_solutions = solve_2bar_ik(P1_x, P1_y, a1, a2);
    u4_solutions = solve_2bar_ik(P2_x, P2_y, a4, a5);
end

function solutions = solve_2bar_ik(x, y, a1, a2)
    % 二连杆逆向运动学求解
    L = sqrt(x^2 + y^2);
    if L <= a1 + a2
        theta = acos((a1^2 + a2^2 - L^2) / (2 * a1 * a2));
        solutions = [atan2(y, x) - theta; atan2(y, x) + theta];
    else
        solutions = [];
    end
end