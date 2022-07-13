#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   
#define SANTACLAUS	"npc/party/santaclaus"

//圣诞节物品
int is_christmas() { return 1;}

void reset()
{
        if( gone_time( get_drop_time() ) > 7200 )    // 2小时
        {
                remove_from_scene();
                destruct( this_object() );
        }
}
// 函数：构造处理
void create()
{
        set_name("Hạt Giống Cây Noel");
        set_picid_1(3234);
        set_picid_2(3234);
        set_unit("只");
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{
	return "Sử dụng sẽ trồng ra 1 cây Noel tuyệt đẹp";
}

int get_use_effect(object who) { return __FILE__->get_use_effect_callout(who,this_object()); }

int get_use_effect_callout(object who,object item)
{
	int x,y,z,x0,y0,p;
	object obj,*nObj;
	
        z = get_z(who);  x0 = get_x(who);  y0 = get_y(who);
	p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK);
        if( !p )
        	return 0;
	x = p / 1000;  y = p % 1000;
	obj = new("npc/party/santatree1");
	if ( !obj )
		return 0;
	obj->set("birth",time());
	obj->add_to_scene( z, x, y);
	nObj = SANTACLAUS->get("plant");
	if ( !arrayp(nObj) )
		nObj = ({});
	nObj += ({obj});
	SANTACLAUS->set("plant",nObj);
	send_user(who,"%c%s",'!',"Bạn đã trồng 1 cây Noel");
	return 1;
}