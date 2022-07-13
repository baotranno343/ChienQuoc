
#include <ansi.h>

#define DEFAULT_TIME    43200                   // 缺省封闭一个月
#define CHANNEL_LOG     "gm/channel.txt"        // 频道管理日志

// 函数：命令处理
int main( object me, string arg )
{
        object who;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6;
        string id, channel;
        int min, t, n;

        if( is_player(me) ) 
        {
                notify( "Không đủ quyền hạn" );
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
                send_user( me, "%c%c%d%s", '?', 1, 0, sprintf( "Kênh quản lý\n\nHãy nhập vào ID :\n"
                        ESC "channel %%s %s %d\n", channel, min ) );
                return 1;
        }
        if( !( who = find_player(id) ) ) 
        {
                notify( "Không tìm thấy người này" );
                return 1;
        }
/*        if( !is_player(who) )
        {
                notify( "您只能封闭玩家的频道。" );
                return 1;
        }*/

        if( channel == "?" )
        {
                cmd1 = sprintf( "channel %s all %d\n", id, min );
                cmd2 = sprintf( "channel %s chat %d\n", id, min );
                cmd3 = sprintf( "channel %s rumor %d\n", id, min );
                cmd4 = sprintf( "channel %s vipchat %d\n", id, min );
                cmd5 = sprintf( "channel %s\n", id );
				cmd6 = sprintf( "channel %s tlta %d\n", id, min );
                send_user( me, "%c%s", ':', sprintf( "Bạn muốn để ý %s(%d) kênh?\n", who->get_name(), who->get_number() ) +
                        ESC "Quản lý tất cả các kênh\n" + cmd1 +
                        ESC "Quản lý kênh thế giới\n" + cmd2 +
                        ESC "Quản lý kênh tán gẫu\n" + cmd3 +
                        ESC "Quản lý kênh vip\n" + cmd4 +
                        ESC "Phong bế kênh\n" + cmd5 +
                        ESC "Phong bế Thiên Lý Truyền Âm\n" + cmd6 +
                        ESC "Suy nghĩ đã...\nCLOSE\n" );
                return 1;
        }

        if( min < 0 )
        {
                send_user( me, "%c%c%d%s", '?', 1, DEFAULT_TIME, sprintf( "Phong bế %s(%d) kênh\n\nhãy đưa vào số phút muốn phong bế(0 là mở lại kênh)\n"
                        ESC "channel %s %s %%s\n", who->get_name(), who->get_number(), id, channel ) );
                return 1;
        }
        if( min < 0 || min > DEFAULT_TIME ) min = DEFAULT_TIME;

        t = gone_time( who->get_chblk("time") );
        if( !channel || channel == "" )
        {
                if( ( n = who->get_chblk("chat") - t ) > 0 ) 
                        tell_user( me, "%s bị phong bế kênh Thế Giới %d phút", who->get_name(), n / 60 + 1 );
                else    tell_user( me, who->get_name() + "kênh Thế Giới : mở ra" );
                if( ( n = who->get_chblk("rumor") - t ) > 0 ) 
                        tell_user( me, "%s bị phong bế kênh Tán Gẫu %d phút", who->get_name(), n / 60 + 1 );
                else    tell_user( me, who->get_name() + "kênh Tán Gẫu : mở ra" );
                if( ( n = who->get_chblk("vipchat") - t ) > 0 ) 
                        tell_user( me, "%s bị phong bế kênh VIP %d phút", who->get_name(), n / 60 + 1 );
                else    tell_user( me, who->get_name() + "kênh VIP : mở ra" );
        } 
        else if( channel == "all" )
        {
                if( min )
                {
                        tell_user( me, "%s tất cả kênh bị phong bế %d phút", who->get_name(), min );
                        who->set_chblk("chat", min * 60 );
                        who->set_chblk("rumor", min * 60 );
                        who->set_chblk("family", min * 60 );
                        who->set_chblk("say", min * 60 );
                        who->set_chblk("city", min * 60 );
                        who->set_chblk("vipchat", min * 60 );
                        who->set_chblk("time", time() );
                        who->set_save("nomail", time()+min*60);
//                      who->save();

//                        CHAT_D->chat_channel( 0, sprintf( HIC "游戏管理员ＧＭ封闭%s(%d)的所有频道 %d 分钟。", 
//                                who->get_name(), who->get_number(), min ) );
//                        CHAT_D->rumor_channel( 0, sprintf( HIM "游戏管理员ＧＭ封闭%s(%d)的谣言频道 %d 分钟。", 
//                                who->get_name(), who->get_number(), min ) );
                        log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 封闭 %s(%d)%s 的全部频道 %d 分钟。(ＧＭ)\n", 
                                short_time(), me->get_name(), me->get_number(), me->get_id(),
                                who->get_name(), who->get_number(), who->get_id(), min ) );
                }
                else
                {
                        tell_user( me, who->get_name() + " tất cả kênh mở ra" );
                        who->delete_chblk("chat");
                        who->delete_chblk("rumor");
                        who->delete_chblk("say");
                        who->delete_chblk("city");
                        who->delete_chblk("family");
                        who->delete_chblk("vipchat");
                        who->delete_chblk("time");
                        who->set_save("nomail", 0);
//                      who->save();

//                        CHAT_D->chat_channel( 0, sprintf( HIC "游戏管理员ＧＭ打开%s(%d)的所有频道。", 
//                              who->get_name(), who->get_number() ) );
//                        CHAT_D->rumor_channel( 0, sprintf( HIM "游戏管理员ＧＭ打开%s(%d)的谣言频道。", 
//                                who->get_name(), who->get_number() ) );
                        log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 打开 %s(%d)%s 的全部频道。(ＧＭ)\n", 
                                short_time(), me->get_name(), me->get_number(), me->get_id(),
                                who->get_name(), who->get_number(), who->get_id() ) );
                }
        }
		else if( channel == "tlta" )
        {
                if( min )
                {
                        tell_user( me, "%s đã bị phong bế Thiên Lý Truyền Âm vĩnh viễn", who->get_name() );
						who->set_save("camtlta", 1);
                }
                else
                {
                        tell_user( me, who->get_name() + " đã giải phong bế Thiên Lý Truyền Âm" );
						who->set_save("camtlta", 0);
                }
        }
        else if( channel == "chat" )
        {
                if( min )
                {
                        if( ( n = who->get_chblk("chat") - t ) > 0 ) 
                                tell_user( me, "%s kênh Thế Giới đã bị phong bế %d phút", who->get_name(), n / 60 + 1 );
                        else 
                        {
                                tell_user( me, "%s kênh Thế Giới bị phong bế %d phút", who->get_name(), min );
                                if( who->get_chblk("rumor") )
                                {
                                        if( who->add_chblk("rumor", -t ) < 1 ) 
                                                who->delete_chblk("rumor");
                                }
                                if( who->get_chblk("vipchat") )
                                {
                                        if( who->add_chblk("vipchat", -t ) < 1 ) 
                                                who->delete_chblk("vipchat");
                                }
                                who->set_chblk("chat", min * 60 );
                                who->set_chblk("time", time() );

                                log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 封闭 %s(%d)%s 的 chat 频道 %d 分钟。(ＧＭ)\n", 
                                        short_time(), me->get_name(), me->get_number(), me->get_id(),
                                        who->get_name(), who->get_number(), who->get_id(), min ) );
                        }
                }
                else
                {
                        if( !who->get_chblk("chat") ) 
                                tell_user( me, who->get_name() + "kênh Thế Giới đã mở ra" );
                        else 
                        {
                                tell_user( me, who->get_name() + "kênh Thế Giới đã mở ra" );
                                who->delete_chblk("chat");

                                log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 打开 %s(%d)%s 的 chat 频道。(ＧＭ)\n", 
                                        short_time(), me->get_name(), me->get_number(), me->get_id(),
                                        who->get_name(), who->get_number(), who->get_id() ) );
                        }
                }
        }
        else if( channel == "rumor" )
        {
                if( min )
                {
                        if( ( n = who->get_chblk("rumor") - t ) > 0 ) 
                                tell_user( me, "%s kênh Tán Gẫu đã bị phong bế %d phút", who->get_name(), n / 60 + 1 );
                        else 
                        {
                                tell_user( me, "%s kênh Tán Gẫu bị phong bế %d phút", who->get_name(), min );
                                if( who->get_chblk("chat") )
                                {
                                        if( who->add_chblk("chat", -t ) < 1 ) 
                                                who->delete_chblk("chat");;
                                }
                                if( who->get_chblk("vipchat") )
                                {
                                        if( who->add_chblk("vipchat", -t ) < 1 ) 
                                                who->delete_chblk("vipchat");
                                }
                                who->set_chblk("rumor", min * 60 );
                                who->set_chblk("time", time() );
//                              who->save();

//                                CHAT_D->rumor_channel( 0, sprintf( HIM "游戏管理员ＧＭ封闭%s(%d)的谣言频道 %d 分钟。", 
//                                        who->get_name(), who->get_number(), min ) );
                                log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 封闭 %s(%d)%s 的 rumor 频道 %d 分钟。(ＧＭ)\n", 
                                        short_time(), me->get_name(), me->get_number(), me->get_id(),
                                        who->get_name(), who->get_number(), who->get_id(), min ) );
                        }
                }
                else
                {
                        if( !who->get_chblk("rumor") ) 
                                tell_user( me, who->get_name() + "kênh Tán Gẫu mở ra" );
                        else 
                        {
                                tell_user( me, who->get_name() + "kênh Tán Gẫu mở ra" );
                                who->delete_chblk("rumor");

                                log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 打开 %s(%d)%s 的 rumor 频道。(ＧＭ)\n", 
                                        short_time(), me->get_name(), me->get_number(), me->get_id(),
                                        who->get_name(), who->get_number(), who->get_id() ) );
                        }
                }
        }
        else if(channel == "vipchat")
        {
        	if( min )
                {
                        if( ( n = who->get_chblk("vipchat") - t ) > 0 ) 
                                tell_user( me, "%s kênh VIP đã bị phong bế %d phút", who->get_name(), n / 60 + 1 );
                        else 
                        {
                                tell_user( me, "%s kênh VIP bị phong bế %d phút", who->get_name(), min );
                                if( who->get_chblk("chat") )
                                {
                                        if( who->add_chblk("chat", -t ) < 1 ) 
                                                who->delete_chblk("chat");
                                }
                                if( who->get_chblk("rumor") )
                                {
                                        if( who->add_chblk("rumor", -t ) < 1 ) 
                                                who->delete_chblk("rumor");
                                }
                                who->set_chblk("vipchat", min * 60 );
                                who->set_chblk("time", time() );

                                log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 封闭 %s(%d)%s 的 vipchat 频道 %d 分钟。(ＧＭ)\n", 
                                        short_time(), me->get_name(), me->get_number(), me->get_id(),
                                        who->get_name(), who->get_number(), who->get_id(), min ) );
                        }
                }
                else
                {
                        if( !who->get_chblk("vipchat") ) 
                                tell_user( me, who->get_name() + "kênh VIP mở ra" );
                        else 
                        {
                                tell_user( me, who->get_name() + "kênh VIP mở ra" );
                                who->delete_chblk("vipchat");

                                log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 打开 %s(%d)%s 的 VIP 频道。(ＧＭ)\n", 
                                        short_time(), me->get_name(), me->get_number(), me->get_id(),
                                        who->get_name(), who->get_number(), who->get_id() ) );
                        }
                }
        }
        else 
        {
                notify( "Những kênh có thể phong bế : chat, rumor,vipchat" );
		return 1;
        }

        return 1;
}
