//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "map.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[TEX_BG_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CBg::CBg()
{
	m_fTexUVY = 1.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(void)
{
	CPolygon3D::Init();
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSize(MAP_HEIGHT * POLYGON_SIZE, MAP_WIDTH * POLYGON_SIZE);
	BindTexture(m_apTexture[TEX_BG_0]);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CBg::Update()
{
	CPolygon3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CBg::Draw()
{
	CPolygon3D::Draw();
}

//=============================================================================
// 終了処理
//=============================================================================
void CBg::Uninit()
{
	CPolygon3D::Uninit();
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CBg::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "./data/TEXTURE/bg_001.png", &m_apTexture[TEX_BG_0]);
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "./data/TEXTURE/bg101.png", &m_apTexture[TEX_BG_1]);
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "./data/TEXTURE/bg102.png", &m_apTexture[TEX_BG_2]);

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CBg::Unload(void)
{
	for (int nCount = 0; nCount < TEX_BG_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CBg * CBg::Create(void)
{
	CBg *pBg;
	pBg = new CBg;
	pBg->Init();
	pBg->SetObjType(OBJ_TYPE_WALL);
	return pBg;
}
