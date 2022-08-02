#include<iostream>
#include<math.h>
#include<string>
#include <cstdlib> 
#include <ctime>
using namespace std;
 //第一题 
std::string miller_rabin_prime_test(unsigned int n,unsigned int a){
	if(!(a>1&&a<n-1)){
		string error="error";
		return error;
	}
	string not_prime="not_prime";
	string uncertain="uncertain";
	unsigned int n_temp=n-1,k=0,q; 
	while(n_temp){
		if(n_temp%2==0){
			n_temp/=2;
			k++;
		}else{
			q=n_temp;
			break;
		}
	}
	
	bool bo=false;
	int i;
	unsigned int a_q=1;
	for(i=0;i<q;i++){
		a_q=(a_q*q)%n;
	}
	if(a_q==1) bo=true;
	
	if(!bo){
		int j;
		for(j=1;j<=k;j++){
			unsigned int temp=1;
			int m;
			for(m=0;m<j-1;m++){
				temp*=2;
			}
			temp*=q;
			
			unsigned int a_temp=1;
			for(i=0;i<temp;i++){
				a_temp=(a_temp*a)%n;
			}
			
			if(a_temp==n-1){
				bo=true;
				break;
			}
		}
	}
	
	if(bo) return uncertain;
	return not_prime;
}


std::string miller_rabin_multiple_test(unsigned int n,unsigned int repeat_times){
	string not_prime="not_prime";
	string uncertain="uncertain";
	srand((int)time(0));
	int i;
	for(i=0;i<repeat_times;i++){
		unsigned int a=rand()%(n-1);
		if(!(a>1&&a<n-1)){
			i--;
			continue;
		}
		if(miller_rabin_prime_test(n,a)=="not_prime"){
			return not_prime;
		}
	}
	return uncertain;
}

//第二题 
int gcd(int a, int b){
	if (a < b){
		int temp = b;
		b = a;
		a = temp;
	}
	if (a%b == 0){
		return b;
	}else{
		return gcd(b, a%b);
	}
}
 
 
int ExtendEculid(int a, int b, int &x, int &y, int c){
	if (b == 1){
		x = 1;
		y = -c/a;
		return a;
	}
	int result = ExtendEculid(b, a%b, x, y, a);
	if (c != 0){
		int temp = x;
		x = y;
		y = temp - c / a*y;
	}
	return result;
}
 
 
int Generate(int a, int b){
	int x, y;
	if (b > a)
	{
		a += b;
		int result = ExtendEculid(a, b, x, y, 0);
		y += x;
		a -= b;
	}else{
		int result = ExtendEculid(a, b, x, y, 0);
	} 
	y %= a;
	if (y < 0) return y + a;
	else return y;
}
 
int euclid_mod_reverse(int a, int m){
	if (a<=0||m<=0) return -1; 
	if (gcd(a, m) != 1) return -1;
	return Generate(m, a);
}


int main(){
	int num;
	cin>>num;
	if(num==1){
		unsigned int n,a;
		cin>>n>>a;
		cout<<miller_rabin_prime_test(n,a)<<endl;
	} 
	if(num==2){
		unsigned int n,repeat_times;
		cin>>n>>repeat_times;
		cout<<miller_rabin_multiple_test(n,repeat_times)<<endl;
	}
	if(num==3){
		int a,m;
		cin>>a>>m;
		cout<<euclid_mod_reverse(a,m)<<endl;
	}
	return 0;
}
