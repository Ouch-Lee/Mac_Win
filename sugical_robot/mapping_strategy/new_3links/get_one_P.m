function one_P = get_one_P(five_DH_para)
% 给出5个关节变量，求解末端位置
% TODO: 有几个关键参数需要缺点一下 {dc1，}

d1 = sym(five_DH_para(1));
a2 = sym(five_DH_para(2)) ;
theta3 = sym(five_DH_para(3)) ;
theta4 = sym(five_DH_para(4)) ;
theta5 = sym( five_DH_para(5));

% d1 = sym(100);
% a2 = sym(0);
% theta3 = sym(0);
% theta4 = sym(0);
% theta5 = sym(0);

syms d0 dt2 d3 dt3 d4 d5 a0 a1 at2 a3 at3 a4 a5 real
syms alp1 alp2 alp_t2 alp3 alp_t3 alp4 alp5 real
syms theta0 theta1 theta2 theta_t2 theta_t3 real;

%% base => 0
a0 = sym(0);
alp0 = sym(-pi/2);
theta0 = sym(0);
d0 = sym(0);
A0 = simplify([cos(theta0), -sin(theta0)*cos(alp0), sin(theta0)*sin(alp0), a0*cos(theta0)
    sin(theta0), cos(theta0)*cos(alp0), -cos(theta0)*sin(alp0), a0*sin(theta0)
    0, sin(alp0), cos(alp0), d0
    0, 0, 0, 1]);




%% 0 => 1
a1 = sym(0);
alp1 = sym(pi/2);
theta1 = sym(0);
dc1 = 200;
A1 = simplify([cos(theta1), -sin(theta1)*cos(alp1), sin(theta1)*sin(alp1), a1*cos(theta1)
    sin(theta1), cos(theta1)*cos(alp1), -cos(theta1)*sin(alp1), a1*sin(theta1)
    0, sin(alp1), cos(alp1), d1 + dc1
    0, 0, 0, 1]);

%% 1=>2
alp2 = sym(0);
% a2 = sym(218.55);
d2 = sym(0);
theta2 = 0;
A2 = simplify([cos(theta2), -sin(theta2)*cos(alp2), sin(theta2)*sin(alp2), a2*cos(theta2)
    sin(theta2), cos(theta2)*cos(alp2), -cos(theta2)*sin(alp2), a2*sin(theta2)
    0, sin(alp2), cos(alp2), d2
    0, 0, 0, 1]);

%% 2=>t2
% the theta3 is the theta in row "t2"
at2 = sym(0);
alp_t2 = sym(pi/2);
dt2 = sym(140);
% theta3 = 0
At2 = simplify([cos(theta3 + pi/2), -sin(theta3 + pi/2)*cos(alp_t2), sin(theta3 + pi/2)*sin(alp_t2), at2*cos(theta3 + pi/2)
    sin(theta3 + pi/2), cos(theta3 + pi/2)*cos(alp_t2), -cos(theta3 + pi/2)*sin(alp_t2), at2*sin(theta3 + pi/2)
    0, sin(alp_t2), cos(alp_t2), dt2
    0, 0, 0, 1]);

%% t2=>3
a3 = sym(0);
alp3 = sym(0);
d3 = sym(90);
theta_t2 = sym(pi/2);
A3 = simplify([cos(theta_t2), -sin(theta_t2)*cos(alp3), sin(theta_t2)*sin(alp3), a3*cos(theta_t2)
    sin(theta_t2), cos(theta_t2)*cos(alp3), -cos(theta_t2)*sin(alp3), a3*sin(theta_t2)
    0, sin(alp3), cos(alp3), d3
    0, 0, 0, 1]);

%% 3=>t3
at3 = sym(160);
alp_t3 = sym(-pi/2);
dt3 = sym(0);
At3 = simplify([cos(theta4 - pi/2), -sin(theta4 - pi/2)*cos(alp_t3), sin(theta4 - pi/2)*sin(alp_t3), at3*cos(theta4 - pi/2)
    sin(theta4 - pi/2), cos(theta4 - pi/2)*cos(alp_t3), -cos(theta4 - pi/2)*sin(alp_t3), at3*sin(theta4 - pi/2)
    0, sin(alp_t3), cos(alp_t3), dt3
    0, 0, 0, 1]);

%% t3=>4
a4 = sym(-90);
alp4 = sym(-pi/2);
d4 = sym(0);
theta_t3 = sym(-pi/2);
A4 = simplify([cos(theta_t3), -sin(theta_t3)*cos(alp4), sin(theta_t3)*sin(alp4), a4*cos(theta_t3)
    sin(theta_t3), cos(theta_t3)*cos(alp4), -cos(theta_t3)*sin(alp4), a4*sin(theta_t3)
    0, sin(alp4), cos(alp4), d4
    0, 0, 0, 1]);

%% 4=>5
d5 = sym(-40);
a5 = sym(0);
alp5 = sym(0);
A5 = simplify([cos(theta5), -sin(theta5)*cos(alp5), sin(theta5)*sin(alp5), a5*cos(theta5)
    sin(theta5), cos(theta5)*cos(alp5), -cos(theta5)*sin(alp5), a5*sin(theta5)
    0, sin(alp5), cos(alp5), d5
    0, 0, 0, 1]);

%% 
T = simplify(A0 * A1 * A2 * At2 * A3* At3 * A4  * A5);
% disp(T(3,4))
T_ex = zeros(4,4);
for i = 1:4
    for j = 1:4
        T_ex(i,j) = T(i,j);
    end
end

% disp(T_ex);
one_P = zeros(1,3);
for i = 1:3
    one_P(1,i) = T_ex(i,4);
end


