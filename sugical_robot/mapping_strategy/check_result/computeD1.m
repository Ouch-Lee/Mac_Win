function [D1, alpha2, Phi3, alpha4, Theta5] = computeD1(data)
    % computeD1 computes the transformation from input Data line to D1 line
    % Input:
    %   data: A vector of 5 elements corresponding to the Data line values
    % Output:
    %   D1, alpha2, Phi3, alpha4, Theta5: Corresponding calculated values
    
    % Extract input values
    beta_1 = deg2rad(data(1));
    beta_2 = deg2rad(data(2));
    beta_3 = deg2rad(data(3));
    beta_4 = deg2rad(data(4));
    beta_5 = deg2rad(data(5));

    % Length parameters (fixed in this example)
    l5 = 8;

    % Forward kinematics to get end-effector position
    [xc, yc, u3] = plannar_5_bar_fk(beta_1, beta_2);
    beta_4_t = pi - u3;

    % Compute equivalent three-bar transformation matrix
    theta_1 = atan((0.5*l5 - xc) / yc);
    d_2 = sqrt((xc - 0.5*l5)^2 + yc^2);
    delta_3 = (theta_1 + beta_4_t - 0.2*pi);
    theta_3 = beta_3 - delta_3;

    % Compute master transformation matrix
    joints_master = [theta_1, d_2, theta_3, beta_4, beta_5];
    T_master = compute_master_T(joints_master(1), joints_master(2), joints_master(3), joints_master(4), joints_master(5));
    px = T_master(1, 4);
    pz = T_master(3, 4);

    % Solve nonlinear equation
    theta_3e = solve_nonlinear_eq(px, joints_master(1), joints_master(3), joints_master(4));
    alpha2 = (joints_master(1) + joints_master(3) - theta_3e);
    alpha4 = acos(cos(theta_3e) * cos(joints_master(4)));

    % Calculate Phi3
    sign_3 = sign(theta_3e);
    sign_4 = sign(joints_master(4));
    Phi3 = sign_4 * acos(cos(joints_master(4)) * sin(theta_3e) / sin(alpha4));
    Delta_x = sign_3 * acos(cos(theta_3e) * sin(Phi3)) + Phi3 - pi/2;
    Theta5 = joints_master(5) + Delta_x;
    
    T_slave_1 = compute_slave_T(0, alpha2, Phi3, alpha4, Theta5);
    D1 = pz - T_slave_1(3, 4);
    alpha2 = rad2deg(alpha2);
    Phi3 = rad2deg(Phi3);
    alpha4 = rad2deg(alpha4);
    Theta5 = rad2deg(Theta5);
end