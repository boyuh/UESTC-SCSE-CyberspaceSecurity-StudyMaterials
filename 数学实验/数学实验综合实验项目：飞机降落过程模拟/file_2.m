h=10;
L=80;
x=0:0.01:L;
y=(10.*h/L.^3).*x.^3-(15.*h/L.^4).*x.^4+(6.*h/L.^5).*x.^5;
plot(x,y)
xlabel('x/km');
ylabel('y/km');
title('·É»ú½µÂäÇúÏß');