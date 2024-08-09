% 经过重新学习DH坐标系配置和参数规定，我他妈终于搞懂了(5-29)
% 因此重新为主端坐标系三连杆配置DH参数，并计算

% | i    | $a_{i-1}$ | $\alpha_{i-1}$ | $d_i $ | $\theta_i$           |
% | ---- | --------- | -------------- | ------ | -------------------- |
% | 3    | 0         | $\pi/2$        | h      | $\theta_3^* + \pi/2$ |
% | 4    | 0         | $\pi/2$       | 0      | $\theta_4^* + \pi/2$ |
% | 5    | 0         | $\pi/2$       | l      | $\theta_5^* $        |
function T_RPY = RPY_DH(t3_input, t4_input, t5_input)

% t3_input = -pi/6;
%  = -pi/6;
% t5_input = pi/4;

h = 15;
l = 20;
% 为了适应{0}和世界坐标系，在前面添加一个变化
% A_pre = modified_DH(0, 0, 0, pi/2);

% i = 3
% offset_t3 = pi/2;
t3 = t3_input + pi/2; % + offset_t3;  % 修改这里改变theta_3
alp_t2 = pi/2;
A3 = modified_DH(0 ,alp_t2, h, t3);


% % i =4
offset_t4 = pi/2;
t4 = t4_input + offset_t4 ;% 修改这里改变theta_4
alp_t3 = pi/2;
A4 = modified_DH(0, alp_t3, 0, t4);

% % i =5
offset_t5 = pi/2;
t5 = t5_input + offset_t5 ;% 修改这里改变theta_5
alp_t5 = pi/2;
A5 = modified_DH(0, alp_t5, l, t5);


T_RPY =  A3 * A4 * A5;% * A4 * A5); A_pre* 
% disp(T_RPY)

end

% show T_RPY in 3D
% T0 = eye(4);
% trplot(T0,'frame','O','color','g','length', 2, 'thick', 4);
% hold on,
% T_ex = zeros(4,4);
% for i = 1:3
%     for j = 1:3
%         T_ex(i,j) = T_RPY(i,j);
%     end
% end
% 
% T_ex(:,4) = [0;0;0;1];
% % disp(T_ex);
% axis_range_3_links = [-1, 1, -1, 1, -1, 1];
% trplot(T_ex,'framelabel','3_link3','color','b','length', 2, 'thick', 4);
% axis([-1 2 -2 2 -1 2]);