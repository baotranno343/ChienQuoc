#include <ansi.h>
#include <npc.h>
#include <cmd.h>
#include <city.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

int is_self_look() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 9715; }

void do_welcome( string arg );
void do_look2( object me, object who );

// 函数：构造处理
void create()
{
	object me = this_object();
        set_name("Thần Cơ Viện Chủ");
        set_city_name("Bang Phái");

        set_2( "good", ([
                "01" : "/item/std/0401",
                "02" : "/item/std/0498",
                "03" : "/item/std/0499",
//                "04" : "/item/std/0497",
                "05" : "/item/std/0413",
                "06" : "/item/std/0591",
                "07" : "/item/32/3231",
                "08" : "/item/91/9100",
                "09" : "/item/91/9101",
                "10" : "/item/91/9110",
                "11" : "/item/91/9111",
                "12" : "/item/stuff/0106",
        ]) );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
        setup();
}

void do_look( object who )
{
        string result;
        object me = this_object();
        __FILE__ ->do_look2(me, who);
}       

void do_look2( object me, object who )
{
	 string result;        
        if (me->get_org_name()==who->get_org_name())
        {
        	result = sprintf("%s：\n    在战场中老夫能为你提供一切所需的物质，另外老夫这里还能开发研究高级的攻城器械。怎么？是否需要老夫做些什么？\n", me->get_name());
        	result += sprintf(ESC "购买物资\nlist %x#\n", getoid(me) );
        	if (who->get_org_position()>=8)
        		result += sprintf(ESC "研究战斗傀儡\ntalk %x# welcome.1\n", getoid(me) );
        }
        else return;
        result += ESC"离开\nCLOSE\n";
        send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(), result );
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object who, string arg )
{
	int flag, position, weapon;
	object me, orgnpc;
	string name, result;
	me = this_player();
	position = me->get_org_position();
	name = me->get_org_name();
	if (name=="") return;
	if (position<8 ) return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );		
	if (!objectp(orgnpc)) return;	
	weapon = orgnpc->get_weapon();
	if (weapon==1)
	{
		result = sprintf("%s：\n    帮派的攻城器械已经研究成功。\n", who->get_name());
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		return ;
	}
	if (weapon>1)
	{
		if (time() < weapon)
		{
			result = sprintf("%s：\n    现在本帮派正全力进行投石车的研究开发中，大人再等待%d秒便可见到研究成果。\n", who->get_name(), weapon - time());
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			return ;		
		}
		else
		{
			remove_call_out( "weapon_callout" );
			orgnpc->set_weapon(1);
			result = "战争中神机院主已经成功开发了战斗傀儡技术。";
			FAMILY_D->org_channel( name, 0, result);
			return;			
		}
	}
	flag = to_int(arg);
	switch(flag)
	{
	case 1:
		result = sprintf("%s：\n    当前的帮派木材" HIR "储备为%d，帮派资金为%d" NOR "。研究战斗傀儡必须消耗" HIR "500000的帮派资金" NOR "和" HIR" 200的木材储备" NOR "，研究成功后可在武教头处招募战斗傀儡协助战斗，研究需时为" HIR "300秒" NOR "。\n    你确定要研究战斗傀儡吗？\n", who->get_name(), orgnpc->get_wood(), orgnpc->get_gold());
		result += sprintf(ESC "确定\ntalk %x# welcome.2\n", getoid(who) );
		result += ESC"取消\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		break;
	case 2:
		if (orgnpc->get_gold()<500000)
		{
			result = sprintf("%s：\n    帮派资金不足500000，无法开始研究。\n", who->get_name());
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			return ;	
		}
		if (orgnpc->get_wood()<200)
		{
			result = sprintf("%s：\n    帮派木材储备不足200，无法开始研究。\n", who->get_name());
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			return ;	
		}		
		orgnpc->add_gold(-500000);
		orgnpc->add_wood(-200);
		orgnpc->set_weapon(time()+300);
		call_out("weapon_callout", 300, who);
		result = "战争中神机院主开始研发战斗傀儡技术。";
		FAMILY_D->org_channel( name, 0, result);
		break;
	}
}

// 函数：心跳处理(循环)
void weapon_callout( object me )    // 每１分处理
{
	string name, result;
	int weapon;
	object orgnpc;
        name = me->get_org_name();
        remove_call_out( "weapon_callout" );
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );	
	if (!objectp(orgnpc)) return;        
	weapon = orgnpc->get_weapon();
	if (weapon<=1) return;
	
	orgnpc->set_weapon(1);
	result = "战争中神机院主已经成功开发了战斗傀儡技术。";
	FAMILY_D->org_channel( name, 0, result);
	
}