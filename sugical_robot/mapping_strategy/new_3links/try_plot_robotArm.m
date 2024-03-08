L(1) = Link([0,0,0,0,1]);
L(2) = Link([0 0 1 0 0]);
L(3) = Link([0 0 1 -pi/2 0]);
L(1).qlim = [0,0.3];

RobotArm = SerialLink(L,'name','ws');
for i = 0:0.02:0.3
    for j = 0:0.5:2*pi
        for k = 0:0.5:2*pi
            T = RobotArm.fkine([i j k]);
            a = T.t';
%         qn = T*[0;0;0;1];
%         ws.plot([i j]);
%         plot3(qn(1),qn(2),qn(3),'.');
            plot3(a(1),a(2),a(3),'.');
            hold on
        end
    end
end