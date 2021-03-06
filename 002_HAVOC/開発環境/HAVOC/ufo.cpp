//================================================================================
//
// UFO (ufo.cpp)
// Author : ã¡TV(s®AIAGtFNg) / ó{ (Kw\¢AAj[V§ä)
//
//================================================================================

//========================
// CN[ht@C
//========================
#include "ufo.h"
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

//========================================
// ÃIoÏé¾
//========================================
LPD3DXMESH CUfo::m_pMesh[PARTS_MAX] = {};
LPD3DXBUFFER CUfo::m_pBuffMat[PARTS_MAX] = {};
DWORD CUfo::m_nNumMat[PARTS_MAX] = {};

//=============================================================================
// RXgN^
// Author : ã¡TV
//=============================================================================
CUfo::CUfo() :CCharacter(OBJTYPE::OBJTYPE_ENEMY)
{
    m_move = DEFAULT_VECTOR;
    m_nScore = 0;
    m_nOrbs = 0;

    m_patrolCentralPos = DEFAULT_VECTOR;
    m_patrolDestPos = DEFAULT_VECTOR;
    m_nPatrolDistance = 0;
    m_nCntTime = 0;

    m_fSpeed = 0.0f;
    m_rotDest = DEFAULT_VECTOR;
    m_rotMin = DEFAULT_VECTOR;

    m_bWarning = false;
    m_fDiscoveryDistance = 0.0f;

    m_attackAI = ATTACK_AI_WAIT;
}

//=============================================================================
// fXgN^
// Author : ã¡TV
//=============================================================================
CUfo::~CUfo()
{
}

//=============================================================================
// ú»
// Author : ó{ 
//=============================================================================
HRESULT CUfo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // p[cðÝè
    SetPartNum(PARTS_MAX);

    for (int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        BindMesh(CCharacter::TRIBE_UFO, nCount, m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount]);
    }

    // ÀWEeqÖWÌÇÝÝ
    LoadModelData("./data/ANIMATION/motion_UFO.txt");

    CCharacter::Init(pos, size);

    return S_OK;
}

//=============================================================================
// I¹
// Author : ã¡TV
//=============================================================================
void CUfo::Uninit(void)
{
    CCharacter::Uninit();
}

//=============================================================================
// XV
// Author : ã¡TV
//=============================================================================
void CUfo::Update(void)
{
    // s®
    Movement();

    // Aj[VÌXV
    CCharacter::Update();

    // ÌÍª0ÈºÈçAXRAÁZµA¢gpÉ
    if (GetLife() <= 0)
    {
        // ÊuÆü«ðæ¾
        D3DXVECTOR3 pos = DEFAULT_VECTOR;
        D3DXVECTOR3 rot = DEFAULT_VECTOR;
        pos = GetPos();
        rot = GetRot();

        // ²Ó
        DeathCrush(pos, rot);

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
            if (nRandNum <= UFO_DROP_HEAL_ITEM)
            {
                CItem::Create(pos, DEFAULT_VECTOR, CItem::TYPE_HEAL);
            }
        }

        // I¹
        Uninit();
    }
}

//=============================================================================
// s®
// Author : ã¡TV
//=============================================================================
void CUfo::Movement(void)
{
    // ÊuÆü«ðæ¾
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    D3DXVECTOR3 rot = DEFAULT_VECTOR;
    pos = GetPos();
    rot = GetRot();

    // xúµÄ¢È¢Èç
    if (m_bWarning == false)
    {
        // [VðÒ@É·é
        GetAnimation()->SetAnimation(ANIM_IDLE);

        // ñ]§ä
        rot = RotControl(rot);
    }
    // xúµÄ¢éÈç
    else
    {
        // [VðxúÉ·é
        GetAnimation()->SetAnimation(ANIM_WARN);
    }

    // 1FOÌÊuðL¯
    SetPosOld(pos);

    // ñAI
    pos = PatrolAI(pos);

    // xúAI
    rot = WarningAI(pos, rot);

    // UAI
    if (CGame::GetState() == CGame::STATE_NORMAL)
    {
        pos = AttackAI(pos, rot);
    }

    // Ú®ÊÆÊuðÑÂ¯é
    pos += m_move;

    // }bv§À
    CGame::MAP_LIMIT mapLimit = CGame::GetMapLimit();
    if (pos.x - GetActiveCollisionSize().x < mapLimit.fWest)
    {
        pos.x = mapLimit.fWest + GetActiveCollisionSize().x;
    }
    if (pos.x + GetActiveCollisionSize().x > mapLimit.fEast)
    {
        pos.x = mapLimit.fEast - GetActiveCollisionSize().x;
    }
    if (pos.z - GetActiveCollisionSize().z < mapLimit.fSouth)
    {
        pos.z = mapLimit.fSouth + GetActiveCollisionSize().z;
    }
    if (pos.z + GetActiveCollisionSize().z > mapLimit.fNorth)
    {
        pos.z = mapLimit.fNorth - GetActiveCollisionSize().z;
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
#endif // COLLISION_TEST
}

//=============================================================================
// ½è»èÌÊuðXV
// Author : ã¡TV
//=============================================================================
void CUfo::UpdateCollisionPos(void)
{
    SetCollisionPos(0, GetPos() + UFO_UP_COLLISION_POS);
}

//=============================================================================
// ñ]§ä
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CUfo::RotControl(D3DXVECTOR3 rot)
{
    // Ô·ñ]Ê
    D3DXVECTOR3 returnRot = rot;

    // 1FOÆÀWªá¤Èç
    if (GetPosOld() != GetPos())
    {
        // 1FOÌÊuÆA»ÝÌÊuðärµApxðßé
        float fAngle = atan2((GetPosOld().x - GetPos().x), (GetPosOld().z - GetPos().z));

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
            returnRot.y += (m_rotDest.y - returnRot.y) * UFO_TURN_SPEED;
        }
    }

    return returnRot;
}

//=============================================================================
// ñAI
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CUfo::PatrolAI(D3DXVECTOR3 pos)
{
    // Ô·Êuðßé
    D3DXVECTOR3 returnPos = pos;

    // xúÅÈ¢Èç
    if (m_bWarning == false)
    {
        // ÚIÌÊuÜÅÌ£ðßé
        float fDistance = sqrtf(
            powf((m_patrolDestPos.x - pos.x), 2) +
            powf((m_patrolDestPos.z - pos.z), 2));

        // £ªÚIÌÊuÉß¢Èç
        if (fDistance <= UFO_CONSIDER_CLOSE_DEST)
        {
            // JE^ðÁZ
            m_nCntTime++;

            // êèJE^ÅAÌÚInðßé
            if (m_nCntTime >= UFO_CHANGE_MOVE_IN_PATROL)
            {
                // JE^ðZbg
                m_nCntTime = 0;

                // ÌÚInðßé
                float fPosX = float(rand() % m_nPatrolDistance) - float(rand() % m_nPatrolDistance) + m_patrolCentralPos.x;
                float fPosZ = float(rand() % m_nPatrolDistance) - float(rand() % m_nPatrolDistance) + m_patrolCentralPos.z;

                // }bv§À
                CGame::MAP_LIMIT mapLimit = CGame::GetMapLimit();
                if (fPosX - GetActiveCollisionSize().x < mapLimit.fWest)
                {
                    fPosX = mapLimit.fWest + GetActiveCollisionSize().x;
                }
                if (fPosX + GetActiveCollisionSize().x > mapLimit.fEast)
                {
                    fPosX = mapLimit.fEast - GetActiveCollisionSize().x;
                }
                if (fPosZ - GetActiveCollisionSize().z < mapLimit.fSouth)
                {
                    fPosZ = mapLimit.fSouth + GetActiveCollisionSize().z;
                }
                if (fPosZ + GetActiveCollisionSize().z > mapLimit.fNorth)
                {
                    fPosZ = mapLimit.fNorth - GetActiveCollisionSize().z;
                }

                // ÌÚInðAoÏÉÑÂ¯é
                m_patrolDestPos = D3DXVECTOR3(fPosX, 0.0f, fPosZ);
            }
        }
        // £ªÚIÌÊuæè¢Èç
        else
        {
            // JE^ðZbg
            m_nCntTime = 0;

            // »ÝÌÊuÆAÚInÜÅÌpxðßé
            float fAngle = atan2((GetPos().x - m_patrolDestPos.x), (GetPos().z - m_patrolDestPos.z));

            // Ú®Êðßé
            D3DXVECTOR3 move = D3DXVECTOR3(-sinf(fAngle)*m_fSpeed, 0.0f, -cosf(fAngle)*m_fSpeed);

            // ÊuÉÚ®ÊðÑÂ¯é
            returnPos += move;
        }
    }

    return returnPos;
}

//=============================================================================
// xúAI
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CUfo::WarningAI(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // Ô·ü«
    D3DXVECTOR3 returnRot = rot;

    // vC[ÌÊuðæ¾
    D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPos();

    // xúµÄ¢È¢Èç
    if (m_bWarning == false)
    {
        // vC[ÆÌ£ðªé
        float fDistance = sqrtf(
            powf((playerPos.x - pos.x), 2) +
            powf((playerPos.z - pos.z), 2));

        // vC[­©£ÉBµ½ç
        if (fDistance <= m_fDiscoveryDistance)
        {
            // xúÉ(¼ÉxúÉÈép^[ÍAUð­ç¤Aß­ÌÔªUð­ç¤ª é)
            m_bWarning = true;
        }
    }
    // xúÈç
    else
    {
        // vC[ÌÊuÆA©gÌÊuðärµApxðßé
        float fAngle = atan2((GetPos().x - playerPos.x), (GetPos().z - playerPos.z));

        // vC[ÆÌ£ðªé
        float fDistance = sqrtf(
            powf((playerPos.x - pos.x), 2) +
            powf((playerPos.z - pos.z), 2));

        // vC[ÆÌ³Ì·ðªé
        float fHeight = fabsf((playerPos.y) - pos.y);

        // cÌpxðßé
        float fAngleY = atan2(fDistance, fHeight);

        // ß½pxðü­æ¤É·é
        m_rotDest.x = cosf(fAngleY);
        m_rotDest.y = fAngle;

        // WIÌÊuÌÙ¤ªAíÌÊuæèá¢Èç
        if (playerPos.y < pos.y)
        {
            // ðtÉ·é
            m_rotDest.x *= -1;
        }

        // ñ]Ì§À
        if (returnRot.y > D3DX_PI)
        {
            returnRot.y -= D3DX_PI * 2;
        }
        else if (returnRot.y < -D3DX_PI)
        {
            returnRot.y += D3DX_PI * 2;
        }
        if (returnRot.x > D3DX_PI)
        {
            returnRot.x -= D3DX_PI * 2;
        }
        else if (returnRot.x < -D3DX_PI)
        {
            returnRot.x += D3DX_PI * 2;
        }

        m_rotMin.x = m_rotDest.x - returnRot.x;
        m_rotMin.y = m_rotDest.y - returnRot.y;

        // ÚIÌpxÌñ]ð§À
        if (m_rotMin.y > D3DX_PI)
        {
            m_rotDest.y -= D3DX_PI * 2;
        }
        else if (m_rotMin.y < -D3DX_PI)
        {
            m_rotDest.y += D3DX_PI * 2;
        }
        if (m_rotMin.x > D3DX_PI)
        {
            m_rotDest.x -= D3DX_PI * 2;
        }
        else if (m_rotMin.x < -D3DX_PI)
        {
            m_rotDest.x += D3DX_PI * 2;
        }

        // ñ]Ì§À
        if (returnRot.y > D3DX_PI)
        {
            returnRot.y -= D3DX_PI * 2;
        }
        else if (returnRot.y < -D3DX_PI)
        {
            returnRot.y += D3DX_PI * 2;
        }
        if (returnRot.x > D3DX_PI)
        {
            returnRot.x -= D3DX_PI * 2;
        }
        else if (returnRot.x < -D3DX_PI)
        {
            returnRot.x += D3DX_PI * 2;
        }

        if (fabsf(m_rotMin.y) < 0)
        {
            m_rotMin.y = m_rotDest.y;
        }
        else
        {
            returnRot.y += (m_rotDest.y - returnRot.y) * UFO_TURN_SPEED;
        }

        if (fabsf(m_rotMin.x) < 0)
        {
            m_rotMin.x = m_rotDest.x;
        }
        else
        {
            returnRot.x += (m_rotDest.x - returnRot.x) * UFO_TURN_SPEED;
        }

        // £ð´¦½ç
        if (fDistance >= UFO_CONSIDER_AS_LONG)
        {
            // xúðð
            m_bWarning = false;
        }
    }

    return returnRot;
}

//=============================================================================
// UAI
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CUfo::AttackAI(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // Ô·ÊuAÚ®Êðßé
    D3DXVECTOR3 returnPos = pos;
    D3DXVECTOR3 move = DEFAULT_VECTOR;

    // vC[ÜÅÌ£
    D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPos();
    float fDistance = 0.0f;

    // xúÈç
    if (m_bWarning == true)
    {
        switch (m_attackAI)
        {
        case ATTACK_AI_WAIT:

            // JE^Abv
            m_nCntTime++;

            // vC[ÜÅÌ£ðßé
            fDistance = sqrtf(
                powf((playerPos.x - pos.x), 2) +
                powf((playerPos.z - pos.z), 2));

            // £ª¢Èç
            if (fDistance > UFO_CONSIDER_CLOSE_DEST)
            {
                // ÇÕ
                returnPos += D3DXVECTOR3(-sinf(rot.y) * UFO_TRACKING_SPEED, 0.0f, -cosf(rot.y) * UFO_TRACKING_SPEED);

                // ñÌSÊuðÏ¦é
                m_patrolCentralPos = returnPos;
            }

            // êèJE^Å
            if (m_nCntTime >= UFO_NEXT_ATTACK_COUNT)
            {
                // JE^Zbg
                m_nCntTime = 0;

                // ËUÖ
                m_attackAI = ATTACK_AI_SHOT;
            }

            break;

        case ATTACK_AI_SHOT:

            // JE^Abv
            m_nCntTime++;

            // NGCgt[
            if (m_nCntTime == UFO_SHOT_CREATE_FRAME_1)
            {
                SetShotAttack(pos, rot);
            }
            else if (m_nCntTime == UFO_SHOT_CREATE_FRAME_2)
            {
                SetShotAttack(pos, rot);
            }
            else if (m_nCntTime == UFO_SHOT_CREATE_FRAME_3)
            {
                SetShotAttack(pos, rot);
            }

            // êèJE^Å
            if (m_nCntTime >= UFO_SHOT_WHOLE_FRAME)
            {
                // JE^Zbg
                m_nCntTime = 0;

                // Ò@É·é
                m_attackAI = ATTACK_AI_WAIT;
            }

            break;
        }
    }

    return returnPos;
}

//=============================================================================
// ËU
// Author : ã¡TV
//=============================================================================
void CUfo::SetShotAttack(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // Ú®pxðßé
    D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(rot.y), rot.x, -cosf(rot.y));

    // EüiÌÊuæ¾
    D3DXVECTOR3 rightWing = D3DXVECTOR3(GetParts(CUfo::PARTS_RIGHT_WING_2)->GetWorldMtx()._41,
        GetParts(CUfo::PARTS_RIGHT_WING_2)->GetWorldMtx()._42,
        GetParts(CUfo::PARTS_RIGHT_WING_2)->GetWorldMtx()._43);

    // ¶üiÌÊuæ¾
    D3DXVECTOR3 leftWing = D3DXVECTOR3(GetParts(CUfo::PARTS_LEFT_WING_2)->GetWorldMtx()._41,
        GetParts(CUfo::PARTS_LEFT_WING_2)->GetWorldMtx()._42,
        GetParts(CUfo::PARTS_LEFT_WING_2)->GetWorldMtx()._43);

    // eðNGCg
    CBullet::Create(pos, BULLET_AR_COLLISION_SIZE, moveAngle, CBullet::TYPE_CLAP, CBullet::TRIBE_ENEMY);

    // eðNGCg
    CBullet::Create(rightWing, BULLET_AR_COLLISION_SIZE, moveAngle, CBullet::TYPE_CLAP, CBullet::TRIBE_ENEMY);

    // eðNGCg
    CBullet::Create(leftWing, BULLET_AR_COLLISION_SIZE, moveAngle, CBullet::TYPE_CLAP, CBullet::TRIBE_ENEMY);
}

//=============================================================================
// `æ
// Author : ã¡TV
//=============================================================================
void CUfo::Draw(void)
{
    CCharacter::Draw();
}

//=============================================================================
// ff[^ÇÝÝ
// Author : ó{ 
//=============================================================================
HRESULT CUfo::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/UFO/00_Fighter.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_FIGHTER], NULL, &m_nNumMat[PARTS_FIGHTER], &m_pMesh[PARTS_FIGHTER]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/UFO/01_RightWing1.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RIGHT_WING_0], NULL, &m_nNumMat[PARTS_RIGHT_WING_0], &m_pMesh[PARTS_RIGHT_WING_0]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/UFO/02_RightWing2.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RIGHT_WING_1], NULL, &m_nNumMat[PARTS_RIGHT_WING_1], &m_pMesh[PARTS_RIGHT_WING_1]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/UFO/03_RightWing3.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RIGHT_WING_2], NULL, &m_nNumMat[PARTS_RIGHT_WING_2], &m_pMesh[PARTS_RIGHT_WING_2]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/UFO/04_RightWing4.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RIGHT_WING_3], NULL, &m_nNumMat[PARTS_RIGHT_WING_3], &m_pMesh[PARTS_RIGHT_WING_3]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/UFO/05_LeftWing1.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LEFT_WING_0], NULL, &m_nNumMat[PARTS_LEFT_WING_0], &m_pMesh[PARTS_LEFT_WING_0]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/UFO/06_LeftWing2.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LEFT_WING_1], NULL, &m_nNumMat[PARTS_LEFT_WING_1], &m_pMesh[PARTS_LEFT_WING_1]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/UFO/07_LeftWing3.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LEFT_WING_2], NULL, &m_nNumMat[PARTS_LEFT_WING_2], &m_pMesh[PARTS_LEFT_WING_2]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/UFO/08_LeftWing4.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LEFT_WING_3], NULL, &m_nNumMat[PARTS_LEFT_WING_3], &m_pMesh[PARTS_LEFT_WING_3]);
    return S_OK;
}

//=============================================================================
// ff[^jü
// Author : ó{ 
//=============================================================================
void CUfo::Unload(void)
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
CUfo * CUfo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // mÛ
    CUfo *pUfo = NULL;
    pUfo = new CUfo;

    // e³ÌîñðÝè
    pUfo->SetPos(pos);
    pUfo->SetRot(rot);
    pUfo->SetTribe(CCharacter::TRIBE_UFO);

    // ú»
    pUfo->Init(pos, DEFAULT_SCALE);

    // pg[ÌSÊuðL¯
    pUfo->m_patrolCentralPos = pos;

    // ÚWÊuðL¯
    pUfo->m_patrolDestPos = pos;

    pUfo->SetActiveCollisionSize(UFO_ACTIVE_COLLISION_SIZE);
    pUfo->SetLife(UFO_LIFE);
    pUfo->m_nScore = UFO_SCORE;
    pUfo->m_nOrbs = UFO_ORBS;
    pUfo->m_fSpeed = UFO_SPEED;
    pUfo->m_nPatrolDistance = UFO_PATROL_DISTANCE;
    pUfo->m_fDiscoveryDistance = UFO_DISCOVERY_DISTANCE;

    pUfo->SetCntCollision(UFO_COLLISION_MAX);
    pUfo->SetCollisionSize(0, UFO_ACTIVE_COLLISION_SIZE);

    // ½è»èÌÊuðXV
    pUfo->UpdateCollisionPos();

    return pUfo;
}

//=============================================================================
// I[uðoÜ­
// Author : ã¡TV
//=============================================================================
void CUfo::ScatterOrbs(void)
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
// âçê½Ì²Ó
// Author : ã¡TV
//=============================================================================
void CUfo::DeathCrush(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // p[cÌÊuÆAfGtFNgÌíÞ
    D3DXVECTOR3 partsPos = DEFAULT_VECTOR;
    CModelEffect::TYPE modelEffectType = CModelEffect::TYPE_UFO;

    //==============================
    // Ì
    //==============================
    // Êu
    partsPos = D3DXVECTOR3(GetParts(CUfo::PARTS_FIGHTER)->GetWorldMtx()._41,
        GetParts(CUfo::PARTS_FIGHTER)->GetWorldMtx()._42,
        GetParts(CUfo::PARTS_FIGHTER)->GetWorldMtx()._43);

    // GtFNgÌ­¶
    SetDeathCrushEffect(partsPos, rot, modelEffectType);

    //==============================
    // 
    //==============================
    modelEffectType = CModelEffect::TYPE_UFO_WING;

    // «Ì{ªoÜ­
    for (int nCnt = 0; nCnt < UFO_MAX_LEG; nCnt++)
    {
        // GtFNgÌ­¶(«ÍS©ço·)
        SetDeathCrushEffect(pos, rot, modelEffectType);
    }
}

//=============================================================================
// âçê½Ì²ÓGtFNgÌ­¶
// Author : ã¡TV
//=============================================================================
void CUfo::SetDeathCrushEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelEffect::TYPE type)
{
    // ²ÓGtFNgpÌÏé¾
    float fSpeedX = 0.0f;               // ¬³X
    float fSpeedY = 0.0f;               // ¬³Y
    float fSpeedZ = 0.0f;               // ¬³Z
    float fRotSpeedX = 0.0f;            // ñ]¬xX
    float fRotSpeedY = 0.0f;            // ñ]¬xY
    float fRotSpeedZ = 0.0f;            // ñ]¬xZ
    int nPlusMinusX = 0;                // X
    int nPlusMinusZ = 0;                // Z

    // ¬³ÆAð_Éßé
    fSpeedX = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_X, 0)) / 100.0f;
    fSpeedY = 0.0f;
    fSpeedZ = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_Z, 0)) / 100.0f;
    fRotSpeedX = float(GetRandNum(MODEL_EFFECT_UFO_ROT_MAX, MODEL_EFFECT_UFO_ROT_MIN)) / 100.0f - float(GetRandNum(MODEL_EFFECT_UFO_ROT_MAX, MODEL_EFFECT_UFO_ROT_MIN)) / 100.0f;
    fRotSpeedY = float(GetRandNum(MODEL_EFFECT_UFO_ROT_MAX, MODEL_EFFECT_UFO_ROT_MIN)) / 100.0f - float(GetRandNum(MODEL_EFFECT_UFO_ROT_MAX, MODEL_EFFECT_UFO_ROT_MIN)) / 100.0f;
    fRotSpeedZ = float(GetRandNum(MODEL_EFFECT_UFO_ROT_MAX, MODEL_EFFECT_UFO_ROT_MIN)) / 100.0f - float(GetRandNum(MODEL_EFFECT_UFO_ROT_MAX, MODEL_EFFECT_UFO_ROT_MIN)) / 100.0f;
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

    // ñ]Êðßé
    D3DXVECTOR3 rotMove = D3DXVECTOR3(D3DXToRadian(fRotSpeedX), D3DXToRadian(fRotSpeedY), D3DXToRadian(fRotSpeedZ));

    // GtFNg­¶
    CModelEffect::Create(pos, rot, move, rotMove, type);
}

//=============================================================================
// ÔÉx·é
// Author : ã¡TV
//=============================================================================
void CUfo::WarnFellow(void)
{
    // üÍÌÔðxúÉ·é
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

            // GÌí°ªUFOÈç
            if (pEnemy->GetTribe() == CCharacter::TRIBE_UFO)
            {
                // ÎÛÌÊu
                D3DXVECTOR3 targetPos = pEnemy->GetPos();

                // ÎÛÆÌ£
                float fDistance = sqrtf(
                    powf((targetPos.x - GetPos().x), 2) +
                    powf((targetPos.z - GetPos().z), 2));

                // ÎÛÆÌ£ªAÔÉx·éÆ«ÌÍÍàÈç
                if (fDistance <= UFO_WARN_UFO_DISTANCE)
                {
                    // UFO^ÉLXg
                    CUfo*pUfo = (CUfo*)pEnemy;

                    // xúÉ
                    pUfo->SetWarning(true);
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
// ~bVNAÉÁZ·é
// Author : ã¡TV
//=============================================================================
void CUfo::AddMissionClear(void)
{
    // Xe[WÆ»ÝÌ~bVÉ¶ÄANAðÁ
    CGame::STAGE stage = CGame::GetStage();
    CGame::CURRENT_MISSION currentMission = CGame::GetCurrentMission();
    switch (stage)
    {
    case CGame::STAGE_1:

        break;

    case CGame::STAGE_2:

        switch (currentMission)
        {
        case CGame::CURRENT_MISSION_1:
            CGame::SetClearNumMission1();
            break;

        case CGame::CURRENT_MISSION_2:

            break;
        }

        break;

    case CGame::STAGE_FINAL:

        break;
    }
}