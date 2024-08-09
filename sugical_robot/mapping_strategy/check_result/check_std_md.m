

%% 使用std和md方法分别对平面二连杆建模，得出相同的结果
%% 这里是一个简单的例子，验证std法和md在平面二连杆上会得到相同的结果
% % 标准 DH 参数表
% a1 = 1;
% a2 = 1;
% theta1 = pi/3;
% theta2 = pi/4;
% 
% % 标准 DH 方法的齐次变换矩阵
% A1_standard = standard_DH(a1, 0, 0, theta1);
% A2_standard = standard_DH(a2, 0, 0, theta2);
% 
% % 总的齐次变换矩阵
% T_standard = A1_standard * A2_standard;
% 
% % 修正后的 DH 参数表
% d1 = a1;
% 
% % 修正后的 DH 方法的齐次变换矩阵
% A1_modified = modified_DH(0, 0, 0, theta1);
% A2_modified = modified_DH(d1, 0, 0, theta2);
% A3_modified = modified_DH(a2, 0, 0, 0);
% 
% % 总的齐次变换矩阵
% T_modified = A1_modified * A2_modified * A3_modified;
% 
% % 输出结果
% disp('Standard DH:');
% disp(T_standard);
% 
% disp('Modified DH:');
% disp(T_modified);


%% 之前编写过一个std建模连续体的函数，2024.7.15再尝试一下新的函数 == > std法没有问题
% 使用示例
phi = pi/3;  % 示例参数
ks = pi/6;      % 示例参数
s = 2;       % 示例参数

% T_end_effector = end_effector_transform(phi, ks, s);
% 
% % 输出结果
% disp('End effector transformation matrix:');
% disp(T_end_effector);
% 
% disp('continuum transformation matrix:');
% disp(get_continuum_T(phi, ks));

%% 尝试使用md DH对连续体建模  ==> md 方法也没有问题
T_end_effector_modified = end_effector_transform_modified(phi, ks, s);

% 输出结果
disp('End effector transformation matrix (modified DH):');
disp(T_end_effector_modified);

%% 现在的问题是，简化完后的md 不对，那肯定是简化的时候出了问题，或者其实坐标系的问题？
% 简化完ok
% 检查坐标系应该怎么换
disp('simplfy continuum transformation matrix (modified DH):');
As1 = modified_DH(0,0 ,0, phi);
As2 = modified_DH(0,-pi/2,0,ks);
As3 = modified_DH(0,pi/2 ,0, -phi);
disp(As1 * As2 *As3);