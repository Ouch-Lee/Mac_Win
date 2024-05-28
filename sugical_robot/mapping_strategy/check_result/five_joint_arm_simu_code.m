% Author: Li Aoqi
% Date: 2023/10/25
% Description: this file is the project for course Robotics Introduction
%% 利用标准D-H法建立多轴机器人
% clear;
% clc;
l1 = 0.35;
l2 = 0.305;
l3 = 0.3;
L1 = Link('d', 0, 'a', 0, 'alpha',0,'offset',0, 'revolute', 'modified');    %Link 类函数;offset建立初始的偏转角
L2 = Link('d', l1, 'a', 0, 'alpha', -pi/2,  'offset',0, 'revolute', 'modified');
L3 = Link('d', 0, 'a', 0, 'alpha', pi/2,'offset', 0, 'revolute', 'modified');
L4 = Link('d', l2, 'a', 0, 'alpha',-pi/2,'offset',-pi/2, 'revolute', 'modified');
L5 = Link('d', 0, 'a', 0, 'alpha', -pi/2,'offset',-pi/2, 'revolute', 'modified');
tool = [
    1 0 0 l3;
    0 1 0 0;
    0 0 1 0;
    0 0 0 1
    ];% * troty(90);
robot = SerialLink([L1,L2,L3,L4,L5], 'tool', tool,'name','SCHUNK');
view(3);


% %% plot the plane and points
% normal_vector = [1, 0, 0];
% point_on_plane = [0, 0.4, 0];
% 
% % 半径
% R = 0.2;
% 
% % 计算8等分点
% num_points = 8;
% theta = linspace(0, 7/4 * pi, num_points); % 角度范围
% 
% % 初始化点的坐标
% points = zeros(3, num_points);
% 
% for i = 1:num_points
%     % 使用极坐标计算点的位置
%     z = point_on_plane(3) + R * cos(theta(i));
%     x = point_on_plane(1) + R * sin(theta(i));
%     y = point_on_plane(2);
% 
%     points(:, i) = [x; y; z];
% end
% 
% 
% % 绘制点
% plot3(points(1, :), points(2, :), points(3, :), 'ro', 'MarkerSize', 4);
% grid on;
% xlabel('X');
% ylabel('Y');
% zlabel('Z');
% hold on;


%% ikine
% orens = pi/6 * [1,1,0,5,4,5,6,1];
% q0 = [pi/2, -pi/12, pi/12, pi/4, 0, 0]; % 初始猜测的关节角度
q0 = [0 0 0 0 0];

robot.plot(q0);
% % qs = zeros(8,6);
% view(3);
% 
% angles = linspace(0, 2*pi, 13);
% angles = angles(1:end-1);
% 
% % for j = 1:8
% %     fprintf('%s %d\n', 'the point', j);
% %     for i = 1:12
% %             T = transl(points(:,j))*trotx(angles(i)) ;
% %             T_se3 = SE3(T);
% %             q_test=robot.ikine(T_se3, 'q0', q0,'mask', [1, 1, 1, 1, 1, 0]);
% %             if ~isempty(q_test)
% %                 fprintf('%s %d\n', 'x=', i);
% %                 disp(q_test);
% %             end
% %     end
% % end
% 
% 
% 
% 
% 
% 
% qs = zeros(8,5);
% for i = 1:8
%     T = transl(points(:,i))*trotx(orens(i));
%     T_se3 = SE3(T);
%     q=robot.ikine(T_se3, 'q0', q0,'mask', [1, 1, 1, 1, 1, 0]);
%     disp(q);
%     qs(i,:) = q;
% end
% 
% 
% %% for more smooth move, add the frequency of simulation
% frames = 30;
% simu_time = 5;
% advanced_qs = zeros(7*frames, 5);
% for j = 1:7
%     advanced_qs(((j-1)*frames+1):j*frames,:) = Arith_mat(qs(j,:), qs(j+1,:), frames);
% end
% 
% all_steps = length(advanced_qs);
% % pause(11)
% for i = 1:all_steps
%     robot.plot(advanced_qs(i,:));
% %     pause( 0.2 * simu_time/(all_steps));
% end
% 
% % robot.teach();

