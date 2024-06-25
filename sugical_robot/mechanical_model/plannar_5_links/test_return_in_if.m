function [check, a,b,c] = test_return_in_if(test_a)
if test_a == 0
    check = 0;
    % a=0;
    % b=0;
    % c=0;
    return;

end
check = 1;
a = 1;
b = 2;
c = 3;
end
