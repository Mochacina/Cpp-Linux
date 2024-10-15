// KISA_SEED_CBC 암복호화 함수
// Insert Jhlee 2022-12-13
// Retuen Value : 암호화된 길이
int SpwClient::EncryptMsg(unsigned char* pszSrcMsg, unsigned char* pszEncMsg, int nDataLen)
{
	
	BYTE pbszUserKey[16] = {0x00f, 0x043, 0x057, 0x0da, 0x059, 0x0a4, 0x0bc, 0x05e, 0x064, 0x0db, 0x0aa, 0x0b9, 0x08d, 0x0cb, 0x056, 0x0ba}; 
	BYTE pbszIV[16] = {0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000};
	
	BYTE plainText[1024] ;
	BYTE pbszCipherText[1024] = {0x00};
	BYTE pbszPlainText[1024] = {0x00};
	BYTE szLogBuff[2048];
	char szbyteLog[5];
	
	int i;
	int nPlainTextLen = 0;		// 평문 길이 
	int nCipherTextLen = 0;		// 암호화된 길이
	
	memset(plainText, 0x00, sizeof(plainText));
	memset(szLogBuff, 0x00, sizeof(szLogBuff));		// Hex Log Buffer
	
	strcpy((char*)plainText, (char*)pszSrcMsg);
	nPlainTextLen = nDataLen;

	log(7, "  < Fn: EncryptMsg>  plainText(%d): %s", nPlainTextLen, plainText);

	// Encryption......
	nCipherTextLen = SEED_CBC_Encrypt( pbszUserKey, pbszIV, plainText, nPlainTextLen, pbszCipherText );
	
	for (i=0;i<nCipherTextLen;i++)	{
		memset(szbyteLog, 0x00, sizeof(szbyteLog));
		sprintf((char*)szbyteLog, "%02X ",(char*)pbszCipherText[i]);
		memcpy(&szLogBuff[strlen((char*)szLogBuff)], szbyteLog, strlen(szbyteLog));
		}
	log(7, "  < Fn: EncryptMsg> Encryption end, nCiphertext(%d) : %s", nCipherTextLen, szLogBuff);
			
	memcpy(pszEncMsg, pbszCipherText, nCipherTextLen);
	
	return nCipherTextLen;
	
}

int SpwClient::DecryptMsg(unsigned char* pszCipherText, unsigned char* pszPlainText, int nCipherTextLen)
{
	// KISA_SEED_CBC
	BYTE pbszUserKey[16] = {0x00f, 0x043, 0x057, 0x0da, 0x059, 0x0a4, 0x0bc, 0x05e, 0x064, 0x0db, 0x0aa, 0x0b9, 0x08d, 0x0cb, 0x056, 0x0ba}; 
	BYTE pbszIV[16] = {0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000};
	BYTE plainText[2048] ;
	BYTE pbszCipherText[2048] = {0x00};
	BYTE pbszPlainText[2048] = {0x00};
	
	int nPlainTextLen = 0;
		
	log(7, "  < Fn: DecryptMsg> nCipherTextLen(%d)", nCipherTextLen);
	
	nPlainTextLen = SEED_CBC_Decrypt( pbszUserKey, pbszIV, pszCipherText, nCipherTextLen, pszPlainText );
	
	log(7, "  < Fn: DecryptMsg> pszPlainText(%d) : %s", nPlainTextLen, pszPlainText);

	return nPlainTextLen;
}