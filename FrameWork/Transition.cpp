#include "Include.h"

Transition transition;

Transition::Transition()
{
    warpX = 0;
    warpY = 530 / 2;
}
Transition::~Transition() {}

void Transition::Init()
{
    char FileName[256];
    for (int i = 0; i < 6; i++)
    {
        sprintf_s(FileName, "./resource/Img/chess/battleUIsprite/vs_%02d.png", i + 1);
        WarpTransition[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
    }
    sprintf_s(FileName, "./resource/Img/chess/battleUIsprite/background_vs.png");
    BackTransition.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

void Transition::Draw(PieceType pieceAI)
{
    if (m_framecnt <= 0.0f)
        return;

    float scrollX = m_framecnt * 168.0f;
    WarpTransition[pieceAI - 1].RenderDraw(warpX, warpY, scrollX, 0, scrollX + 1680, 530, 0, 1, 1);
    BackTransition.Render(0, 0, 0, 1, 1);
}

void Transition::Update(double frame)
{
    if (!active)
    {
        //OutputDebugStringA("[Transition] Update(): active == false (종료됨)\n");
        return;
    }

    char buf[128];
    sprintf_s(buf, "[Transition] Update(): active=1, m_framecnt=%.2f, scrollRight=%d\n", m_framecnt, scrollRight);
    //OutputDebugStringA(buf);

    if (GetTickCount64() - m_WarpTime > 10)
    {
        m_WarpTime = GetTickCount64();

        if (scrollRight)
        {
            m_framecnt += 0.2f;
            if (m_framecnt >= 25.0f)
            {
                m_framecnt = 30.0f;
                scrollRight = OFF;
                //OutputDebugStringA("Transition.Update: scrollRight OFF 전환됨\n");
            }
        }
        else // scrollRight == OFF 상태 → 감소하다가 0 도달 시 Stop
        {
            m_framecnt -= 0.5f;
            if (m_framecnt <= 0.0f)
            {
                m_framecnt = 0.0f;
                scrollRight = ON;
                Stop(); // 여기서 트랜지션 종료
                //OutputDebugStringA("Transition.Update: 트랜지션 완전히 종료, Stop() 호출됨\n");
            }
        }
    }
}

void Transition::Start()
{
    active = ON;
    scrollRight = ON;
    m_framecnt = 0.0f;
    m_WarpTime = GetTickCount64();

    //OutputDebugStringA("[Transition] Start() 호출됨: active=1, m_framecnt=0.0\n");


}

void Transition::Stop()
{
    active = OFF;
}