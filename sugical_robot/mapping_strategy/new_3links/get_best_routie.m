function [V_next, ustar] = get_best_routie(V, para)
V_next = zeros(para.n, 1);
ustar = zeros(para.n ,1);
for i = 1:para.n
    for u = 1:para.n
        if i == para.xf
            xnext = i;
        else
            xnext = u;
        end
           
        if u == para.xf
            rc = para.A(i,u);
        else
            rc = para.A(i,u) + para.c; 
        end
        tmpCost(u) = rc + V(xnext);
    end
    [V_next(i), ustar(i)] = min(tmpCost);
end

        