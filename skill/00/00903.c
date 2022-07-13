
#include <ansi.h>
#include <equip.h>
#include <skill.h>

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *team, item;

        if( !objectp(who) ) return 1;

        if( me->get("pending_fly") != who ) return 1;    // 自己没记录(玩家乱发，或有其他人对你用)

        if( !arrayp( team = who->get("pending_fly") ) || member_array(me, team) == -1 ) return 1;    // 主人没记录

        me->delete("pending_fly");
        who->set( "pending_fly", team - ({ who, 0 }) );

        if(     objectp( item = who->get_equip(HAND_TYPE) )    // 法宝
        &&      item->get_talisman_type() == 4    // 灵犀环
        &&      item->get_lasting() >= 100 )    // 耐久度
        {
                if( random(100) < item->get_active_rate() ) 
                        item->accept_use_effect_2(who, me);    // 成功率
                else
                {
                        write_user( me, ECHO "%s đã được bạn sử dụng " HIY "Linh Tê Hoàn" ECHO " triệu hồi tới.", who->get_name() );
                        write_user( who, ECHO "Bạn đã được %s sử dụng " HIY "Linh Tê Hoàn" ECHO " triệu hồi tới.", me->get_name() );
                }

                item->add_lasting(-100);    // 使用减少耐久
        }

        return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_CHAR_7; }
