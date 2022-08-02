#include <bits/stdc++.h>
#include <openssl/bn.h>
#include <cstdio>
#include <openssl/pem.h>
#include <openssl/rsa.h>

#define PUBLICKEY "../keys/public.pem"
#define PRIVATEKEY "../keys/private.pem"

using namespace std;

RSA *rsa_private_key = NULL; // rsa私钥
RSA *rsa_public_key = NULL; // rsa公钥

bool load_RSA_keys() {
	FILE *fp = NULL; // 初始化文件指针
	if ((fp = fopen(PUBLICKEY, "r")) == NULL){
		return false;
	}
	rsa_public_key = PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL);
	if((fp = fopen(PRIVATEKEY, "r")) == NULL){
        return false;
    }
    rsa_private_key = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL);
    if(!rsa_public_key || !rsa_private_key){
        return false;
    }
	fclose(fp); 
	return true;
}

string RSA_Encryption(string plaintext)
{
    load_RSA_keys();
    char* cipher = (char*)malloc(RSA_size(rsa_public_key));
    memset(cipher, 0, RSA_size(rsa_public_key));
    int len_cipher = RSA_public_encrypt(plaintext.size(), (unsigned char*)plaintext.c_str(),(unsigned char*)cipher, rsa_public_key, RSA_PKCS1_PADDING);
    return string(cipher, len_cipher);
}

string RSA_Decryption(string ciphertext)
{
    load_RSA_keys();
    char* plain = (char*)malloc(RSA_size(rsa_private_key));
    memset(plain, 0, RSA_size(rsa_private_key));
    int len_plain = RSA_private_decrypt(ciphertext.size(), (unsigned char*)ciphertext.c_str(),(unsigned char*)plain, rsa_private_key, RSA_PKCS1_PADDING);
    return string(plain, len_plain);
}

string RSA_signature_signing(string input)
{
    load_RSA_keys();
    return RSA_Encryption(input);
}

bool RSA_signature_verify(string message, string signature)
{
    load_RSA_keys();
    return RSA_Decryption(signature) == message;
}
