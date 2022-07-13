//makesellcard.c自动生成
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   

int card_id;
int card_time;
// 函数：物品叠加上限
int get_max_combined() { return 1; }
//int get_item_value() {return 2 ;}
//int get_item_value_2() {return 2 ;}
//int get_item_number() {return 10001053 ;}
//int get_item_color() {return 1 ;}
int get_item_color() {return 1 ;}
//设置变身卡ID
int set_card_id(int i) { return card_id = i;}
//获取变身卡ID
int get_card_id() { return card_id;}
//设置变身卡时间
int set_card_time(int i) { return card_time = i;}
//获取变身卡时间
int get_card_time() { return card_time;}

// 函数：构造处理
void create()
{
        set_name("年兽卡");
        set_picid_1(3811);
        set_picid_2(3811);
        set_value(198);
        set_card_id(8100);
        set_card_time(3600);
        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "一种拥有神奇力量的变身卡，使用后不但可以变成年兽的造型，还有可能拥有年兽的力量。\n最大气血值增加10％，物理防御力与法术防御力增加10％。"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}
//使用后的影响
int get_use_effect_callout( object who,object item) 
{
	send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("你确定要使用%s吗？\n"ESC"确定\nuse ! %x#\n"ESC"取消",item->get_name(),getoid(item))); 
	return 0;
}

// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	int hp,dp,pp;
	if ( "sys/sys/magic_card"->change_shape(who,item->get_card_id(),item->get_card_time()) != 1 )
		return 0;
	hp = who->get_max_hp()*10/100;
	who->set_2("magic_card.hp",hp);
	USER_ENERGY_D->count_max_hp(who);

	dp = who->get_dp()*10/100;
	who->set_2("magic_card.dp",dp);
	USER_ENERGY_D->count_dp(who);

	pp = who->get_pp()*10/100;
	who->set_2("magic_card.pp",pp);
	USER_ENERGY_D->count_pp(who);

	return 1;
}

void remove_effect(object who)
{
	int hp,dp,pp;
	
	hp = who->get_2("magic_card.hp");
	dp = who->get_2("magic_card.dp");
	pp = who->get_2("magic_card.pp");
	if ( !hp || !dp || !pp )
		return ;
	who->delete_2("magic_card.hp");	
	who->delete_2("magic_card.dp");	
	who->delete_2("magic_card.pp");	
	USER_ENERGY_D->count_max_hp(who);
	USER_ENERGY_D->count_dp(who);
	USER_ENERGY_D->count_pp(who);
	send_user( who, "%c%s", ';', "年兽卡的力量已经用完了，你回复了正常状态……");
}
