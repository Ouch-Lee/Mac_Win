% 导入 Robotics Toolbox
% 如果还没有安装 Robotics Toolbox，请使用以下命令进行安装：
% addpath('路径到Robotics Toolbox')

% 导入符号工具箱
% syms dt2 at3 d3
clc;
clear all
dt2 = 20;
d3 = 15;
at3 = 20;
% 定义 DH 表格
dh_params = [
    0,      0,      0,      0;      % base=>1 *
    0,      -pi/2,  0,      0;      % 1=>t_1
    0,      pi/2,   0,      pi/2;      % t_1=>2
    0,    -pi/2,  dt2,      0; % 2=>t_2
    0,     0,      d3,      0;      % t_2=>3
    -at3,      0,      0,   0; % t_3=>4
    -dt2,      -pi/2,  0,   pi/2;   % 3=>t_3
    0,      0,      0,      0  % 4=>5
];

% 定义 Link 对象
links(1) = Link('modified', 'a', dh_params(1, 1), 'alpha', dh_params(1, 2), 'theta', dh_params(1, 4), 'prismatic', 'qlim', [0, 20]);
links(2) = Link('modified', 'a', dh_params(2, 1), 'alpha', dh_params(2, 2), 'd', dh_params(2, 3), 'offset', dh_params(2, 4), 'revolute');
links(3) = Link('modified', 'a', dh_params(3, 1), 'alpha', dh_params(3, 2), 'theta', dh_params(3, 4), 'prismatic', 'qlim', [0, 20]);
% links(4) = Link('modified', 'a', dh_params(4, 1), 'alpha', dh_params(4, 2), 'd', dh_params(4, 3), 'offset', dh_params(4, 4), 'revolute');
% links(5) = Link('modified', 'a', dh_params(5, 1), 'alpha', dh_params(5, 2), 'd', dh_params(5, 3), 'offset', dh_params(5, 4), 'revolute');
% links(6) = Link('modified', 'a', dh_params(6, 1), 'alpha', dh_params(6, 2), 'd', dh_params(6, 3), 'offset', dh_params(6, 4), 'revolute');
% links(7) = Link('modified', 'a', dh_params(7, 1), 'alpha', dh_params(7, 2), 'd', dh_params(7, 3), 'offset', dh_params(7, 4), 'revolute');
% links(8) = Link('modified', 'a', dh_params(8, 1), 'alpha', dh_params(8, 2), 'd', dh_params(8, 3), 'offset', dh_params(8, 4), 'revolute');
tool = [
    1 0 0 0;
    0 1 0 0;
    0 0 1 0;
    0 0 0 1
    ];

% 创建机器人模型
robot = SerialLink(links, 'name', 'Custom_DH_Robot');
view(3);
% % 显示机器人细节
% robot.name
% robot.offset

% 可视化机器人
q = [20 0 20];% 0 0 0 0 0]; % 设定关节角度
robot.plot(q);
