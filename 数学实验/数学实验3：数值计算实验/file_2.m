function A=myfun
x0=[2;0];
tn=0:0.1:5;
[t,y]=ode45(@vdpol,tn,x0);
A=y(:,1)
    function dfun=vdpol(t,x)
        dfun=[x(2);20.*(1-x(1).^2).*x(2)+0.5.*x(1)];
    end
end
