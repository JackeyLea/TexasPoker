#include "ai.h"


AI::AI(uint bb, bool isNoLimit)
    :m_unBB(bb)
    ,m_bNoLimit(isNoLimit)
{
    //NOTHING
}

void AI::setTableInfo(TableInfo &tInfo)
{
    m_sTInfo = tInfo;
}

QPair<int, int> AI::getNextAction()
{
    QPair<int, int> result;

    switch(m_sTInfo.eGameFlow){
    case NotStart:
        //不需要处理
        break;
    case Perflop:
    {
        //此时处于发底牌阶段
        {
            switch(m_sTInfo.eBetFlow){
            case NoBet:
                //此时是底牌发完，准备开始下注，从小盲注开始下注
                //先找小盲注，可能有用户弃牌
                break;
            }
        }
        break;
    }
    }

    return result;
}
