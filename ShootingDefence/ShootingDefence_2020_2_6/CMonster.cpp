#include "framework.h"
#include "CMonster.h"
#include "CHero.h"
#include "CItem_Mgr.h"
#include "GlobalValue.h"

CMonster::CMonster()
{
	m_CharicType = CT_Zombi1; //캐릭터 종류가 "몬스터"인지? "나나미"인지?

	m_isActive = false;

	m_MaxHP = 100.0f;
	m_CurHP = 100.0f;

	m_Speed = 150.0f;
	m_HalfColl = 20;
}

CMonster::~CMonster()
{
}

void CMonster::Init_Unit()
{
}

void CMonster::Update_Unit(float a_DeltaTime, CHero& a_Hero)
{
	Vector2D a_CacVec = a_Hero.m_CurPos - m_CurPos;

	if (0.0f < a_Hero.m_SdOnTime) //쉴드 적용중이라면
	{
		if (a_CacVec.Magnitude() < a_Hero.m_SdHalfSize)
		{
			a_DeltaTime = a_DeltaTime * 0.05f;
		}
	}

	//-----------Monster AI
	if (a_Hero.m_HalfColl + m_HalfColl < a_CacVec.Magnitude()) //(충돌반경의합<중점의거리) 아직 부딪히지 않았다.는 뜻
	{
		//추적
		m_DirVec = a_CacVec;  //몬스터의 방향 벡터
		m_DirVec.Normalize();
		m_CurPos = m_CurPos + (m_DirVec * (a_DeltaTime * m_Speed));
	}
	//-----------Monster AI

	//---------- 몬스터 공격 처리 부분
	static float m_AttackTick = 0.0f;
	m_AttackTick = m_AttackTick - a_DeltaTime;
	if (a_CacVec.Magnitude() < (a_Hero.m_HalfColl + m_HalfColl + 10.0f))
	{
		if (m_AttackTick < 0.0f)  //공격 범위 안에 들어오면 즉시 공격
		{
			//몬스터가 주인공 공격 공격 
			a_Hero.TakeDamage(10);

			m_AttackTick = 1.0f;
		}
	}
	//---------- 몬스터 공격 처리 부분

	//------------------- 애니메이션 플레임 계산 부분 
	if (0.0f < a_CacVec.x)
	{
		ChangeState(Right_Walk);  //몬스터 개별적으로 있어야 한다. 
	}
	else
	{
		ChangeState(Left_Walk);
	}
	CUnit::Update_Unit(a_DeltaTime);
	//------------------- 애니메이션 플레임 계산 부분 
}

void CMonster::Render_Unit(HDC a_hDC, HBRUSH& a_R_brsh)
{
	if (m_SocketImg == NULL)
		return;

	//---- HP Bar Render
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hDC, a_R_brsh);
	static float a_CacMXX = 0.0f;
	static float a_CacMYY = (int)(m_HalfHeight * 0.8f);
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CacMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_CurHP / (float)m_MaxHP);

	a_CacMYY = (int)(m_HalfHeight * 0.97f);
	if (m_CharicType == CT_Zombi1)
	{
		a_CacMYY = (int)(m_HalfHeight * 0.83f);
	}
	else if (m_CharicType == CT_Zombi2 || m_CharicType == CT_Zombi4)
	{
		a_CacMYY = (int)(m_HalfHeight * 0.67f);
	}

	Rectangle(a_hDC, m_CurPos.x - a_CacMXX, m_CurPos.y - a_CacMYY,
		m_CurPos.x - a_CacMXX + a_CurHpSize,
		m_CurPos.y - (a_CacMYY + 10.0f));
	SelectObject(a_hDC, h_Old_Brush);//기존 브러쉬로 교체
	//---- HP Bar Render

	Graphics graphics(a_hDC);
	graphics.DrawImage(m_SocketImg, m_CurPos.x - m_HalfWidth,
									m_CurPos.y - (int)(m_HalfHeight * 1.2f),
									(float)m_ImgSizeX, (float)m_ImgSizeY);
}

void CMonster::Destroy_Unit()
{
}

void CMonster::Spawn(float a_XX, float a_YY)
{
	//난이도에 따른 HP 변경
	m_MaxHP = 50.0f + ((g_DiffLevel - 3) * 15.0f);
	if (m_MaxHP < 50.0f)
		m_MaxHP = 50.0f;

	if (200.0f < m_MaxHP)
		m_MaxHP = 200.0f;
	//난이도에 따른 HP 변경

	//난이도에 따른 이속 변경
	m_Speed = 150.0f + ((g_DiffLevel - 1) * 30.0f);
	if (280.0f < m_Speed)
		m_Speed = 280.0f;
	//난이도에 따른 이속 변경

	m_CurPos.x = a_XX;
	m_CurPos.y = a_YY;

	m_isActive = true;

	m_CurHP = m_MaxHP;

	SetAni_Rsc(m_CharicType);
}

void CMonster::TakeDamage(float a_Value)
{
	m_CurHP = m_CurHP - a_Value;

	if (m_CurHP <= 0.0f) //몬스터 사망 처리
	{
		m_CurHP = 0.0f;
		g_Hero.m_KillCount++;

		//--------- Item 스폰
		g_ItemMgr.SpawnItem(m_CurPos);
		//--------- Item 스폰

		m_isActive = false; 	//-------- 사망 몬스터 제거
	}
}
