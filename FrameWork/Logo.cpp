#define _CRT_NONSTDC_NO_DEPRECATE

#include "Include.h"

Sprite background_img;

Logo::Logo()
{
	// ����Ÿ ���̽� ����
	sql.mysql_Success = false;
	// ����Ÿ ���̽� �׽�Ʈ ����
	count = 0;
	//g_Mng.n_Chap = GAME;//�ΰ� ���̷��� �ּ�ȭ
}

Logo::~Logo()
{
}

void Logo::Init(HWND m_hWnd)
{
	this->m_hWnd = m_hWnd;

	background_img.Create("./resource/Img/chess/map/background_menu.png", false, D3DCOLOR_XRGB(0, 0, 0));
	logo_team.Create("./resource/Img/chess/UImenu/game_teamlogo.png", false, D3DCOLOR_XRGB(0, 0, 0));

#pragma region MySQL
	//g_SoundManager.Create(&Sound1, (LPWSTR)L"sound/hatnim.wav", 0, GUID_NULL);

	//// ����Ÿ ���̽�//////////////////////////////////////////////////////////////////////////////////////////////////////

	// 1 �ܰ� �׽�Ʈ ���� Ȯ��////////////////////////////////////////////////////////////////////

	//// MYSQL ����ü ���� ���� (��ü���� ����Ÿ ���̽��� ��Ʈ�� ���ش�)
	////MYSQL mysql;
	//// mysql ����ü ���� �ʱ�ȭ
	//mysql_init(&sql.mysql);
	//// mysql ����Ÿ ���̽��� ���� (���⼱ �׳� ���Ӹ� Ȯ��)
	//if(!mysql_real_connect(&sql.mysql, NULL/*host�ּ�(ip)*/, "root", "Ws03230323*", NULL/*DB�̸�*/, 3306, NULL, 0) )
	//	sql.mysql_Success = false;
	//else sql.mysql_Success = true;
	//// mysql  ���� ����
	//mysql_close(&sql.mysql);
	//////////////////////////////////////////////////////////////////////////////////////////////

	// 2 �ܰ� ���� Ȯ��

	/*
	MYSQL *mysql_real_connect(

		MYSQL *mysql,				// MYSQL ������ ��巹�� 

		const char *host,			// ȣ��Ʈ �̸� �Ǵ� IP ��巹�� (default = localhost) 

		const char *user,			// MySQL Login ID (default = ���� �α��� �̸�) 

		const char *passwd,			// �н����� (default = none) 

		const char *db,				// �����ͺ��̽� �̸� (default = none) 

		unsigned int port,			// TCP/IP ���� ��Ʈ (use default) 

		const char *unix_socket,    // ���� (use default) 

		unsigned long client_flag)  // flag (none) 

		*/

	// mysql ����ü ���� �ʱ�ȭ
	mysql_init( &sql.conn );

	// ip, ���� id , pass, ����Ÿ ���̽���, ��Ʈ��ȣ ������ ����
	sql.connection = mysql_real_connect(&sql.conn, DB_HOST,
		DB_USER, DB_PASS,
		DB_NAME, 3306,
		(char *)NULL, 0);

	// ���� ���ӿ� �����ϸ� ���� ����
	if (sql.connection == NULL)
	{
		sprintf_s(sql.state, "Mysql connection error : %s", mysql_error(&sql.conn));
		sql.mysql_Success = false;
	}
	else // �ƴϸ�...
	{
		sql.mysql_Success = true;
	}

	// ���� mysql_query() �Լ��� MYSQL ����ü�� ���� ������ ����
	sql.query_start = mysql_query(sql.connection, "select * from login");
	if (sql.query_start != 0) // ���� ���н�
	{
		sprintf_s(sql.state, "Mysql query error : %s", mysql_error(&sql.conn));
	}
	else // ������
	{
		sql.mysql_Success = true;
	}

	// mysql_store_result �Լ��� �Ѿ�� ����Ÿ ���̽� �� ����
	sql.sql_result = mysql_store_result(sql.connection);

	// ID, ��й�ȣ �������� 
	// select * from login where ?? ��� ��������... �� ���ڵ� �� ��ŭ �Ѿ��(�� ��ŭ ������ ����)
	while ( ( sql.sql_row = mysql_fetch_row( sql.sql_result ) ) != NULL)
	{
		// ���� ����� ������ ���ڵ� ���� ����������... where id = ? ? ������ Ư�� ����� ���� ����������...
		// ��ü ����Ÿ�� �ʿ��� ���� �迭�� ������ ó������....
		// sql.sql_row[0] �ε����� �ش� Į��(��,�ʵ�)�� ������
		sprintf_s(sql.result, "%s %s\n", sql.sql_row[0], sql.sql_row[1]);

		// �̷������� ���ڿ��� ������ ��ȯ
		int a = atoi(sql.sql_row[1]);
		// �������� ���ڿ��� ��ȯ �Լ� ����� #define _CRT_NONSTDC_NO_DEPRECATE ���ϸ� ���� �߻�
		itoa(a, pw, 10);	// 10 ������ ������

		// ���ڵ� ����ŭ ����... 
		count += 1;
	}

	// �������� ���ڿ��� ��ȯ �Լ� ����� #define _CRT_NONSTDC_NO_DEPRECATE ���ϸ� ���� �߻�
	itoa(count, cnt, 10);	// 10 ������ ������

	// sql.sql_result �� ����
	mysql_free_result(sql.sql_result);

	///////////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion
}

// Chap, ������ �Լ� ȣ��
void Logo::Update(double frame)
{
	float alpha = speed * frame / 1000;

	if (fadein_teamlogo)
	{
		alpha_teamlogo += (int)alpha;
		if (alpha_teamlogo >= 255)
		{
			alpha_teamlogo = 255;
			fadein_teamlogo = false;
			fadeout_teamlogo = true;
			holdlogo = 0;
		}
	}
	else if (fadeout_teamlogo)
	{
		holdlogo += frame;
		if (holdlogo >= 300)
		{
			alpha_teamlogo -= (int)alpha;
			if(alpha_teamlogo<=0)
			{
				alpha_teamlogo = 0;
				fadeout_teamlogo = false;
				g_Mng.n_Chap = MENU;
			}
		}
	}
}

void Logo::Draw()
{
	background_img.SetColor(255, 255, 255, 255);  // ���� ����
	background_img.Draw(0, 0);  //�̹������

	logo_team.SetColor(255, 255, 255, alpha_teamlogo);
	logo_team.Draw(120, 430);
	//dv_font.DrawString( "�ΰ�" , 200 , 210 ) ;   //�������


	// ����Ÿ ���̽� ��� �� ó�� ���� ǥ��/////////////////////////////////////
	/*if (sql.mysql_Success)
	{
		dv_font.DrawString("Success", 500, 0);   
	}
	else
	{
		dv_font.DrawString("Error", 500, 0);   
		dv_font.DrawString(sql.state, 700, 0);
	}*/

	// ���
	dv_font.DrawString(sql.result, 500, 30, 0xff0000ff);

	// �� ���ڵ� ��
	dv_font.DrawString(cnt, 500, 60, 0xff0000ff);

	// ���
	dv_font.DrawString(pw, 500, 100, 0xff0000ff);
	////////////////////////////////////////////////////////////
}

void Logo::OnMessage( MSG* msg )
{
	switch(msg->message)
	{
	case WM_LBUTTONDOWN :
		g_Mng.n_Chap = MENU;
		//MessageBox(NULL, "","",0);
		break;
	}

}