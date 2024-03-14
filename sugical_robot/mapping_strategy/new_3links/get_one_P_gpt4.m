function one_P = get_one_P_gpt4(five_DH_para)
% Given 5 joint parameters, compute the end-effector position relative to the base
% five_DH_para is a vector containing the 5 joint parameters

d1 = five_DH_para(1);
a2 = five_DH_para(2);
theta3 = five_DH_para(3); 
theta4 = five_DH_para(4); % Converting degrees to radians if necessary
theta5 = five_DH_para(5); % Converting degrees to radians if necessary

% Parameters for each transformation
dc1 = 200;
dt2 = 140;
d3 = 90;
at3 = 160;
a4 = -90;
d5 = -40;

% Define the transformation matrices using standard DH parameters
A0 = DH_transform(0, -pi/2, 0, 0); % Base to 0, identity since it's the base frame

A1 = DH_transform(0, pi/2, d1 + dc1, 0);

A2 = DH_transform(a2, 0, 0, 0);

At2 = DH_transform(0, pi/2, dt2, theta3 + pi/2);

A3 = DH_transform(0, 0, d3, pi/2);

At3 = DH_transform(at3, -pi/2, 0, theta4 - pi/2);

A4 = DH_transform(a4, -pi/2, 0, -pi/2);

A5 = DH_transform(0, 0, d5, theta5);

% Multiply the matrices to get the transformation from base to end-effector
T = A0 * A1 * A2 * At2 * A3 * At3 * A4 * A5;
% disp(T);
% Extract the position from the transformation matrix
one_P = T(1:3, 4)';
end