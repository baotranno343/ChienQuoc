
#include <ansi.h>

// 函数:命令处理
int main( object me, string arg )
{   
        int id;

        id = to_int(arg);

        if( me->get_save_2("Newbie.Login") )    // 新手场景提示
                QUEST_TIPS->send_newbie_tips( me, sprintf("%d", id) );
        else if( id >= 200 )    // 场景公用提示，放在 200～255
                QUEST_TIPS->send_common_tips( me, sprintf("%d", id) );
        else    QUEST_TIPS->send_map_tips( me, sprintf("%d", id) );

        return 1;
}
