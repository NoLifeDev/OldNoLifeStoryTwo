////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

AES AESGen;
uint8_t WZKeys[3][0x10000];

void GenWzKey(const uint8_t* IV, uint8_t* key) {
	uint8_t BigIV[16];
	for (int i = 0; i < 16; i += 4) {
		memcpy(BigIV+i, IV, 4);
	}
	AESGen.SetParameters(256, 128);
	AESGen.StartEncryption(AESKey2);
	AESGen.EncryptBlock(BigIV, key);
	for (int i = 16; i < 0x1000; i += 16) {
		AESGen.EncryptBlock(key+i-16, key+i);
	}
}

void Crypto::Init() {
	GenWzKey(GMSKeyIV, WZKeys[1]);
	GenWzKey(KMSKeyIV, WZKeys[2]);
}