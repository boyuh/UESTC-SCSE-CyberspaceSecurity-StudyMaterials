#include <bits/stdc++.h>
#include <cstdio>
#include <openssl/rc4.h>
#include <openssl/des.h>
#include <openssl/sha.h>

using namespace std;

// ================ RC4 Start ================================

// 该函数实现RC4加密算法功能
//  参数:
//      data - 输入的明文字符串
//      secret_key - 密钥
//  返回值:
//      string类型, 返回加密的结果。如果输入数据异常，则返回空字符串并退出
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

// 该函数实现RC4解密算法功能
//  参数:
//      data - 输入的密文字符串
//      secret_key - 密钥
//  返回值:
//      string类型, 返回解密的结果。如果输入数据异常，则返回空字符串并退出
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

// 请使用该函数将string类型转换为DES_cblock类型。（请勿更改此函数）
// - 该函数仅用于转换明文和密文内容，请不要把用此函数转换secret_key。
// - secret_key请使用`DES_string_to_key()`函数转换。
void convert_string_to_des_block(string str, DES_cblock &output);

// 该函数实现DES-ECB加密算法功能
//  参数:
//      plain - 输入的明文字符串
//      secret_key - 密钥
//  返回值:
//      string类型, 返回加密的结果
//  其他说明:
//      - 请使用`convert_string_to_des_block()`函数将string类型转换为DES_cblock类型。
//        若自行转换，可能导致测试无法通过
//      - secret_key使用前请用`DES_string_to_key()`设置key；
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

// 该函数实现DES-ECB解密算法功能
//  参数:
//      cipher - 输入的密文字符串
//      secret_key - 密钥
//  返回值:
//      string类型, 返回解密的结果
//  其他说明:
//      - 请使用`convert_string_to_des_block()`函数将string类型转换为DES_cblock类型。
//        若自行转换，可能导致测试无法通过
//      - secret_key使用前请用`DES_string_to_key()`设置key
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

// 该函数实现SHA1 hash算法功能
//  参数:
//      msg - 输入的字符串
//  返回值:
//      string类型, 返回sha1消息摘要结果
string sha1_digest(string msg) {
	char res[33]={'\0'};
	SHA1((const unsigned char *)msg.c_str(), msg.length(), (unsigned char*)res);
    return res;
}
// ================ SHA1   End ===============================

// ================ Helper Start =============================
// Helper 说明：
//     1. 你的测试已经全部完成了，不用再往下看了。
//     2. 请勿修改以下内容。其他功能函数。尝试修改可能导致单元测试无法通过

void convert_string_to_des_block(string str, DES_cblock &output) {
    for(int i = 0; i < 8; ++i) {
        output[i] = str[i];
    }
}
// ================ Helper End ================================
