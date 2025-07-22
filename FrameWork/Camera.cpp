#include "Include.h"


Camera cam;

//	���� ��ü (����Ÿ ������ �ö� ������ �ʱⰪ �� nullptr �� ����)
//  �� ������ ���α׷� ��������(main ȣ��) ����ȴ�.
Camera * Camera::m_pInstance = nullptr;

Camera* Camera::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// �� �޸𸮿� ��ü �Ҵ� and ����Ÿ ������ ���� ������ �ּ� �Ҵ�
		m_pInstance = new Camera();
	}

	return m_pInstance;
}


Camera::Camera()
{
	camPos.posX = 0;
	camPos.posY = 0;
}

Camera::~Camera()
{
}

void Camera::Update() // ������ ��� Ŭ������ ���������� �迭�� �����Ͽ� ���� ���� ����(����Ʈ?)
{
	// �ϴ� �� ó��...
	//background.posX = camPos.posX;
	//background.posY = camPos.posY;
}

void Camera::SetXCam(double x)
{
	camPos.posX += x;
}

void Camera::SetYCam(double y)
{
	camPos.posY += y;
}

// Singleton ������ �������� extern ���� ���ص� �� (���ο�)
