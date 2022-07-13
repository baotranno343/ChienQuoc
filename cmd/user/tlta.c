#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg) 
{

    int skill = to_int(arg), p;
	string result,thongbao;
    object item, item1, who;
	me = this_player();
    
			if( !objectp( item1 = present("Thiên Lý Truyền Âm", me, 1, MAX_CARRY*4) ) )
        {
                write_user(me, ECHO "Bạn không có Thiên Lý Truyền Âm !");
                return 1;
        }

		if( !arg ) return 1;
		if (arg==0) return 1;
		if( sscanf(arg, "@ %s", thongbao) == 1 )
		{
			if ( me->get_save("camtlta") > 0 )
			{
				write_user(me, ECHO "Đang bị Phong Bế, không thể sử dụng !");
				return 1;
			}
			if ( get_z(me)==704 )
			{
				write_user(me, ECHO "Trong Nhà Ngục không thể sử dụng !");
                return 1;	
			}
			if ( gone_time(me->get("tlta" )) < 60 )
			{
				write_user(me, sprintf(ECHO "Thiên Lý Truyền Âm tái sử dụng sau %d giây !", 60-gone_time(me->get("tlta" )) ));
				return 1;	
			}
			me->set("tlta", time() );
			send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIY"%s "HIR "hét lớn : "HIY"%s", me->get_name(), thongbao ) );
			item1->add_amount(-1);
		}
		
	return 1;
} 