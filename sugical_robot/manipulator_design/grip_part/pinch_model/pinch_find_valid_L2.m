% function [a_i, a_f, L2_values] = pinch_find_valid_L2(L2_range)
%     % 初始化存储 a_i, a_f 的数组
%     a_i = [];
%     a_f = [];
% 
%     % 初始化 L2 值数组
%     L2_values = [];
% 
%     % 循环遍历给定的 L2 范围
%     for L2 = L2_range
%         % 计算 a_i 和 a_f
%         L1 = 15;
%         L = sqrt(L1^2 + L2^2);
%         theta_i = 120 - rad2deg(atan2(L2,L1));
%         a_i_val = 2 * L * cosd(theta_i);
%         theta_f = theta_i - 30;
%         a_f_val = 2 * L * cosd(theta_f);
% 
%         % 将结果添加到对应的数组中
%         a_i = [a_i, a_i_val];
%         a_f = [a_f, a_f_val];
%         L2_values = [L2_values, L2];
%     end
% 
%     % 绘制图像
%     plot(L2_values, a_i, 'b-', 'LineWidth', 2);
%     hold on;
%     plot(L2_values, a_f, 'r--', 'LineWidth', 2);
%     xlabel('L2');
%     ylabel('a_i, a_f');
%     title('a_i 和 a_f 关于 L2 的变化');
%     legend('a_i', 'a_f');
%     grid on;
% end

function [valid_L2] = pinch_find_valid_L2()
    % 初始化存储符合条件的 L2 值的数组
    valid_L2 = [];

    % 给定的 L2 范围
    L2_range = linspace(5*sqrt(3), 25, 1000);

    % 循环遍历 L2 范围
    for L2 = L2_range
        % 计算 a_i 和 a_f
        L1 = 15;
        L = sqrt(L1^2 + L2^2);
        theta_i = 120 - rad2deg(atan2(L2,L1));
        a_i = 2 * L * cosd(theta_i);
        theta_f = theta_i - 30;
        a_f = 2*L* cosd(theta_f);

        % 检查条件
        if a_i > 17 && a_f < 37.5
            % 将符合条件的 L2 值添加到数组中
            valid_L2 = [valid_L2, L2];
        end
    end

    % 打印符合条件的 L2 值
    disp('符合条件的 L2 值为：');
    disp(valid_L2);
end

