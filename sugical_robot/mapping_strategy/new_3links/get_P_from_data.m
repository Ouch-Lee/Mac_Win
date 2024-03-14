%% 数据采样
% data 是源数据，不要动
function P_all = get_P_from_data(data)

    sampling_data = sampling_array(data,5);

    %% 减去初始值
    row = size(sampling_data,1);
    delta_para = sampling_data(1,:);
    for i=1:row
        sampling_data(i,:) = sampling_data(i,:) - delta_para;
    end

    %% 预处理数据
    d = 22; % 齿轮分度圆直径
    for j =1:row
        sampling_data(j,1) = ( sampling_data(j,1) / 360 ) * pi * d;
        sampling_data(j,2) = sampling_data(j,1);
        for i = 3:5
              sampling_data(j,i) = deg2rad(sampling_data(j,i));
        end
    end 

    P_all = get_end_position(sampling_data);
end


