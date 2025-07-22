//#include "Include.h"
//
//FmodSound fmodsound;
//
//FmodSound::FmodSound()
//{
//	System_Create(&m_pSystem);
//	//init(채널 최대설정값, 초기화 시점, 추가로 넣을 보조 드라이버);
//	m_pSystem->init(10, FMOD_INIT_NORMAL, 0);
//
//	m_Index = 0;
//	m_volume = 1.0f;
//	m_pBGChannel = nullptr;
//
//	Init();
//}
//FmodSound::~FmodSound()
//{
//	m_CheckList.clear();
//
//	for (auto& Iter : m_SoundList)
//	{
//		Iter.second->release();
//	}
//	m_SoundList.clear();
//
//	m_pSystem->release();
//	m_pSystem->close();
//}
//
//void FmodSound::Init() {
//	FmodBGM = AddSoundFile("./resource/Sound/bgm/XXXX.mp3", true);
//	FmodSFX = AddSoundFile("./resource/Sound/sfx/XXXX.mp3", false);
//}
//
//int FmodSound::AddSoundFile(std::string _FullPath, bool _IsLoop)
//{
//	auto Find = m_CheckList.find(_FullPath);
//
//	if (Find != m_CheckList.end())
//	{
//		return Find->second;
//	}
//
//	Sound* pSound = nullptr;
//	int Mode = FMOD_HARDWARE | (_IsLoop ? FMOD_LOOP_NORMAL | FMOD_DEFAULT : FMOD_LOOP_OFF);
//
//	//사운드를 지정된 경로에서 두 번째 인자인 LOOP/ONCE 로 선택해서 로딩
//	m_pSystem->createSound(_FullPath.c_str(), Mode, 0, &pSound);
//
//	if (pSound == nullptr)
//	{
//		return -1;
//	}
//
//	m_CheckList.insert(std::make_pair(_FullPath, m_Index));
//	m_SoundList.insert(std::make_pair(m_Index, pSound));
//
//	return m_Index++;
//}
//
////Effect Play
//void FmodSound::EffectPlay(int _SoundNum)
//{
//	auto Find = m_SoundList.find(_SoundNum);
//
//	m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &m_pBGChannel);
//}
//
//void FmodSound::BGPlay(int _SoundNum)
//{
//	auto Find = m_SoundList.find(_SoundNum);
//
//	m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &m_pBGChannel);
//}
//
//void FmodSound::BGStop()
//{
//	if (m_pBGChannel != nullptr)
//	{
//		m_pBGChannel->stop();
//	}
//}
//
//void FmodSound::VolumeDown()
//{
//	m_volume -= 0.1f;
//	if (m_volume <= 0) m_volume = 0;
//	m_pBGChannel->setVolume(m_volume);
//}
//
//void FmodSound::VolumeUp()
//{
//	m_volume += 0.1f;
//	if (m_volume >= 0) m_volume = 1.0;
//	m_pBGChannel->setVolume(m_volume);
//}
//
//static FmodSound g_SoundMgr;
//
//int AddSoundFile(std::string _FullPath, bool _IsLoop)
//{
//	return g_SoundMgr.AddSoundFile(_FullPath, _IsLoop);
//}
//
//void EffectPlay(int _SoundNum)
//{
//	g_SoundMgr.EffectPlay(_SoundNum);
//}
//
//void BGPlay(int _SoundNum)
//{
//	g_SoundMgr.BGPlay(_SoundNum);
//}
//
//void VolumeUp()
//{
//	g_SoundMgr.VolumeUp();
//}
//
//void VolumeDown()
//{
//	g_SoundMgr.VolumeDown();
//}
//
//void BGStop()
//{
//	g_SoundMgr.BGStop();
//}