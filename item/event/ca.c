#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

int get_max_combined() { return 10000; }
int get_item_color() { return 2; }
int get_item_value() {return 100 ;}
int get_item_value_2() {return 100 ;}

// 函数：构造处理
void create()
{
        set_name("Cá Chép");
        set_picid_1(4215);
        set_picid_2(4215);
		set_level(20);
        set_value(100);
		set_amount(1);		

}

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "Một loại Cá đem nướng lên cực kỳ thơm ngon,\n sử dụng sẽ nhận được kinh nghiệm và ngân lượng." ;
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int gender,family,exp,type,level;
	object item,item1;
	string cTmp,cFile,p;
		if ( who->get_level() < 20 )
		{
		send_user(who,"%c%s",'!',"Cấp 20 mới có thể sử dụng.");
		    		return 0;

		}
		level = who->get_level();
					who->add_exp(50000+level*level*987);
					who->add_cash(2000000+random(500000));
		gift->add_amount(-1);			

}