function [x0,y0]=fun
f=inline('-exp(x).*x.*sin(x)');
[x1,y1]=fminbnd(f,0,2);
[x2,y2]=fminbnd(f,2,9);
if y1<y2
    x0=x1;
    y0=-y1;
else
    x0=x2;
    y0=-y2;
end
ezplot('exp(x).*x.*sin(x)',[0,9]);
hold on
plot(x0,y0,'o');
end