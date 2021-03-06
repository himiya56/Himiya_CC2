//================================================================================
//
// hqR (force.cpp)
// Author : ã¡TV(s®AIAGtFNg) / ó{ (Kw\¢AAj[V§ä)
//
//================================================================================

//========================
// CN[ht@C
//========================
#include "force.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "animation.h"
#include "block.h"
#include "effect3d.h"
#include "bullet.h"
#include "library.h"
#include "debug.h"
#include "score.h"
#include "game.h"
#include "modelEffect.h"
#include "player.h"
#include "bullet.h"
#include "item.h"
#include "sound.h"

//========================================
// ÃIoÏé¾
//========================================
LPD3DXMESH CForce::m_pMesh[PARTS_MAX] = {};
LPD3DXBUFFER CForce::m_pBuffMat[PARTS_MAX] = {};
DWORD CForce::m_nNumMat[PARTS_MAX] = {};

//=============================================================================
// RXgN^
// Author : ã¡TV
//=============================================================================
CForce::CForce() :CCharacter(OBJTYPE::OBJTYPE_ENEMY)
{
    m_move = DEFAULT_VECTOR;
    m_nScore = 0;
    m_nOrbs = 0;

    m_nCntTime = 0;

    m_fSpeed = 0.0f;
    m_rotDest = DEFAULT_VECTOR;
    m_rotMin = DEFAULT_VECTOR;

    m_fDiscoveryDistance = 0.0f;

    m_attackAI = ATTACK_AI_WAIT;

    m_targetPos = DEFAULT_VECTOR;
    m_bUseRotControl = true;

    m_nDeathCounter = 0;
}

//=============================================================================
// fXgN^
// Author : ã¡TV
//=============================================================================
CForce::~CForce()
{
}

//=============================================================================
// ú»
// Author : ó{ 
//=============================================================================
HRESULT CForce::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // p[cðÝè
    SetPartNum(PARTS_MAX);

    for (int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        BindMesh(CCharacter::TRIBE_FORCE, nCount, m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount]);
    }

    // ÀWEeqÖWÌÇÝÝ
    LoadModelData("./data/ANIMATION/motion_ranger.txt");

    CCharacter::Init(pos, size);

    return S_OK;
}

//=============================================================================
// I¹
// Author : ã¡TV
//=============================================================================
void CForce::Uninit(void)
{
    CCharacter::Uninit();
}

//=============================================================================
// XV
// Author : ã¡TV
//=============================================================================
void CForce::Update(void)
{
    // ÌÍª éÈç
    if (GetLife() > 0)
    {
        // s®
        Movement();
    }

    // Aj[VÌXV
    CCharacter::Update();

    // ÌÍª0ÈºÈçAXRAÁZµA¢gpÉ
    if (GetLife() <= 0)
    {
        // [VðfXÉ·é
        GetAnimation()->SetAnimation(ANIM_DEATH);

        // fXJE^[ðÁZ
        m_nDeathCounter++;

        // j¹ðÂç·t[
        if (m_nDeathCounter == FORCE_DEATH_PLAY_SOUND)
        {
            CSound *pSound = CManager::GetSound();
            pSound->Play(CSound::LABEL_SE_FORCE);
        }

        // êèJE^ÅAí
        if (m_nDeathCounter >= FORCE_DEATH_COUNTER)
        {
            // ÊuÆü«ðæ¾
            D3DXVECTOR3 pos = DEFAULT_VECTOR;
            D3DXVECTOR3 rot = DEFAULT_VECTOR;
            pos = GetPos();
            rot = GetRot();

            // ~bVNAÉÁZ·é
            AddMissionClear();

            // XgqbgªvC[Èç
            if (GetLastHit() == LAST_HIT_PLAYER)
            {
                // I[uðoÜ­
                ScatterOrbs();

                // XRAÁZ
                CScore *pScore = CGame::GetScore();
                pScore->AddScore(m_nScore);

                // êèm¦ÅAñACeðÆ·
                int nRandNum = GetRandNum(100, 1);
                if (nRandNum <= FORCE_DROP_HEAL_ITEM)
                {
                    CItem::Create(pos, DEFAULT_VECTOR, CItem::TYPE_HEAL);
                }
            }

            // I¹
            Uninit();
        }
    }
}

//=============================================================================
// s®
// Author : ã¡TV
//=============================================================================
void CForce::Movement(void)
{
    // ÊuÆü«ðæ¾
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    D3DXVECTOR3 rot = DEFAULT_VECTOR;
    pos = GetPos();
    rot = GetRot();

    // [VðÜ¸ÍÒ@É·é
    GetAnimation()->SetAnimation(ANIM_IDLE);

    // ÚWÖÌÊuðßé
    DicisionTargetPos(pos);

    // ñ]§ä·éÈç
    if (m_bUseRotControl == true)
    {
        // ñ]§ä
        rot = RotControl(rot);
    }

    // 1FOÌÊuðL¯
    SetPosOld(pos);

    // UAI
    if (CGame::GetState() == CGame::STATE_NORMAL)
    {
        pos = AttackAI(pos, rot);
    }

    // Ú®ÊÆÊuðÑÂ¯é
    pos += m_move;

    // nÊæèãÈç
    if (pos.y > 0.0f)
    {
        // dÍ
        m_move.y -= GRAVITY;
    }
    else
    {
        // nÊÉ¢éÈçAdÍð©¯È¢
        pos.y = 0.0f;
        m_move.y = 0.0f;
    }

    // ubNÖÌ½è»è
    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_BLOCK);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_BLOCK); nCntScene++)
    {
        // gª éÈç
        if (pScene != NULL)
        {
            // ÌV[ðL¯
            CScene*pNextScene = pScene->GetNextScene();

            // ubNÉLXg
            CBlock *pBlock = (CBlock*)pScene;

            // GªÇèÅ«éubNÈç
            if (pBlock->GetEnemyWallRun() == true)
            {
                // ubNÌÊuÆå«³ðæ¾
                D3DXVECTOR3 blockPos = pBlock->GetPos();
                D3DXVECTOR3 blockSize = pBlock->GetCollisionSize();

                // ubNÆÌ½è»èðvZ
                BLOCK_HIT_INFO blockHitInfo;
                blockHitInfo.hitSurface = HIT_SURFACE_NONE;
                blockHitInfo.pos = pos;
                blockHitInfo = (BlockCollision3D(&pos, &GetPosOld(), &blockPos,
                    &GetActiveCollisionSize(), &blockSize));

                // ubNÌ½è»èÅvZµ½ÊuðAÑÂ¯é
                pos = blockHitInfo.pos;
            }

            // ÌV[É·é
            pScene = pNextScene;
        }
        else
        {
            // gªÈ¢ÈçA»±ÅðI¦é
            break;
        }
    }

    // ÊuÆü«ð½f
    SetPos(pos);
    SetRot(rot);

    // ½è»èÌÊuðXV
    UpdateCollisionPos();

#ifdef COLLISION_TEST
    for (int nCnt = 0; nCnt < GetCntCollision(); nCnt++)
    {
        COLLISION collision = GetCollision(nCnt);
        CDebug::Create(collision.pos, collision.size, CDebug::TYPE_MOMENT);
    }
    CDebug::Create(pos, GetActiveCollisionSize(), CDebug::TYPE_MOMENT);
#endif // COLLISION_TEST
}

//=============================================================================
// ½è»èÌÊuðXV
// Author : ã¡TV
//=============================================================================
void CForce::UpdateCollisionPos(void)
{
    SetCollisionPos(0, GetPos());
}

//=============================================================================
// ñ]§ä
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CForce::RotControl(D3DXVECTOR3 rot)
{
    // Ô·ñ]Ê
    D3DXVECTOR3 returnRot = rot;

    // ÚWÖÌpxðßé
    float fAngle = atan2((GetPos().x - m_targetPos.x), (GetPos().z - m_targetPos.z));

    // ß½pxðü­æ¤É·é
    m_rotDest.y = fAngle;

    // ñ]Ì§À
    if (returnRot.y > D3DX_PI)
    {
        returnRot.y -= D3DX_PI * 2;
    }
    if (returnRot.y < -D3DX_PI)
    {
        returnRot.y += D3DX_PI * 2;
    }

    m_rotMin.y = m_rotDest.y - returnRot.y;

    // ÚIÌpxÌñ]ð§À
    if (m_rotMin.y > D3DX_PI)
    {
        m_rotDest.y -= D3DX_PI * 2;
    }
    if (m_rotMin.y < -D3DX_PI)
    {
        m_rotDest.y += D3DX_PI * 2;
    }

    // ñ]Ì§À
    if (returnRot.y > D3DX_PI)
    {
        returnRot.y -= D3DX_PI * 2;
    }
    if (returnRot.y < -D3DX_PI)
    {
        returnRot.y += D3DX_PI * 2;
    }

    if (fabsf(m_rotMin.y) < 0)
    {
        m_rotMin.y = m_rotDest.y;
    }
    else
    {
        returnRot.y += (m_rotDest.y - returnRot.y) * FORCE_TURN_SPEED;
    }

    return returnRot;
}

//=============================================================================
// UAI
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CForce::AttackAI(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // Ô·ÊuAÚ®Êðßé
    D3DXVECTOR3 returnPos = pos;
    D3DXVECTOR3 move = DEFAULT_VECTOR;

    switch (m_attackAI)
    {
    case ATTACK_AI_WAIT:

        // ñ]§ä·é
        m_bUseRotControl = true;

        // JE^Abv
        m_nCntTime++;

        // êèJE^Å
        if (m_nCntTime >= FORCE_NEXT_ATTACK_COUNT)
        {
            // JE^Zbg
            m_nCntTime = 0;

            // é©U·é©Ì»f
            JudgmentRunOrAttack(pos);
        }

        break;

    case ATTACK_AI_DUSH:

        // ñ]§äµÈ¢
        m_bUseRotControl = false;

        // JE^Abv
        m_nCntTime++;

        // Aj[VðèÉ
        GetAnimation()->SetAnimation(ANIM_WALK);

        // é
        returnPos = Dush(returnPos, rot);

        // êèJE^Å
        if (m_nCntTime >= FORCE_DUSH_WHOLE_FRAME)
        {
            // JE^Zbg
            m_nCntTime = 0;

            // UÉh¶
            m_attackAI = ATTACK_AI_SHOT;
        }

        break;

    case ATTACK_AI_SHOT:

        // ñ]§ä·é
        m_bUseRotControl = true;

        // JE^Abv
        m_nCntTime++;

        // Aj[VðUÉ
        GetAnimation()->SetAnimation(ANIM_ATTACK);

        // NGCgt[
        if (m_nCntTime % FORCE_SHOT_CREATE_FRAME == 0)
        {
            SetShotAttack(pos, rot);
        }

        // êèJE^Å
        if (m_nCntTime >= FORCE_SHOT_WHOLE_FRAME)
        {
            // JE^Zbg
            m_nCntTime = 0;

            // Ò@É·é
            m_attackAI = ATTACK_AI_WAIT;
        }

        break;
    }

    return returnPos;
}

//=============================================================================
// é©U·é©Ì»f
// Author : ã¡TV
//=============================================================================
void CForce::JudgmentRunOrAttack(D3DXVECTOR3 pos)
{
    // ÚWÜÅÌ£
    float fDistance = sqrtf(powf((m_targetPos.x - pos.x), 2) + powf((m_targetPos.z - pos.z), 2));

    // ­©£É¢éÈç
    if (fDistance <= m_fDiscoveryDistance)
    {
        // UÉ·é
        m_attackAI = ATTACK_AI_SHOT;
    }
    // ­©£É¢È¢Èç
    else
    {
        // é
        m_attackAI = ATTACK_AI_DUSH;
    }
}

//=============================================================================
// ^[QbgÌÊuðßé
// Author : ã¡TV
//=============================================================================
void CForce::DicisionTargetPos(D3DXVECTOR3 pos)
{
    // ^[QbgÌÊuÉ¶ÄADæÊðÂ¯é
    m_targetPos = CGame::GetPlayer()->GetPos();                                                              // ÚWÌÊu(êxvC[É)
    float fFirstTargetDistance = sqrtf(powf((m_targetPos.x - pos.x), 2) + powf((m_targetPos.z - pos.z), 2)); // ÚWÜÅÌ£1
    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_ENEMY);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_ENEMY); nCntScene++)
    {
        // gª éÈç
        if (pScene != NULL)
        {
            // ÌV[ðL¯
            CScene*pNextScene = pScene->GetNextScene();

            // LN^[ÉLXg
            CCharacter *pEnemy = (CCharacter*)pScene;

            // GÌí°ªhqRÈOÈç
            if (pEnemy->GetTribe() != CCharacter::TRIBE_FORCE)
            {
                // ÎÛÌÊu
                D3DXVECTOR3 targetPos = pEnemy->GetPos();

                // ÚWÜÅÌ£2
                float fSecondTargetDistance = sqrtf(
                    powf((targetPos.x - pos.x), 2) +
                    powf((targetPos.z - pos.z), 2));

                // ÚWÜÅÌ£2ªAÚWÜÅÌ£1æèàß¢Èç
                if (fSecondTargetDistance < fFirstTargetDistance)
                {
                    // ^[QbgÌÊuðXV
                    m_targetPos = targetPos;

                    // ÚWÜÅÌ£1ðXV
                    fFirstTargetDistance = fSecondTargetDistance;
                }
            }

            // ÌV[É·é
            pScene = pNextScene;
        }
        else
        {
            // gªÈ¢ÈçA»±ÅðI¦é
            break;
        }
    }
}

//=============================================================================
// é
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CForce::Dush(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    D3DXVECTOR3 returnPos = pos;

    // üÄ¢éûüÉiÞ
    D3DXVECTOR3 move = D3DXVECTOR3(-sinf(rot.y) * m_fSpeed, 0.0f, -cosf(rot.y) * m_fSpeed);
    returnPos += move;

    // ÚWÜÅÌ£
    float fDistance = sqrtf(powf((m_targetPos.x - returnPos.x), 2) + powf((m_targetPos.z - returnPos.z), 2));

    // ­©£É¢éÈç
    if (fDistance <= m_fDiscoveryDistance)
    {
        // JE^Zbg
        m_nCntTime = 0;

        // ·®ÉU·é
        m_attackAI = ATTACK_AI_SHOT;
    }

    return returnPos;
}

//=============================================================================
// ËU
// Author : ã¡TV
//=============================================================================
void CForce::SetShotAttack(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // íÌÊuæ¾
    D3DXVECTOR3 weaponPos = D3DXVECTOR3(GetParts(CForce::PARTS_WEAPON)->GetWorldMtx()._41,
        GetParts(CForce::PARTS_WEAPON)->GetWorldMtx()._42,
        GetParts(CForce::PARTS_WEAPON)->GetWorldMtx()._43);

    // vC[ÆÌ£ðªé
    float fDistance = sqrtf(
    	powf((m_targetPos.x - weaponPos.x), 2) +
    	powf((m_targetPos.z - weaponPos.z), 2));

    // vC[ÆÌ³Ì·ðªé
    float fHeight = fabsf((m_targetPos.y + FORCE_SHOT_AIM_UP) - weaponPos.y);

    // pxðßé
    float fAngleY = atan2(fDistance, fHeight);

    // Ú®pxðßé
    D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(rot.y), cosf(fAngleY), -cosf(rot.y));

    // WIÌÊuÌÙ¤ªAíÌÊuæèá¢Èç
    if (m_targetPos.y + FORCE_SHOT_AIM_UP < weaponPos.y)
    {
        // Y²ÌÚ®pxðtÉ·é
        moveAngle.y *= -1;
    }

    // eðNGCg
    CBullet::Create(weaponPos, BULLET_CLAP_COLLISION_SIZE, moveAngle, CBullet::TYPE_CLAP, CBullet::TRIBE_NEUTRAL);
}

//=============================================================================
// `æ
// Author : ã¡TV
//=============================================================================
void CForce::Draw(void)
{
    CCharacter::Draw();
}

//=============================================================================
// ff[^ÇÝÝ
// Author : ó{ 
//=============================================================================
HRESULT CForce::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/00_body.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_BODY], NULL, &m_nNumMat[PARTS_BODY], &m_pMesh[PARTS_BODY]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/01_head.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_HEAD], NULL, &m_nNumMat[PARTS_HEAD], &m_pMesh[PARTS_HEAD]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/02_right_arm.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RIGHT_ARM], NULL, &m_nNumMat[PARTS_RIGHT_ARM], &m_pMesh[PARTS_RIGHT_ARM]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/03_right_hand.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RIGHT_HAND], NULL, &m_nNumMat[PARTS_RIGHT_HAND], &m_pMesh[PARTS_RIGHT_HAND]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/04_left_arm.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LEFT_ARM], NULL, &m_nNumMat[PARTS_LEFT_ARM], &m_pMesh[PARTS_LEFT_ARM]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/05_left_hand.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LEFT_HAND], NULL, &m_nNumMat[PARTS_LEFT_HAND], &m_pMesh[PARTS_LEFT_HAND]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/06_right_leg.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RIGHT_LEG], NULL, &m_nNumMat[PARTS_RIGHT_LEG], &m_pMesh[PARTS_RIGHT_LEG]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/07_right_foot.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RIGHT_FOOT], NULL, &m_nNumMat[PARTS_RIGHT_FOOT], &m_pMesh[PARTS_RIGHT_FOOT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/08_left_leg.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LEFT_LEG], NULL, &m_nNumMat[PARTS_LEFT_LEG], &m_pMesh[PARTS_LEFT_LEG]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/09_left_foot.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LEFT_FOOT], NULL, &m_nNumMat[PARTS_LEFT_FOOT], &m_pMesh[PARTS_LEFT_FOOT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ranger/10_weapon.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_WEAPON], NULL, &m_nNumMat[PARTS_WEAPON], &m_pMesh[PARTS_WEAPON]);

    return S_OK;
}

//=============================================================================
// ff[^jü
// Author : ó{ 
//=============================================================================
void CForce::Unload(void)
{
    for (int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        if (m_pBuffMat[nCount] != NULL)
        {
            m_pBuffMat[nCount] = NULL;
        }

        if (m_nNumMat[nCount] != NULL)
        {
            m_nNumMat[nCount] = NULL;
        }

        if (m_pMesh[nCount] != NULL)
        {
            m_pMesh[nCount] = NULL;
        }
    }
}

//=============================================================================
// CX^X¶¬
// Author : ã¡TV
//=============================================================================
CForce * CForce::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // mÛ
    CForce *pForce = NULL;
    pForce = new CForce;

    // e³ÌîñðÝè
    pForce->SetPos(pos);
    pForce->SetRot(rot);
    pForce->SetTribe(CCharacter::TRIBE_FORCE);

    pForce->Init(pos, DEFAULT_SCALE);

    pForce->SetActiveCollisionSize(FORCE_ACTIVE_COLLISION_SIZE);
    pForce->SetLife(FORCE_LIFE);
    pForce->m_nScore = FORCE_SCORE;
    pForce->m_nOrbs = FORCE_ORBS;
    pForce->m_fSpeed = FORCE_SPEED;
    pForce->m_fDiscoveryDistance = FORCE_DISCOVERY_DISTANCE;

    pForce->SetCntCollision(FORCE_COLLISION_MAX);
    pForce->SetCollisionSize(0, FORCE_ACTIVE_COLLISION_SIZE);

    // ½è»èÌÊuðXV
    pForce->UpdateCollisionPos();

    pForce->m_targetPos = CGame::GetPlayer()->GetPos();

    return pForce;
}

//=============================================================================
// I[uðoÜ­
// Author : ã¡TV
//=============================================================================
void CForce::ScatterOrbs(void)
{
    // Êuðæ¾
    D3DXVECTOR3 pos = GetPos();

    // I[uòUGtFNg
    float fSpeedX = 0.0f;   //¬³X
    float fSpeedY = 0.0f;   //¬³Y
    float fSpeedZ = 0.0f;   //¬³Z
    int nPlusMinusX = 0;    //X
    int nPlusMinusZ = 0;    //Z
    for (int nCnt = 0; nCnt < m_nOrbs; nCnt++)
    {
        // ¬³ÆAð_Éßé
        fSpeedX = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_X, 0)) / 100.0f;
        fSpeedY = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_Y, EFFECT_CHARGE_SPREAD_MIN_Y)) / 100.0f;
        fSpeedZ = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_Z, 0)) / 100.0f;
        nPlusMinusX = GetRandNum(2, 1);
        nPlusMinusZ = GetRandNum(2, 1);
        if (nPlusMinusX == 1)
        {
            nPlusMinusX = 1;
        }
        else
        {
            nPlusMinusX = -1;
        }

        if (nPlusMinusZ == 1)
        {
            nPlusMinusZ = 1;
        }
        else
        {
            nPlusMinusZ = -1;
        }

        // Ú®Êðßé
        D3DXVECTOR3 move = D3DXVECTOR3(fSpeedX*nPlusMinusX, fSpeedY, fSpeedZ*nPlusMinusZ);

        // GtFNg­¶
        CEffect3D::Create(pos, EFFECT_CHARGE_SIZE, move,
            EFFECT3D_PURPLE_FIRE_FIRST_COLOR, DEFAULT_VECTOR, EFFECT3D_PURPLE_FIRE_FADE_OUT_RATE, CEffect3D::TYPE_CHARGE);
    }
}

//=============================================================================
// ~bVNAÉÁZ·é
// Author : ã¡TV
//=============================================================================
void CForce::AddMissionClear(void)
{
    // Xe[WÆ»ÝÌ~bVÉ¶ÄANAðÁ
    CGame::STAGE stage = CGame::GetStage();
    CGame::CURRENT_MISSION currentMission = CGame::GetCurrentMission();
    switch (stage)
    {
    case CGame::STAGE_1:

        switch (currentMission)
        {
        case CGame::CURRENT_MISSION_1:

            break;

        case CGame::CURRENT_MISSION_2:
            CGame::SetClearNumMission2();
            break;
        }

        break;

    case CGame::STAGE_2:

        break;

    case CGame::STAGE_FINAL:

        break;
    }
}