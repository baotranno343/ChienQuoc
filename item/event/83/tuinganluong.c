#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;
inherit COMBINED;
int get_item_color() { return 1; }
int get_item_value() {return 150 ;}
int get_item_value_2() {return 150 ;}

// 函数：构造处理
void create()
{
        set_name("Túi Ngân Lượng");
        set_picid_1(3102);
        set_picid_2(3102);
        set_value(100);
	//	set_save("tbpt",200);
		set_amount(1);
}

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "Sau khi sử dụng có thể nhận được ngẫu nhiên một số Ngân lượng.";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who, object gift ) 
{
	int p,level,tien;
	object item;
	string *nTmp,cFile;

	gift->add_amount(-1);
	if ( random100() < 20 ) tien=300000;
	else if ( random100() < 50 ) tien=200000;
	else if ( random100() < 80 ) tien=100000;
	else tien=50000;
	if ( tien ) {who->add_cash(tien);send_user(who,"%c%s",';',"Bạn nhận được "+tien+" lượng, xin chúc mừng !");}
	return 0;
}