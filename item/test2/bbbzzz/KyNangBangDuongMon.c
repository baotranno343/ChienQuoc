#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 2; }
int get_item_value() {return 100 ;}
int get_item_value_2() {return 100 ;}

// 函数：构造处理
void create()
{
        set_name("Kĩ Năng Bang Hội Đường Môn");
        set_picid_1(9808);
        set_picid_2(9808);
		set_level(10);
        set_value(5000000);
		set_no_give(0);		
        set_no_sell(1);
		set_no_drop(0);
}

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "Kĩ năng bang hội \nSau khi sử dụng tất cả kĩ năng Bang hội sẽ max";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int p,gender,family,type;
	object item;
	string cTmp,cFile;
	gender = who->get_gender() == 1 ? 0 : 1;


	gift->remove_from_user();
	destruct(gift);
	
	who->set_skill(0430, 20);
	who->set_skill(0431, 20);
	who->set_skill(0433, 20);
	who->set_skill(0434, 10);
	who->set_skill(0435, 10);
	who->set_skill(0436, 5);
	who->set_skill(0437, 20);
//	who->set_skill(0438, 20);
	who->set_skill(0104, 150);
	who->set_skill(0109, 150);
	who->set_skill(0161, 150);
	who->set_skill(0202, 150);
	who->set_skill(0401, 150);
	who->set_skill(0403, 150);
	who->set_skill(0404, 150);
	who->set_skill(0405, 150);	
	send_user(who,"%c%s",';',"Tất cả kĩ năng "HIR "Bang Hội dành cho Đường Môn "NOR "đã max");
	return 0;
}