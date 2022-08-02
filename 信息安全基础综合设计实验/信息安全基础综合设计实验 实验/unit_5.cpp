#include <iostream>
#include<string.h>
#include <openssl/bn.h>
#include <openssl/bio.h>

using namespace std;

//第一问
string mod_exp(string a, string e, string m) {
    BIGNUM *A, *E, *M, *R;
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    A = BN_new();
    E = BN_new();
    M = BN_new();
    R = BN_new();
    BN_dec2bn(&A, a.data());
    BN_dec2bn(&E, e.data());
    BN_dec2bn(&M, m.data());
    BN_mod_exp(R, A, E, M, ctx);
    string ret = BN_bn2dec(R);
    BN_free(A);
    BN_free(E);
    BN_free(M);
    BN_free(R);
    BN_CTX_free(ctx);
    return ret;
}

//第二问
string mod_inverse(string a, string m) {
    BIGNUM *A, *M, *R;
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    A = BN_new();
    M = BN_new();
    R = BN_new();
    BN_dec2bn(&A, a.data());
    BN_dec2bn(&M, m.data());
    BN_mod_inverse(R, A, M, ctx);
    string ret = BN_bn2dec(R);
    BN_CTX_free(ctx);
    BN_free(A);
    BN_free(M);
    BN_free(R);
    return ret;
}

int main(){
	int num;
	cin>>num;
	if(num==1){
		string a="82019154470699086128524248488673846867876336512717";
		string e="82019154470699";
		string m="8201915447069908612852424848867384686787636512717";
		cout<<mod_exp(a,e,m)<<endl;
	}
	if(num==2){
		string a="3264712363521453245324654373467546854684";
		string e="1235324673547";
		string m="23735685468796536472546763256";
		cout<<mod_exp(a,e,m)<<endl;
	}
	if(num==3){
		string a="32647123635214532453246543465437373467546854684";
		string e="123532463456345746854685473547";
		string m="373454356735476354734";
		cout<<mod_exp(a,e,m)<<endl;
	}
	if(num==4){
		string a="5";
		string m="14";
		cout<<mod_inverse(a,m)<<endl;
	}
	if(num==5){
		string a="1000007";
		string m="16";
		cout<<mod_inverse(a,m)<<endl;
	}
	if(num==6){
		string a="99998071";
		string m="73";
		cout<<mod_inverse(a,m)<<endl;
	}
	return 0;
}
