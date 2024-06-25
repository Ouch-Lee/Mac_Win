% 这个文件用来验证论文目前推导的RPY三连杆和连续体映射的正确性

%% 生成n组随机数进行验证
rng(0);

% 生成 100 组数，每组 3 个数
numGroups = 10000;
numElementsPerGroup = 3;

% 初始化一个矩阵来存储生成的数
randomNumbers = zeros(numGroups, numElementsPerGroup);

% 生成随机数并赋值
for i = 1:numGroups
    randomNumbers(i, :) = (rand(numElementsPerGroup, 1) - 0.5) * pi; % 缩放到[-pi/2, pi/2]
end

%%
for i = 1:numGroups
    T_RPY = RPY_DH(randomNumbers(i,1), randomNumbers(i,2), randomNumbers(i,3));
    T_continuum = get_T_con_from_mapping(randomNumbers(i,1), randomNumbers(i,2), randomNumbers(i,3));
    if isRotationEqual(T_RPY, T_continuum) == 0
        disp("error!!!");
        break
    end
end

disp("over")


