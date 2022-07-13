
// 自动生成：/make/npc/make0007

#include <npc.h>
#include <cmd.h>
#include <ansi.h>
#include <item.h>

inherit OFFICER;

// 函数：修理师傅
int is_repairer() { return 1; }

void do_welcome(string arg);
void do_identify(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5407; }

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Sửa Chữa");
        set_city_name("Chu Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
                "identify"          : (: do_identify :),
        ]));
        setup();
}



// 函数：对话处理
void do_look( object me )
{
	object who = this_object();
	"/quest/help"->send_help_tips(who, 52);
        if (me->get_skill(650))
	        send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                        sprintf(" %s :\n %s \n Xin hỏi bạn cần phục vụ gì?\n"
                        ESC "Tôi cần đánh giá trang bị\nrepair %x# identify\n"
                        ESC "我要分解装备\nrepair * %x#\n"
                        ESC "Tôi cần sửa chữa thông thường\nrepair %x# 2\n"
                        ESC "Tôi chỉ tham quan, dạo qua mà thôi\nCLOSE\n", who->get_name(), "/quest/word"->get_normal_word(who),  getoid(who), getoid(who), getoid(who) ) );
        else
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                	sprintf(" %s :\n %s \n Xin hỏi bạn cần phục vụ gì?\n"
                	ESC "Tôi cần đánh giá trang bị\nrepair %x# identify\n"
//                        ESC "我需要完美的特殊修理\nrepair %x# 1\n"
                        ESC "Tôi cần sửa chữa thông thường\nrepair %x# 2\n"
                        ESC "Tôi chỉ tham quan, dạo qua mà thôi\nCLOSE\n", who->get_name(), "/quest/word"->get_normal_word(who),  getoid(who), getoid(who) ) );
}
/*
void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object who, string arg )
{
	int level;
	object me,*inv,item;
	string result;
	me = this_player();
	if (arg==0)
	{
//		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf("%s：\n    我可以帮你鉴定未鉴定的装备，但是每件装备要收取你一些鉴定费用，你直接将装备给予我就可以了。", who->get_name() ) );
		send_user( me, "%c%c%d", 0x61, 1, getoid(who) );
		return;
	}
	item = present(arg, me,	0, 0);
	if (!item) return;
        if( !item->is_equip() )
        {
                return 0;
        }
        if (item->get_item_type() == ITEM_TYPE_TALISMAN)
        {
        	return 0;
        }
        if (!item->get_hide())
        {
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                	sprintf("%s：\n    %s已经鉴定过了。"
                        , who->get_name(), item->get_name() ) );
		return;
        }	
        level = item->get_level();
        level *= 30;
        if (level==0) level = 30;
        if (me->get_cash()<level)
        {
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                	sprintf("%s：\n    你的现金不足%d，无法鉴定%s。"
                        , who->get_name(), level, item->get_name() ) );
		return;        	
        }        
        me->add_cash(-level);
	me->log_money("鉴定", -level);
	"/sys/sys/count"->add_use("鉴定", level);   
	item->set_hide(0);
	level = get_d(item);
	item->add_to_user(level);     
	level = item->get_item_color();
	switch(level)
	{
	case 0:
		result = "你的装备很普通没什么特别的。";
		break;
	case 1:
		result = "你的装备不错！一件的优秀装备。";
		break;
	case 2:
		result = "这是一件很难得的一件珍贵装备，恭喜你。";
		break;
	default:
		result = "这是一件稀世珍品呀！很荣幸我能看到这样的一件宝物。";
		break;
	}
	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                sprintf("%s：\n    %s\n"
                ESC "继续鉴定\ntalk %x# welcome\n"
                ESC "离开\nCLOSE\n"
		, who->get_name(), result, getoid(who) ) );
}

// 函数：接受物品
int accept_object( object me, object item ){ return __FILE__ ->accept_object_callout( this_object(), me, item ); }

// 函数：接受物品(在线更新)
int accept_object_callout( object who, object me, object item )
{
        int level;

        me->to_front_eachother(who);

        if( !item->is_equip() )
        {
                return 0;
        }
        if (item->get_item_type() == ITEM_TYPE_TALISMAN)
        {
        	return 0;
        }
        if (!item->get_hide())
        {
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                	sprintf("%s：\n    %s已经鉴定过了。"
                        , who->get_name(), item->get_name() ) );
		return -99;
        }
        level = item->get_level();
        level *= 30;
        if (level==0) level = 30;
	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                sprintf("%s：\n    鉴定这件装备需要%d金，是否真的需要鉴定？\n"
                ESC "是的，我要鉴定\ntalk %x# welcome.%x#\n"
                ESC "太贵了，我不鉴定了\nCLOSE\n", who->get_name(), level, getoid(who), getoid(item) ) );
	return -99;               
}

void do_identify( string arg )
{
        object me = this_object();
        __FILE__ ->do_identify2(me, arg);
}

void do_identify2( object who, string arg )
{
	int level;
	object me,*inv,item;
	string result;
	me = this_player();
	item = present(arg, me,	0, 0);
	if (!item) return;
        if( !item->is_equip() )
        {
                return;
        }
        if (item->get_item_type() == ITEM_TYPE_TALISMAN)
        {
        	return;
        }
        if (!item->get_hide())
        {
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                	sprintf("%s：\n    %s已经鉴定过了。"
                        , who->get_name(), item->get_name() ) );
		return ;
        }
        level = item->get_level();
        level *= 30;
        if (level==0) level = 30;
	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                sprintf("%s：\n    鉴定这件装备需要%d金，是否真的需要鉴定？\n"
                ESC "是的，我要鉴定\ntalk %x# welcome.%x#\n"
                ESC "太贵了，我不鉴定了\nCLOSE\n", who->get_name(), level, getoid(who), getoid(item) ) );
	send_user( me, "%c%c", 0x61, 0 );                
	return ;   
}
*/