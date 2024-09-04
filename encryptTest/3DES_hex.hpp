#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define BLOCK_SIZE      64
#define HALF_BLOCK      32
#define EP_SIZE         48
#define LOOPCOUNT       16
#define QUARTET          4
#define SEXTET           6
#define OCTET            8
#define LEFT             0
#define RIGHT            1
#define PC1_SIZE        56
#define PC2_SIZE        48
#define HALF_PC1        28
#define ENCIPHER         1
#define DECIPHER         0
#define DEFAULT          1
#define INVERT           0

void ENDECRYPT(char *p1 , char *p2, char *p3, char *p4);

typedef unsigned char byte;

byte shift_left [LOOPCOUNT]= {
   1, 1, 2, 2, 2, 2, 2, 2,
   1, 2, 2, 2, 2, 2, 2, 1    };

byte shift_right [LOOPCOUNT]= {
   0, 1, 2, 2, 2, 2, 2, 2,
   1, 2, 2, 2, 2, 2, 2, 1     };

byte ip_table    [BLOCK_SIZE]= {
   58, 50, 42, 34, 26, 18, 10,  2,
   60, 52, 44, 36, 28, 20, 12,  4,
   62, 54, 46, 38, 30, 22, 14,  6,
   64, 56, 48, 40, 32, 24, 16,  8,
   57, 49, 41, 33, 25, 17,  9,  1,
   59, 51, 43, 35, 27, 19, 11,  3,
   61, 53, 45, 37, 29, 21, 13,  5,
   63, 55, 47, 39, 31, 23, 15,  7 };

byte ep_table    [EP_SIZE   ]= {
   32,  1,  2,  3,  4,  5,
	  4,  5,  6,  7,  8,  9,
		8,  9, 10, 11, 12, 13,
   12, 13, 14, 15, 16, 17,
   16, 17, 18, 19, 20, 21,
   20, 21, 22, 23, 24, 25,
   24, 25, 26, 27, 28, 29,
   28, 29, 30, 31, 32,  1 };

byte sbox_table [OCTET][QUARTET]  [16 ]   = {
   14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
		0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
		4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
   15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,

   15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
		3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
		0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
   13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,

   10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
   13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
   13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
		1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,

		7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
   13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
   10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
		3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,

		2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
   14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
		4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
   11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,

   12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
   10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
		9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
		4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,

		4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
   13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
		1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
		6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
   13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
		1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
		7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
		2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11  };

   /*                    -[1 1]-[1 1]-[1 1]-      */
   /*                    -[1 1]-[1 1]-            */
byte p_table [HALF_BLOCK]= {
   16,  7, 20, 21, 29, 12, 28, 17,
		1, 15, 23, 26,  5, 18, 31, 10,
		2,  8, 24, 14, 32, 27,  3,  9,
   19, 13, 30,  6, 22, 11,  4, 25 };

byte pc1_table [PC1_SIZE]   = {
   57, 49, 41, 33, 25, 17,  9,
		1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4 };

  /*                           -[1 1]-[1 1]-     */
byte pc2_table [PC2_SIZE]  = {
   14, 17, 11, 24,  1,  5,
		3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32 };

// key setting
/*
byte org_key1[8] ={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};        
byte org_key2[8] ={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
*/
byte org_key1[8] ={0xa1, 0x32, 0x2a, 0x3d, 0x7d, 0x13, 0xa8, 0xc7};
byte org_key2[8] ={0xb1, 0xa3, 0xd2, 0x16, 0x3c, 0xb8, 0x2c, 0xa2};

void des_strcpy(byte *dest,byte *src, int len)
{
  int  i;

  for(i=0;i<len;i++) {
  	*(dest+i)=*(src+i);
  }
}


int  des_strlen(byte *str)
{
  int  len = 0;

  while(*(str+len) != '\0') len++;

  return len;
}

void des_self_permute(byte *refer, byte *dest, int mode, int max)
{
  int  i, pos;
  byte src[BLOCK_SIZE];
  
  des_strcpy(src, dest, max);
  
  for(i=0;i<max;i++) {
		pos = *(refer+i);
		
		if(mode == DEFAULT) *(dest+i)=*(src+pos-1);
		else                *(dest+pos-1)=*(src+i);
  }
}


void des_permute(byte *refer, byte *dest, byte *src, int max)
{
  int  i, pos;
  for(i=0;i<max;i++) {
		pos = *(refer+i);
		*(dest+i)=*(src+pos-1);
  }
}

void des_xor(byte *dest, byte *src, int max)
{
  int  i;

  for(i=0;i<max;i++) {
		*(dest+i)^= *(src+i);
	}
}
void des_sbox_substitute(byte *dest, byte *src, int num)
{
  int  i, row, result, column = 0;
  
  row = (*(src+0) << 1) | *(src+5);
  
  for(i=1;i<5;i++) {
		column <<= 1;
		column |= *(src+i);
  }
  result = sbox_table[num][row][column];
  
  for(i=0;i<QUARTET;i++) {
		*(dest+i) = (result & 0x08) >> 3;
		result <<= 1;
  }
}

void des_key_shift_left(byte *left_key, byte *right_key, int num)
{
  int  i, j, count, msb;
  byte temp_left, temp_right;

  msb = HALF_PC1 - 1;
  count = shift_left[num];

  for(i=0;i<count;i++) {
		temp_left  = *(left_key+0);
		temp_right = *(right_key+0);
		
		for(j=0;j<msb;j++) {
	  	*(left_key+j)= *(left_key+j+1);
	  	*(right_key+j)= *(right_key+j+1);
		}
	
		*(left_key+msb) = temp_left;
		*(right_key+msb)= temp_right;
  }
}

void des_key_shift_right(byte *left_key, byte *right_key, int num)
{
  int  i, j, count, lsb;
  byte temp_left, temp_right;

  lsb = HALF_PC1 - 1;
  count = *(shift_right+num);


	for(i=0;i<count;i++) {
		temp_left= *(left_key+lsb);
		temp_right= *(right_key+lsb);
	
		for(j=lsb;j>0;j--) {
		  *(left_key+j) = *(left_key+j-1);
		  *(right_key+j) = *(right_key+j-1);
		}
		
			*(left_key+0)  = temp_left;
			*(right_key+0) = temp_right;
	  }
}



void des_hex2bin(byte *dest, byte *src, int size)
{
  int  i, j, count = 0;
  byte hexa[BLOCK_SIZE];

  if(size < 1 || size > 8)
  {
		return;
  }

  des_strcpy(hexa, src, 8*size);

  for(i=0;i<size;i++) {
  	
		for(j=0;j<8;j++) {
	 		*(dest+count++) = (*(hexa+i) & 0x80) >> 7;
	  	*(hexa+i) <<= 1;
		}
	}
}

void des_bin2hex(byte *dest, byte *src, int size)
{
  int  i, j, count = 0;

  if(size < 1 || size > 8)
  {
		return;
  }

  for(i=0;i<size;i++) {
  	
		for(j=0;j<8;j++) {
	  	*(dest+i)= (*(dest+i) << 1) | *(src+(count++));
		}
	}
}

void comm_des8_key1(byte plain[], int mode)
{
  int  i, j, k;
  union {
	byte full[BLOCK_SIZE];
	byte half[2][HALF_BLOCK];
  } info;
  union {
	byte full[HALF_BLOCK];
	byte sbox[OCTET][QUARTET];
  } temp;
  union {
	byte full[PC1_SIZE];
	byte half[2][HALF_PC1];
  } key;
  union {
	byte right[EP_SIZE];
	byte sbox[OCTET][SEXTET];
  } exp;
  byte chosen_key[EP_SIZE];

  des_hex2bin(info.full, org_key1, 8);
  des_permute(pc1_table, key.full, info.full, PC1_SIZE);
  des_hex2bin(info.full, plain, 8);
  des_self_permute(ip_table, info.full, DEFAULT, BLOCK_SIZE);

	for(i=0;i<LOOPCOUNT;i++) {
		des_permute(ep_table, exp.right, *(info.half+RIGHT),EP_SIZE);
	
		if(mode == ENCIPHER ) des_key_shift_left(key.half[0], key.half[1], i);
		else des_key_shift_right(key.half[0], key.half[1], i);
	
		des_permute(pc2_table, chosen_key, key.full, PC2_SIZE);
		des_xor(exp.right, chosen_key, EP_SIZE);
		
		for(j=0;j<OCTET;j++) {
	  	des_sbox_substitute(temp.sbox[j], exp.sbox[j], j);
		}
	
		des_self_permute(p_table, temp.full, DEFAULT, HALF_BLOCK);
		des_xor(temp.full, info.half[LEFT], HALF_BLOCK);
		des_strcpy(info.half[LEFT], info.half[RIGHT], HALF_BLOCK);
		des_strcpy(info.half[RIGHT], temp.full, HALF_BLOCK);
  }
  
  des_strcpy(temp.full, info.half[LEFT], HALF_BLOCK);
  des_strcpy(info.half[LEFT], info.half[RIGHT], HALF_BLOCK);
  des_strcpy(info.half[RIGHT], temp.full, HALF_BLOCK);
  des_self_permute(ip_table, info.full, INVERT, BLOCK_SIZE);
  des_bin2hex(plain, info.full, 8);
}

void comm_des8_key2(byte plain[], int mode)
{
  int  i, j, k;
  union {
	byte full[BLOCK_SIZE];
	byte half[2][HALF_BLOCK];
  } info;
  union {
	byte full[HALF_BLOCK];
	byte sbox[OCTET][QUARTET];
  } temp;
  union {
	byte full[PC1_SIZE];
	byte half[2][HALF_PC1];
  } key;
  union {
	byte right[EP_SIZE];
	byte sbox[OCTET][SEXTET];
  } exp;
  byte chosen_key[EP_SIZE];

  des_hex2bin(info.full, org_key2, 8);
  des_permute(pc1_table, key.full, info.full, PC1_SIZE);
  des_hex2bin(info.full, plain, 8);
  des_self_permute(ip_table, info.full, DEFAULT, BLOCK_SIZE);

	for(i=0;i<LOOPCOUNT;i++) {
		des_permute(ep_table, exp.right, *(info.half+RIGHT),EP_SIZE);
	
		if(mode == ENCIPHER ) des_key_shift_left(key.half[0], key.half[1], i);
		else des_key_shift_right(key.half[0], key.half[1], i);
	
		des_permute(pc2_table, chosen_key, key.full, PC2_SIZE);
		des_xor(exp.right, chosen_key, EP_SIZE);
		
		for(j=0;j<OCTET;j++) {
	  	des_sbox_substitute(temp.sbox[j], exp.sbox[j], j);
		}
	
		des_self_permute(p_table, temp.full, DEFAULT, HALF_BLOCK);
		des_xor(temp.full, info.half[LEFT], HALF_BLOCK);
		des_strcpy(info.half[LEFT], info.half[RIGHT], HALF_BLOCK);
		des_strcpy(info.half[RIGHT], temp.full, HALF_BLOCK);
  }
  
  des_strcpy(temp.full, info.half[LEFT], HALF_BLOCK);
  des_strcpy(info.half[LEFT], info.half[RIGHT], HALF_BLOCK);
  des_strcpy(info.half[RIGHT], temp.full, HALF_BLOCK);
  des_self_permute(ip_table, info.full, INVERT, BLOCK_SIZE);
  des_bin2hex(plain, info.full, 8);
}
  
void des_lfsr(byte init_key[])
{
  int  i, j;
  byte bin_f, coef[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  byte bin_s[BLOCK_SIZE], bin_coef[BLOCK_SIZE];
  des_strcpy(bin_s, init_key, BLOCK_SIZE);
  
  for(i=0; i<BLOCK_SIZE; i++)
  {
		*(init_key+i)=*(bin_s+0);
		bin_f=*(bin_coef+0) * *(bin_s+0);
	
		for(j=1; j<BLOCK_SIZE; j++)
		{
	  	bin_f=*(bin_coef+j) * *(bin_s+j);
	 		*(bin_s+j-1)= *(bin_s+j);
		}
		
		*(bin_s+BLOCK_SIZE-1)=   bin_f ;
  }
}

void mod_des_key1(byte *plain, int len)
{
  int  i;
  byte hex_key[8];
  byte bin_plain[BLOCK_SIZE], bin_key[BLOCK_SIZE];

  des_hex2bin(bin_key, org_key1, 8);
  des_lfsr(bin_key);
  des_bin2hex(hex_key, bin_key, 8);
  comm_des8_key1(hex_key, ENCIPHER);
  des_hex2bin(bin_key, hex_key, 8);

  des_hex2bin(bin_plain, plain, len);

  for(i=0; i < 8*len; i++) {
  	*(bin_plain+i)^= *(bin_key+i);
	}
	
  des_bin2hex(plain, bin_plain, len);
}

void mod_des_key2(byte *plain, int len)
{
  int  i;
  byte hex_key[8];
  byte bin_plain[BLOCK_SIZE], bin_key[BLOCK_SIZE];

  des_hex2bin(bin_key, org_key2, 8);
  des_lfsr(bin_key);
  des_bin2hex(hex_key, bin_key, 8);
  comm_des8_key2(hex_key, ENCIPHER);
  des_hex2bin(bin_key, hex_key, 8);

  des_hex2bin(bin_plain, plain, len);

  for(i=0; i < 8*len; i++) {
  	*(bin_plain+i)^= *(bin_key+i);
	}
	
  des_bin2hex(plain, bin_plain, len);
}

void des_key1(char *src, int mode, int len)
{
  int  loopcnt, mo, i;
  byte temp_plain[8];

  loopcnt = len / 8;
  mo = len % 8;
  
  for(i=0; i<loopcnt; i++)
  {
		des_strcpy(temp_plain, (byte*)&src[i*8], 8);
		comm_des8_key1(temp_plain, mode);
		des_strcpy((byte*)&src[i*8], temp_plain, 8);
  }
  
  if(mo != 0)
  {
		des_strcpy(temp_plain, (byte*)&src[loopcnt*8], mo);
		mod_des_key1(temp_plain, mo);
		des_strcpy((byte*)&src[loopcnt*8], temp_plain, mo);
  }
}

void des_key2(char *src, int mode, int len)
{
  int  loopcnt, mo, i;
  byte temp_plain[8];

  loopcnt = len / 8;
  mo = len % 8;
  
  for(i=0; i<loopcnt; i++)
  {
		des_strcpy(temp_plain, (byte*)&src[i*8], 8);
		comm_des8_key2(temp_plain, mode);
		des_strcpy((byte*)&src[i*8], temp_plain, 8);
  }
  
  if(mo != 0)
  {
		des_strcpy(temp_plain, (byte*)&src[loopcnt*8], mo);
		mod_des_key2(temp_plain, mo);
		des_strcpy((byte*)&src[loopcnt*8], temp_plain, mo);
  }
}

void BytesToHexString( char *bytes, int inlen, char *hexstr )
{       
		int i;
		unsigned char c1, c2;

		for (i=0; i<inlen; i++) {
			c1 = (bytes[i] >> 4) & 0x0F;
			hexstr[2*i] = (c1 < 0x0A) ? (c1 + '0') : (c1 - 0x0A + 'A');
			c2 = bytes[i] & 0x0F;
			hexstr[2*i+1] = (c2 < 0x0A) ? (c2 + '0') : (c2 - 0x0A + 'A');
		}
}

void AsciiToEbcdic(unsigned char *bytes, int inlen, unsigned char *hexstr )
{       
		int i;

		for (i=0; i<inlen; i++) {
			hexstr[i] = bytes[i] + 0xF0;
		/*	hexstr[2*i+1] = bytes[i]; */
		}
}



int HexStringToBytes( char *hexstr, int inlen,  char *bytes )
{
		int i;
		char a,b;

		if (inlen % 2) return -1;

		for (i=0; i<(inlen/2); i++) {
			a = toupper(hexstr[2*i]);
			b = toupper(hexstr[2*i+1]);

			bytes[i] = (((a >= 'A') ? (a - 'A' + 0x0A) : (a - '0')) << 4) +
				((b >= 'A') ? (b - 'A' + 0x0A) : (b - '0'));
		}

		return 0;
}


void PrintData(void * buf, int size)
{
	int i;

 	for(i=0; i<size; ++i){
  	
  	if((i%16)==0){
   		printf("%08X ", i);
  	}

  	printf("%02X ", ((unsigned char * )buf)[i]);
  
  	if(((i+1)%16)==0){
   		printf("\n");
  	}
 	}

 	if((i%16)){
  	printf("\n");
  }
}

/* input1 - plain, input2 - length, input3 - mode, input4 - result */
void ENDECRYPT(char *p1 , char *p2, char *p3, char *p4)
{
  int i;
  int len;
  char str[2048];
  char buf[2048];
 	char buf2[2048];
  char hinput[4096];

  /* plain source */
  len = atoi( p2) ;

  if (!strcmp(p3, "F" ) || !strcmp(p3, "f" ) )
  {
  	/* org_key1 로 암호화 */
		memcpy(str, p1 , len);
	 	des_key1(str , ENCIPHER, len );
		
		/* org_key2 로 복호화 */
		memcpy(buf, str , len );
		*(buf+len) = '\0';
		des_key2( buf , DECIPHER, len );
		memcpy(str, buf , len );
	
		/* org_key1 로 암호화 */
	 	des_key1(str , ENCIPHER, len );

		/* Test Print */
		printf("Print Encrypted Result Hex \n");
		PrintData(str, len);  
		printf("\n"); 

		BytesToHexString ( str, len, buf );
		*(buf+len*2) = '\0';  

		memcpy(p4, buf, len*2);    
		
  } else if (!strcmp(p3, "B" ) || !strcmp(p3, "b" ) ) {

		/* org_key1 으로 복호화 */
		memcpy(hinput, p1 , len);
		HexStringToBytes (hinput, len, buf );
		
		memcpy(str, buf , len/2);
		*(str+len/2) = '\0';
		des_key1(str , DECIPHER, len/2);
		
		/* org_key2 으로 암호화 */
		des_key2(str , ENCIPHER, len/2 );
		
		/* org_key1 으로 복호화 */
		memcpy(buf, str , len/2);
		*(buf+len/2) = '\0';
		des_key1(buf , DECIPHER, len / 2 );
		
		memcpy(p4, buf , len / 2);
	
	} else {		
		strcpy(p4,"Error");
	}

}

 /* < Test Part >   *
  * 아래 main 함수는 자체 모듈 테스트를 위한 부분입니다.
	Production 적용시는 아래 main 함수를 삭제하고 ENDECRYPT 함수를
	직접 호출하면 됩니다.
	위 source의  Test Print  영역도 삭제하시면 됩니다.

 */

/*
int main(int argc, char *argv[])
{
	
	char szresult[4096]="";
	char szresult2[2048]="";
	char szPlain[30+1]="";
	
	memset(szPlain, 0x20, sizeof(szPlain)-1);
	memcpy(szPlain,"99가9999", 8);
	szPlain[29]='E';
	printf("30Byte. Plaine Data: %s\n\n\n",szPlain);
    ENDECRYPT(szPlain,
            "30",
            "F",		// 암호화 
            szresult );

    printf("60byte. 암호문길이 %d\n",strlen(szresult));
    printf("60byte. 암호문: %s\n\n\n",szresult);
  
    memset (szresult, 0x00, sizeof (szresult));
    strcpy (szresult, "68F3A833F93FC64D5C06D8254798889C755CDE2B073F021265390B6FC0D1");
    strcpy (szresult, "0D765C3879A2F15598BB9595DEACBC9D566F7F83AA11AB5B65390B6FC0D1");
    
    ENDECRYPT(szresult,
            "60",
            "B",	// 복호화
            szresult2 );

    printf("30byte. 복호문길이 %d\n",strlen(szresult2));
    printf("30byte. 복호문: %s\n\n",szresult2);

 	return(0);

}
*/

