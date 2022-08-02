function r=myfun
syms x;
y=1/(1+x^2);
r=taylor(y,x,0,'order',7);