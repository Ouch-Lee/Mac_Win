function D1_calculated =  compareData(MotorData, D1_extracted) %, D1_extracted
    % compareData compares calculated D1 data with extracted D1 data
    % Inputs:
    %   MotorData: An nx5 matrix containing input Data line values
    %   D1_extracted: An nx5 matrix containing extracted D1 line values
    
    % Number of data rows
    n = size(MotorData, 1);
    
    % Initialize calculated D1 array
    D1_calculated = zeros(n, 5);
    
    % Iterate through each row of MotorData
    for i = 1:n
        % Compute D1 line for each row
        [D1, alpha2, Phi3, alpha4, Theta5] = computeD1(MotorData(i, :));
        
        % Store calculated results in the array
        D1_calculated(i, :) = [D1, alpha2, Phi3, alpha4, Theta5];
    end
    

    % Calculate differences
    difference = D1_calculated - D1_extracted;
    disp('Difference (Calculated - Extracted):');
    disp(difference);

    % Compute and display mean squared error
    mse = mean(difference.^2, 'all');
    fprintf('Mean Squared Error: %f\n', mse);
end

% Assume the computeD1, plannar_5_bar_fk, modified_DH, compute_master_T,
% compute_slave_T, and solve_nonlinear_eq functions are defined here or in
% separate files accessible to the script.

