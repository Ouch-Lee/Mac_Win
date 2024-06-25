function result = isRotationEqual(matrix1, matrix2)
    % 默认阈值，如果未提供则使用 1e-6

    threshold = 1e-12;

    
    % 检查输入矩阵是否为 4x4 矩阵
    if ~isequal(size(matrix1), [4, 4]) || ~isequal(size(matrix2), [4, 4])
        error('输入的矩阵必须是 4x4 齐次变换矩阵。');
    end
    
    % 提取旋转部分
    rotation1 = matrix1(1:3, 1:3);
    rotation2 = matrix2(1:3, 1:3);
    
    % 计算两个旋转矩阵的差的绝对值
    diff = abs(rotation1 - rotation2);
    
    % 求差的和
    sumDiff = sum(diff(:));
    
    % 判断累计误差是否小于阈值
    if sumDiff < threshold
        result = 1;
    else
        result = 0;
    end
end