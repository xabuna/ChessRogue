//#ifndef _FMOD_H_
//#define _FMOD_H_
//
//#include "FMODENGIN/inc/fmod.hpp"
//#pragma comment(lib,"FMODENGIN/lib/fmodex64_vc.lib")
//// FOMD 비즈니스 로직
//using namespace FMOD;
//
//#include <string>
////STL Container
//#include <map>
//
////FMOD Business Logic Class
//class FmodSound {
//	System* m_pSystem;
//	int				m_Index;
//	Channel* m_pBGChannel;
//	float			m_volume;
//public:
//	std::map<std::string, int>		m_CheckList;
//	std::map<int, Sound*>			m_SoundList;
//
//	int FmodBGM;
//	int FmodSFX;
//
//	FmodSound();
//	~FmodSound();
//
//	void Init();
//
//	int AddSoundFile(std::string _FullPath, bool _IsLoop);
//	void EffectPlay(int _SoundNum);
//	void BGPlay(int _SoundNum);
//	void BGStop();
//	void VolumeDown();
//	void VolumeUp();
//};
//
//int     AddSoundFile(std::string _FullPath, bool IsLoop = false);
//void    EffectPlay(int _SoundNum);
//void    BGPlay(int _SoundNum);
//void    VolumeUp();
//void    VolumeDown();
//void    BGStop();
//
//extern FmodSound fmodsound;
//#endif