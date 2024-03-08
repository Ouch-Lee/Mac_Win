syms fi ks d3
t3_c = -t3;
t4_c = t4;
ks  = acos(cos(t3_c) * cos(t4_c));
fi = acos( (cos(t4_c)* sin(t3_c)) / sin(ks) );
%% this part is to calculate the Delta_x
t2_c = atan(tan(t3_c) / cos(fi) );
cos_x1_0_x = (cos(fi) * cos(t3_c)) / cos(t2_c);
delta_x = -acos(cos(ks - t2_c) * cos(fi) * cos(t3_c) / cos(t2_c) ) + fi;
% delta_x = 0;

if (t4_c >0)
    fi = -fi;
    delta_x = -delta_x;
end




%%


fprintf('%g\n',ks);  
fprintf('%g\n',fi);  
fprintf('%g\n',delta_x);  
% A1 = simplify([cos(fi), -sin(fi)*0, sin(fi)*sin(pi/2), 0*cos(fi)
%     sin(fi), cos(fi)*0, -cos(fi)*sin(pi/2), 0*sin(fi)
%     0, sin(pi/2), 0, 0
%     0, 0, 0, 1]);
% 
% A2 = simplify([cos(ks / 2), -sin(ks / 2)*0, sin(ks / 2)*sin(-pi/2), 0*cos(ks / 2)
%     sin(ks / 2), cos(ks / 2)*0, -cos(ks / 2)*sin(-pi/2), 0*sin(ks / 2)
%     0, sin(-pi/2), 0, 0
%     0, 0, 0, 1]);
% 
% A3 = simplify([cos(0), -sin(0)*0, sin(0)*sin(pi/2), 0*cos(0)
%     sin(0), cos(0)*0, -cos(0)*sin(pi/2), 0*sin(0)
%     0, sin(pi/2), 0, d3
%     0, 0, 0, 1]);
% 
% A4 = simplify([cos(ks / 2), -sin(ks / 2)*0, sin(ks / 2)*sin(-pi/2), 0*cos(ks / 2)
%     sin(ks / 2), cos(ks / 2)*0, -cos(ks / 2)*sin(-pi/2), 0*sin(ks / 2)
%     0, sin(-pi/2), 0, 0
%     0, 0, 0, 1]);
% % 
% A5 = simplify([cos(-fi), -sin(-fi)*cos(0), sin(-fi)*sin(0), 0*cos(-fi)
%     sin(-fi), cos(-fi)*cos(0), -cos(-fi)*sin(0), 0*sin(-fi)
%     0, sin(0), cos(0), 0
%     0, 0, 0, 1]);

% rotation1 R(y,thetea4)
% fi1 =0;
% ks1 =-pi/3;
% T1 = get_continuum_T(fi1,ks1);
% 
% rotation1 R(z,pi/2)
% fi2 =pi/2;
% ks2 = 0;
% T2 = get_continuum_T(fi2,ks2);
% 
% rotation1 R(y,theta3)
% fi3 =0;
% ks3 = -0/6;
% T3 = get_continuum_T(fi3,ks3);


T_continuum =get_continuum_T(fi,ks);

disp("the T for continuum bending: ")
disp(T_continuum)

