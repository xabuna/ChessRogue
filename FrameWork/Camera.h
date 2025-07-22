#pragma once

struct CameraPos
{
	double posX;
	double posY;

};

class Camera
{
private:
	//	������ ��ü
	// ���� ����Ÿ ������ �ö�
	static Camera* m_pInstance;
	CameraPos camPos;

public:
	Camera(void);
	~Camera(void);

	//	��ü ���
	static Camera*	GetInstance();

	void SetXCam(double);
	void SetYCam(double);

	void Update();
};

extern Camera cam;