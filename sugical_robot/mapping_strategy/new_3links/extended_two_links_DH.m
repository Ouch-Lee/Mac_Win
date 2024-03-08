% this function is used to compute T of 2-links, but we add some extended
% axis to fit initial and end axis

% the params are corrected at 3-2
syms a2 at2 a3 at3 a4 dt2 d3 dt3 d4
syms t3 t4  theta_t2  alp_t3 theta_t3

%%
at3 = sym(2);
a4 = sym(2);
d3 =  sym(2);
a4 =  sym(2);
dt2 = sym(2);

t3 = sym(-pi/6);
t4 = sym(pi/3);

a2 = sym(0);
A2 = simplify([cos(0), -sin(0)*0, sin(0)*sin(pi/2), a2*cos(0)
    sin(0), cos(0)*0, -cos(0)*sin(pi/2), a2*sin(0)
    0, sin(pi/2), 0, 0
    0, 0, 0, 1]);

% disp(A2);
% 
% alp_t2 = sym(-pi/2);
% At2 = simplify([cos(t3), -sin(t3)*cos(alp_t2), sin(t3)*sin(alp_t2), at2*cos(t3)
%     sin(t3), cos(t3)*cos(alp_t2), -cos(t3)*sin(alp_t2), at2*sin(t3)
%     0, sin(alp_t2), cos(alp_t2), dt2
%     0, 0, 0, 1]);


at2 = sym(0);
alp_t2 = sym(pi/2);
At2 = simplify([cos(t3+pi/2), -sin(t3+pi/2)*cos(alp_t2), sin(t3+pi/2)*sin(alp_t2), at2*cos(t3+pi/2)
    sin(t3+pi/2), cos(t3+pi/2)*cos(alp_t2), -cos(t3+pi/2)*sin(alp_t2), at2*sin(t3+pi/2)
    0, sin(alp_t2), cos(alp_t2), dt2
    0, 0, 0, 1]);

a3 = sym(0);
alp3 = sym(0);
% d3 = sym(155);
theta_t2 = sym(pi/2);
A3 = simplify([cos(theta_t2), -sin(theta_t2)*cos(alp3), sin(theta_t2)*sin(alp3), a3*cos(theta_t2)
    sin(theta_t2), cos(theta_t2)*cos(alp3), -cos(theta_t2)*sin(alp3), a3*sin(theta_t2)
    0, sin(alp3), cos(alp3), d3
    0, 0, 0, 1]);

alp_t3 = sym(-pi/2);
dt3 = sym(0);
At3 = simplify([cos(t4 - pi/2), -sin(t4 - pi/2)*cos(alp_t3), sin(t4 - pi/2)*sin(alp_t3), at3*cos(t4 - pi/2)
    sin(t4 - pi/2), cos(t4 - pi/2)*cos(alp_t3), -cos(t4 - pi/2)*sin(alp_t3), at3*sin(t4 - pi/2)
    0, sin(alp_t3), cos(alp_t3), dt3
    0, 0, 0, 1]);
% 
alp4 = sym(-pi/2);
d4 = sym(0);
theta_t3 = sym(-pi/2);
A4 = simplify([cos(theta_t3), -sin(theta_t3)*cos(alp4), sin(theta_t3)*sin(alp4), a4*cos(theta_t3)
    sin(theta_t3), cos(theta_t3)*cos(alp4), -cos(theta_t3)*sin(alp4), a4*sin(theta_t3)
    0, sin(alp4), cos(alp4), d4
    0, 0, 0, 1]);

disp("the result of T for master matrix: ")
T_extended = simplify( A2 * At2 * A3 * At3 * A4);

disp(T_extended)