
#include <ansi.h>

#define MANAGER_LOG     "gm/manager.txt"        // 任命管理员日志

// 函数：命令处理
int main( object me, string arg )
{
        object who;
        string cmd1, cmd2, result;
        string flag, id;

        if( me != this_player(1) || !is_god(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg || sscanf(arg, "%s %s", flag, id) != 2 )
        {
                flag = "?";  id = "?";
        }

        if( flag != "+" && flag != "-" )
        {
                cmd1 = sprintf( "manager + %s\n", id );
                cmd2 = sprintf( "manager - %s\n", id );
                
                if( who = find_player(id) )
                        result = sprintf( "您想对玩家%s(%d)做：\n", who->get_name(), who->get_number() );
                else    result = "您想：\n";

                send_user( me, "%c%s", ':', result + 
                        ESC "任命频道管理员。\n" + cmd1 +
                        ESC "撤销频道管理员。\n" + cmd2 +
                        ESC "我再想想……\nCLOSE\n" );
                return 1;
        }

        if( id == "?" )
        {
                send_user( me, "%c%c%d%s", '?', 1, 0, sprintf("%s频道管理员，请输入对方的数字ＩＤ：\n"
                        ESC "manager %s %%s\n", flag == "+" ? "任命" : "撤销", flag) );
                return 1;
        }
        if( !( who = find_player(id) ) ) 
        {
                notify( "您找不到这位玩家。" );
                return 1;
        }

        switch( flag )
        {
     case "+" : who->set_save("channel_manager", 1);
                tell_user(me, "您委任%s(%d)担当频道管理员。", who->get_name(), who->get_number() );
                tell_user(who, "%s(%d)委任您担当频道管员。", me->get_name(), me->get_number() );
                log_file( MANAGER_LOG, sprintf("%s %s(%d)%s 委任 %s(%d)%s 担当频道管理员。\n", 
                        short_time(), me->get_name(), me->get_number(), me->get_id(), 
                        who->get_name(), who->get_number(), who->get_id() ) );
                break;

      default :
     case "-" : who->delete_save("channel_manager");
                tell_user(me, "您免去%s(%d)频道管理员职务。", who->get_name(), who->get_number() );
                tell_user(who, "%s(%d)免去您频道管员职务。", me->get_name(), me->get_number() );
                log_file( MANAGER_LOG, sprintf("%s %s(%d)%s 免去 %s(%d)%s 频道管理员职务。(╳)\n", 
                        short_time(), me->get_name(), me->get_number(), me->get_id(), 
                        who->get_name(), who->get_number(), who->get_id() ) );
                break;
        }

        return 1;
}
