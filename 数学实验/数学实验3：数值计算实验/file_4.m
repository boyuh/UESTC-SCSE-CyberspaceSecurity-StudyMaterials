h=0.2;
t=0:h:10;
n=length(t);
y=10.*ones(n,1);
for k=2:n
    y(k)=y(k-1)+h.*(0.02.*(1-0.001.*y(k-1)).*y(k-1));
end
[t,y2]=ode23(@(t,y)0.02.*(1-0.001.*y).*y,t,y(1));
plot(t,y,'o',t,y2)
legend('Euler','ode23º¯Êý');
fprintf('      t     y_Euler    y_ode23      error\n');
for k=1:n
    fprintf('%9.4f  %9.6f  %9.6f  %10.8f\n',t(k),y(k),y2(k),y(k)-y2(k));
end