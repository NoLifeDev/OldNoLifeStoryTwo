////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

AES AESGen;

void Crypto::Init() {
	AESGen.SetParameters(256);
	AESGen.Encrypt(0, 0, 0, AES::ECB);
}
