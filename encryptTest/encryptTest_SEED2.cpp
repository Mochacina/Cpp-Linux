#include <bits/stdc++.h>
#include "./KISA_SEED_CBC.h"

// g++ encryptTest_SEED2.cpp KISA_SEED_CBC_test.c -o encryptTest_SEED2
// BYTE = unsigned char

using namespace std;

int	Hex_Dump(unsigned char* buff, int nLen);

int main(int argc, char* argv[])
{
	
	//BYTE pbszUserKey[16] = {0x088, 0x0e3, 0x04f, 0x08f, 0x008, 0x017, 0x079, 0x0f1, 0x0e9, 0x0f3, 0x094, 0x037, 0x00a, 0x0d4, 0x005, 0x089}; 
	//BYTE pbszIV[16] = {0x026, 0x08d, 0x066, 0x0a7, 0x035, 0x0a8, 0x01a, 0x081, 0x06f, 0x0ba, 0x0d9, 0x0fa, 0x036, 0x016, 0x025, 0x001};
	//BYTE plainText[71] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
	//	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
	//	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
	//	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
	//	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};

    if(argc != 2) {
        cout << "input two arguments." << endl;
        return false;
    }
	
    char* input = argv[1];
    size_t len = strlen(argv[1]);

    cout << "input: " << input << " / size: " << len << endl;
	
	BYTE pbszUserKey[16] = {0x0f, 0x43, 0x57, 0xda, 0x59, 0xa4, 0xbc, 0x5e, 0x64, 0xdb, 0xaa, 0xb9, 0x8d, 0xcb, 0x56, 0xba}; 
	BYTE pbszIV[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	//BYTE plainText[] = "1234567898";
    BYTE plainText[len+1] = {0,};

    for (size_t i = 0; i < len; ++i){
        plainText[i] = (BYTE)input[i];
    }
    cout << "plainText: " << plainText << "\r\n" << endl;

	//BYTE plainText[1024] ;
	
	BYTE pbszCipherText[1024] = {0x00};
	BYTE pbszCipherText2[1024] = {0x88,0xB9,0xAA,0xAF,0x8E,0xBA,0x02,0x33,0x34,0xFC,0x6F,0xE5,0x55,0xE5,0x45,0xDA,0x93,0xC2,0xBD,0x5B,0xD6,0x0C,
				0x32,0x9E,0x83,0xAA,0xE1,0xA4,0x77,0x99,0x6A,0x2D,0xD0,0xC9,0x11,0xE9,0x04,0x54,0x6F,0x11,0x23,0xF9,0x21,0x06,0x27,0xF1,0x23,0xB7};
	BYTE pbszPlainText[1024] = {0x00};
	int i;
	int nPlainTextLen;
	int nCipherTextLen;
	int nPaddingCnt; 
	int nSentCnt = 5;
	
	printf ("Key        : ");
	for (i=0;i<16;i++)	{printf("%02X ",pbszUserKey[i]);}

	printf ("\nIV       : ");
	for (i=0;i<16;i++)	{printf("%02X ",pbszIV[i]);}
	
	
	printf("\n\nSOURCE Length : %d", strlen((char*)plainText));

	nPlainTextLen = strlen((const char*)plainText);
	nPaddingCnt = 16 - (nPlainTextLen	 % 16);
	
	printf ("\nPlaintext(%d)  : ", nPlainTextLen);
	for (i=0;i<nPlainTextLen;i++)	{printf("%02X ",plainText[i]);}
	
	printf("\n\nnPlainTextLen: %d, nPaddingCnt: %d, CipherCnt: %d", nPlainTextLen, nPaddingCnt, nPlainTextLen+nPaddingCnt);
	
	printf ("\nEncryption....\n");

	// Encryption Algorithm //
	nCipherTextLen = SEED_CBC_Encrypt( pbszUserKey, pbszIV, plainText, nPlainTextLen, pbszCipherText );

	printf ("\nCiphertext(%d) : ", nCipherTextLen);
	for (i=0;i<nCipherTextLen;i++)	{printf("%02X ",pbszCipherText[i]);}

	std::string CipherText = "";
	char buffer[] = "  ";

	printf ("\nszCipher Test(%d) : \n", nCipherTextLen);
	for (i=0;i<nCipherTextLen;i++)	{
		//printf("%02X ", pbszCipherText[i]);
		sprintf(buffer, "%02X", pbszCipherText[i]);
		cout << "buffer: " << buffer << endl;
		CipherText += buffer;
	}

	cout << CipherText << endl;

	printf ("\nCiphertext Decimal  : ");
	for (i=0;i<nCipherTextLen;i++)	{printf("%d ", pbszCipherText[i]);}

	printf ("\nstring(%d) : ", nCipherTextLen);
	for (i=0;i<nCipherTextLen;i++)	{printf("%c", pbszCipherText[i]);}

	Hex_Dump(pbszCipherText, nCipherTextLen);

	printf ("\n\nDecryption....\n");

	// Decryption Algorithm //
	nPlainTextLen = SEED_CBC_Decrypt( pbszUserKey, pbszIV, pbszCipherText, nCipherTextLen, pbszPlainText );

	printf ("\nPlaintext(%d)  : ", nPlainTextLen);
	for (i=0;i<nPlainTextLen;i++)	{printf("%02X ",pbszPlainText[i]);}
	printf("\npbszPlainText string (%d): %s ", strlen((char*)pbszPlainText), pbszPlainText);

	printf ("\n");

	// printf("\n\n test :% -10s,   \n\n", "1234");
	
	return 0;

}

int	Hex_Dump(unsigned char* buff, int nLen)
{
	int 	i;
	char	szbyteLog[5];
	unsigned char  szlogBuff[2048];
	unsigned char  szsrcBuff[1024];
	
		
	memset(szlogBuff, 0x00, sizeof(szlogBuff));
	memset(szsrcBuff, 0x00, sizeof(szsrcBuff));
	
	memcpy(szsrcBuff, buff, nLen);
	
	// log(7,"nLen: %d, szsrcBuff: %s", nLen, szsrcBuff);
		
	for (i=0; i < nLen; i++)	
	{
		// log(7,"      nLen: %d, buff[%d] : %02X", nLen, i, szsrcBuff[i]);
		memset(szbyteLog, 0x00, sizeof(szbyteLog));
		sprintf(szbyteLog, "%02X", (char*)szsrcBuff[i]);
		// log(7,"      szbyteLog: %s", szbyteLog);
		memcpy(&szlogBuff[strlen((char*)szlogBuff)], szbyteLog, strlen(szbyteLog));
		// log(7,"      szlogBuff : %s", szlogBuff);
	}
	
	printf("\n\nHEX_DUMP(%d) : %s", nLen, szlogBuff);
	
	
	return i;		// pBuff length
}