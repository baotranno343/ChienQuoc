
#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>
#include <item.h>
#include <skill.h>

inherit OFFICER;

#define THIS_SKILL	680
#define SKILL_LEVEL	20
#define SKILL_EXP	0
#define RESET_TIME	900
#define TOOL_LEVEL	0
#define STUFF_NUMBER	111
#define PF_NAME		"Dược Sư"
#define TOOL_TYPE	21
#define RESET_FILE	"/sys/item/stuff2"

// 函数：获取人物造型
int get_char_picid() { return 2505; }

// 有自己的do_look函数
int is_self_look() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Dã Cúc");
        set("time", 1+random(3));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object item, me, *inv;
	int z, y, x, i, size;
	me = this_object();
	if( get_effect(who, EFFECT_CHAR_INVISIBLE) ) set_effect_2(who, EFFECT_CHAR_INVISIBLE, 1, 1 );
	if (get_z(me)!=get_z(who)||abs(get_x(me)-get_x(who))>5||abs(get_y(me)-get_y(who))>5) return;
	if (who->get_online_rate()<100)
	{
		send_user(who, "%c%s", ';', "非健康时间不能采集");
		return;
	}	
	if (who->get_skill(THIS_SKILL)<SKILL_LEVEL) 
	{
		send_user( who, "%c%s", '!', sprintf("您的%s技能不足%d级！", PF_NAME, SKILL_LEVEL));
		return;
	}
	if (who->get_skill_degree(THIS_SKILL)<SKILL_EXP) 
	{
		send_user( who, "%c%s", '!', sprintf("您的%s熟练度不足%d！", PF_NAME, SKILL_EXP));
		return;
	}
	item = who->get_equip(107);
	if (!item || item->get_item_type_2()!=TOOL_TYPE || item->get_level()< TOOL_LEVEL || item->get_lasting()< 100) item = 0;
	if (!item) 
	{
		send_user( who, "%c%s", '!', sprintf("您没有%d级以上的%s工具！", TOOL_LEVEL, PF_NAME));
		return;
	}
	if (get_effect(who, EFFECT_PROGRESS2)) return ;
	if (get_effect_3(who, EFFECT_PROGRESS)) return ;
        set_effect(who, EFFECT_PROGRESS2, 6 );
        who->set_progress_file(__FILE__);	
        who->set_progress_arg( me->get_char_id());
	send_user(who, "%c%c%w%s", 0x5a, 0, 6, PF_NAME+"中……");	
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 02011, 10, OVER_BODY, PF_LOOP );
	item->add_lasting(-100);
}

// 函数：对话处理
void into_effect( object who, string arg )
{
	object item, me, *inv;
	int p, z, y, x, i, size, total, amount;	
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 02011, 0, OVER_BODY, PF_STOP );
	if( !objectp( me = find_char(arg) ) )
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}
	if (get_z(me)!=get_z(who)||abs(get_x(me)-get_x(who))>5||abs(get_y(me)-get_y(who))>5)
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}		
	send_user(who, "%c%c%c", 0x5a, 1, 1);
	item = new (sprintf("/item/stuff/%04d", STUFF_NUMBER));
	if (item)
	{
		item->set_amount(me->get("time"));
		if( ( total = USER_INVENTORY_D->can_carry_3(who, item) ) < 1 )
		{
                        send_user( who, "%c%s", '!', "您身上没有空位！");
                        destruct(item);       
                        return ;  			
		}
		printf( ECHO "您获得%d个%s。", item->get_amount(), item->get_name() );
		if( total > item->get_amount() ) total = item->get_amount();
		amount = USER_INVENTORY_D->carry_combined_item_3(who, item, total);
                if( amount > 0 && item->set_amount(amount) )
                {              	
                        if( p = item->move2(who) )
                        {
                                item->add_to_user(p);
                        }
                }
                else    item->add_amount( -total );	
	}
	me->set("time", 0);
	if (me->get("time")<=0)
	{
		if ( me->get("never_refresh") )		//不刷新
		{
			me->remove_from_scene();
			destruct(me);
		}
		else
			me->wait_for_reset(me);		
		return;
	}
	// 检查是否已采完
	item = who->get_equip(107);
	if (!item || item->get_item_type_2()!=TOOL_TYPE || item->get_level()< TOOL_LEVEL || item->get_lasting()< 100) item = 0;
	if (!item) return;	
	set_effect(who, EFFECT_PROGRESS2, 6 );
	send_user(who, "%c%c%w%s", 0x5a, 0, 6, PF_NAME + "中……");
	item->add_lasting(-100);
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 02011, 10, OVER_BODY, PF_LOOP );
}

void effect_break(object who, string arg)
{
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 02011, 0, OVER_BODY, PF_STOP );
	set_effect(who, EFFECT_PROGRESS2, 0);
	send_user(who, "%c%c%c", 0x5a, 1, 0);
}

void wait_for_reset(object me)
{
	me->remove_from_scene();
	call_out( "reset_stuff", RESET_TIME, me );
}

void reset_stuff(object me)
{
	int z, x, y, p;
	z = me->get("z");
	if (z==0) 
	{
		z = 281;
		me->set("z", 281);
	}
	p = RESET_FILE->get_xy(z);
	me->add_to_scene(z, p / 1000, p % 1000, 3);
	me->set("time", 1+random(3));
}