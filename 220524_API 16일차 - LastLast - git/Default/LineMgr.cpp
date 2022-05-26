#include "stdafx.h"
#include "LineMgr.h"
#include "ObjMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{	
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(LINENO _NO)
{
	m_LineNo = _NO;

	if(m_LineNo == LINE_STAGE)
	{
		LINEPOINT	tLinePoint[2]{
			{ -100.f, 520.f },
			{ 800.f, 520.f }
		};
		m_LineList.push_back(new CLine(tLinePoint[0], tLinePoint[1]));
	}
	else if (m_LineNo == LINE_TUTORIAL)
	{
		LINEPOINT	tLinePoint[10]{
			{ -100.f, 520.f },
			{ 5000.f, 520.f },
			{ 1491.f, 370.f },
			{ 1673.f, 370.f },
			{ 1834.f, 220.f },
			{ 1995.f, 220.f },
			{ 2856.f, 220.f },
			{ 3015.f, 220.f },
			{ 3304.f, 370.f },
			{ 3500.f, 370.f }
		};
		m_LineList.push_back(new CLine(tLinePoint[0], tLinePoint[1]));
		m_LineList.push_back(new CLine(tLinePoint[2], tLinePoint[3]));
		m_LineList.push_back(new CLine(tLinePoint[4], tLinePoint[5]));
		m_LineList.push_back(new CLine(tLinePoint[6], tLinePoint[7]));
		m_LineList.push_back(new CLine(tLinePoint[8], tLinePoint[9]));

	}
	else if (m_LineNo == LINE_RUN)
	{
		LINEPOINT	tLinePoint[100]{
			
			// ������ 1 ~ ������ 2 ���۹���
			{ -1000.f, 560.f }, // 0-1
			{ 961.f, 560.f },  // 1-2
			{ 1204.f, 490.f }, // 2-3
			{ 3220.f, 490.f }, // 3~4
			{ 3464.f, 560.f }, // 4~5
			{ 5252.f, 560.f }, // 5~6
			{ 5504.f, 490.f },

			// ������ 2 �ĺ���
			{ 7527.f, 490.f }, // 7~8
			{ 7786.f, 560.f }, // 8~9
			{ 16000.f, 560.f },

			// ������ ��ٸ�
			{ 10260.f, 280.f },  // 10
			{ 10440.f, 280.f },
			{ 10260.f, 80.f },   // 12
			{ 10440.f, 80.f },
			{ 10260.f, -150.f }, // 14
			{ 10440.f, -150.f },

			// ������Ʈ 1����
			{ 3750.f, 390.f }, // 16 ���� 1
			{ 3845.f, 390.f },

			{ 4350.f, 390.f }, // 18 ���� 2
			{ 4454.f, 390.f },

			{ 4874.f, 450.f }, // 20 �и����� ����
			{ 4986.f, 450.f },

			{ 5030.f, 200.f }, // 22 �и�����
			{ 5130.f, 200.f },

			// ������Ʈ 2����
			{ 8031.f, 390.f }, // 24 ���� 1
			{ 8157.f, 390.f },

			{ 8635.f, 390.f }, // 26 ���� 2
			{ 8750.f, 390.f },

			{ 9170.f, 450.f }, // 28 �и����� ����
			{ 9300.f, 450.f },

			{ 9310.f, 200.f }, // 30 �и�����
			{ 9430.f, 200.f },


			// ������� (32����)
			{ 5670.f, 370.f }, // 32
			{ 5837.f, 370.f },

			{ 5887.f, 520.f }, // 34
			{ 6068.f, 520.f },

			{ 6160.f, 370.f }, // 36
			{ 6334.f, 370.f },

			{ 6420.f, 250.f }, // 38
			{ 6593.f, 250.f },

			{ 6692.f, 520.f }, // 40
			{ 6873.f, 520.f },

			{ 6951.f, 370.f }, // 42
			{ 7132.f, 370.f },

			{ 7240.f, 250.f }, // 44
			{ 7449.f, 250.f },

			// �߷������ ����?
			{ -199.f, 1000.f }, // 46
			{ 17000.f, 1000.f },

			// ������ �ܻ�
			{ 14470.f, 100.f }, // 48
			{ 15783.f, 100.f },

			//�ƹ���
		{ 10100.f, 490.f }, // 50
		{ 10300.f, 490.f }
			

		};

		for (int i = 0; i < 9; ++i)
		{
			if (i == 6)	// ������ 2 �ٴ��� �̼�ġ
				continue;
			m_LineList.push_back(new CLine(tLinePoint[i], tLinePoint[i + 1]));
		}

		for (int i = 10; i < 51;)
		{
			m_LineList.push_back(new CLine(tLinePoint[i], tLinePoint[i + 1]));
			i += 2;
		}


		//Run n Gun �����̴� ���� ����

		LINEPOINT	tLinePointMove[36]{
			// ���ĺ�
			{ 10567.f, m_vecAlphabetfY[0] },
			{ 10819.f, m_vecAlphabetfY[0] },

			{ 10882.f, m_vecAlphabetfY[1] },
			{ 11120.f, m_vecAlphabetfY[1] },

			{ 11180.f, m_vecAlphabetfY[2] },
			{ 11414.f, m_vecAlphabetfY[2] },

			{ 11477.f, m_vecAlphabetfY[3] },
			{ 11722.f, m_vecAlphabetfY[3] },

			{ 11778.f, m_vecAlphabetfY[4] },
			{ 12009.f, m_vecAlphabetfY[4] },

			{ 12080.f, m_vecAlphabetfY[5] },
			{ 12318.f, m_vecAlphabetfY[5] },

			{ 12388.f, m_vecAlphabetfY[6] },
			{ 12619.f, m_vecAlphabetfY[6] },

			{ 12690.f, m_vecAlphabetfY[7] },
			{ 12913.f, m_vecAlphabetfY[7] },

			{ 12983.f, m_vecAlphabetfY[8] },
			{ 13207.f, m_vecAlphabetfY[8] },

			{ 13284.f, m_vecAlphabetfY[9] },
			{ 13508.f, m_vecAlphabetfY[9] },

			{ 13585.f, m_vecAlphabetfY[10] },
			{ 13823.f, m_vecAlphabetfY[10] },

			{ 13880.f, m_vecAlphabetfY[11] },
			{ 14117.f, m_vecAlphabetfY[11] },

			{ 14180.f, m_vecAlphabetfY[12] },
			{ 14425.f, m_vecAlphabetfY[12] },
		};

		for (int i = 0; i < 26;)
		{
			m_MoveLineList.push_back(new CLine(tLinePointMove[i], tLinePointMove[i + 1]));
			i += 2;
		}
	}
}


void CLineMgr::Update()
{
	if (m_LineNo == LINE_RUN)
	{
		for (auto& _Line : m_MoveLineList)
		{
			_Line->Set_InfoMoveY(-260.f, 140.f);
		}
	}
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);

	for (auto& iter : m_MoveLineList)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();

	for_each(m_MoveLineList.begin(), m_MoveLineList.end(), CDeleteObj());
	m_MoveLineList.clear();
}

//bool CLineMgr::Collision_Line(float& _fX, float& _fY, float* pY)
//{
//	// ������ ������
//
//	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
//	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1
//
//	if (m_LineList.empty())
//		return false;
//
//	CLine*		pTarget = nullptr;
//
//	for (auto& iter : m_LineList)
//	{
//		if (_fX >= iter->Get_Info().tLPoint.fX &&
//			_fX <= iter->Get_Info().tRPoint.fX)
//		{
//			if (pTarget)	//���� Ÿ�� ������ �켱���� ������
//			{
//				float fpTargetDistance = abs(pTarget->Get_Info().tRPoint.fY - _fY); //�����Ÿ�
//				float fiterDistance = abs(iter->Get_Info().tRPoint.fY - _fY);       // ���� iter �Ÿ�
//
//				if (fpTargetDistance > fiterDistance)
//				{
//					pTarget = iter;
//				}
//			}
//			else // ������
//				pTarget = iter;
//		}
//	}
//
//	if (!pTarget)
//		return false;
//
//	float	x1 = pTarget->Get_Info().tLPoint.fX;
//	float	x2 = pTarget->Get_Info().tRPoint.fX;
//
//	float	y1 = pTarget->Get_Info().tLPoint.fY;
//	float	y2 = pTarget->Get_Info().tRPoint.fY;
//
//	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
//	return true;
//}

bool CLineMgr::Collision_Line(float& _fX, float& _fY, float* pY)
{
	// ������ ������

	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	// �̵� ���� Ž��
	for (auto& iter : m_LineList)
	{
		//float fpTargetDistanceL = abs(iter->Get_Info().tLPoint.fY - (_fY + 50.f));
		//float fpTargetDistanceR = abs(iter->Get_Info().tRPoint.fY - (_fY + 50.f));

		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX /*&&
			(fpTargetDistanceL < 50.f || fpTargetDistanceR < 50.f)*/)
		{
			if (pTarget)	//���� Ÿ�� ������ �켱���� ������
			{
				float fpTargetDistance = abs(pTarget->Get_Info().tRPoint.fY - (_fY + 50.f)); //�����Ÿ�
				float fiterDistance = abs(iter->Get_Info().tRPoint.fY - (_fY + 50.f));       // ���� iter �Ÿ�

				if (fpTargetDistance > fiterDistance)
				{
					pTarget = iter;
				}
			}
			else // ������
				pTarget = iter;
		}
	}

	// �����̴� ���� Ž��
	for (auto& iter : m_MoveLineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			if (pTarget)	//���� Ÿ�� ������ �켱���� ������
			{
				float fpTargetDistance = abs(pTarget->Get_Info().tRPoint.fY - (_fY + 50.f)); //�����Ÿ�
				float fiterDistance = abs(iter->Get_Info().tRPoint.fY - (_fY + 50.f));       // ���� iter �Ÿ�

				if (fpTargetDistance > fiterDistance)
				{
					pTarget = iter;
				}
			}
			else // ������
				pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	return true;
}



bool CLineMgr::Collision_LineDown(float& _fX, float& _fY, float* pY)
{
	// ������ ������

	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			if (pTarget)	//���� Ÿ�� ������ �켱���� ������
			{
				if (pTarget->Get_Info().tRPoint.fY < iter->Get_Info().tRPoint.fY) //Y�� �� ������ ���ο� Ÿ������ ��ü
				{
					pTarget = iter;
				}
			}
			else // ������
				pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	return true;
}

void CLineMgr::Insert_AlphabetfYList(float _fY)
{
	m_vecAlphabetfY.push_back(_fY);
}
