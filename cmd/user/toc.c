
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main( object me, string arg )
{
	int gender;
	gender = me->get_gender();
	
        if ( arg==0 ) return 1;
		if (arg=="hien")
    {
			if ( !me->get_save_2("marry_fashion") )
			{
				write_user(me, ECHO "Bạn không có mặc áo cưới !");
				return 1;
			}
		if ( me->get_save_2("marry_fashion.type")==2 )
		{
			if ( me->get_hair()==10 ) {notify("Không thể sử dụng");return 1;} 
			else if ( me->get_hair()==1010 ) {notify("Không thể sử dụng");return 1;}
			if ( gender == 1 )
			{
			me->set_save("old_hair", me->get_hair());
			me->set_hair(10);
			me->set_save("nonaocuoi",0);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			}
			else
			{
			me->set_save("old_hair", me->get_hair());
			me->set_hair(1010);
			me->set_save("nonaocuoi",0);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			}
			return 1;
		}
			else if ( me->get_save_2("marry_fashion.type")==1 )
		{
			if ( me->get_hair()==1009 ) {notify("Không thể sử dụng");return 1;}  
			if ( gender == 1 ) {notify("Không thể sử dụng");return 1;}
			else
			{
			me->set_save("old_hair", me->get_hair());
			me->set_hair(1009);
			me->set_save("nonaocuoi",0);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			}
			return 1;
		}
			else if ( me->get_save_2("marry_fashion.type")==3 )
		{
			notify("Không thể sử dụng");
			return 1;
		}
			else if ( me->get_save_2("marry_fashion.type")==4 )
		{
			notify("Không thể sử dụng");
			return 1;
		}
        	return 1;
    }
		if (arg=="an")
    {
				if ( !me->get_save_2("marry_fashion") )
				{
				write_user(me, ECHO "Bạn không có mặc áo cưới !");
				return 1;
				}
			if ( me->get_save("nonaocuoi") == 1 ) {notify("Không thể sử dụng");return 1;} 
			if ( me->get_save_2("marry_fashion.type")==2 )
		{
			me->set_hair(me->get_save("old_hair"));
			me->set_save("nonaocuoi",1);
			me->delete_save("old_hair");
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			return 1;
		}
			else if ( me->get_save_2("marry_fashion.type")==1 )
		{  
			if ( gender == 1 ) {notify("Không thể sử dụng");return 1;}
			else
			{
			me->set_hair(me->get_save("old_hair"));
			me->set_save("nonaocuoi",1);
			me->delete_save("old_hair");
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			}
			return 1;
		}
			else if ( me->get_save_2("marry_fashion.type")==3 )
		{
			notify("Không thể sử dụng");
			return 1;
		}
			else if ( me->get_save_2("marry_fashion.type")==4 )
		{
			notify("Không thể sử dụng");
			return 1;
		}
        	return 1;
    }
 
        return 1;
}