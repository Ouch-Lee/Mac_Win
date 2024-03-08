syms d1 d2 dt2 d3 dt3 d4 d5 a1 a2 at2 a3 at3 a4 a5 real
syms alp1 alp2 alp_t2 alp3 alp_t3 alp4 alp5 real
syms theta1 theta2 theta_t2 theta3 theta_t3 theta4 theta5 real;

% a1 = sym(0);
alp1 = sym(0);
d1 = sym(0);
A1 = simplify([cos(theta1), -sin(theta1)*cos(alp1), sin(theta1)*sin(alp1), a1*cos(theta1)
    sin(theta1), cos(theta1)*cos(alp1), -cos(theta1)*sin(alp1), a1*sin(theta1)
    0, sin(alp1), cos(alp1), d1
    0, 0, 0, 1]);

alp2 = sym(pi/2);
a2 = sym(0);
d2 = sym(0);
theta2 = sym(-pi/2);
A2 = simplify([cos(theta2), -sin(theta2)*cos(alp2), sin(theta2)*sin(alp2), a2*cos(theta2)
    sin(theta2), cos(theta2)*cos(alp2), -cos(theta2)*sin(alp2), a2*sin(theta2)
    0, sin(alp2), cos(alp2), d2
    0, 0, 0, 1]);

% the theta3 is the theta in row "t2"

alp_t2 = sym(-pi/2);
% theta3 = 0
dt2 = sym(0);
At2 = simplify([cos(theta3), -sin(theta3)*cos(alp_t2), sin(theta3)*sin(alp_t2), at2*cos(theta3)
    sin(theta3), cos(theta3)*cos(alp_t2), -cos(theta3)*sin(alp_t2), at2*sin(theta3)
    0, sin(alp_t2), cos(alp_t2), dt2
    0, 0, 0, 1]);

alp3 = sym(-pi/2);
d3 = sym(0);
theta_t2 = sym(-pi/2);
A3 = simplify([cos(theta_t2), -sin(theta_t2)*cos(alp3), sin(theta_t2)*sin(alp3), a3*cos(theta_t2)
    sin(theta_t2), cos(theta_t2)*cos(alp3), -cos(theta_t2)*sin(alp3), a3*sin(theta_t2)
    0, sin(alp3), cos(alp3), d3
    0, 0, 0, 1]);

T = A1 * A2 * At2 * A3;
disp(T)