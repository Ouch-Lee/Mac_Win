function [xc,yc,u3_deg, u2_deg] = planar_5_bar_foward_paper(u1,u4,l1,l2,l3,l4,l5)
% 定义连杆长度和关节角度

theta1 = u1; % 假设 u1 是关节角 theta1
theta4 = u4; % 假设 u4 是关节角 theta4

% l1 * cos(u1) + l2 * cos(u2) = l5 + l3 * cos(u3) + l4 * cos(u4)
% l1 * sin(u1) + l2 * sin(u2) = l3 * sin(u3) + l4 * sin(u4)
% 计算公式中的 A, B, C
A = 2 * l3* l4 * sin(theta4) - 2*l1 * l3 * sin(theta1); % checked
B = 2* l3 * l5 - 2* l1 *l3 * cos(theta1) + 2*l4 * l3 * cos(theta4); % checked
C = l1^2 - l2^2 + l3^2 + l4^2 + l5^2 - 2*l1 * l4 * sin(theta1) * sin(theta4)- 2*l1*l5*cos(u1) + 2*l4*l5*cos(u4) - 2*l1*l4*cos(u1) * cos(u4); % checked

% u3 = 2* atan(A - sqrt(A^2 + B^2 - C^2) / (B -C)); % checked

u3 = 2* atan(A + sqrt(A^2 + B^2 - C^2) / (B -C));
u3_deg = rad2deg(u3);
% u3_2_deg = rad2deg(u3_2);
u2 = asin((l3* sin(u3) + l4*sin(u4) - l1*sin(u1) )/ l2); % checked
u2_deg = rad2deg(u2);
% u2_2 = asin((l3* sin(u3_2) + l4*sin(u4) - l1*sin(u1) )/ l2);

xb = l1 * cos(u1);
yb = l1 * sin(u1);
% xd = l5 + l4 * cos(u4);
% yd = l4 * sin(u4);

xc = xb + l2 * cos(u2);
yc = yb + l2 * sin(u2);
% xc_2 = xd + l3 * cos(u3);
% yc_2 = yd + l3 * sin(u3);
% xc_2 = xb + l2 * cos(u2_2);
% yc_2 = yb + l2 * sin(u2_2);

end
