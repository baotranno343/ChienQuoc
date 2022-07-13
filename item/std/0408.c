
#include <ansi.h>
#include <map.h>
#include <effect.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：构造处理
void create()
{
        set_name( "Hồi Môn Phù" );
        set_picid_1(0408);
        set_picid_2(0408);
        set_unit( "张" );
        set_value(1500);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Sử dụng có thể truyền tống quay về môn phái";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
        object map, npc;
        int z, x, y, p;

        if( me->get_fam_name() == "" ) return 0;    // 没有门派

        write_user(me, ECHO "Bạn sử dụng Hồi Môn Phù……");

        if( objectp( map = get_map_object( get_z(me) ) ) 
        	&& map->get_map_type() == BATTLE_MAP && map->is_changping() )
        {
                send_user(me, "%c%s", '!', "Trong Chiến Trường không thể sử dụng Hồi Môn Phù.");
//              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
		if ( get_z(me)==704 )
		{
				notify("Trong Nhà Ngục không thể sử dụng");
                return 0;	
		}
        if( present("钱票", me, 1, MAX_CARRY) )
        {
                send_user(me, "%c%s", '!', "带着钱票不能使用Hồi Môn Phù.");
//              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if( present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY*4) )
        {
                send_user(me, "%c%s", '!', "带着Vật Phẩm Quý Bấu不能使用Hồi Môn Phù.");
//              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if( objectp( npc = me->get_quest("escort.robber#") ) && npc->is_escort_robber() )    // 寻找蒙面人
        {
                send_user(me, "%c%s", '!', "蒙面人出现，您的行动受到影响.");
//              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }

        switch( me->get_fam_name() )
        {
              default : 
        case "Đào Hoa Nguyên" : z = 289;  p = get_jumpin(z, 20);  break;
          case "Thục Sơn" : z = 273;  p = get_jumpin(z, 20);  break;
        case "Cấm Vệ Quân" : z = 080;  p = get_jumpin(z, 20);  break;
          case "Đường Môn" : z = 324;  p = get_jumpin(z, 20);  break;
          case "Mao Sơn" : z = 269;  p = get_jumpin(z, 20);  break;
        case "Côn Luân" : z = 054;  p = get_jumpin(z, 20);  break;
        case "Vân Mộng Cốc" : z = 165;  p = get_jumpin(z, 20);  break;
        }

        if( p )
        {
                x = p / 1000;  y = p % 1000;
	        send_user(me, "%c%c%w%s", 0x5a, 0, 3, "Hồi Môn Phù……");	                
	        me->set_2("travel.z", z);
	        me->set_2("travel.p", p);
	        me->set_2("travel.money", 0);
	        set_effect(me, EFFECT_TRAVEL, 3);
                return 1;
        }
        else
        {
                write_user(me, ECHO "……không hiệu quả");
                return 0;
        }
}
