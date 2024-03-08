function T =  get_continuum_T(fi,ks)
s = 1;
if (ks == 0)
    d3 = s;
else
    d3 =  (2*s/ks)*sin(ks/2);
end



A1 = [cos(fi), -sin(fi)*0, sin(fi)*sin(-pi/2), 0*cos(fi)
    sin(fi), cos(fi)*0, -cos(fi)*sin(-pi/2), 0*sin(fi)
    0, sin(-pi/2), 0, 0
    0, 0, 0, 1];

% disp(A1)
A2 = [cos(ks / 2), -sin(ks / 2)*0, sin(ks / 2)*sin(pi/2), 0*cos(ks / 2)
    sin(ks / 2), cos(ks / 2)*0, -cos(ks / 2)*sin(pi/2), 0*sin(ks / 2)
    0, sin(pi/2), 0, 0
    0, 0, 0, 1];

A3 = [cos(0), -sin(0)*0, sin(0)*sin(-pi/2), 0*cos(0)
    sin(0), cos(0)*0, -cos(0)*sin(-pi/2), 0*sin(0)
    0, sin(-pi/2), 0, d3
    0, 0, 0, 1];

A4 = [cos(ks / 2), -sin(ks / 2)*0, sin(ks / 2)*sin(pi/2), 0*cos(ks / 2)
    sin(ks / 2), cos(ks / 2)*0, -cos(ks / 2)*sin(pi/2), 0*sin(ks / 2)
    0, sin(pi/2), 0, 0
    0, 0, 0, 1];
% 
A5 = [cos(-fi), -sin(-fi)*cos(0), sin(-fi)*sin(0), 0*cos(-fi)
    sin(-fi), cos(-fi)*cos(0), -cos(-fi)*sin(0), 0*sin(-fi)
    0, sin(0), cos(0), 0
    0, 0, 0, 1];

T = A1*A2*A3*A4 *A5;