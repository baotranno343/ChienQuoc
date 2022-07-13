// ministry of resident 户籍官

#include <ansi.h>
#include <city.h>

#define DEFAULT_TIME    10080                   // 缺省封闭一周
#define CHANNEL_LOG     "gm/channel.txt"        // 频道管理日志

// 函数：对话处理
void do_look( object who, object me )
{
        string name1, name2;
        string cmd1, cmd2;
        int id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if( stringp(name1) && stringp(name2) && name1 == name2 )
        {
                if( who->get_id() == me->get_master() || who->get_id() == me->get_master_2() || who->get_id() == me->get_master_3() )
                {
                        cmd1 = sprintf( "talk %x# shutup.?.-1\n", id );
                        cmd2 = sprintf( "talk %x# shutup.?.0\n", id );
                        send_user( who, "%c%s", ':', me->get_name() + "：\n    " + "/quest/word"->get_country_word(me) + "\n    " + who->get_name() + "阁下，您有什么事情？\n" 
                                ESC "封闭居民的城市频道.(消耗 10 体力)\n" + cmd1 +
                                ESC "打开居民的城市频道.(消耗 10 体力)\n" + cmd2 +
                                ESC "离开.\nCLOSE\n" );
                }
                else
                {
                        cmd1 = sprintf( "talk %x# leave.?\n", id );
                        send_user( who, "%c%s", ':', sprintf( " %s :\n " + "/quest/word"->get_country_word(me) + "\n " + who->get_name() + " , người có việc gì?\n" 
                                ESC "Rời khỏi " + name2 + " .\n" + cmd1 +
                                ESC "Rời khỏi.\nCLOSE\n", me->get_name() ) );
                }
        }
        else
        {
                cmd1 = sprintf( "talk %x# enter.?\n", id );
                send_user( who, "%c%s", ':', sprintf( " %s :\n " + "/quest/word"->get_country_word(me) + "\n Ta là Hộ Tịch Quan của thành, ngươi có việc gì ?\n" 
                        ESC "Gia nhập " + name2 + " .\n" + cmd1 +
                        ESC "Rời khỏi.\nCLOSE\n", me->get_name() ) );
        }
}

// 函数：加入户籍
void do_enter( object who, object me, string arg )
{
        object city;
        string name1, name2;
        string cmd;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if( stringp(name1) && name1 != "" )
        {
                if( name1 == name2 )
                {
                        send_user( who, "%c%s", '!', "您已经是" + name1 + "户籍了." );
                }
                else
                {
                        send_user( who, "%c%s", ':', sprintf( " %s :\n Hộ tịch của ngươi vẫn còn ở %s , xóa bỏ rồi quay lại.\n", me->get_name(), name1 ) );
                }
        }
        else if( arg == "?" )
        {
                cmd = sprintf( "talk %x# enter\n", getoid(me) );
                send_user( who, "%c%s", ':', "Bạn xác nhận muốn gia nhập " + name1 + " phải không ？\n" 
                        ESC "Đúng vậy\n" + cmd +
                        ESC "Ta còn suy nghĩ....\nCLOSE\n" );
        }
        else if( city = CITY_D->get_city_object(me) )
        {
                who->set_city_name(name2);
                who->set_city_position(1);
                who->set_city_time( time() );
                who->log_legend( sprintf("Bạn gia nhập %s.", name2) );
                send_user( who, "%c%s", ':', sprintf( "%s：\nHoan nghênh bạn trở thành phần tử của %s !\n", me->get_name(), name2 ) );

                who->set_contribute(0);    // 清除贡献，以防 BUG
                who->set_save( "salary", city->get_save("day") );    // 标记今天
        }
}

// 函数：放弃户籍
void do_leave( object who, object me, string arg )
{
        object city;
        string name1, name2;
        string cmd;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if( !stringp(name1) || name1 == "" )
        {
                send_user( who, "%c%s", '!', "您没加入任何国家." );
                return;
        }
        if( name1 != name2 )
        {
                send_user( who, "%c%s", '!', "对不起，您的户籍在" + name1 + "." );
                return;
        }

        if( who->get_id() == me->get_master() || who->get_id() == me->get_master_2() || who->get_id() == me->get_master_3() )
        {
                send_user( who, "%c%s", '!', "您有职务在身，不能放弃户籍." );
                return;
        }
        if( who->get_org_name() && who->get_org_name() != "" )
        {
                send_user( who, "%c%s", '!', "您加入了本地帮派，不能放弃户籍." );
                return;
        }

        if(     objectp( city = CITY_D->get_city_object(who) )
        &&      city->get_save_2( sprintf( "elect.id.%d", who->get_number() ) ) )
        {
                send_user( who, "%c%s", '!', "您参加了竞选，不能放弃户籍." );
                return;
        }

        if( arg == "?" )
        {
                cmd = sprintf( "talk %x# leave\n", getoid(me) );
                send_user( who, "%c%s", ':', "Bạn xác nhận phải thoát khỏi " + name1 + " phải không ？\n" 
                        ESC "Đồng ý\n" + cmd +
                        ESC "Ta còn suy nghĩ\nCLOSE\n" );
        }
        else if( city = CITY_D->get_city_object(me) )
        {
                who->set_city_name(0);
                who->set_city_position(0);
                who->set_city_time( time() );

                name2 = who->get_occupation();
                if( name2 && member_array( name2, ({ JOB_SCHOLAR, JOB_ACTOR }) ) != -1 ) who->set_occupation("");

                who->log_legend( sprintf("Bạn rời khỏi %s.", name1) );
                send_user( who, "%c%s", ':', sprintf( "%s：\nHộ tịch của bạn đã bị gạch bỏ, hiện tại bạn và %s không còn quan hệ !\n", me->get_name(), name1 ) );

                who->set_contribute(0);    // 清除贡献，以防 BUG
                who->set_save( "salary", city->get_save("day") );    // 标记今天
        }
}

// 函数：频道管理
void do_shutup( object who, object me, string arg )
{
        object player;
        string id, name1, name2, name3;
        int min;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&    ( who->get_id() == me->get_master() || who->get_id() == me->get_master_2() || who->get_id() == me->get_master_3() ) )
        {
                if( sscanf( arg, "%s.%d", id, min ) == 2 )
                {
                        if( id == "?" )
                        {
                                send_user( who, "%c%c%d%s", '?', 1, 0, sprintf( "%s频道管理，请输入对方的数字ＩＤ：\n"
                                        ESC "talk %x# shutup.%%s.%d\n", name1, getoid(me), min ) );
                                return;
                        }

                        if( who->get_strength() < 10 )
                        {
                                send_user(who, "%c%s", '!', "管理频道要 10 点体力.");
                                return;
                        }
                        if( !( player = find_player(id) ) ) 
                        {
                                send_user( who, "%c%s", '!', "您找不到这位玩家." );
                                return;
                        }
                        if( !is_player(player) ) 
                        {
                                send_user( who, "%c%s", '!', "您只能管理居民的频道." );
                                return;
                        }
                        if( !stringp( name3 = player->get_city_name() ) || name3 != name1 )
                        {
                                send_user( who, "%c%s", '!', "您只能管理居民的频道." );
                                return;
                        }

                        if( min < 0 )
                        {
                                send_user( who, "%c%c%d%s", '?', 1, DEFAULT_TIME, sprintf( "%s频道管理，请输入要封闭的分钟数：\n(0 表示打开频道)\n"
                                        ESC "talk %x# shutup.%s.%%s\n", name1, getoid(me), id ) );
                                return;
                        }

                        if( min )    // 封闭频道
                        {
                                player->set_chblk("city", min * 60 );
                                player->set_chblk("time", time() );
                                who->add_strength(-10);

                                FAMILY_D->city_channel( name1, 0, sprintf( HIY "城主%s(%d)封闭%s(%d)的%s频道 %d 分钟.", 
                                        who->get_name(), who->get_number(), player->get_name(), player->get_number(), name1, min ) );
                                log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 封闭 %s(%d)%s 的 city 频道 %d 分钟.\n", 
                                        short_time(), who->get_name(), who->get_number(), who->get_id(), 
                                        player->get_name(), player->get_number(), player->get_id(), min ) );
                        }
                        else    // 打开频道
                        {
                                player->delete_chblk("city");
                                who->add_strength(-10);

                                FAMILY_D->city_channel( name1, 0, sprintf( HIY "城主%s(%d)解封%s(%d)的%s频道.", 
                                        who->get_name(), who->get_number(), player->get_name(), player->get_number(), name1 ) );
                                log_file( CHANNEL_LOG, sprintf("%s %s(%d)%s 解封 %s(%d)%s 的 city 频道.\n", 
                                        short_time(), who->get_name(), who->get_number(), who->get_id(), 
                                        player->get_name(), player->get_number(), player->get_id() ) );
                        }
                }
        }
}
