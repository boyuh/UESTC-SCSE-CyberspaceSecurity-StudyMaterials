syms s u h x y;
y=(10.*h/s.^3).*x.^3-(15.*h/s.^4).*x.^4+(6.*h/s.^5).*x.^5;
a=u^2*diff(y,x,2)
da=diff(a,x,1)
x0=solve(da,x)
a0=simplify(subs(a,x,x0))