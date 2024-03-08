A = [1 2 3;2 1 0;1 1 3];
B = [1 ;0 ;1];
Q = eye(3);
Q(2,2) = 10; Q(3,3) = 3;
R =2;

N = 10;
P_all = zeros(3,3*N);
P = Q;
for k = 1:N
    P_next = compute_Pnext(A,B,Q,R,P);
    if P == P_next
        disp(k)
        break;
    end
    P = P_next;
    P_all(:,3*k-2 : 3*k) = P;
end

    
    