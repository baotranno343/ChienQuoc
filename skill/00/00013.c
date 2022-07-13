
#include <ansi.h>
#include <skill.h>
#include <effect.h>

#define THIS_PERFORM    00013
#define PF_NAME        "Đào Dược"

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "［" PF_NAME "］\nThu thập thảo dược ngoài Thành Thị\n"; 
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object map, item;
        string file;
        int z, total, amount, p;

        if(     get_effect(me, EFFECT_CHAR_BUSY)
        ||      get_effect(me, EFFECT_CHAR_FAINT)
        ||      get_effect(me, EFFECT_CHAR_FAINT_2)
        ||      get_effect(me, EFFECT_CHAR_FREEZE)
        ||      get_effect(me, EFFECT_CHAR_SHUT) )
                return 1;
                
	send_user( me, "%c%s", '!', "Chức năng đào dược chưa mở." );                
	return;

        if( get_effect(me, EFFECT_USER_HERB) )
        {
                send_user(me, "%c%s", '!', "Ngài đang bận rộn thu thập thảo dược khác.");
                return 1;
        }

        z = get_z(me);  x = get_x(me);  y = get_y(me);

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

        if( !inside_jumpin(z, x, y, 16) )
        {
                send_user(me, "%c%s", '!', "Ngài đã chiếm được ruộng đất để đào dược.");
                return 1;
        }
        if( !( map = get_map_object(z) ) )
        {
//              send_user(me, "%c%s", '!', "您得到田地采集草药。");
                return 1;
        }

        if( ( total = map->get_herb(x, y) ) >= 3 )
        {
                send_user(me, "%c%s", '!', "Nơi này đã hết thảo dược.");
                return 1;
        }

        printf( ECHO "Ngài bắt đầu đào……" );
        set_effect(me, EFFECT_USER_HERB, 2);
        send_user(me, "%c%c%w%s", 0x5a, 0, 2, "Đang đào dược……");
        CHAR_CHAR_D->init_loop_perform(me);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 00131, 10, OVER_BODY, PF_LOOP );

        return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_ME_7; }

// 函数：能否使用指令
void can_perform( object me )
{
// 尚未开放
	return;	
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
