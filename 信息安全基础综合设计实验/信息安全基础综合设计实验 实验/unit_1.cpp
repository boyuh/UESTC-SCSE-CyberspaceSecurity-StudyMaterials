#include<iostream>
#include<string.h>
#include<math.h>
#include<algorithm> 
using namespace std;

unsigned int binary_to_decimal(std::string input){
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

std::string decimal_to_binary(unsigned int input){
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
