#include "Include.h"

Player2::Player2()
{
	pos.x = 700;
	pos.y = 50;
	gravity = 5.75f;
	grounded = false;

	D3DXGetImageInfoFromFile("./resource/Img/7.png", &imagesinfo);
	m_rc.left = pos.x;
	m_rc.top = pos.y;
	m_rc.right = pos.x + imagesinfo.Width + 10;
	m_rc.bottom = pos.y + imagesinfo.Height + 30;

}

Player2::~Player2()
{
}

void Player2::Init()
{

}

void Player2::Update()
{
	if (GetTickCount() - m_PlayerTime > 10)
	{
		if (!grounded) pos.y += gravity;

		if (m_rc.left < coll.m_rc.right && coll.m_rc.left < m_rc.right && m_rc.top < coll.m_rc.bottom && coll.m_rc.top < m_rc.bottom) grounded = true;

		for (auto Iter = Gmanager.myList.begin(); Iter != Gmanager.myList.end(); Iter++)
		{
			if ((*Iter)!= this && m_rc.left < (*Iter)->m_rc.right && (*Iter)->m_rc.left < m_rc.right && m_rc.top < (*Iter)->m_rc.bottom && (*Iter)->m_rc.top < m_rc.bottom) grounded = true;
		}

		m_rc.left = pos.x;
		m_rc.top = pos.y;
		m_rc.right = pos.x + imagesinfo.Width + 10;
		m_rc.bottom = pos.y + imagesinfo.Height + 30;

		m_PlayerTime = GetTickCount();
	}
}

void Player2::Draw()
{
	if (Gmanager.m_GameStart == true)
	{
		player.playerimg.Render(pos.x, pos.y, 0, 2, 2);
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
	���� �Ҵ����� ������ �������, ������ Ȱ���Ͽ� ������Ʈ�鿡 ���� ���� �и� Ŭ������ �̾Ƴ���(�̹��� ������)
	������� �پ缺�� Ȱ���Ͽ� �����ؾ���.. ���⼱ ���� �Ҵ� �� ����� ���� ��.
*/