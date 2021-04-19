#pragma once
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string>

using namespace std;
namespace Midas
{
	//AES加密，ECB模式
	int aes_ecb_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *ciphertext);
	//AES解密，ECB模式
	int aes_ecb_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char  *key, unsigned char *plaintext);

	//Midas AES加密: ECB + No Padding
	std::string AESEncrypt(const std::string& input, const std::string& key);
	//Midas AES解密: ECB + No Padding
	string AESDecrypt(const std::string& input, const std::string& key);
}

