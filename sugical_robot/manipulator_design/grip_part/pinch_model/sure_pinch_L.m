% L1 = 15;
% L2 = L1*tan(pi/6) :0.1:20;
% n = length(L2);
% delta_x_s = zeros(1,n);
% for i = 1:n
%     delta_x_s(i) = pinch_cal_4_links(L2(i));
% end
% 
% plot(L2, delta_x_s, 'LineWidth', 2);
% xlabel('L_2');
% ylabel('\Delta_x');
% title('-');
% grid on;
L2_range = linspace(5*sqrt(3), 25, 1000);

[a_i, a_f, L_2s] = pinch_find_valid_L2(L2_range);