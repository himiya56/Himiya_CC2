//=============================================================================
//
// 自作簡易処理関数群 [Library.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "library.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_STRING_LENGTH 256

//*****************************************************************************
// 遅延関数
//*****************************************************************************
void Delay(const int nSecond)
{
	time_t now = nSecond * CLOCKS_PER_SEC + clock();

	while (now > clock());
}

//*****************************************************************************
// 指定範囲内の乱数を生成
//*****************************************************************************
int GetRandom(const int min, const int max)
{
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}

//*****************************************************************************
// 合計値計算関数
// 第 1 引数   : 計算する値の個数
// 第 2 引以降 : 合計値計算したい値群
//*****************************************************************************
int Sum(int nValue, ...)
{
	va_list arg;
	int nSum = 0;	// 合計値格納用

	va_start(arg, nValue);

	// 引数の数だけ繰り返す
	for (int nCount = 0; nCount < nValue; nCount++)
	{
		// 合計値に加算
		nSum += va_arg(arg, int);
	}

	va_end(arg);

	// 合計値を返す
	return nSum;
}

//*****************************************************************************
// intをcharポインタに変換
//*****************************************************************************
char * NumberToChar(const int nNumber)
{
	// 文字列保持用
	char cString[MAX_STRING_LENGTH];
	// 変換
	snprintf(cString, MAX_STRING_LENGTH, "%d", nNumber);

	return cString;
}

//*****************************************************************************
// floatをcharポインタに変換
//*****************************************************************************
char * NumberToChar(const float fNumber)
{
	// 文字列保持用
	char cString[MAX_STRING_LENGTH];
	// 変換
	snprintf(cString, MAX_STRING_LENGTH, "%.2f", fNumber);

	return cString;
}

//*****************************************************************************
// ベクトルの大きさを計算
//*****************************************************************************
float Vec3Length(D3DXVECTOR3 *pVec)
{
	double x, y, z;
	double len;

	if (!pVec) return 0.0f;

	x = (double)(pVec->x);
	y = (double)(pVec->y);
	z = (double)(pVec->z);
	len = sqrt(x * x + y * y + z * z);

	return (float)(len);
}