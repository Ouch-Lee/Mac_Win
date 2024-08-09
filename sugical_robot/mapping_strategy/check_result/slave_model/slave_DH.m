% 尝试使用CCP方法建立DH模型，并绘制对应图像，以验证DH表格正确性


%% 根据DH表在matlab中进行可视化，初步判定DH表没有问题，下一步是计算带有符号的其次变换矩阵
% 定义连续体长度参数
s1 = 10;
s2 = 18;
l = 6;
% 定义 DH 表格
% 定义 DH 表格，将所有非数值的字符串替换为0
dh_params = [
    0, 0, 0, 0; 
    0, pi/2, 0, 0; 
    0, -pi/2, 0, 0;  %3
    0, pi/2, 0, 0; 
    0, -pi/2, 0, 0; 
    0, pi/2, 0, 0; % 6
    0, -pi/2, 0, 0; 
    0, pi/2, 0, 0; 
    0, -pi/2, 0, 0; 
    0, 0, l, 0 
];

n = size(dh_params, 1);
% 定义 Link 对象
for i = 1:n
    if i == 3 || i == 7 || i ==1
        links(i) = Link('modified', 'a', dh_params(i, 1), 'alpha', dh_params(i, 2), 'theta', dh_params(i, 4), 'prismatic', 'qlim', [0, 20]);
    else
        links(i) = Link('modified', 'a', dh_params(i, 1), 'alpha', dh_params(i, 2), 'd', dh_params(i, 3), 'offset', dh_params(i, 4), 'revolute');
    end
end

robot = SerialLink(links, 'name', 'Slave\_Arm');
view(3);



% 绘制效果
qs_d = linspace(0,20,5);
qs_r = linspace(0,2*pi, 5);


q = zeros(1,n);
alpha2 = 0;
alpha4 = pi/12;
if alpha2 == 0
    d2 = s1;
else
    d2 =(2 * s1 / alpha2) * sin(alpha2 / 2); % 有个问题，这里 alpha2 不能是 0
end

if alpha4 == 0
    d4 = s2;
else
    d4 = (2 * s2 / alpha4) * sin(alpha4 / 2);
end

q = [2, alpha2/2, d2, alpha2/2, pi, alpha4/2, d4, alpha4/2, -pi, 0];
% q(1) = 2;
% q(2) = 0;
% q(3) = 8;
% q(4) = pi/12;
% q(5) = pi/3;
% q(6) = pi/6;
% q(7) = 30;
% q(8) = pi/6;
% q(9) = -pi/3;
robot.plot(q);
% for i = 1: length(qs_d)
%     q(n) = qs_r(i);
%     robot.plot(q);
%     pause(1);
% end
