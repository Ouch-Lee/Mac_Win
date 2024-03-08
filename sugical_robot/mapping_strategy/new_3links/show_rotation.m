% check if the T_extended is correct
% R = roty(pi/6) * rotx(pi/3);
% T_check = r2t(R);
% disp(T_check)
T0 = eye(4);
trplot(T0,'frame','O','color','g');
hold on,
T_ex = zeros(4,4);
for i = 1:3
    for j = 1:3
        T_ex(i,j) = T_extended(i,j);
    end
end

T_ex(:,4) = [0;0;0;1];
% disp(T_ex);
trplot(T_ex,'frame','A','color','b');
axis([-1 2 -2 2 -1 2]);
hold on,
% trplot(T_ex,'frame','B','color','r');

%% the next is to check if the relationship between (fi,ks) with (t3,t4) is correct
T_cont = zeros(4,4);
for i = 1:3
    for j = 1:3
        T_cont(i,j) = T_continuum(i,j);
    end
end
T_cont(:,4) = [0;0;0;1];
R_delta_x = rotz(delta_x);
T_delta_x = r2t(R_delta_x);

T_cont_delta_x = T_cont * T_delta_x;
T_cont_delta_x_1 = eye(4);
for i = 1:3
    for j = 1:3
        T_cont_delta_x_1(i,j) = T_cont_delta_x(i,j);
    end
end

trplot(T_cont_delta_x_1,'frame','B','color','r');