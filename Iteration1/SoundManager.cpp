#include "SoundManager.h"
#include <Windows.h>

void SoundManager::playWhiteBallStart() {
	PlaySound(TEXT("smb_powerup.wav"), nullptr, SND_ASYNC);
}

void SoundManager::playScore() {
	PlaySound(TEXT("smb_coin.wav"), nullptr, SND_ASYNC);
}

void SoundManager::playFinish() {
	PlaySound(TEXT("mk64_firstplace.wav"), nullptr, SND_ASYNC);
}
