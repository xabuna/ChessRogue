#include "Include.h"


Player player;


Player::Player()
{
	pos.x = 700;
	pos.y = 300;
	gravity = 5.75f;
	grounded = false;

}

Player::~Player()
{
}

void Player::Init()
{

	char FileName[256];
	

	sprintf_s(FileName, "./resource/Img/7.png");
	playerimg.Create(FileName,false,D3DCOLOR_XRGB(0,0,0));
	D3DXGetImageInfoFromFile(FileName, &imagesinfo);

	m_rc.left = pos.x;
	m_rc.top = pos.y;
	m_rc.right = pos.x+imagesinfo.Width+10;
	m_rc.bottom = pos.y+imagesinfo.Height+30;

}

void Player::Update()
{
	if(GetTickCount() - m_PlayerTime > 10)
	{
		if(!grounded) pos.y += gravity;

		if (m_rc.left		< coll.m_rc.right &&
			coll.m_rc.left	< m_rc.right && 
			m_rc.top		< coll.m_rc.bottom && 
			coll.m_rc.top	< m_rc.bottom) grounded = true;

		m_rc.left = pos.x;
		m_rc.top = pos.y;
		m_rc.right = pos.x + imagesinfo.Width + 10;
		m_rc.bottom = pos.y + imagesinfo.Height + 30;

		m_PlayerTime = GetTickCount();
	}
}

void Player::Draw()
{
	if (Gmanager.m_GameStart == true)
	{
		playerimg.Render(pos.x, pos.y, 0, 2, 2);
		if (grounded)
		{
			coll.BoxSow(m_rc, 0, -5, 0xffff0000);
		}
		else
		{
			coll.BoxSow(m_rc, 0, -5);
		}
	}

}

/*

	�⺻ �浹ó��

	= �簢�� �⵿ ���� ó��
	�÷��̾���� �浹 ���� ��ǥ�� (ML, MT) ~ (MR, MB), ź�� �浹 ���� ��ǥ�� (BL, BT) ~ (BR, BB)��� �غ���.
	(ML, MT), (BL, BT)�� ������ �簢���� ���� �� ��ǥ�̰� (MR. MB), (BR, BB)�� �簢���� ������ �Ʒ� ��ǥ�̴�.
	�� ���, �÷��̾�⿡ ź�� �浹 ������ ������ ����.
	* ML < BR && BL < MR && MT < BB && BT < MB

	= ���� �̿��� �浹 ���� ó��
	���� �̿��� �浹 ���� ó���� ������ ����.
	�÷��̾���� �߽���ǥ�� (MX, MY), ź�� �߽���ǥ�� (BX, BY)��� �ϰ�, �÷��̾���� �浹 ���� �ݰ��� MR,
	ź�� �浹 ���� �ݰ��� BR�̶�� ����. �̶� �÷��̾��� ź�� �浹 ������ �Ʒ��� ����.
	* (MX-BX)*(MX-BX) + (MY-BY)*(MY-BY) < (MR+BR)*(MR+BR)

*/