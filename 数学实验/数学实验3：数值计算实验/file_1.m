function xp=myfun
xp=fzero(@(x)2.*x.^3-3.*x.^2+4.*x-5,1);
end
