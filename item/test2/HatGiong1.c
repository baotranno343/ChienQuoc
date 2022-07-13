#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   
//#define SANTACLAUS	"npc/party/santaclaus"

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
        set_name("Hạt Giống Cây Xanh");
        set_picid_1(3234);
        set_picid_2(3234);
        set_unit("只");
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{
	return "Sử dụng sẽ trồng ra 1 Cây xanh tươi tốt";
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
	obj = new("npc/event/CayLon");
	if ( !obj )
		return 0;
	obj->set("birth",time());
	obj->add_to_scene( z, x, y);
//	nObj = SANTACLAUS->get("plant");
//	if ( !arrayp(nObj) )
//		nObj = ({});
//	nObj += ({obj});
//	SANTACLAUS->set("plant",nObj);
	"sys/sys/test_db"->add_yuanbao(who,50);
	who->add_exp(500000);
	who->add_cash(100000);
//	send_user(who,"%c%s",'!',"Bạn đã trồng 1 cây Lớn");
	send_user(who,"%c%s",';',"Bạn đã trồng Cây và nhận được 5 Kim Nguyên Bảo + 500.000 kinh nghiệm + 100.000 lượng");
	return 1;
}