
#include <ansi.h>

#define DEFAULT_TIME    10080                   // 缺省封闭一周
#define CHANNEL_LOG     "gm/channel.txt"        // 频道管理日志

// 函数：命令处理
int main( object me, string arg )
{
        object who;
        string cmd1, cmd2, cmd3;
        string id, channel;
        int min, t, n;

        if( is_player(me) && !me->get_save("channel_manager") ) 
        {
                notify( "您不是频道管理员。" );
		return 1;
        }

        if( !arg )
        {
                id = "?";  channel = "?";  min = -1;
        }
        else if( sscanf( arg, "%s %s %d", id, channel, min ) != 3 )
	{
                min = DEFAULT_TIME;
                if( sscanf( arg, "%s %s", id, channel ) != 2 )
                {
                        id = arg;  channel = "";
                }
	}

        if( id == "?" )
        {
                send_user( me, "%c%c%d%s", '?', 1, 0, sprintf( "Phong bế kênh. \n\nHãy nhập số ID :\n"
                        ESC "shutup %%s %s %d\n", channel, min ) );
                return 1;
        }
        if( !( who = find_player(id) ) ) 
        {
                notify( "Không tìm thấy người này." );
                return 1;
        }
        if( !is_player(who) )
        {
                notify( "您只能封闭玩家的频道。" );
                return 1;
        }
        if( who->get_save("channel_manager") ) 
        {
                notify( "Đối phương là Quản lý viên." );
		return 1;
        }

        if( channel == "?" )
        {
                cmd1 = sprintf( "shutup %s chat %d\n", id, min );
                cmd2 = sprintf( "shutup %s rumor %d\n", id, min );
                cmd3 = sprintf( "shutup %s\n", id );
                send_user( me, "%c%s", ':', sprintf( "Ngươi muốn phong bế %s(%d) kênh nào ?\n", who->get_name(), who->get_number() ) +
                        ESC "Kênh Thế Giới.\n" + cmd1 +
                        ESC "Kênh Lời Đồn.\n" + cmd2 +
                        ESC "Xem xét tình huống phong bế kênh.\n" + cmd3 +
                        ESC "Ta suy nghĩ đã……\nCLOSE\n" );
                return 1;
        }

        if( min < 0 )
        {
                send_user( me, "%c%c%d%s", '?', 1, DEFAULT_TIME, sprintf( "Phong bế %s(%d) kênh \n\nHãy nhập số phút muốn phong bế:\n"
                        ESC "shutup %s %s %%s\n", who->get_name(), who->get_number(), id, channel ) );
                return 1;
        }
        if( min < 1 || min > DEFAULT_TIME ) min = DEFAULT_TIME;

        t = gone_time( who->get_chblk("time") );
        if( !channel || channel == "" ) 
        {
                if( ( n = who->get_chblk("chat") - t ) > 0 ) 
                        tell_user( me, "%s bị phong bế kênh Thế Giới %d phút.", who->get_name(), n / 60 + 1 );
                else    tell_user( me, who->get_name() + " Kênh Thế Giới : mở ra." );
                if( ( n = who->get_chblk("rumor") - t ) > 0 ) 
                        tell_user( me, "%s bị phong bế kênh Lời Đồn %d phút.", who->get_name(), n / 60 + 1 );
                else    tell_user( me, who->get_name() + " Kênh Lời Đồn : mở ra." );
        } 
        else if( channel == "chat" )
        {
                if( ( n = who->get_chblk("chat") - t ) > 0 ) 
                        tell_user( me, "%s đã bị phong bế kênh Thế Giới %d phút.", who->get_name(), n / 60 + 1 );
                else 
                {
                        tell_user( me, "%s bị phong bế kênh Thế Giới %d phút.", who->get_name(), min );
                        if( who->get_chblk("rumor") )
                        {
                                if( who->add_chblk("rumor", -t ) < 1 ) 
                                        who->delete_chblk("rumor");
//                              else    who->set_chblk("time", time() );
                        }
                        who->set_chblk("chat", min * 60 );
                        who->set_chblk("time", time() );
//                      who->save();

                        CHAT_D->chat_channel( 0, sprintf( HIC "Quản lý viên %s(%d) phong bế kênh Thế Giới của %s(%d) %d phút.", 
                                me->get_name(), me->get_number(), who->get_name(), who->get_number(), min ) );
                        log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s Phong bế %s(%d) kênh %s %d phút.\n", 
                                short_time(), me->get_name(), me->get_number(), me->get_id(),
                                who->get_name(), who->get_number(), who->get_id(), min ) );
                }
        }
        else if( channel == "rumor" )
        {
                if( ( n = who->get_chblk("rumor") - t ) > 0 ) 
                        tell_user( me, "%s bị phong bế kênh Lời Đồn %d phút.", who->get_name(), n / 60 + 1 );
                else 
                {
                        tell_user( me, "%s bị phong bế kênh Lời Đồn %d phút.", who->get_name(), min );
                        if( who->get_chblk("chat") )
                        {
                                if( who->add_chblk("chat", -t ) < 1 ) 
                                        who->delete_chblk("chat");
//                              else    who->set_chblk("time", time() );
                        }
                        who->set_chblk("rumor", min * 60 );
                        who->set_chblk("time", time() );
//                      who->save();

//                        CHAT_D->rumor_channel( 0, sprintf( HIM "管理员%s(%d)封闭%s(%d)的谣言频道 %d 分钟。", 
//                                me->get_name(), me->get_number(), who->get_name(), who->get_number(), min ) );
                        log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 封闭 %s(%d)%s 的 rumor 频道 %d 分钟。\n", 
                                short_time(), me->get_name(), me->get_number(), me->get_id(),
                                who->get_name(), who->get_number(), who->get_id(), min ) );
                }
        }
        else 
        {
                notify( "您能封闭的频道有：chat, rumor" );
		return 1;
        }

        return 1;
}
