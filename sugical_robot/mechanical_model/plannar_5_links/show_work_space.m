% Parameters
l1 = 8; % Length of link l1
l2 = 8; % Length of link l2
l3 = 8; % Length of link l3
l4 = 8; % Length of link l4
l5 = 4;  % Length of link l5

% Angle ranges for joints u1 and u4
u1_range = linspace(pi/6, 3*pi/2, 200);
u4_range = linspace(-pi/2, 5*pi/6, 200);

% Initialize arrays to store reachable positions
reachable_x = [];
reachable_x2 = [];
reachable_y = [];
reachable_y2 = [];

% Compute reachable workspace
for u1 = u1_range
    for u4 = u4_range
        [check_para, xc, yc, xe, ye, ~, ~, ~, ~] = planar_5_bar_foward_my(u1, u4, l1, l2, l3, l4, l5);
        if check_para == 1
            reachable_x = [reachable_x, xc]; %#ok<AGROW>
            reachable_x2 = [reachable_x2, xe];%#ok<AGROW>
            reachable_y = [reachable_y, yc]; %#ok<AGROW>
            reachable_y2 = [reachable_y2, ye];%#ok<AGROW>
        end
    end
end

% Plotting the reachable workspace
figure;
scatter(reachable_x, reachable_y, 1, 'b.'); % Plot as blue points
hold on;
% scatter(reachable_x2, reachable_y2, 1, "red");
axis equal;
grid on;
xlabel('X-axis');
xlim([-12 16]);
ylim([0 16]);
ylabel('Y-axis');
title('Workspace of the Planar 5-Bar Linkage');



%% Parameters
% L = 5; % Distance between the centers of the circles
% R = 2 * L; % Radius of each circle
% 
% % Circle centers
% center1 = [0, 0];
% center2 = [L, 0];
% 
% % Define the circles
% theta = linspace(0, 2*pi, 500);
% circle1_x = center1(1) + R * cos(theta);
% circle1_y = center1(2) + R * sin(theta);
% 
% circle2_x = center2(1) + R * cos(theta);
% circle2_y = center2(2) + R * sin(theta);
% 
% % Plot the circles
% figure;
% hold on;
% fill(circle1_x, circle1_y, 'r', 'FaceAlpha', 0.3, 'EdgeColor', 'none'); % Circle 1
% fill(circle2_x, circle2_y, 'b', 'FaceAlpha', 0.3, 'EdgeColor', 'none'); % Circle 2
% 
% % Set plot properties
% axis equal;
% grid on;
% title('Intersection of Two Circles');
% xlabel('X-axis');
% ylabel('Y-axis');
% 
% % Compute intersection area (optional)
% % Area formula for two intersecting circles
% d = L; % Distance between centers
% if d < 2*R
%     part1 = R^2 * acos(d / (2 * R));
%     part2 = R^2 * acos(d / (2 * R));
%     part3 = (1/2) * sqrt((-d + R + R) * (d + R - R) * (d - R + R) * (d + R + R));
%     intersection_area = part1 + part2 - part3;
%     disp(['Intersection Area: ', num2str(intersection_area)]);
% else
%     disp('The circles do not intersect.');
% end
% 
% hold off;
