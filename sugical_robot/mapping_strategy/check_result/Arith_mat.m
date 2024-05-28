function X = Arith_mat(q1, q2, N)
% this function is used to generate a matrix, whose first row is q1, while
% last row is q2, and others rows are Arithmetic sequence
    X = zeros(N, 5);
    array1 = q1;
    array2 = q2;
    common_difference = (array2 - array1) / (N-1);
    for i = 1:N
        if i == 1
            X(i, :) = array1;
        elseif i == N
            X(i, :) = array2;
        else
            X(i, :) = array1 + common_difference * (i - 1);
        end
    end
end

    