function T = getDH_matix(theta3,theta4)

% theta2 = theta2 + pi/2;
theta4 = theta4 - pi/2;

syms d2 dt2 d3 dt3 d4 d5 a1 a2 at2 a3 at3 a4 a5 real
syms alp1 alp2 alp_t2 alp3 alp_t3 alp4 alp5 real
syms theta1 theta_t2 theta_t3  real;

% a1 = sym(0);
% alp1 = sym(pi/2);
% theta1 = sym(pi/2);
% A1 = simplify([cos(theta1), -sin(theta1)*cos(alp1), sin(theta1)*sin(alp1), a1*cos(theta1)
%     sin(theta1), cos(theta1)*cos(alp1), -cos(theta1)*sin(alp1), a1*sin(theta1)
%     0, sin(alp1), cos(alp1), d1
%     0, 0, 0, 1]);
% 
% alp2 = sym(0);
% a2 = sym(218.55);
% d2 = sym(60.1);
% % theta2 = 0
% A2 = simplify([cos(theta2), -sin(theta2)*cos(alp2), sin(theta2)*sin(alp2), a2*cos(theta2)
%     sin(theta2), cos(theta2)*cos(alp2), -cos(theta2)*sin(alp2), a2*sin(theta2)
%     0, sin(alp2), cos(alp2), d2
%     0, 0, 0, 1]);

% the theta3 is the theta in row "t2"
at2 = sym(0);
alp_t2 = sym(pi/2);
dt2 = sym(165);
At2 = simplify([cos(theta3), -sin(theta3)*cos(alp_t2), sin(theta3)*sin(alp_t2), at2*cos(theta3)
    sin(theta3), cos(theta3)*cos(alp_t2), -cos(theta3)*sin(alp_t2), at2*sin(theta3)
    0, sin(alp_t2), cos(alp_t2), dt2
    0, 0, 0, 1]);

a3 = sym(0);
alp3 = sym(0);
d3 = sym(155);
theta_t2 = sym(pi/2);
A3 = simplify([cos(theta_t2), -sin(theta_t2)*cos(alp3), sin(theta_t2)*sin(alp3), a3*cos(theta_t2)
    sin(theta_t2), cos(theta_t2)*cos(alp3), -cos(theta_t2)*sin(alp3), a3*sin(theta_t2)
    0, sin(alp3), cos(alp3), d3
    0, 0, 0, 1]);

at3 = sym(145);
alp_t3 = sym(-pi/2);
dt3 = sym(0);
At3 = simplify([cos(theta4), -sin(theta4)*cos(alp_t3), sin(theta4)*sin(alp_t3), at3*cos(theta4)
    sin(theta4), cos(theta4)*cos(alp_t3), -cos(theta4)*sin(alp_t3), at3*sin(theta4)
    0, sin(alp_t3), cos(alp_t3), dt3
    0, 0, 0, 1]);

a4 = sym(155);
alp4 = sym(-pi/2);
d4 = sym(0);
theta_t3 = sym(pi/2);
A4 = simplify([cos(theta_t3), -sin(theta_t3)*cos(alp4), sin(theta_t3)*sin(alp4), a4*cos(theta_t3)
    sin(theta_t3), cos(theta_t3)*cos(alp4), -cos(theta_t3)*sin(alp4), a4*sin(theta_t3)
    0, sin(alp4), cos(alp4), d4
    0, 0, 0, 1]);

% d5 = sym(15);
% a5 = sym(0);
% alp5 = sym(0);
% A5 = simplify([cos(theta5), -sin(theta5)*cos(alp5), sin(theta5)*sin(alp5), a5*cos(theta5)
%     sin(theta5), cos(theta5)*cos(alp5), -cos(theta5)*sin(alp5), a5*sin(theta5)
%     0, sin(alp5), cos(alp5), d5
%     0, 0, 0, 1]);

T = simplify(At2* A3 * At3 * A4);
