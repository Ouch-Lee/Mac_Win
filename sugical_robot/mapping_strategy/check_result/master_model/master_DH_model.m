% 导入 Robotics Toolbox
% 如果还没有安装 Robotics Toolbox，请使用以下命令进行安装：
% addpath('路径到Robotics Toolbox')

% 导入符号工具箱
% syms dt2 at3 d3
clc;
clear all
h = 15;
l = 20;

% 定义 DH 表格
dh_params = [
    0, pi/2, 0, 0; 
    0, -pi/2,0, 0; 
    0, pi/2, h, pi/2; 
    0, pi/2, 0, pi/2; 
    0, pi/2, l, pi/2; 
];

n = size(dh_params, 1);
% 定义 Link 对象
for i = 1:n
    if i == 2
        links(i) = Link('modified', 'a', dh_params(i, 1), 'alpha', dh_params(i, 2), 'theta', dh_params(i, 4), 'prismatic', 'qlim', [0, 20]);
    else
        links(i) = Link('modified', 'a', dh_params(i, 1), 'alpha', dh_params(i, 2), 'd', dh_params(i, 3), 'offset', dh_params(i, 4), 'revolute');
    end
end


% 创建机器人模型
robot = SerialLink(links, 'name', 'Master\_Console');
view(3);
% % 显示机器人细节

qs_d = linspace(0,20,5);
qs_r = linspace(0,2*pi, 5);

% 设置背景颜色
% set(gca, 'Color', 'w');

% 设置光照效果
% light('Position', [1 1 1], 'Style', 'infinite');

% 可视化机器人
q = zeros(1,n);
% q(1) = -pi/6;
% q(2) = 10;
% for i = 1: length(qs_d)
%     q(n) = qs_r(i);
%     robot.plot(q);
%     pause(1);
% end

q = [0, 10, pi/12, 0, 0 ];

robot.plot(q);