#pragma once

#include <unordered_map>
#include <string>




using namespace std;


extern bool recalculateMultipliers;


enum FadeThreadState {
	ft_NotRunning,
	ft_Started,
	ft_Updated,
	ft_Stopped
};



struct Multiplier {

private:
	volatile float* value;
	bool userMultiplier;


public:

	Multiplier () {};
	Multiplier (float value) : value (new float (value)), userMultiplier (true) {};
	Multiplier (volatile float* var) : value (var), userMultiplier (false) {};
	~Multiplier ();

	float startValue = 1;
	float targetValue = 1;
	float fadeTime = 0;
	HANDLE hThread = CreateMutex (nullptr, FALSE, nullptr);
	bool isFading = false;
	bool isChanged = false;
	bool isDestroyed = false;
	bool saveGame = false;
	bool saveSession = false;

	volatile float getValue ();

	void setValue (float newValue);

	bool setValueLimit (float newValue, float limit);

	FadeThreadState fadeVolume (float targetValue, float fadeTime);

	void destroy ();

	float operator=(float value);
};


typedef unordered_map<string, Multiplier> MultipliersMap;
typedef pair<MultipliersMap::iterator, bool> MultiplierEmplaced;

extern Multiplier multObMaster;
extern Multiplier multObMasterIni;
extern Multiplier multObMusic;
extern Multiplier multObMusicIni;
extern Multiplier multObEffects;
extern Multiplier multObEffectsIni;
extern Multiplier multObVoice;
extern Multiplier multObVoiceIni;
extern Multiplier multObFoot;
extern Multiplier multObFootIni;
extern MultipliersMap multipliersCustom;