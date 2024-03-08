
syms d1 theta2 theta3 theta4 theta5
the_d1 = 10:10:120;
theta2 = sym(deg2rad(0));
theta5 = sym(0);
the_theta3 = -180:10:180;
the_theta3 = deg2rad(the_theta3);
the_theta4 = deg2rad(-180:10:180);
len1 = length(the_d1);
len3 = length(the_theta3);
len4 = length(the_theta4);

figure(1)
% scatter3(0,0,0,[],'r')
% hold on
positions = zeros(3,len3*len4);
% positions_d1 = zeros(3,len1);
count_d1 = 1;
count = 1;

% for i = 1:len1
%     d1 = the_d1(i);
%     theT = getDH_matix(d1,theta2,0,0,theta5);
%     positions_d1(1:3, count_d1) = theT(1:3,4);
%     count_d1 = count_d1 + 1;
% end
% 
% d1_z = positions_d1(1,:);
% d1_y = positions_d1(2,:);
% d1_x = positions_d1(3,:);
% figure(1)

% hold on
% scatter3(d1_x,d1_y,d1_z,'p')


d1 = 0;

for i = 1:len3
    for j = 1:len4
        theT = getDH_matix(d1,theta2,the_theta3(i),the_theta4(j),theta5);
        position = theT(1:3,4);
%         positions(1:3,count) = position;
%         count = count+1;
        z = position(1);
        y = position(2);
        x = position(3);
        scatter3(x,y,z,[],i+j);
        hold on
    end
end

xlim([0,400]);
ylim([-200,200])
zlim([0,400])
% disp(positions(1:3,40:end))
