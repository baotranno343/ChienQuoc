#include <ansi.h>
//inherit USABLE;
inherit ITEM;

int get_item_value() {return 10 ;}
int get_item_value_2() {return 10 ;}
int get_item_number() {return 10001030 ;}
int get_item_color() {return 1 ;}

int is_jishihulu() { return 1; }

// 函数：构造处理
void create()
{
        set_name("济世宝玉");
        set_picid_1(9811);
        set_picid_2(9811);
        set_value(40);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //
}

// 函数：获取描述
string get_desc()
{
        return "相传当年太上老君所用宝玉。
        每使用一张可以增加济世葫芦5万的可存经验上限。";
}

// 函数：使用效果
//int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	return "npc/std/0003"->do_agend(who);
}

//int get_use_effect( object me ) 
//{
//	return __FILE__->get_use_effect_callout(me,this_object());	
//}

int get_use_effect_callout( object who,object item) 
{
	if ( !who->get_save_2("jishihulu.id") )
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("是否要使用济世葫芦\n"ESC"确定\nuse ! %x#\n"ESC"取消",getoid(item))); 
	else
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("使用新的济世葫芦可直接增加葫芦"HIR"可存经验"NOR"上限5万点，你确定要扩展你的葫芦吗？（"HIR"可存经验上限为3亿"NOR"）\n"ESC"确定\nuse ! %x#\n"ESC"取消",getoid(item))); 
	return 0;
}