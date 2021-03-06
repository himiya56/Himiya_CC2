//================================================================================
//
// wå (spider.cpp)
// Author : ã¡TV(s®AIAGtFNg) / ó{ (Kw\¢AAj[V§ä)
//
//================================================================================

//========================
// CN[ht@C
//========================
#include "spider.h"
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
#include "item.h"
#include "sound.h"

//========================================
// ÃIoÏé¾
//========================================
LPD3DXMESH CSpider::m_pMesh[TYPE_MAX][PARTS_MAX] = {};
LPD3DXBUFFER CSpider::m_pBuffMat[TYPE_MAX][PARTS_MAX] = {};
DWORD CSpider::m_nNumMat[TYPE_MAX][PARTS_MAX] = {};

//=============================================================================
// RXgN^
// Author : ã¡TV
//=============================================================================
CSpider::CSpider() :CCharacter(OBJTYPE::OBJTYPE_ENEMY)
{
    m_type = TYPE_YELLOW;
    m_move = DEFAULT_VECTOR;
    m_nScore = 0;
    m_nOrbs = 0;

    m_patrolCentralPos = DEFAULT_VECTOR;
    m_patrolDestPos = DEFAULT_VECTOR;
    m_nPatrolDistance = 0;
    m_nCntTime = 0;

    m_bWallRun = false;
    m_fSpeed = 0.0f;
    m_rotDest = DEFAULT_VECTOR;
    m_rotMin = DEFAULT_VECTOR;

    m_bWarning = false;
    m_fDiscoveryDistance = 0.0f;

    m_bAttack = false;
    m_attackAI = ATTACK_AI_WAIT;
}

//=============================================================================
// fXgN^
// Author : ã¡TV
//=============================================================================
CSpider::~CSpider()
{
}

//=============================================================================
// ú»
// Author : ó{ 
//=============================================================================
HRESULT CSpider::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // p[cðÝè
    SetPartNum(PARTS_MAX);

    for (int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        BindMesh(CCharacter::TRIBE_SPIDER, nCount, m_pMesh[m_type][nCount], m_pBuffMat[m_type][nCount], m_nNumMat[m_type][nCount]);
    }

    // ÀWEeqÖWÌÇÝÝ
    LoadModelData("./data/ANIMATION/motion_spider.txt");

    CCharacter::Init(pos, size);

    return S_OK;
}

//=============================================================================
// I¹
// Author : ã¡TV
//=============================================================================
void CSpider::Uninit(void)
{
    CCharacter::Uninit();
}

//=============================================================================
// XV
// Author : ã¡TV
//=============================================================================
void CSpider::Update(void)
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
            if (nRandNum <= SPIDER_DROP_HEAL_ITEM)
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
void CSpider::Movement(void)
{
    // ÊuÆü«ðæ¾
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    D3DXVECTOR3 rot = DEFAULT_VECTOR;
    pos = GetPos();
    rot = GetRot();

    // [VðÜ¸ÍÒ@É·é
    GetAnimation()->SetAnimation(ANIM_IDLE);

    // ñ]§ä
    rot = RotControl(rot);

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

    // nÊæèãÈç
    if (pos.y > 0.0f)
    {
        // dÍ
        m_move.y -= GRAVITY;
    }
    else
    {
        // ÇèÍµÄ¢È¢
        m_bWallRun = false;

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

                // qbgÊæÁÄAÇèÌdlðÏ¦é
                //=====================================================================================
                switch (blockHitInfo.hitSurface)
                {
                case HIT_SURFACE_TOP:

                    // ÇèÍµÄ¢È¢
                    m_bWallRun = false;

                    // dÍðl¶µÈ¢
                    m_move.y = 0.0f;

                    break;

                case HIT_SURFACE_LEFT:

                    // Çè
                    pos.y += m_fSpeed;
                    m_bWallRun = true;
                    m_move.y = 0.0f;

                    // X­
                    rot.x += SPIDER_TILT_SPEED;

                    // ü­ûüðÏ¦é
                    m_rotDest.y = D3DXToRadian(270.0f);

                    break;

                case HIT_SURFACE_BACK:

                    // Çè
                    pos.y += m_fSpeed;
                    m_bWallRun = true;
                    m_move.y = 0.0f;

                    // X­
                    rot.x += SPIDER_TILT_SPEED;

                    // ü­ûüðÏ¦é
                    m_rotDest.y = D3DXToRadian(0.0f);

                    break;

                case HIT_SURFACE_RIGHT:

                    // Çè
                    pos.y += m_fSpeed;
                    m_bWallRun = true;
                    m_move.y = 0.0f;

                    // X­
                    rot.x += SPIDER_TILT_SPEED;

                    // ü­ûüðÏ¦é
                    m_rotDest.y = D3DXToRadian(90.0f);

                    break;

                case HIT_SURFACE_FRONT:

                    // Çè
                    pos.y += m_fSpeed;
                    m_bWallRun = true;
                    m_move.y = 0.0f;

                    // X­
                    rot.x += SPIDER_TILT_SPEED;

                    // ü­ûüðÏ¦é
                    m_rotDest.y = D3DXToRadian(180.0f);

                    break;
                }
                //=====================================================================================
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

    // ÇèµÄ¢È¢Èç
    if (m_bWallRun == false)
    {
        // X«ð¼·
        rot.x -= SPIDER_TILT_SPEED;
    }

    // X«§À
    if (rot.x > SPIDER_TILT_LIMIT)
    {
        rot.x = SPIDER_TILT_LIMIT;
    }
    else if (rot.x < 0.0f)
    {
        rot.x = 0.0f;
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
void CSpider::UpdateCollisionPos(void)
{
    // ÌÌÊuæ¾
    D3DXVECTOR3 bodyPos = D3DXVECTOR3(GetParts(CSpider::PARTS_BODY)->GetWorldMtx()._41,
        GetParts(CSpider::PARTS_BODY)->GetWorldMtx()._42,
        GetParts(CSpider::PARTS_BODY)->GetWorldMtx()._43);

    //  ÌÊuæ¾
    D3DXVECTOR3 stomachPos = D3DXVECTOR3(GetParts(CSpider::PARTS_STOMACH_CUBE)->GetWorldMtx()._41,
        GetParts(CSpider::PARTS_STOMACH_CUBE)->GetWorldMtx()._42,
        GetParts(CSpider::PARTS_STOMACH_CUBE)->GetWorldMtx()._43);

    // EåÌÊuæ¾
    D3DXVECTOR3 rightFangPos = D3DXVECTOR3(GetParts(CSpider::PARTS_FANG_RIGHT)->GetWorldMtx()._41,
        GetParts(CSpider::PARTS_FANG_RIGHT)->GetWorldMtx()._42,
        GetParts(CSpider::PARTS_FANG_RIGHT)->GetWorldMtx()._43);

    // ¶åÌÊuæ¾
    D3DXVECTOR3 leftFangPos = D3DXVECTOR3(GetParts(CSpider::PARTS_FANG_LEFT)->GetWorldMtx()._41,
        GetParts(CSpider::PARTS_FANG_LEFT)->GetWorldMtx()._42,
        GetParts(CSpider::PARTS_FANG_LEFT)->GetWorldMtx()._43);

    // íÞ²ÆÉA½è»èÌÊuðXV
    switch (m_type)
    {
    case TYPE_YELLOW:
        SetCollisionPos(0, GetPos());
        break;
    case TYPE_BLACK:
        SetCollisionPos(0, bodyPos);
        SetCollisionPos(1, stomachPos);
        SetCollisionPos(2, rightFangPos);
        SetCollisionPos(3, leftFangPos);
        break;
    }
}

//=============================================================================
// ñ]§ä
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CSpider::RotControl(D3DXVECTOR3 rot)
{
    // Ô·ñ]Ê
    D3DXVECTOR3 returnRot = rot;

    // 1FOÆÀWªá¤Èç
    if (GetPosOld() != GetPos())
    {
        // à«É·é
        GetAnimation()->SetAnimation(ANIM_WALK);

        // 1FOÌÊuÆA»ÝÌÊuðärµApxðßé
        float fAngle = atan2((GetPosOld().x - GetPos().x), (GetPosOld().z - GetPos().z));

        // 1FOÆXÀWÜ½ÍZÀWªá¤Èç
        if (GetPosOld().x != GetPos().x || GetPosOld().z != GetPos().z)
        {
            // ÇèµÄ¢È¢Èç
            if (m_bWallRun == false)
            {
                // ß½pxðü­æ¤É·é
                m_rotDest.y = fAngle;
            }
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
            returnRot.y += (m_rotDest.y - returnRot.y) * SPIDER_TURN_SPEED;
        }
    }

    return returnRot;
}

//=============================================================================
// ñAI
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CSpider::PatrolAI(D3DXVECTOR3 pos)
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
        if (fDistance <= SPIDER_CONSIDER_CLOSE_DEST)
        {
            // JE^ðÁZ
            m_nCntTime++;

            // êèJE^ÅAÌÚInðßé
            if (m_nCntTime >= SPIDER_CHANGE_MOVE_IN_PATROL)
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
D3DXVECTOR3 CSpider::WarningAI(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // Ô·ü«
    D3DXVECTOR3 returnRot = rot;

    // vC[ÌÊuðæ¾
    D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPos();

    // UµÄ¢È¢©ÂAÇèµÄ¢È¢Èç
    if (m_bAttack == false && m_bWallRun == false)
    {
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
        // xúÈçA
        else
        {
            // vC[ÌÊuÆA©gÌÊuðärµApxðßé
            float fAngle = atan2((GetPos().x - playerPos.x), (GetPos().z - playerPos.z));

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
                returnRot.y += (m_rotDest.y - returnRot.y) * SPIDER_TURN_SPEED;
            }

            // vC[ÆÌ£ðªé
            float fDistance = sqrtf(
                powf((playerPos.x - pos.x), 2) +
                powf((playerPos.z - pos.z), 2));

            // £ð´¦½ç
            if (fDistance >= SPIDER_CONSIDER_AS_LONG)
            {
                // xúðð
                m_bWarning = false;
            }
        }
    }

    return returnRot;
}

//=============================================================================
// UAI
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CSpider::AttackAI(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // Ô·ÊuAÚ®Êðßé
    D3DXVECTOR3 returnPos = pos;
    D3DXVECTOR3 move = DEFAULT_VECTOR;

    // xúÈç
    if (m_bWarning == true)
    {
        switch (m_attackAI)
        {
        case ATTACK_AI_WAIT:

            // UµÄ¢È¢
            m_bAttack = false;

            // JE^Abv
            m_nCntTime++;

            // êèJE^Å
            if (m_nCntTime >= SPIDER_NEXT_ATTACK_COUNT)
            {
                // JE^Zbg
                m_nCntTime = 0;

                // _Éðßé
                int nRandNum = GetRandNum(SPIDER_NEXT_ATTACK_PERCENT_MAX, 1);

                // ½ÌUªÌp³ê½©ßé
                if (nRandNum >= 1 && nRandNum <= SPIDER_TAUNT_PERCENT)
                {
                    m_attackAI = ATTACK_AI_TAUNT;
                }
                else if (nRandNum > SPIDER_TAUNT_PERCENT && nRandNum <= SPIDER_TAUNT_PERCENT + SPIDER_ACID_PERCENT)
                {
                    m_attackAI = ATTACK_AI_ACID;
                }
                else if (nRandNum > SPIDER_TAUNT_PERCENT + SPIDER_ACID_PERCENT && nRandNum <= SPIDER_JUMP_PERCENT + SPIDER_TAUNT_PERCENT + SPIDER_ACID_PERCENT)
                {
                    m_attackAI = ATTACK_AI_JUMP;
                }
            }

            break;

        case ATTACK_AI_TAUNT:

            // §­àUÆÝÈ·
            m_bAttack = true;

            // JE^Abv
            m_nCntTime++;

            // Aj[Vð§­É
            GetAnimation()->SetAnimation(ANIM_TAUNT);

            // êèJE^Å
            if (m_nCntTime >= SPIDER_TAUNT_WHOLE_FRAME)
            {
                // JE^Zbg
                m_nCntTime = 0;

                // Ò@É·é
                m_attackAI = ATTACK_AI_WAIT;
            }

            break;

        case ATTACK_AI_ACID:

            // _òÎµÍUµÄ¢é
            m_bAttack = true;

            // JE^Abv
            m_nCntTime++;

            // Aj[VðUÉ
            GetAnimation()->SetAnimation(ANIM_ATTACK);

            // NGCgt[
            if (m_nCntTime == SPIDER_ACID_CREATE_FRAME)
            {
                SetAcidAttack(pos, rot);
            }

            // êèJE^Å
            if (m_nCntTime >= SPIDER_ACID_WHOLE_FRAME)
            {
                // JE^Zbg
                m_nCntTime = 0;

                // Ò@É·é
                m_attackAI = ATTACK_AI_WAIT;
            }

            break;

        case ATTACK_AI_JUMP:

            // WvÍUµÄ¢é
            m_bAttack = true;

            // JE^Abv
            m_nCntTime++;

            // ÇoèÅÈ¢Èç
            if (m_bWallRun == false)
            {
                // Aj[VðWvÉ
                GetAnimation()->SetAnimation(ANIM_JUMP);
            }

            // WvU
            returnPos = SetJumpAttack(pos, rot);

            // ñÌSÊuðÏ¦é
            m_patrolCentralPos = returnPos;

            // êèJE^Å
            if (m_nCntTime >= SPIDER_JUMP_WHOLE_FRAME)
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
// _òÎµU
// Author : ã¡TV
//=============================================================================
void CSpider::SetAcidAttack(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // vC[ÌÊuðæ¾
    D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPos();

    // vC[ÆÌ£ðªé
    float fDistance = sqrtf(
        powf((playerPos.x - pos.x), 2) +
        powf((playerPos.z - pos.z), 2));
    float fAngleY = 0.0f;

    // òÎ·pxâðAíÞÉæÁÄÏ¦é
    D3DXVECTOR3 moveAngle = DEFAULT_VECTOR;
    float fHorizontalAngle = 0.0f;
    switch (m_type)
    {
    case TYPE_YELLOW:

        // £É¶ÄA_ÉãÉòÎ·
        // ß£
        if (fDistance <= SPIDER_CONSIDER_AS_SHORT)
        {
            fAngleY = D3DXToRadian(float(GetRandNum(SPIDER_ACID_SHORT_MAX_ANGLE_Y, SPIDER_ACID_SHORT_MIN_ANGLE_Y)) / 100.0f);
        }
        // £
        else if (fDistance > SPIDER_CONSIDER_AS_SHORT && fDistance <= SPIDER_CONSIDER_AS_MEDIUM)
        {
            fAngleY = D3DXToRadian(float(GetRandNum(SPIDER_ACID_MEDIUM_MAX_ANGLE_Y, SPIDER_ACID_MEDIUM_MIN_ANGLE_Y)) / 100.0f);
        }
        // £
        else if (fDistance > SPIDER_CONSIDER_AS_MEDIUM)
        {
            fAngleY = D3DXToRadian(float(GetRandNum(SPIDER_ACID_LONG_MAX_ANGLE_Y, SPIDER_ACID_LONG_MIN_ANGLE_Y)) / 100.0f);
        }

        // Ú®pxðßé
        moveAngle = D3DXVECTOR3(-sinf(rot.y), fAngleY, -cosf(rot.y));

        // eðNGCg
        CBullet::Create(pos + SPIDER_ACID_ADD_SET_POS_Y, BULLET_ACID_COLLISION_SIZE, moveAngle, CBullet::TYPE_ACID, CBullet::TRIBE_ENEMY);

        break;

    case TYPE_BLACK:

        // ¡ÂòÎ·
        for (int nCnt = 0; nCnt < SPIDER_BLACK_ACID_NUMBER_ONCE; nCnt++)
        {
            // £É¶ÄA_ÉãÉòÎ·
            // ß£
            if (fDistance <= SPIDER_CONSIDER_AS_SHORT)
            {
                fAngleY = D3DXToRadian(float(GetRandNum(SPIDER_ACID_SHORT_MAX_ANGLE_Y, SPIDER_ACID_SHORT_MIN_ANGLE_Y)) / 100.0f);
            }
            // £
            else if (fDistance > SPIDER_CONSIDER_AS_SHORT && fDistance <= SPIDER_CONSIDER_AS_MEDIUM)
            {
                fAngleY = D3DXToRadian(float(GetRandNum(SPIDER_ACID_MEDIUM_MAX_ANGLE_Y, SPIDER_ACID_MEDIUM_MIN_ANGLE_Y)) / 100.0f);
            }
            // £
            else if (fDistance > SPIDER_CONSIDER_AS_MEDIUM)
            {
                fAngleY = D3DXToRadian(float(GetRandNum(SPIDER_ACID_LONG_MAX_ANGLE_Y, SPIDER_ACID_LONG_MIN_ANGLE_Y)) / 100.0f);
            }

            // ¡ÉgU³¹é
            if (nCnt == 1)
            {
                fHorizontalAngle = D3DXToRadian(float(GetRandNum(SPIDER_ACID_MAX_ANGLE_TO_SHIFT_FROM_CENTER, 0)) / 100.0f);
            }
            else if (nCnt == 2)
            {
                fHorizontalAngle = -D3DXToRadian(float(GetRandNum(SPIDER_ACID_MAX_ANGLE_TO_SHIFT_FROM_CENTER, 0)) / 100.0f);
            }

            // Ú®pxðßé
            moveAngle = D3DXVECTOR3(-sinf(rot.y + fHorizontalAngle), fAngleY, -cosf(rot.y + fHorizontalAngle));

            // eðNGCg
            CBullet::Create(pos + SPIDER_ACID_ADD_SET_POS_Y, BULLET_ACID_COLLISION_SIZE, moveAngle, CBullet::TYPE_ACID, CBullet::TRIBE_ENEMY);
        }

        break;
    }
}

//=============================================================================
// WvU
// Author : ã¡TV
//=============================================================================
D3DXVECTOR3 CSpider::SetJumpAttack(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // Ô·Êuðßé
    D3DXVECTOR3 returnPos = pos;

    // cÌÚ®ÊªÈ­ÈÁ½ç
    if (m_move.y == 0.0f)
    {
        // ÇoèÅÈ¢Èç
        if (m_bWallRun == false)
        {
            // Wv
            m_move.y += SPIDER_JUMP_VALUE;
        }
    }

    // üÄ¢éûüÉiÞ
    returnPos += D3DXVECTOR3(-sinf(rot.y) * m_fSpeed * SPIDER_JUMP_SPEED_RATE, 0.0f, -cosf(rot.y) * m_fSpeed* SPIDER_JUMP_SPEED_RATE);

    return returnPos;
}

//=============================================================================
// `æ
// Author : ã¡TV
//=============================================================================
void CSpider::Draw(void)
{
    CCharacter::Draw();
}

//=============================================================================
// ff[^ÇÝÝ
// Author : ó{ 
//=============================================================================
HRESULT CSpider::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_000_body.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_BODY], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_BODY], &m_pMesh[TYPE_YELLOW][PARTS_BODY]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_001_stomach.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_STOMACH], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_STOMACH], &m_pMesh[TYPE_YELLOW][PARTS_STOMACH]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_002_fang_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_FANG_RIGHT], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_FANG_RIGHT], &m_pMesh[TYPE_YELLOW][PARTS_FANG_RIGHT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_003_fang_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_FANG_LEFT], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_FANG_LEFT], &m_pMesh[TYPE_YELLOW][PARTS_FANG_LEFT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_004_leg_right_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_LEG_RIGHT_0], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_LEG_RIGHT_0], &m_pMesh[TYPE_YELLOW][PARTS_LEG_RIGHT_0]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_005_leg_right_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_LEG_RIGHT_1], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_LEG_RIGHT_1], &m_pMesh[TYPE_YELLOW][PARTS_LEG_RIGHT_1]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_006_leg_right_002.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_LEG_RIGHT_2], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_LEG_RIGHT_2], &m_pMesh[TYPE_YELLOW][PARTS_LEG_RIGHT_2]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_007_leg_right_003.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_LEG_RIGHT_3], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_LEG_RIGHT_3], &m_pMesh[TYPE_YELLOW][PARTS_LEG_RIGHT_3]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_008_leg_left_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_LEG_LEFT_0], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_LEG_LEFT_0], &m_pMesh[TYPE_YELLOW][PARTS_LEG_LEFT_0]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_009_leg_left_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_LEG_LEFT_1], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_LEG_LEFT_1], &m_pMesh[TYPE_YELLOW][PARTS_LEG_LEFT_1]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_010_leg_left_002.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_LEG_LEFT_2], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_LEG_LEFT_2], &m_pMesh[TYPE_YELLOW][PARTS_LEG_LEFT_2]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_011_leg_left_003.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_LEG_LEFT_3], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_LEG_LEFT_3], &m_pMesh[TYPE_YELLOW][PARTS_LEG_LEFT_3]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_012_cube.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_YELLOW][PARTS_STOMACH_CUBE], NULL, &m_nNumMat[TYPE_YELLOW][PARTS_STOMACH_CUBE], &m_pMesh[TYPE_YELLOW][PARTS_STOMACH_CUBE]);

    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_000_body.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_BODY], NULL, &m_nNumMat[TYPE_BLACK][PARTS_BODY], &m_pMesh[TYPE_BLACK][PARTS_BODY]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_001_stomach.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_STOMACH], NULL, &m_nNumMat[TYPE_BLACK][PARTS_STOMACH], &m_pMesh[TYPE_BLACK][PARTS_STOMACH]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_002_fang_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_FANG_RIGHT], NULL, &m_nNumMat[TYPE_BLACK][PARTS_FANG_RIGHT], &m_pMesh[TYPE_BLACK][PARTS_FANG_RIGHT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_003_fang_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_FANG_LEFT], NULL, &m_nNumMat[TYPE_BLACK][PARTS_FANG_LEFT], &m_pMesh[TYPE_BLACK][PARTS_FANG_LEFT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_004_leg_right_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_RIGHT_0], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_RIGHT_0], &m_pMesh[TYPE_BLACK][PARTS_LEG_RIGHT_0]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_005_leg_right_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_RIGHT_1], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_RIGHT_1], &m_pMesh[TYPE_BLACK][PARTS_LEG_RIGHT_1]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_006_leg_right_002.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_RIGHT_2], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_RIGHT_2], &m_pMesh[TYPE_BLACK][PARTS_LEG_RIGHT_2]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_007_leg_right_003.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_RIGHT_3], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_RIGHT_3], &m_pMesh[TYPE_BLACK][PARTS_LEG_RIGHT_3]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_008_leg_left_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_LEFT_0], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_LEFT_0], &m_pMesh[TYPE_BLACK][PARTS_LEG_LEFT_0]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_009_leg_left_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_LEFT_1], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_LEFT_1], &m_pMesh[TYPE_BLACK][PARTS_LEG_LEFT_1]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_010_leg_left_002.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_LEFT_2], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_LEFT_2], &m_pMesh[TYPE_BLACK][PARTS_LEG_LEFT_2]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_011_leg_left_003.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_LEFT_3], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_LEFT_3], &m_pMesh[TYPE_BLACK][PARTS_LEG_LEFT_3]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/spider/spider_012_cube.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_STOMACH_CUBE], NULL, &m_nNumMat[TYPE_BLACK][PARTS_STOMACH_CUBE], &m_pMesh[TYPE_BLACK][PARTS_STOMACH_CUBE]);

    return S_OK;
}

//=============================================================================
// ff[^jü
// Author : ó{ 
//=============================================================================
void CSpider::Unload(void)
{
    for (int nCntType = 0; nCntType < TYPE_MAX; nCntType++)
    {
        for (int nCount = 0; nCount < PARTS_MAX; nCount++)
        {
            if (m_pBuffMat[nCntType][nCount] != NULL)
            {
                m_pBuffMat[nCntType][nCount] = NULL;
            }

            if (m_nNumMat[nCntType][nCount] != NULL)
            {
                m_nNumMat[nCntType][nCount] = NULL;
            }

            if (m_pMesh[nCntType][nCount] != NULL)
            {
                m_pMesh[nCntType][nCount] = NULL;
            }
        }
    }
}

//=============================================================================
// CX^X¶¬
// Author : ã¡TV
//=============================================================================
CSpider * CSpider::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bWarning, TYPE type)
{
    // mÛ
    CSpider *pSpider = NULL;
    pSpider = new CSpider;

    // e³ÌîñðÝè
    pSpider->SetPos(pos);
    pSpider->SetRot(rot);
    pSpider->SetTribe(CCharacter::TRIBE_SPIDER);

    // ÇÝÞíÞÌÝè
    pSpider->m_type = type;

    // ú»(wåÍXP[2{)
    D3DXVECTOR3 scale = DEFAULT_SCALE;
    if (type == TYPE_BLACK)
    {
        scale = SPIDER_BLACK_SCALE;
    }
    pSpider->Init(pos, scale);

    // pg[ÌSÊuðL¯
    pSpider->m_patrolCentralPos = pos;

    // ÚWÊuðL¯
    pSpider->m_patrolDestPos = pos;

    // xú©Ç¤©ðø©çÑÂ¯é
    pSpider->m_bWarning = bWarning;

    // ^Cv²ÆÉAÅèÌlðRÃ¯
    switch (type)
    {
    case TYPE_YELLOW:

        pSpider->SetActiveCollisionSize(SPIDER_YELLOW_ACTIVE_COLLISION_SIZE);
        pSpider->SetLife(SPIDER_YELLOW_LIFE);
        pSpider->m_nScore = SPIDER_YELLOW_SCORE;
        pSpider->m_nOrbs = SPIDER_YELLOW_ORBS;
        pSpider->m_fSpeed = SPIDER_YELLOW_SPEED;
        pSpider->m_nPatrolDistance = SPIDER_YELLOW_PATROL_DISTANCE;
        pSpider->m_fDiscoveryDistance = SPIDER_YELLOW_DISCOVERY_DISTANCE;

        pSpider->SetCntCollision(SPIDER_YELLOW_COLLISION_MAX);
        pSpider->SetCollisionSize(0, SPIDER_YELLOW_BODY_COLLISION_SIZE);

        break;

    case TYPE_BLACK:

        pSpider->SetActiveCollisionSize(SPIDER_BLACK_ACTIVE_COLLISION_SIZE);
        pSpider->SetLife(SPIDER_BLACK_LIFE);
        pSpider->m_nScore = SPIDER_BLACK_SCORE;
        pSpider->m_nOrbs = SPIDER_BLACK_ORBS;
        pSpider->m_fSpeed = SPIDER_BLACK_SPEED;
        pSpider->m_nPatrolDistance = SPIDER_BLACK_PATROL_DISTANCE;
        pSpider->m_fDiscoveryDistance = SPIDER_BLACK_DISCOVERY_DISTANCE;

        pSpider->SetCntCollision(SPIDER_BLACK_COLLISION_MAX);
        pSpider->SetCollisionSize(0, SPIDER_BLACK_BODY_COLLISION_SIZE);
        pSpider->SetCollisionSize(1, SPIDER_BLACK_STOMACH_COLLISION_SIZE);
        pSpider->SetCollisionSize(2, SPIDER_BLACK_FANG_COLLISION_SIZE);
        pSpider->SetCollisionSize(3, SPIDER_BLACK_FANG_COLLISION_SIZE);

        break;
    }

    // ½è»èÌÊuðXV
    pSpider->UpdateCollisionPos();

    return pSpider;
}

//=============================================================================
// I[uðoÜ­
// Author : ã¡TV
//=============================================================================
void CSpider::ScatterOrbs(void)
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
void CSpider::DeathCrush(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // j¹
    CSound *pSound = CManager::GetSound();
    pSound->Play(CSound::LABEL_SE_BUG);

    // p[cÌÊuÆAfGtFNgÌíÞ
    D3DXVECTOR3 partsPos = DEFAULT_VECTOR;
    CModelEffect::TYPE modelEffectType = CModelEffect::TYPE_YELLOW_SPIDER_BODY;

    //==============================
    // Ì
    //==============================
    // Êu
    partsPos = D3DXVECTOR3(GetParts(CSpider::PARTS_BODY)->GetWorldMtx()._41,
        GetParts(CSpider::PARTS_BODY)->GetWorldMtx()._42,
        GetParts(CSpider::PARTS_BODY)->GetWorldMtx()._43);

    // íÞ
    switch (m_type)
    {
    case TYPE_YELLOW:
        modelEffectType = CModelEffect::TYPE_YELLOW_SPIDER_BODY;
        break;
    case TYPE_BLACK:
        modelEffectType = CModelEffect::TYPE_BLACK_SPIDER_BODY;
        break;
    }

    // GtFNgÌ­¶
    SetDeathCrushEffect(partsPos, rot, modelEffectType);

    //==============================
    //  
    //==============================
    // Êu
    partsPos = D3DXVECTOR3(GetParts(CSpider::PARTS_STOMACH)->GetWorldMtx()._41,
        GetParts(CSpider::PARTS_STOMACH)->GetWorldMtx()._42,
        GetParts(CSpider::PARTS_STOMACH)->GetWorldMtx()._43);

    // íÞ
    switch (m_type)
    {
    case TYPE_YELLOW:
        modelEffectType = CModelEffect::TYPE_YELLOW_SPIDER_STOMACH;
        break;
    case TYPE_BLACK:
        modelEffectType = CModelEffect::TYPE_BLACK_SPIDER_STOMACH;
        break;
    }

    // GtFNgÌ­¶
    SetDeathCrushEffect(partsPos, rot, modelEffectType);

    //==============================
    // «
    //==============================
    // íÞ
    switch (m_type)
    {
    case TYPE_YELLOW:
        modelEffectType = CModelEffect::TYPE_YELLOW_SPIDER_LEG;
        break;
    case TYPE_BLACK:
        modelEffectType = CModelEffect::TYPE_BLACK_SPIDER_LEG;
        break;
    }

    // «Ì{ªoÜ­
    for (int nCnt = 0; nCnt < SPIDER_MAX_LEG; nCnt++)
    {
        // GtFNgÌ­¶(«ÍS©ço·)
        SetDeathCrushEffect(pos, rot, modelEffectType);
    }
}

//=============================================================================
// âçê½Ì²ÓGtFNgÌ­¶
// Author : ã¡TV
//=============================================================================
void CSpider::SetDeathCrushEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelEffect::TYPE type)
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
    fSpeedY = float(GetRandNum(MODEL_EFFECT_SPIDER_SPLATTER_FORCE_MAX, MODEL_EFFECT_SPIDER_SPLATTER_FORCE_MIN)) / 100.0f;
    fSpeedZ = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_Z, 0)) / 100.0f;
    fRotSpeedX = float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f - float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f;
    fRotSpeedY = float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f - float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f;
    fRotSpeedZ = float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f - float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f;
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
void CSpider::WarnFellow(void)
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

            // GÌí°ªwåÈç
            if (pEnemy->GetTribe() == CCharacter::TRIBE_SPIDER)
            {
                // ÎÛÌÊu
                D3DXVECTOR3 targetPos = pEnemy->GetPos();

                // ÎÛÆÌ£
                float fDistance = sqrtf(
                    powf((targetPos.x - GetPos().x), 2) +
                    powf((targetPos.z - GetPos().z), 2));

                // ÎÛÆÌ£ªAÔÉx·éÆ«ÌÍÍàÈç
                if (fDistance <= SPIDER_WARN_SPIDER_DISTANCE)
                {
                    // XpC_[^ÉLXg
                    CSpider*pSpider = (CSpider*)pEnemy;

                    // ÇèµÄ¢È¢Èç
                    if (pSpider->GetWallRun() == false)
                    {
                        // xúÉ
                        pSpider->SetWarning(true);
                    }
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
void CSpider::AddMissionClear(void)
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
            CGame::SetClearNumMission1();
            break;

        case CGame::CURRENT_MISSION_2:

            break;
        }

        break;

    case CGame::STAGE_2:

        break;

    case CGame::STAGE_FINAL:

        break;
    }
}