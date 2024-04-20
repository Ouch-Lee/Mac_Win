function F1 = calculate_F1(theta_i, theta, k, l0, mu, Fpress)
    % F1 = (4 * k * l0^2 * sind(theta) + (mu * Fpress - sqrt(3) * k * l0) * l0 * sind(theta/2)) / L1;
    % 
    % F1 = 4 * k* l0^2 * sind(theta) * (cosd(theta) - sqrt(3)/2);
    F1 = (k* 2*l0* (cosd(theta) - cosd(theta_i))  + mu * Fpress  ) * 2* l0 * sind(theta);
end