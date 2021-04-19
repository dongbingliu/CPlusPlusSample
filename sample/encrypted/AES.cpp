#include "../Head/AES.h"
#include "../Head/MTools.h"

namespace Midas
{

	/*
	* 处理AES错误
	*/
	void handleErrors(void)
	{
		ERR_print_errors_fp(stderr);
		abort();
	}


	/*
	 * AES加密,ECB模式
	 * 返回加密长度
	 */
	int aes_ecb_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *ciphertext)
	{
		EVP_CIPHER_CTX *ctx;

		int len;

		int ciphertext_len;

		/* Create and initialise the context */
		if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
		
		/* Initialise the encryption operation. IMPORTANT - ensure you use a key
		* In this example we are using 256 bit AES (i.e. a 256 bit key).
		*/
		if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL))
			handleErrors();

		//设置padding,no padding
		if (!(EVP_CIPHER_CTX_set_padding(ctx, 0))) handleErrors();

		/* Provide the message to be encrypted, and obtain the encrypted output.
		* EVP_EncryptUpdate can be called multiple times if necessary
		*/
		if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
			handleErrors();
		ciphertext_len = len;

		/* Finalise the encryption. Further ciphertext bytes may be written at
		* this stage.
		*/
		if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))  handleErrors();
		ciphertext_len += len;

		/* Clean up */
		EVP_CIPHER_CTX_free(ctx);

		return ciphertext_len;
	}


	/*
	* AES解密 ECB模式
	*/
	int aes_ecb_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char  *key, unsigned char *plaintext)
	{
		EVP_CIPHER_CTX *ctx;

		int len;

		int plaintext_len;

		/* Create and initialise the context */
		if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

		/* Initialise the decryption operation. IMPORTANT - ensure you use a key
		* In this example we are using 256 bit AES (i.e. a 256 bit key). The
		*/
		if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL))
			handleErrors();

		//设置padding,no padding
		if (!(EVP_CIPHER_CTX_set_padding(ctx, 0))) handleErrors();

		/* Provide the message to be decrypted, and obtain the plaintext output.
		* EVP_DecryptUpdate can be called multiple times if necessary
		*/
		if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
			handleErrors();
		plaintext_len = len;

		/* Finalise the decryption. Further plaintext bytes may be written at
		* this stage.
		*/
		if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
		plaintext_len += len;

		/* Clean up */
		EVP_CIPHER_CTX_free(ctx);

		return plaintext_len;
	}


	/*
	 * Midas AES加密
	 * ECB+No Padding
	 */
	string AESEncrypt(const std::string& input, const std::string& key)
	{
		if (input.empty() || key.empty())
		{
			return input;
		}

		string temp = input;
		while (temp.length() % 16 != 0)
		{
			temp += 'a';	//用字符a填充
		}

		//unsigned char* _data = (unsigned char*)temp.c_str();

		/* Buffer for ciphertext. Ensure the buffer is long enough for the
		 * ciphertext which may be longer than the plaintext, dependant on the
		 * algorithm and mode
		 */
		unsigned char ciphertext[1024] = {0};	//分配1k，默认堆栈1M，避免溢出
		int encrypt_len = aes_ecb_encrypt((unsigned char*)temp.data(), temp.size(), (unsigned char*)key.c_str(), ciphertext);
		//int encrypt_len = aes_ecb_encrypt(_data, strlen((char*)_data), (unsigned char*)key.c_str(), ciphertext);
		//printf("AES Encrypt Length: before = %d,after = %d\n", input.length(), encrypt_len);

		string res = bin2str(ciphertext, encrypt_len);
		return res;
	}


	/*
	* Midas AES解密
	* ECB+No Padding
	*/
	string AESDecrypt(const std::string& input, const std::string& key)
	{
		if (input.empty() || key.empty())
		{
			return input;
		}

		string temp = str2bin(input);

		/* Buffer for ciphertext. Ensure the buffer is long enough for the
		 * ciphertext which may be longer than the plaintext, dependant on the
		 * algorithm and mode
		 */
		unsigned char plainText[1024] = { 0 };	//分配1k，默认堆栈1M，避免溢出

		int encrypt_len = aes_ecb_decrypt((unsigned char*)temp.data(), temp.size(), (unsigned char*)key.c_str(), plainText);
		//int encrypt_len = aes_ecb_decrypt(_data, strlen((char*)_data), (unsigned char*)key.c_str(), plainText);
		//printf("AES Decrypt Length: before = %d,after = %d\n", input.length(), encrypt_len);

		string res((char*)plainText);
		res.resize(encrypt_len);
		return res;
	}
}