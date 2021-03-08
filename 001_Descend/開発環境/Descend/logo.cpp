//=============================================================================
//
// タイトルロゴ処理 [logo.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "logo.h"
#include "manager.h"
#include "keyboard.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLogo::m_pTexture = NULL;
bool CLogo::m_bPlay = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CLogo::CLogo()
{
	m_bPlay = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLogo::~CLogo()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLogo::Init(D3DXVECTOR3 pos)
{
	CPolygon3D::Init();
	SetPos(D3DXVECTOR3(pos.x + POLYGON_SIZE / 4, pos.y, pos.z));
	m_bPlay = false;

	// テクスチャの作成
	BindTexture(m_pTexture);
	SetSize(POLYGON_SIZE * 3, POLYGON_SIZE * 10);
	SetTexUV(0.0f, 1.0f, 0.0f, 0.5f);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CLogo::Update(void)
{
	CInputKeyboard *pInput = CManager::GetInput();

	if (!m_bPlay)
	{
		if (pInput->GetKeyboardTrigger(DIK_SPACE) || pInput->GetKeyboardTrigger(DIK_RSHIFT) || pInput->GetKeyboardTrigger(DIK_RETURN))
		{
			m_bPlay = true;
			SetTexUV(0.0f, 1.0f, 0.5f, 1.0f);
		}
	}
	CPolygon3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CLogo::Draw(void)
{
	CPolygon3D::Draw();
}

//=============================================================================
// 終了処理
//=============================================================================
void CLogo::Uninit(void)
{
	CPolygon3D::Uninit();
}

//=============================================================================
// テクスチャ読み込み処理
//=============================================================================
HRESULT CLogo::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "./data/TEXTURE/Title_Logo.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CLogo::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//	インスタンス生成処理
//=============================================================================
CLogo * CLogo::Create(D3DXVECTOR3 pos)
{
	CLogo *pLogo;
	pLogo = new CLogo;
	pLogo->Init(pos);

	return pLogo;
}
