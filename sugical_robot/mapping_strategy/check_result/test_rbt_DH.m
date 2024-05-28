% 导入 Robotics Toolbox
% 如果还没有安装 Robotics Toolbox，请使用以下命令进行安装：
% addpath('路径到Robotics Toolbox')

% 定义两个平动关节的 DH 参数
L1 = Link('theta', 0, 'a', 0, 'alpha', 0, 'prismatic', 'qlim', [0, 1]);  % 第一个平动关节
L2 = Link('theta', 0, 'a', 0, 'alpha', 0, 'prismatic', 'qlim', [0, 1]);  % 第二个平动关节
% 创建一个由两个平动关节组成的 SerialLink 机器人
robot = SerialLink([L1 L2], 'name', 'Two Linear Joints Robot');
view(3);
% 定义关节变量的初始值
q = [0.5  0.5];  % 设定初始关节位置

% 使用 plot 函数绘制机器人
robot.plot(q);

% 添加一些绘图选项（可选）
% 设定绘图窗口的轴范围
% axis([-1 2 -1 2 -0.5 0.5]);  % 根据你的机器人工作空间调整轴范围
% title('Two Linear Joints Robot');
% xlabel('X');
% ylabel('Y');
% zlabel('Z');
% grid on;
