function sampledArray = sampling_array(originalArray, n)
% 将初始数组通过采样的方式缩小n 倍
    dim = size(originalArray, 1) / n;
    sampledArray = zeros(dim, 5);
    for i = 1:dim
    % Sample every 5th row starting from (i-1)*5 + 1
    sampledArray(i, :) = originalArray((i-1)*5 + 1, :);
    end
end


