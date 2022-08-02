#include <bits/stdc++.h>
#include <cstdio>
#include <openssl/rc4.h>
#include <openssl/des.h>
#include <openssl/sha.h>

using namespace std;

// ================ RC4 Start ================================

// �ú���ʵ��RC4�����㷨����
//  ����:
//      data - ����������ַ���
//      secret_key - ��Կ
//  ����ֵ:
//      string����, ���ؼ��ܵĽ����������������쳣���򷵻ؿ��ַ������˳�
string rc4_encrypt(string data, string secret_key) {
    int secret_key_len=secret_key.length();
    int data_len=data.length();
    if(secret_key_len==0||data_len==0){
    	return "";
	}
    
    RC4_KEY key;
    RC4_set_key(&key,secret_key_len,(unsigned char*)secret_key.c_str());
    
    unsigned char *outdata;
	outdata=(unsigned char*)malloc(sizeof(unsigned char)*(data_len+1));
	memset(outdata,0,data_len+1); 
    RC4(&key, data_len, (unsigned char*)data.c_str(),outdata);
    string res;
    res.append(reinterpret_cast<const char*>(outdata));
    return res;
}

// �ú���ʵ��RC4�����㷨����
//  ����:
//      data - ����������ַ���
//      secret_key - ��Կ
//  ����ֵ:
//      string����, ���ؽ��ܵĽ����������������쳣���򷵻ؿ��ַ������˳�
string rc4_decrypt(string data, string secret_key) {
    int secret_key_len=secret_key.length();
    int data_len=data.length();
    if(secret_key_len==0||data_len==0){
    	return "";
	}
	
    RC4_KEY key;
    RC4_set_key(&key,secret_key_len,(unsigned char*)secret_key.c_str());
    
    unsigned char *indata;
	indata=(unsigned char*)malloc(sizeof(unsigned char)*(data_len+1));
	memset(indata,0,data_len+1); 
    RC4(&key, data_len, (unsigned char*)data.c_str(),indata);
    string res;
    res.append(reinterpret_cast<const char*>(indata));
    return res;
}

// ================ RC4   End ================================


// ================ DES Start ================================

// ��ʹ�øú�����string����ת��ΪDES_cblock���͡���������Ĵ˺�����
// - �ú���������ת�����ĺ��������ݣ��벻Ҫ���ô˺���ת��secret_key��
// - secret_key��ʹ��`DES_string_to_key()`����ת����
void convert_string_to_des_block(string str, DES_cblock &output);

// �ú���ʵ��DES-ECB�����㷨����
//  ����:
//      plain - ����������ַ���
//      secret_key - ��Կ
//  ����ֵ:
//      string����, ���ؼ��ܵĽ��
//  ����˵��:
//      - ��ʹ��`convert_string_to_des_block()`������string����ת��ΪDES_cblock���͡�
//        ������ת�������ܵ��²����޷�ͨ��
//      - secret_keyʹ��ǰ����`DES_string_to_key()`����key��
string des_encrypt(string plain, string secret_key) {
    DES_cblock key;
    DES_string_to_key(secret_key.c_str(), &key);
    DES_key_schedule schedule;
    DES_set_key_checked(&key,&schedule);
    
    DES_cblock input,output;
    convert_string_to_des_block(plain,input);
    
    DES_ecb_encrypt(&input, &output, &schedule, DES_ENCRYPT);
    return (char*)output;
}

// �ú���ʵ��DES-ECB�����㷨����
//  ����:
//      cipher - ����������ַ���
//      secret_key - ��Կ
//  ����ֵ:
//      string����, ���ؽ��ܵĽ��
//  ����˵��:
//      - ��ʹ��`convert_string_to_des_block()`������string����ת��ΪDES_cblock���͡�
//        ������ת�������ܵ��²����޷�ͨ��
//      - secret_keyʹ��ǰ����`DES_string_to_key()`����key
string des_decrypt(string cipher, string secret_key) {
    DES_cblock key;
    DES_string_to_key(secret_key.c_str(), &key);
    DES_key_schedule schedule;
    DES_set_key_checked(&key,&schedule);
    
    DES_cblock output,input;
    convert_string_to_des_block(cipher,output);
    
    DES_ecb_encrypt(&output, &input, &schedule, DES_DECRYPT);
    return (char*)input;
}

// ================ DES   End ================================

// ================ SHA1 Start ===============================

// �ú���ʵ��SHA1 hash�㷨����
//  ����:
//      msg - ������ַ���
//  ����ֵ:
//      string����, ����sha1��ϢժҪ���
string sha1_digest(string msg) {
	char res[33]={'\0'};
	SHA1((const unsigned char *)msg.c_str(), msg.length(), (unsigned char*)res);
    return res;
}
// ================ SHA1   End ===============================

// ================ Helper Start =============================
// Helper ˵����
//     1. ��Ĳ����Ѿ�ȫ������ˣ����������¿��ˡ�
//     2. �����޸��������ݡ��������ܺ����������޸Ŀ��ܵ��µ�Ԫ�����޷�ͨ��

void convert_string_to_des_block(string str, DES_cblock &output) {
    for(int i = 0; i < 8; ++i) {
        output[i] = str[i];
    }
}
// ================ Helper End ================================
