% 假设 angles 是你的1000 x 5 的数组

% 初始化 angleKF 作为存储处理后数据的数组
data_5_KF = zeros(size(data_3));

% 对每一组数据应用KalmanFilter的update函数
for i = 1:size(data_3, 2)
    % 创建KalmanFilter对象
    encoderKF = KalmanFilter(0.3, 16); % 使用新的预测误差和测量误差初始化对象
    
    for j = 1:size(data_3, 1)
        % 对当前数据点应用KalmanFilter的update函数，并将结果存储在 angleKF 中
        data_5_KF(j, i) = encoderKF.update(data_5(j, i));
    end
end

