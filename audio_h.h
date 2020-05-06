#pragma once
#include <irrKlang.h>
using namespace irrklang;

class AudioManager {
	
private:
	ISoundEngine* audioController;

public:
	AudioManager() : audioController(createIrrKlangDevice()) {}
	void PlayTrack(const char* pathToTrack, bool loop) {
		audioController->play2D(pathToTrack, loop);
	}

	void StopAll() {
		audioController->stopAllSounds();
	}
};