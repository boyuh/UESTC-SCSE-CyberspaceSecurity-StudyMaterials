#include<iostream>
#include<math.h>
using namespace std;

//模指数运算 
unsigned int mod_exp(unsigned int a,unsigned int e,unsigned int m){
	if(e==0) return 1;
	unsigned int y=mod_exp(a%m,e/2,m)%m;
	return e%2==0?(y*y)%m:((y*y)%m*(a%m))%m;
}

//素性测试1
bool prime_test(unsigned int a){
	if(a==1)return false;
	int n=(unsigned int)sqrt(a);
	bool Eratosthenes[n+1];
	int i,j;
	for(i=2;i<=n;i++) Eratosthenes[i]=true;
	for(i=2;i<=n;i++){
		if(Eratosthenes[i]){
			for(j=2;j*i<=n;j++) Eratosthenes[j*i]=false;
		}
	}
	
	bool res=true;
	for(i=2;i<=n;i++){
		if(Eratosthenes[i]){
			if(a%i==0) return false;
		}
	}
	return true;
} 
 
int main(){
	int num;
	cin>>num;
	if(num==1){
		unsigned int a,e,m;
		cin>>a>>e>>m;
		cout<<mod_exp(a,e,m)<<endl;
	}else{
		unsigned int a;
		cin>>a;
		cout<<prime_test(a);
	}
	return 0;
} 
