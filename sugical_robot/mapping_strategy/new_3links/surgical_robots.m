r = 5.1:0.1:30;
len = length(r);
R = 5;
theta = ones(1,len);
h = ones(1,len);
for i = 1:len
    theta(i) = asin(R/r(i));
    h(i) = (1/cos(theta(i)) -1 )*r(i);
end

figure(1);
plot(r,theta);
xlim([6,30])
title('theta-r')
xlabel('r')
ylabel('theta')

figure(2);
plot(r,h);
xlim([6,30])
title('h-r')
xlabel('r')
ylabel('h')


a = 0.76;
b = 0.24;
f = a*theta - b*h;
figure(3)
plot(r,f)
xlim([10,30])
title('f(r)-r')

xlabel('r')
ylabel('f(r)')