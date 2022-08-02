n=0;
for i=1:1000
    j=(i^2-i)/100
    if fix(j)==j&&j>0&&j<=1000
       n=n+1;
       a(n)=i;
       b(n)=j;
    end
end
a
b