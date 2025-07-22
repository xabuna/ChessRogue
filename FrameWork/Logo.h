#ifndef __Logo_H__
#define __Logo_H__

extern Sprite background_img;

class Logo : public Chap
{
public:
	Logo();
	~Logo();

	int alpha_teamlogo = 0;

	bool fadein_teamlogo = true;
	bool fadeout_teamlogo = false;

	HWND m_hWnd;
	//CSound* Sound1;

	Sprite logo_team;

	float speed = 2000.0f;
	float holdlogo;

	// 데이타 베이스 테스트
	int count = 0;
	char cnt[256];
	char pw[256];

	virtual void Init(HWND m_hWnd);
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);

	
};

#endif