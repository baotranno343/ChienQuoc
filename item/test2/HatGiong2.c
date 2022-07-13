#include <item.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <equip.h>
#include <time.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   

int get_item_value() {return 300 ;}
int get_item_value_2() {return 300 ;}
int get_item_color() { return 2;};
// 函数：构造处理
void create()
{
        set_name("Hạt Giống Võ Lâm Bại Hoại");
        set_picid_1(3234);
        set_picid_2(3234);
        set_unit("只");
        set_value(50);
		set_save("knb",300);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{
	return "Sử dụng sẽ gọi ra một NPC Võ Lâm Bại Hoại. \nMỗi một giờ cho phép gọi ra tối đa 5 con.";
}

int get_use_effect(object who) { return __FILE__->get_use_effect_callout(who,this_object()); }

int get_use_effect_callout(object who,object item)
{
	int x,y,z,x0,y0,p,iTime,iDay,iGio,z1;
	object obj,*nObj,map;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);     
	iDay = mxTime[TIME_YDAY];
	iGio = mxTime[TIME_HOUR];
	
	z1 = get_z(who);
	map = get_map_object(z1);
	if (!map) return 0;
    if( MAP_D->is_inside_city( get_z(who), get_x(who), get_y(who) ) )
                {
                        send_user(who,"%c%s",';',"Không thể sử dụng trong \"Thành\" !!!");
                        return 0;
                }
	if (map->get_client_id()==001)
				{
						send_user(who,"%c%s",';',"Không thể sử dụng ở \"Tân Thủ Thôn\" !!!");
                        return 0;
				}
	if (who->get_save_2("gio.tieng")==iGio)
		{
			send_user(who,"%c%s",';',"Đã gọi đủ \"5\" NPC Võ Lâm Bại Hoại, hãy đợi tới giờ kế tiếp !!!");
			return;
		}
		
	z = get_z(who);  x0 = get_x(who);  y0 = get_y(who);
	p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK);
        if( !p )
        	return 0;
	x = p / 1000;  y = p % 1000;
	obj = new("npc/party/scum3");
	if ( !obj )
		return 0;
	obj->set("birth",time());
	obj->add_to_scene( z, x, y);
	who->add_save("hatgiongvlbh.diem",1);
	send_user(who,"%c%s",';', sprintf("Đã gọi ra \"%d\" NPC Võ Lâm Bại Hoại",who->get_save("hatgiongvlbh.diem") ));
	if ( who->get_save("hatgiongvlbh.diem")	> 4 )
	{
		who->set_save_2("gio.tieng", iGio);
		who->set_save("hatgiongvlbh.diem",0);
		send_user(who,"%c%s",';',"Đã gọi đủ \"5\" NPC Võ Lâm Bại Hoại, hãy đợi tới giờ kế tiếp !!!");
	}
	return 1;
}