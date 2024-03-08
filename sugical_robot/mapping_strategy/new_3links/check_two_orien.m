syms theta3 theta4 phi ks 
theta3 = sym(pi/4);
theta4 = sym(pi/4);

the_phi = atan(-sin(theta4) / tan(theta3));
phi = sym(the_phi);
the_ks = acos(-cos(theta3)* cos(theta4) );
ks = sym(the_ks);

A1 = [ cos(theta3), sin(theta3)*sin(theta4), cos(theta4)*sin(theta3);
0, -cos(theta4), sin(theta4);
          sin(theta3),            -cos(theta3)*sin(theta4),             -cos(theta3)*cos(theta4)];
% disp(A1);
A2 = [(cos(phi))^2 * (cos(ks) - 1)+1, sin(phi)*cos(phi)*(cos(ks) -1), -cos(phi)*sin(ks);
     sin(phi)*cos(phi) *(cos(ks) -1 ), (cos(phi))^2 * (1-cos(ks)) + cos(ks) , -sin(phi)*sin(ks);
     cos(phi)*sin(ks), sin(phi)* sin(ks), cos(ks)];
 disp(A2 - A1)
      
