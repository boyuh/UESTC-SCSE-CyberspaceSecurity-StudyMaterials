arrival(1)=5*rand;
i=1;
while arrival(i)<=30*60
    i=i+1;
    arrival(i)=arrival(i-1)+5*rand;
end
arrival(i)=[];
n=length(arrival)
arrival