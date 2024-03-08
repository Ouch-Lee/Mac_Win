function P_next =  compute_Pnext(A,B,Q,R,P)
P_next = Q + A'* P * A - A' * P *B * inv(R + B'*P*B) * B'*P*A;
