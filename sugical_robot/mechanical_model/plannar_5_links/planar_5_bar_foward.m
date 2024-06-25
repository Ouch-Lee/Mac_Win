function [xc,yc] = planar_5_bar_foward(u1,u4,l1,l2,l3,l4,l5)
xb = l1 * cos(u1);
yb = l1 * sin(u1);
xd = l5 + l4 * cos(u4);
yd = l4 * sin(u4);
lbd = sqrt((xd - xb).^2 + (yd - yb).^2);
A0 = 2 * l2 * (xd - xb);
B0 = 2 * l2 * (yd - yb);
C0 = l2.^2 + lbd.^2 - l3.^2;
u2 = 2 * atan((B0 + sqrt(A0.^2 + B0.^2 - C0.^2))/(A0 + C0));
xc = xb + l2 * cos(u2);
yc = yb + l2 * sin(u2);
end
