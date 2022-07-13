
#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
	object who;
        int gold, flag;

        if( gone_time( me->get_time("savings") ) < 1 )    // 时间限制
        {
                me->set_time( "savings", time() );
                return 1;
        }
        me->set_time( "savings", time() );

        if( !arg ) return 1;
        else if( sscanf( arg, "+ %s %d", arg, gold ) == 2 ) flag = 2;
        else if( sscanf( arg, "+ %s", arg ) == 1 ) flag = 1;
        else if( sscanf( arg, "- %s %d", arg, gold ) == 2 ) flag = 4;
        else if( sscanf( arg, "- %s", arg ) == 1 ) flag = 3;
        else return 1;

        if( !objectp( who = find_char(arg) ) ) return 1;

        if( !who->is_banker() ) return 1;

        if( !inside_screen_2(me, who) )
        {
                notify( "Bạn cách %s quá xa rồi.", who->get_name() );
                return 1;
        }

        me->to_front_eachother(who);

        if( flag == 1 )
        {
                send_user( me, "%c%c%d%s", '?', 1, me->get_cash(), sprintf( "Bạn trên người có %d lượng, bạn muốn gửi bao nhiêu ?\n" 
                        ESC "savings + %x# %%s\n", me->get_cash(), getoid(who) ) );
        }
        else if( flag == 2 )
        {
                if( gold < 1 )
                {
                        notify( "Ngân lượng gửi vào phải là số nguyên" );
                        return 1;
                }
                if( gold > me->get_cash() )
                {
                        notify( "Trong tay bạn chỉ có %d lượng.", me->get_cash() );
                        return 1;
                }
                if( me->get_savings() + gold > me->get_max_savings() )
                {
                        notify( "Bạn nhiều nhất có thể gửi %d lượng", me->get_max_savings() / 10000 );
                        return 1;
                }

                me->add_cash2( -gold );
                me->add_savings(gold);
                notify( "Bạn gửi %d lượng vào chỗ của %s .", gold, who->get_name() );
                write_user( me, ECHO "Bạn gửi %d lượng vào chỗ của %s .", gold, who->get_name() );
        }
        else if( flag == 3 )
        {
                send_user( me, "%c%c%d%s", '?', 1, me->get_savings(), sprintf( "Bạn đã gửi %d lượng, bạn muốn lấy ra bao nhiêu ?\n" 
                        ESC "savings - %x# %%s\n", me->get_savings(), getoid(who) ) );
        }
        else if( flag == 4 )
        {
                if( gold < 1 )
                {
                        notify( "Rút tiền phải là con số nguyên" );
                        return 1;
                }
                if( gold > me->get_savings() )
                {
                        notify( "Bạn chỉ gửi %d lượng", me->get_savings() );
                        return 1;
                }
                if( me->get_cash() + gold > me->get_max_cash() )
                {
                        notify( "Bạn trong tay nhiều nhất có thể có %d vạn lượng", me->get_max_cash() / 10000 );
                        return 1;
                }

                me->add_savings( -gold );
                me->add_cash2(gold);
                notify( "Bạn ở chỗ %s rút ra %d lượng", who->get_name(), gold );
                write_user( me, ECHO "Bạn ở chỗ %s rút ra %d lượng", who->get_name(), gold );
        }

        return 1;
}
