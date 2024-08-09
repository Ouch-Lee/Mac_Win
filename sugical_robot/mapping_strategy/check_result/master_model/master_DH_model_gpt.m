% 导入 Robotics Toolbox
% 如果还没有安装 Robotics Toolbox，请使用以下命令进行安装：
% addpath('路径到Robotics Toolbox')

clc;
clear all;
h = 15;
l = 20;

% 定义 DH 表格
dh_params = [
    0, 0, 0, 0; 
    0, -pi/2, 0, -pi/2; 
    0, -pi/2, h, pi; 
    0, 0, 0, -pi/2; 
    0, pi/2, 0, pi/2; 
    0, 0, l, 0
];

% 定义 Link 对象
links(1) = Link('modified', 'a', dh_params(1, 1), 'alpha', dh_params(1, 2), 'theta', dh_params(1, 4), 'prismatic', 'qlim', [0, 20]);
links(2) = Link('modified', 'a', dh_params(2, 1), 'alpha', dh_params(2, 2), 'theta', dh_params(2, 4), 'prismatic', 'qlim', [0, 20]);
links(3) = Link('modified', 'a', dh_params(3, 1), 'alpha', dh_params(3, 2), 'd', dh_params(3, 3), 'offset', dh_params(3, 4), 'revolute');
links(4) = Link('modified', 'a', dh_params(4, 1), 'alpha', dh_params(4, 2), 'd', dh_params(4, 3), 'offset', dh_params(4, 4), 'revolute');
links(5) = Link('modified', 'a', dh_params(5, 1), 'alpha', dh_params(5, 2), 'd', dh_params(5, 3), 'offset', dh_params(5, 4), 'revolute');
links(6) = Link('modified', 'a', dh_params(6, 1), 'alpha', dh_params(6, 2), 'd', dh_params(6, 3), 'offset', dh_params(6, 4), 'revolute');

% 创建机器人模型
robot = SerialLink(links, 'name', 'Custom_DH_Robot');

% 设置机器人模型的末端执行器
robot.tool = [
    1 0 0 0;
    0 1 0 0;
    0 0 1 0;
    0 0 0 1
];

% 设置背景颜色
set(gca, 'Color', 'w');

% 设置光照效果
light('Position', [1 1 1], 'Style', 'infinite');

% 可视化机器人
q = [20 20 0 0 0 0]; % 设定关节角度

% 使用默认设置进行绘制，去除多余的参数设置
robot.plot(q);

% 显示网格和坐标轴
grid on;
xlabel('X');
ylabel('Y');
zlabel('Z');

% 调整视角
view(3);
