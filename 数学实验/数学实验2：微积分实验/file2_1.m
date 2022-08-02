function r=myfun
syms x a;
y=a*exp(x)/sqrt(a^2+x^2);
d=diff(y,x,2);
r=subs(d,x,5*a);