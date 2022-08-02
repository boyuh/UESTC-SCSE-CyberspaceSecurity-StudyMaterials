C=[2.5 5 10];
A=[-2.5 -5 -10;-2 -2 1];
b=[-50;0];
Aeq=[1 1 1];
beq=[100];
e0=[10;0;20];
e1=[30;90;80];
[x,fval]=linprog(-C,A,b,Aeq,beq,e0,e1);
x
max=-fval