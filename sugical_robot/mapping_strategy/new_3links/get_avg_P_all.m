% 计算5个 Position 的平均值
% 假设你有5个mxn的数组存储在 cell 数组 cellArray 中
function averageArray = get_avg_P_all(P_all_1, P_all_2, P_all_3, P_all_4, P_all_5)
% 举例:
    cellArray = {P_all_1, P_all_2, P_all_3, P_all_4, P_all_5};

    % 获取数组的大小
    [m, n] = size(cellArray{1});

    % 初始化一个 mxn 的数组来存储平均值
    averageArray = zeros(m, n);

    % 对每个位置的值求平均
    for i = 1:m
        for j = 1:n
            % 计算对应位置的值的平均值
            sum = 0;
            for k = 1:numel(cellArray)
                sum = sum + cellArray{k}(i, j);
            end
            averageArray(i, j) = sum / numel(cellArray);
        end
    end
