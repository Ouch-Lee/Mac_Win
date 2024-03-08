syms theta1 alp1 a1  d1
a1 = sym(0);
d1 =sym(0);
alp1 = sym(0);
theta1 = sym(pi/6);

A1 = simplify([cos(theta1), -sin(theta1)*cos(alp1), sin(theta1)*sin(alp1), a1*cos(theta1)
    sin(theta1), cos(theta1)*cos(alp1), -cos(theta1)*sin(alp1), a1*sin(theta1)
    0, sin(alp1), cos(alp1), d1
    0, 0, 0, 1]);

disp(A1)