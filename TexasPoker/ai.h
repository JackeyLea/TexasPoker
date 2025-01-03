////////////
/// \author JackeyLea
/// \date 2025.01.02
/// \note AI类 根据记录的每一步的操作作出动作判断
////////////

#ifndef AI_H
#define AI_H

#include "card.h"

#include <QPair>

class AI
{
public:
    AI(uint bb,bool isNoLimit);

    void setTableInfo(TableInfo &tInfo);

    /// 获取机器人下一步动作
    /// \brief getNextAction
    /// \return
    ///
    QPair<int,int> getNextAction();

private:
    TableInfo m_sTInfo;//牌桌信息

    uint m_unBB;//盲注
    bool m_bNoLimit;//是否无限加注
};

#endif // AI_H
