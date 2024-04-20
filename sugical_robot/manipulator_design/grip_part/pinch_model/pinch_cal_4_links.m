% 这个文件用于计算pinch部分，四连杆的单位长度
function [a_i, a_f] = pinch_cal_4_links(L2)
    L1 = 15;
    L = sqrt(L1^2 + L2^2);
    theta_i = 120 + rad2deg(atan2(L2,L1));
    a_i = 2 * L * cosd(theta_i);
    theta_f = theta_i - 30;
    a_f = 2*L* cosd(theta_f);



