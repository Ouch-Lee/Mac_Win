
t3 = pi/6;
t4 = pi/6;
t5 = pi/6;

% A_pre = modified_DH(0, 0, 0, pi/2);
Am1 = modified_DH(0,pi/2,0, pi/2 + t3);
Am2 = modified_DH(0,pi/2,0,pi/2 + t4);
Am3 = modified_DH(0,pi/2,0, pi/2 + t5);

disp( Am1 * Am2 * Am3);

% disp("----------")
% 
% disp(get_T_con_from_mapping(t3,t4,t5));

%% 终于搞定了
disp("----------")

ks_2 = acos( cos(t3) * cos(t4) );
if t4 >= 0
    Phi_2 = acos( (cos(t4) * sin(t3)) / sin(ks_2)) - pi;
else
    Phi_2 = pi -  acos( (cos(t4) * sin(t3)) / sin(ks_2));
end

if t3 >= 0
    Delta_x = 3*pi/2 - acos(cos(t3)*sin(Phi_2)) ;
else
    Delta_x = acos(cos(t3)*sin(Phi_2)) - pi/2;
end

Theta5 = t5 + Delta_x; % + Phi_2;

As1 = modified_DH(0,0 ,0, Phi_2);
As2 = modified_DH(0,-pi/2,0,ks_2);
% As3 = modified_DH(0,pi/2 ,0, -Phi_2); % shit，多转一个phi是多余的？也不是，和论文那个差不多，
As4 = modified_DH(0,pi/2,0,Theta5);
disp(  As1 * As2  * As4); % * As3