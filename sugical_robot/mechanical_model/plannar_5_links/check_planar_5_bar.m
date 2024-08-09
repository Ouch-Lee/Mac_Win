l1=1;
l2 =1;
l3 =1;
l4=1;
l5=1;


%% 这个部分用于检查论文公式和我推导的几何公式结构是否相同，结果是不同
% 定义样本数量
% n = 10;
% % 
% % 生成第一组[0, pi]之间的随机数
% randomNumbers1 =  (7*pi/12 - 5*pi/12) * rand(1, n) + 5*pi/12;
% % axis_range_3_links
% % 生成第二组[0, pi]之间的随机数
% randomNumbers1 =  (7*pi/12 - 5*pi/12) * rand(1, n) + 5*pi/12;
% 
% 
% p_1 = zeros(n,2);
% p_2 = zeros(n,2);
% p_3 = zeros(n,2);
% p_4 = zeros(n,2);
% u_n = zeros(n,2);
% 
% for i = 1:n
%     [~, p_1(i,1), p_1(i,2), ~, ~, ~, ~] = planar_5_bar_foward_my(randomNumbers1(i), randomNumbers2(i), 1,1,1,1,1);
%     [p_3(i,1), p_3(i,2), u_n(i,1), u_n(i,2)] = planar_5_bar_foward_paper(randomNumbers1(i), randomNumbers2(i), 1,1,1,1,1); %, p_4(i,1), p_4(i,2), u3_n(i,2)
% end

%% 为了验证谁出了问题，我决定，将其可视乎
% 定义点的坐标

u1 = linspace(pi/4, 3*pi/4, 10);

x_my = zeros(1,5);
y_my = zeros(1,5);
x_my(5) = l5;

figure;

% 生成一组颜色，每个循环使用不同的颜色
colors = lines(length(u1));

for j = 1: length(u1)
    if planar_5_bar_foward_my(u1(j), pi/2, l1, l2, l3, l4, l5) == 1
         [x_my(3), y_my(3), x_my(2), y_my(2), x_my(4), y_my(4)] = planar_5_bar_foward_my(u1(j), pi/2, l1, l2, l3, l4, l5);
    end
    % % 论文的坐标
    % x_p 
    % x = [1, 2, 3, 4, 5]; % x坐标
    % y = [1, 4, 2, 5, 3]; % y坐标

    % 获取当前循环的颜色
    current_color = colors(j, :);

    % 创建图形窗口
    hold on; % 保持当前图形，以便在同一图上绘制线段

    % 绘制点
    plot(x_my, y_my, 'o', 'Color', current_color); % 使用圆圈标记点，并设置颜色

    % 绘制连接点的线段
    for i = 1:length(x_my)-1
        plot([x_my(i), x_my(i+1)], [y_my(i), y_my(i+1)], 'Color', current_color, 'LineWidth', 2); % 绘制线段，并设置颜色
    end

end


    % 添加标题和坐标轴标签
    title('连接的点');
    xlabel('X轴');
    ylabel('Y轴');
    xlim([-1,2]);


    % 显示网格
grid on;


% 释放hold状态
hold off;

%% 接下来把工作空间大概画出来
% figure;
% N =100;
% u1 = linspace(0,2*pi,N);
% u2 = linspace(0,2*pi,N);
% p_end = zeros(N*N, 2);
% for i = 1:N
%     for j = 1:N
%         [check_para, xc, yc, ~, ~, ~, ~] = planar_5_bar_foward_my(u1(i), u2(j), l1, l2, l3, l4, l5);
%         if check_para == 1
%             p_end(j + N*(i-1), 1) = xc;
%             p_end(j + N*(i-1), 2) = yc;
%         end
%     end
% end
% 
% x_coords = p_end(:, 1);
% y_coords = p_end(:, 2);
% plot(x_coords, y_coords, 'o'); 
