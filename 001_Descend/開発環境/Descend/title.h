//=============================================================================
//
// 数字表示処理 [number.h]
// Author : 樋宮 匠
//
//=============================================================================

// 二重インクルード防止用
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "polygon2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TITLE_POLYGON 1

//*****************************************************************************
// タイトルクラス定義
//*****************************************************************************
class CTitle :public CObject
{
public:
	// メンバ関数
	CTitle();										// コンストラクタ
	~CTitle();										// デストラクタ
	HRESULT Init(void);								// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理
	static CTitle *Create(void);					// インスタンス生成
	static HRESULT Load(void);
	static void Unload(void);
private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	static bool						m_bChageMode;   // モードを変えたかのフラグ
	CPolygon2D						*m_pPolygon;
};

#endif