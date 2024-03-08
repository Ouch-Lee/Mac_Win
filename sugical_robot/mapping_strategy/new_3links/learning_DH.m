clc;
clear;

syms d1 d2 d3 d4 d5 d6 a1 a2 a3 a4 a5 a6 real
syms alpha1 alpha2 alpha3 alpha4 alpha5 alpha6 real
syms theta1 theta2 theta3 theta4 theta5 theta6 real;

%% (1)
a1 = sym(0);
alpha1 = sym(-pi/2);
A1 = simplify([cos(theta1), -sin(theta1)*cos(alpha1), sin(theta1)*sin(alpha1), a1*cos(theta1)
    sin(theta1), cos(theta1)*cos(alpha1), -cos(theta1)*sin(alpha1), a1*sin(theta1)
    0, sin(alpha1), cos(alpha1), d1
    0, 0, 0, 1]);

d2 = sym(0);
alpha2 = sym(0);
A2 = simplify([cos(theta2 - pi/2), -sin(theta2 - pi/2)*cos(alpha2), sin(theta2 - pi/2)*sin(alpha2), a2*cos(theta2 - pi/2)
    sin(theta2 - pi/2), cos(theta2 - pi/2)*cos(alpha2), -cos(theta2 - pi/2)*sin(alpha2), a2*sin(theta2 - pi/2)
    0, sin(alpha2), cos(alpha2), d2
    0, 0, 0, 1]);

d3 = sym(0);
alpha3 = sym(-pi/2);
A3 = simplify([cos(theta3), -sin(theta3)*cos(alpha3), sin(theta3)*sin(alpha3), a3*cos(theta3)
    sin(theta3), cos(theta3)*cos(alpha3), -cos(theta3)*sin(alpha3), a3*sin(theta3)
    0, sin(alpha3), cos(alpha3), d3
    0, 0, 0, 1]);

a4 = sym(0);
alpha4 = sym(pi/2);
A4 = simplify([cos(theta4), -sin(theta4)*cos(alpha4), sin(theta4)*sin(alpha4), a4*cos(theta4)
    sin(theta4), cos(theta4)*cos(alpha4), -cos(theta4)*sin(alpha4), a4*sin(theta4)
    0, sin(alpha4), cos(alpha4), d4
    0, 0, 0, 1]);

a5 = sym(0);
d5 = sym(0);
alpha5 = sym(-pi/2);
A5 = simplify([cos(theta5), -sin(theta5)*cos(alpha5), sin(theta5)*sin(alpha5), a5*cos(theta5)
    sin(theta5), cos(theta5)*cos(alpha5), -cos(theta5)*sin(alpha5), a5*sin(theta5)
    0, sin(alpha5), cos(alpha5), d5
    0, 0, 0, 1]);

a6 = sym(0);
alpha6 = sym(0);
A6 = simplify([cos(theta6+pi), -sin(theta6+pi)*cos(alpha6), sin(theta6+pi)*sin(alpha6), a6*cos(theta6+pi)
    sin(theta6+pi), cos(theta6+pi)*cos(alpha6), -cos(theta6+pi)*sin(alpha6), a6*sin(theta6+pi)
    0, sin(alpha6), cos(alpha6), d6
    0, 0, 0, 1]);

T1 = simplify(A1*A2*A3*A4*A5*A6);

%% (2)
a1 = sym(0);
alpha1 = sym(-pi/2);
A1 = simplify([cos(theta1), -sin(theta1)*cos(alpha1), sin(theta1)*sin(alpha1), a1*cos(theta1)
    sin(theta1), cos(theta1)*cos(alpha1), -cos(theta1)*sin(alpha1), a1*sin(theta1)
    0, sin(alpha1), cos(alpha1), d1
    0, 0, 0, 1]);

d2 = sym(0);
alpha2 = sym(0);
A2 = simplify([cos(theta2 + pi/2), -sin(theta2 + pi/2)*cos(alpha2), sin(theta2 + pi/2)*sin(alpha2), (-a2)*cos(theta2 + pi/2)
    sin(theta2 + pi/2), cos(theta2 + pi/2)*cos(alpha2), -cos(theta2 + pi/2)*sin(alpha2), (-a2)*sin(theta2 + pi/2)
    0, sin(alpha2), cos(alpha2), d2
    0, 0, 0, 1]);

d3 = sym(0);
alpha3 = sym(pi/2);
A3 = simplify([cos(theta3), -sin(theta3)*cos(alpha3), sin(theta3)*sin(alpha3), (-a3)*cos(theta3)
    sin(theta3), cos(theta3)*cos(alpha3), -cos(theta3)*sin(alpha3), (-a3)*sin(theta3)
    0, sin(alpha3), cos(alpha3), d3
    0, 0, 0, 1]);

a4 = sym(0);
alpha4 = sym(-pi/2);
A4 = simplify([cos(theta4), -sin(theta4)*cos(alpha4), sin(theta4)*sin(alpha4), a4*cos(theta4)
    sin(theta4), cos(theta4)*cos(alpha4), -cos(theta4)*sin(alpha4), a4*sin(theta4)
    0, sin(alpha4), cos(alpha4), d4
    0, 0, 0, 1]);

a5 = sym(0);
d5 = sym(0);
alpha5 = sym(pi/2);
A5 = simplify([cos(theta5), -sin(theta5)*cos(alpha5), sin(theta5)*sin(alpha5), a5*cos(theta5)
    sin(theta5), cos(theta5)*cos(alpha5), -cos(theta5)*sin(alpha5), a5*sin(theta5)
    0, sin(alpha5), cos(alpha5), d5
    0, 0, 0, 1]);

a6 = sym(0);
alpha6 = sym(0);
A6 = simplify([cos(theta6), -sin(theta6)*cos(alpha6), sin(theta6)*sin(alpha6), a6*cos(theta6)
    sin(theta6), cos(theta6)*cos(alpha6), -cos(theta6)*sin(alpha6), a6*sin(theta6)
    0, sin(alpha6), cos(alpha6), d6
    0, 0, 0, 1]);
    
T2 = simplify(A1*A2*A3*A4*A5*A6);
err = simplify(T1 - T2)
