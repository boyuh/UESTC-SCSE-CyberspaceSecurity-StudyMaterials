for i=1:7
   eval(strcat('syms x',num2str(i)));
end
funy = 174.42*(x1/x5)*(x3/(x2 - x1))^0.85*sqrt((1 - 2.62*(1 - 0.36*(x4/x2)^(-0.56))^(3/2)*(x4/x2)^1.16)/(x6*x7));
for j=1:7
    eval(['d',num2str(j),'=diff(funy,x',num2str(j),',1);'])
    eval(['df',num2str(j),'=inline(d',num2str(j),')'])
end