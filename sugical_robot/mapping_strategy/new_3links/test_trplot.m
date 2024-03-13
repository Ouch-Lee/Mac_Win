% 创建两个不同尺寸的齐次变换矩阵
T1 = eye(4); % 第一个坐标系的单位尺寸
T2 = eye(4); % 第二个坐标系的单位尺寸

% 在同一个图中绘制两个坐标系
hold on;

% 绘制第一个坐标系，长度设置为1
trplot(T1, 'frame', 'Coordinate Frame 1', 'length', 1);

% 绘制第二个坐标系，长度设置为2，放大两倍
trplot(T2, 'frame', 'Coordinate Frame 2', 'length', 2);

% 设置坐标轴的范围（根据需要调整）
axis equal; % 使得坐标轴比例相等，避免图像变形

hold off;

