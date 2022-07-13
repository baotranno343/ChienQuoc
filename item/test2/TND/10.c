//随机高级技能
#include <ansi.h>
#include <item.h>
#include <skill.h>
#include <public.h>

inherit ITEM;

int get_item_color() { return 2;}
int get_item_value() {return 160 ;}
int get_item_value_2() {return 160 ;}
int get_item_type() { return ITEM_TYPE_SPECIAL; }
//宠物物品
int is_pet_item() { return 1;}
// 函数：构造处理
void create()
{
        set_name("Tinh Nguyên Đơn");
        set_picid_1(9980);
        set_picid_2(9980);
        set_value(5000);
        "quest/pet"->init_item_skill(this_object(),2);
		set("special", sprintf("%d", 74242));
		set_save("knb",160);
}
// 函数：获取描述
string get_desc() 
{
	int skill;
	object oSki;
	string desc;
	
	skill = to_int(get("special"));
	if ( skill == 74101 )			//修复BUG
	{
		"quest/pet"->init_item_skill(this_object(),2);
		skill = to_int(get("special"));
	}
	if( !skill || !(oSki = load_object(SKILL->get_perform_file(skill))) )
	 	return "";
	desc = "quest/pet"->get_skill_desc(skill);
	if ( !desc )
		return sprintf("Kỹ năng bao hàm: %s \n",oSki->get_name());;
	return sprintf("Kỹ năng bao hàm: %s \n %s ",oSki->get_name(),desc);
}
string get_special_desc(string cSpecial) 
{
	int skill;
	object oSki;
	string desc;
	
	skill = to_int(cSpecial);
	if( !skill || !(oSki = load_object(SKILL->get_perform_file(skill))) )
	 	return "";
	desc = "quest/pet"->get_skill_desc(skill);
	if ( !desc )
		return sprintf("Kỹ năng bao hàm: %s \n",oSki->get_name());
	return sprintf("Kỹ năng bao hàm: %s \n %s ",oSki->get_name(),desc);
}
