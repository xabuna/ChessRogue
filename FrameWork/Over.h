#ifndef __Over_H__
#define __Over_H__

class Over : public Chap
{
	HWND m_hWnd;
public:
	Over();
	~Over();

	virtual void Init(HWND m_hWnd);
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);
};

#endif