x(1)=0;
x(2)=1;
for i=3:40
    x(i)=x(i-1)+2*x(i-2);
end
x