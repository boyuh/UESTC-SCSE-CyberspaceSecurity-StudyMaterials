syms s h u a0 a1 a2 a3 a4 a5;
eq1=a0+a1*s+a2*s^2+a3*s^3+a4*s^4+a5*s^5-h;
eq2=a0;
eq3=u*(a1+2*a2*s+3*a3*s^2+4*a4*s^3+5*a5*s^4);
eq4=a1;
eq5=u^2*(2*a2+6*a3*s+12*a4*s^2+20*a5*s^3);
eq6=2*a2*u^2;
[a0 a1 a2 a3 a4 a5]=solve(eq1,eq2,eq3,eq4,eq5,eq6,a0,a1,a2,a3,a4,a5)