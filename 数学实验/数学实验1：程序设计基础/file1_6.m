len=1200;
n1=len/64;
n2=len/85;
m=[]
for k1=0:n1
    k2=fix((len-k1*64)/85);
    remain=len-k1*64-k2*85;
    m=[m;k1,k2,remain];
end
m