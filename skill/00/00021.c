
#include <ansi.h>
#include <skill.h>
#include <action.h>

#define THIS_PERFORM    00021
#define PF_NAME        "Đẩy đi thể"

#define SUB_MP          10

// 函数:获取描述
string get_desc( object me ) 
{ 
        return "[ " PF_NAME " ]\nĐẩy thi thể người khác ra.\n"; 
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, p, mp;

        if( !who->is_die() )
        {
                send_user(me, "%c%s", '!', "Đối phương không phải người chết.");
                return 1;
        }

        z = get_z(who);  x = get_x(who);  y = get_y(who);

        if( distance_between(who, me) > 1 )
        {
                send_user(me, "%c%s", '!', "Khoảng cách với đối phương quá xa.");
                return 1;
        }

        mp = SUB_MP;    // 小心准备 level

        if( me->get_mp() < mp )
        {
                send_user( me, "%c%s", '!', sprintf( "Đẩy thi thể cần tiêu hao %d điểm Pháp Lực.", mp ) );
                return 1;
        }
        me->add_mp(-mp);

        switch( get_d(me) )
        {
       case 1 : x ++;         break;
       case 2 : x ++;  y --;  break;
      default :        y --;  break;
       case 4 : x --;  y --;  break;
       case 5 : x --;         break;
       case 6 : x --;  y ++;  break;
       case 7 :        y ++;  break;
       case 8 : x ++;  y ++;  break;
        }

        if( get_block(z, x, y) & IS_CHAR_BLOCK ) return 1;

        who->add_to_scene( z, x, y, get_d(who) );

        write_user( me, ECHO "Bạn đem " + who->get_name() + " đẩy ra xa." );
        write_user( who, ECHO "%s(%d) bị đẩy ra xa.", me->get_name(), me->get_number() );

        return 1;
}

// 函数:获取指令类型
int get_perform_type() { return ON_CHAR_7; }

// 函数:能否使用指令
void can_perform( object me )
{
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
