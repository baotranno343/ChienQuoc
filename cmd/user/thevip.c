#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg) 
{

    int skill = to_int(arg), p, x, y;
	string result;
    object item, item1;
    
			if( !objectp( item1 = present("Thẻ VIP", me, 1, MAX_CARRY*4) ) )
			{
                write_user(me, ECHO "Bạn không có Thẻ VIP !");
                return 1;
			}
			if( item1->get_lock_time() && item1->get_lock_time() < time() )
			{
				write_user(me, ECHO "Thẻ VIP đã hết hạn !");
                return 1;
			}
	if ( arg==0 )
	{
		send_user( me, "%c%c%c", 0xA2, 4, 1);
		me->set_save("thevip",1);
		result = sprintf("Hãy lựa chọn chức năng của Thẻ VIP :\n" );
		result += ESC "Luyện công ở Võ Công Tu Luyện Trường\nthevip go\n"; 
		result += ESC "Đang cập nhật... \nthevip 123\n"; 
		result += ESC "Hủy bỏ\n"; 
		send_user( me, "%c%s", ':', result);
                return 1;
	}
	if ( arg=="go" ) 
	{		
			if ( get_z(me)==887 )
			{
				write_user(me, ECHO"Bạn đang ở trong Võ Công Tu Luyện Trường rồi");
				return 1;
			}
			if( p = get_jumpin(887, -1) )
			{	
                x = p/1000, y = p % 1000;
                me->add_to_scene(887, x, y, get_d(me));
				me->set_save("thevip",1);
				write_user(me, sprintf(ECHO "Bạn có %d phút ( %d giây ) Tu luyện Võ công !",me->get_save("theviptime")/60,me->get_save("theviptime")));
				write_user(me, sprintf(ECHO "Bạn có %d phút ( %d giây ) Tu luyện Võ công !",me->get_save("theviptime")/60,me->get_save("theviptime")));
				write_user(me, sprintf(ECHO "Bạn có %d phút ( %d giây ) Tu luyện Võ công !",me->get_save("theviptime")/60,me->get_save("theviptime")));
			}
		return 1;	
	}	
	if ( arg=="123" ) 
	{		
		write_user(me, ECHO "Sẽ cập nhật thêm chức năng mới !");
		return 1;	
	}	
	return 1;
} 