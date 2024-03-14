function P = get_end_position(data)
% this function aim to calculate the position of end effector as well as surgeon's finger
% Input:
%   row_data - 由串口发送的nx5 的数组，分别表示5个角度, 
%   input2 - Description of input parameter 2
%
% Output:
%   长度为n的数组，存储n个采样点的位置

%% 将前两个角度信息转化为距离信息 同时将角度转为弧度

%%
row = size(data,1);
P = zeros(row, 3);
for m = 1:row
    P(m,:) = get_one_P_gpt4(data(m,:));
end

end
