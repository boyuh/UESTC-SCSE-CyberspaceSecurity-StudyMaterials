function opt
n=1000000;
goodvalue=inf;
for i=1:n
    x(1)=15*rand;
    x(2)=9*rand;
    x(3)=fix(26*rand);
    temp=fun(x);
    if temp<goodvalue & cons(x)<=0
        goodx=x;
        goodvalue=temp;
    end
end
goodx
goodvalue
end
function r=fun(x)
r=2.*(x(1)-1).^2+3.*(x(2)-4).^2+x(1).*x(2)+(2.*x(3)-5).^2;
end
function c=cons(x)
c=zeros(1,2);
c(1)=3.*x(1)+2.*x(2)+6.*x(3)-20;
c(2)=4.*x(1)+5.*x(2)+2.*x(3)-21;
end