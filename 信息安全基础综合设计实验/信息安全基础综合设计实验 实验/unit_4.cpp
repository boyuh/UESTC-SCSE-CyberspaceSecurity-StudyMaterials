#include<iostream>
#include<cstdlib>
#include<math.h>
#include<string.h>
#include <ctime>
#include <vector>
#include<algorithm> 
#include<sys/time.h>
using namespace std;

//第一问 
unsigned int gseed=1; 
void lcg_srand(unsigned int seed){
	gseed=seed;
}

unsigned int lcg_rand(){
	unsigned int a=1103515245,c=12345,m=pow(2,31);
	unsigned int res=(a*gseed+c)%m;
	lcg_srand(res);
	return res;
}

//第二问 
std::string decimal_to_binary(unsigned int input){//十进制到二进制 
	string res;
	if(input==0)res="0";
	while(input!=0){
		char temp=input%2+'0';
		res=res+temp;
		input/=2;
	}
	reverse(res.begin(),res.end());
	return res;
}

unsigned int binary_to_decimal(std::string input){//二进制到十进制 
	unsigned int res=0;
	int n=input.length();
	int i;
	for(i=n-1;i>=0;i--){
		if(input[i]!='0'&&input[i]!='1') return 0;
		res+=(input[i]-'0')*pow(2,n-1-i);
		if(res==4294967295) break;
	}
	return res;
}

unsigned int bbs_rand(int flag){
	unsigned int p=11,q=19,s=3;
	unsigned int N=p*q;
	int i,j;
	vector<unsigned int> x_temp;
	x_temp.push_back(s);
	for(int i=1;i<=32;i++){
		unsigned int temp;
		temp=(x_temp[i-1]*x_temp[i-1])%N;
		x_temp.push_back(temp);
	}
	vector<string> x_string;
	for(int i=1;i<=32;i++){
		x_string.push_back(decimal_to_binary(x_temp[i]));
	}
	
	string res; 
	if(flag==0){
		for(i=0;i<32;i++){
			string temp=x_string[i];
			int n=temp.length();
			res=res+temp[n-1];
		}
	}else if(flag==1){
		for(i=0;i<32;i++){
			string temp=x_string[i];
			int n=temp.length();
			int num=0;
			for(j=0;j<n;j++){
				if(temp[j]=='1') num++;
			}
			if(num%2==0){
				res=res+'1';
			}else{
				res=res+'0';
			}
		}
	}else if(flag==2){
		for(i=0;i<32;i++){
			string temp=x_string[i];
			int n=temp.length();
			int num=0;
			for(j=0;j<n;j++){
				if(temp[j]=='1') num++;
			}
			if(num%2==0){
				res=res+'0';
			}else{
				res=res+'1';
			}
		}
	}else{
		return 0;
	}
	return binary_to_decimal(res);
}

//第三问 
void rand_time(){
	float time_use1=0,time_use2=0;
    struct timeval start;
    struct timeval end;
    
    //lcg
    gettimeofday(&start,NULL);
    int i;
    for(i=0;i<10;i++){
    	unsigned int temp=lcg_rand(); 
	}
    gettimeofday(&end,NULL);
    time_use1=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
    cout<<"lcg_rand time:"<<time_use1<<"ms"<<endl;
    
    //bbs 
    gettimeofday(&start,NULL);
    for(i=0;i<10;i++){
    	unsigned int temp=bbs_rand(0); 
	}
    gettimeofday(&end,NULL);
    time_use2=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
    cout<<"bbs_rand time:"<<time_use2<<"ms"<<endl;
} 

int main(){
	int num;
	cin>>num;
	if(num==1){
		int seed;
		cin>>seed;
		lcg_srand(seed);
		cout<<seed<<endl;
	}
	if(num==2){
		int i,n;
		unsigned int seed;
		cin>>seed>>n;
		lcg_srand(seed);
		for(i=0;i<n;i++){
			cout<<lcg_rand()<<endl;
		}
	}
	if(num==3){
		int n;
		cin>>n;
		cout<<bbs_rand(n)<<endl;
	}
	if(num==4){
		rand_time();
	}
	return 0;
}
