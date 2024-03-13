startup_rvc;

% DH参数
% L1 = Link('d', 0, 'a', 0, 'alpha', -pi/2);
% L2 = Link('a', 0, 'alpha', pi/2, 'theta',0);
% L3 = Link('d', 0, 'a', 1, 'alpha', 0);

L1 = Link('d', 0, 'a', 0, 'alpha', pi/2);
L2 = Link('d', 0, 'a', 1, 'alpha', 0);
L3 = Link('d', 0, 'a', 1, 'alpha', 0);

% 创建机器人模型
robot = SerialLink([L1 L2 L3], 'name', 'MyRobot');

% 定义关节角度向量
q = [0 0 0];

% 绘制机器人模型
figure;
robot.plot(q);
