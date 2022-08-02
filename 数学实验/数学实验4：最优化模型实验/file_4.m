C=[17 15];
A=[3 5;6 5;2 6];
b=[150;160;180];
Aeq=[];
beq=[];
e0=[0;0];
e1=[inf,inf];
[x,fval]=linprog(-C,A,b,Aeq,beq,e0,e1);
x
fmax=-fval