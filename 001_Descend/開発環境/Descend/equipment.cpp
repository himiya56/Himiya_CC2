//=============================================================================
//
// 装備処理 [equipment.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "equipment.h"
#include "option.h"
#include "sight.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
bool CEquipment::m_bEquipment[EQUIPMENT_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEquipment::CEquipment()
{
	ClearEquipment();
}

//=============================================================================
// デストラクタ
//=============================================================================
CEquipment::~CEquipment()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEquipment::Init(void)
{
	ClearEquipment();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEquipment::Uninit()
{
}

//=============================================================================
// 装備有効化処理
//=============================================================================
void CEquipment::SetEquipment(const int equipment)
{
	m_bEquipment[equipment] = true;
}

//=============================================================================
// 装備破棄処理
//=============================================================================
void CEquipment::ClearEquipment(void)
{
	for (int nCount = 0; nCount < EQUIPMENT_MAX; nCount++)
	{
		m_bEquipment[nCount] = false;
	}
}

//=============================================================================
// 装備有効確認処理
//=============================================================================
void CEquipment::CheckEquipment(void)
{
	for (int nCount = 0; nCount < EQUIPMENT_MAX; nCount++)
	{
		if (m_bEquipment[nCount])
		{
			switch (nCount)
			{
			case EQUIPMENT_OPTION:
				COption::Create();
				break;
			case EQUIPMENT_LASERSIGHT:
			//	CSight::Create();
			default:
				break;
			}
		}
	}
}
