
#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
        object who = me;
        string type, result;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( arg && !( who = find_any_char(arg) ) ) 
        {
                notify( "您无法找到这个人。" );
		return 1;
        }

        if( who->is_npc() )
                result = sprintf( "军队：%s\n", who->get_name() );
        else    result = sprintf( "军队：%s(%d)\n", who->get_name(), who->get_number() );

        switch( who->get_army_type() )
        {
      default : type = "步兵";  break;
       case 1 : type = "弓兵";  break;
       case 2 : type = "车兵";  break;
        }

        result += sprintf( "兵种：%-4s  数量：%4d  装备：%4d  训练：%4d  士气：%4d  机动：%4d", type, 
                who->get_army_amount(), who->get_army_armor(), who->get_army_train(), 
                who->get_army_morale(), who->get_army_power() );

        tell_user(me, result);

        return 1;
}
