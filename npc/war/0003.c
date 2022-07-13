#include <ansi.h>
#include <npc.h>
#include <cmd.h>
#include <city.h>

inherit OFFICER;

int is_self_look() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 9306; }

void do_welcome( string arg );
void do_look2( object me, object who );

// 函数：构造处理
void create()
{
	object me = this_object();
        set_name("Võ Giáo Đầu");
        set_city_name("Bang Phái");
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

void do_look2( object who, object me )
{
	
	string result, name;        
	object orgnpc;
	int position;
	if (me->get_org_name()!=who->get_org_name()) return;
	position = me->get_org_position();
	name = me->get_org_name();
	if (name=="") return;
	if (position<1 ) return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );		
	if (!objectp(orgnpc)) return;	
        result = sprintf("%s：\n    本人专门负责提升战场NPC的战斗力和招募佣兵协助作战。当前本帮的木材存储量为%d，帮派资金总额为%d金。你需要什么服务吗？\n", who->get_name(), orgnpc->get_wood(), orgnpc->get_gold());
        result += sprintf(ESC "了解木材的来源\ntalk %x# welcome.10\n", getoid(who) );
        if (position>=8 ) result += sprintf(ESC "训练部队\ntalk %x# welcome.20\n", getoid(who) );
        if (position>=8 ) result += sprintf(ESC "升级箭塔\ntalk %x# welcome.30\n", getoid(who) );
        if (position>=8 ) result += sprintf(ESC "总管升级\ntalk %x# welcome.40\n", getoid(who) );
        result += sprintf(ESC "招募佣兵\ntalk %x# welcome.50\n", getoid(who) );
        result += ESC"离开\nCLOSE\n";
        send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object who, string arg )
{
	int flag, position, time, level;
	object me, orgnpc, map, npc;
	string name, result, name1, name2;
	int z, size, p, x, y;
	me = this_player();
	position = me->get_org_position();
	name = me->get_org_name();
	if (name=="") return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );		
	if (!objectp(orgnpc)) return;	
	time = orgnpc->get_level1_time();
	z = orgnpc->get_battle();	
	map = get_map_object(z);
	if (map)
	{
		name1 = map->get_war_attack();
		name2 = map->get_war_defense();
	}	
	if (time>0 && time()>time)
	{
		__FILE__->level1_callout(who);
		return;
	}
	time = orgnpc->get_level2_time();
	if (time>0 && time()>time)
	{
		__FILE__->level2_callout(who);
		return;
	}	
	time = orgnpc->get_level3_time();
	if (time>0 && time()>time)
	{
		__FILE__->level3_callout(who);
		return;
	}	
	flag = to_int(arg);
	switch(flag)
	{
	case 10:
		result = sprintf("%s：\n    " HIR "木材" NOR "获得的唯一办法就是通过消灭敌对士兵或军事设施还要击杀敌帮派玩家后获得，获得的木材数量不是归个人所有，而是全部积累到帮会资源中。基本上帮派所有的作战单位升级都离不开" HIR "木材" NOR"。\n    要注意的是，帮战结束后木材是不会继续保留的。\n", who->get_name());
		result += ESC"离开\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		break;
	case 20:	
		if (position<8 ) return;
		level = orgnpc->get_level2();
		result = sprintf("%s：\n    当前的帮派" HIR "木材储备为%d" NOR "，" HIR "帮派资金为%d" NOR "，且士兵的" HIR "等级为%d" NOR "。训练部队一次必须消耗" HIR "%d的帮派资金和%d的木材储备" NOR "，士兵等级提升后气血上限增加40％，攻击力增加20点，训练需时为100秒。\n    你确定要训练部队吗？\n", 
			who->get_name(), orgnpc->get_wood(), orgnpc->get_gold(), level, level*10000, level*60 );
		result += sprintf(ESC "确定\ntalk %x# welcome.21\n", getoid(who) );
		result += ESC"离开\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		break;
	case 21:	
		if (position<8 ) return;
		level = orgnpc->get_level2();
		time = orgnpc->get_level2_time();
		if (time>0)
		{
			result = sprintf("%s：\n    我正抓紧对手下的训练，大人还需等待%d秒便可看到训练的成果。\n", who->get_name(), time - time());
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}		
		if (level>= orgnpc->get_level1())
		{
			result = sprintf("%s：\n    部队的训练等级不能超过总管的等级。\n", who->get_name());
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}
		if (orgnpc->get_wood()<level*60)
		{
			result = sprintf("%s：\n    帮派木材不足%d。\n", who->get_name(), level*60);
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}	
		if (orgnpc->get_gold()<level*10000)
		{
			result = sprintf("%s：\n    帮派资金不足%d。\n", who->get_name(), level*10000);
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}	
		orgnpc->add_gold(-level*10000);		
		orgnpc->add_wood(-level*60);
		orgnpc->set_level2_time(time()+100);
		call_out("level2_callout", 100, who);
		result = "帮派开始训练部队。";
		FAMILY_D->org_channel( name, 0, result);		
		break;	
	case 30:	
		if (position<8 ) return;
		level = orgnpc->get_level3();
		result = sprintf("%s：\n    当前的帮派" HIR "木材储备为%d" NOR "，" HIR "帮派资金为%d" NOR "。升级箭塔一次必须消耗" HIR "%d的帮派资金和%d的木材储备" NOR "，升级后所有的箭塔气血上限增加20％，攻击力增加30点，箭塔升级需时为120秒。\n    你确定要升级箭塔吗？\n", 
			who->get_name(), orgnpc->get_wood(), orgnpc->get_gold(), 80000+(level-1)*20000, 40+(level-1)*30 );
		result += sprintf(ESC "确定\ntalk %x# welcome.31\n", getoid(who) );
		result += ESC"离开\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		break;
	case 31:	
		if (position<8 ) return;
		level = orgnpc->get_level3();
		time = orgnpc->get_level3_time();
		if (time>0)
		{
			result = sprintf("%s：\n    我正全力抓紧对本帮防御设施的加固工作，大人还需等待%d秒便可看到成果。\n", who->get_name(), time - time());
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}		
		if (level>= orgnpc->get_level1())
		{
			result = sprintf("%s：\n    箭塔的等级不能超过总管的等级。\n", who->get_name());
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}
		if (orgnpc->get_wood()<40+(level-1)*30 )
		{
			result = sprintf("%s：\n    帮派木材不足%d。\n", who->get_name(), 40+(level-1)*30 );
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}	
		if (orgnpc->get_gold()<80000+(level-1)*20000)
		{
			result = sprintf("%s：\n    帮派资金不足%d。\n", who->get_name(), 400000+(level-1)*200000);
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}	
		orgnpc->add_gold(-400000-(level-1)*200000);		
		orgnpc->add_wood(-40-(level-1)*30 );
		orgnpc->set_level3_time(time()+120);
		call_out("level3_callout", 120, who);
		result = "帮派开始提升箭塔等级。";
		FAMILY_D->org_channel( name, 0, result);		
		break;			
	case 40:	
		if (position<8 ) return;
		level = orgnpc->get_level1();
		result = sprintf("%s：\n    当前的帮派" HIR "木材储备为%d" NOR "，" HIR "帮派资金为%d" NOR "，且帮派总管的" HIR "等级为%d" NOR "。增强帮派总管的作战能力一次必须消耗" HIR "%d的帮派资金和%d的木材储备" NOR "，总管等级提升后其气血的上限会增加40％，升级需时为120秒。\n    你确定要提升帮派总管能力吗？\n", 
			who->get_name(), orgnpc->get_wood(), orgnpc->get_gold(), orgnpc->get_level1(), level*50000, level*200 );
		result += sprintf(ESC "确定\ntalk %x# welcome.41\n", getoid(who) );
		result += ESC"离开\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		break;
	case 41:	
		if (position<8 ) return;
		time = orgnpc->get_level1_time();
		if (time>0)
		{
			result = sprintf("%s：\n    本帮总管升级还需等待%d秒。\n", who->get_name(), time - time());
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}	
		level = orgnpc->get_level1();
		if (level>= 6)
		{
			result = sprintf("%s：\n    总管的等级不能超过6级。\n", who->get_name());
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}
		if (orgnpc->get_wood()<level*200 )
		{
			result = sprintf("%s：\n    帮派木材不足%d。\n", who->get_name(), level*200 );
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}	
		if (orgnpc->get_gold()<50000*level)
		{
			result = sprintf("%s：\n    帮派资金不足%d。\n", who->get_name(), 50000*level);
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}	
		orgnpc->add_gold(-50000*level);		
		orgnpc->add_wood(-level*200 );
		orgnpc->set_level1_time(time()+120);
		call_out("level1_callout", 120, who);
		result = "帮派开始提升总管等级。";
		FAMILY_D->org_channel( name, 0, result);		
		break;	
	case 50:		
		result = sprintf("%s：\n    你希望招募什么兵种？\n", who->get_name() );
		result += sprintf(ESC "普通佣兵(30000)\ntalk %x# welcome.51\n", getoid(who) );
		if (orgnpc->get_weapon()==1) result += sprintf(ESC "战斗傀儡(50000)\ntalk %x# welcome.52\n", getoid(who) );
		result += ESC"离开\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		break;
	case 51:
		if (!map) return;	
		if (me->get_cash()<30000)
		{
			result = sprintf("%s：\n    你的现金不足30000。\n", who->get_name());
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}		
		if (name==name1) size = map->sizeof_hire_dbase();
		else size = map->sizeof_hire_2_dbase();
		if (size>=20)
		{
			result = sprintf("%s：\n    佣兵数目已达20位，不能再雇佣。\n", who->get_name());
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}	
		me->add_cash(-30000);
		"/sys/sys/count"->add_use("war", 30000);	
		me->log_money("战争购买", -30000);
		npc = new ("/npc/war/0081");
		if (!npc) return;
		npc->set_org_name(name);
		npc->set_name(me->get_name()+"的佣兵");
		if (name==name1)
		{
			npc->set_char_picid(8012);
			p =  get_jumpin(z, 10+random(3));
			map->add_hire(npc);	
			npc->set_manager(map->get_manager());		
			npc->set_front(1);
		}
		else
		{
			npc->set_char_picid(8013);
			p =  get_jumpin(z, 15+random(3));	
			map->add_hire_2(npc);
			npc->set_manager(map->get_manager_2());		
			npc->set_front(2);
		}	
		x = p / 1000;  y = p % 1000;
		npc->add_to_scene(z, x, y, 3);
		result = sprintf("%s：\n    您花费了30000金雇佣了一个佣兵。\n", who->get_name() );
		result += ESC"离开\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );		
		break;	
	case 52:
		if (!map) return;
		if (orgnpc->get_weapon()!=1) return;
		if (me->get_cash()<50000)
		{
			result = sprintf("%s：\n    你的现金不足50000。\n", who->get_name());
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}		
		if (name==name1) size = map->sizeof_power_dbase();
		else size = map->sizeof_power_2_dbase();
		if (size>=5)
		{
			result = sprintf("%s：\n    战斗傀儡数目已达5位，不能再雇佣。\n", who->get_name());
			result += ESC"离开\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
			break;			
		}	
		me->add_cash(-50000);
		"/sys/sys/count"->add_use("war", 50000);	
		me->log_money("战争购买", -50000);
		npc = new ("/npc/war/0082");
		if (!npc) return;
		npc->set_org_name(name);
		npc->set_name(name+"的战斗傀儡");
		if (name==name1)
		{
			npc->set_char_picid(8012);
			p =  get_jumpin(z, 10+random(3));
			map->add_power(npc);	
			npc->set_manager(map->get_manager());		
			npc->set_front(1);
		}
		else
		{
			npc->set_char_picid(8013);
			p =  get_jumpin(z, 15+random(3));	
			map->add_power_2(npc);
			npc->set_manager(map->get_manager_2());		
			npc->set_front(2);
		}	
		x = p / 1000;  y = p % 1000;
		npc->add_to_scene(z, x, y, 3);
		result = sprintf("%s：\n    您花费了50000金雇佣了一个战斗傀儡。\n", who->get_name() );
		result += ESC"离开\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );		
		break;		
	}
}

// 函数：心跳处理(循环)
void level1_callout( object me )    // 每１分处理
{
	string name, result, name1, name2;
	int level, z;
	object orgnpc, map, target;
        name = me->get_org_name();
        remove_call_out( "level1_callout" );
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );	
	if (!objectp(orgnpc)) return;        
	level = orgnpc->get_level1();
	level ++;
	orgnpc->set_level1(level);
	orgnpc->set_level1_time(0);
	z = orgnpc->get_battle();	
	map = get_map_object(z);
	if (!map) return;
	name1 = map->get_war_attack();
	name2 = map->get_war_defense();
	if (name==name1) target = map->get_manager();
	else target = map->get_manager_2();
	target->upgrade(level);	
	result = sprintf(HIR"%s的总管顺利提升了一级，目前等级为%d级。", name, level);
	FAMILY_D->org_channel( name1, 0, result);
	FAMILY_D->org_channel( name2, 0, result);	
}

// 函数：心跳处理(循环)
void level2_callout( object me )    // 每１分处理
{
	string name, result, name1, name2;
	int level, z, i, size;
	object orgnpc, map, *target;
        name = me->get_org_name();
        remove_call_out( "level2_callout" );
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );	
	if (!objectp(orgnpc)) return;        
	level = orgnpc->get_level2();
	level ++;
	orgnpc->set_level2(level);
	orgnpc->set_level2_time(0);
	z = orgnpc->get_battle();
	map = get_map_object(z);
	if (!map) return;
	name1 = map->get_war_attack();
	name2 = map->get_war_defense();
	if (name==name1) target = map->get_comrade_dbase();
	else target = map->get_comrade_2_dbase();
	size = sizeof(target);
	for (i=0;i<size;i++)
		target[i]->upgrade(level);	
	result = sprintf(HIR"%s的部队顺利提升了一级，目前等级为%d级。", name, level);
	FAMILY_D->org_channel( name1, 0, result);
	FAMILY_D->org_channel( name2, 0, result);	
}

// 函数：心跳处理(循环)
void level3_callout( object me )    // 每１分处理
{
	string name, result, name1, name2;
	int level, z, i, size;
	object orgnpc, map, *target;
        name = me->get_org_name();
        remove_call_out( "level3_callout" );
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );	
	if (!objectp(orgnpc)) return;        
	level = orgnpc->get_level3();
	level ++;
	orgnpc->set_level3(level);
	orgnpc->set_level3_time(0);
	z = orgnpc->get_battle();
	map = get_map_object(z);
	if (!map) return;
	name1 = map->get_war_attack();
	name2 = map->get_war_defense();
	if (name==name1) target = map->get_tower_dbase();
	else target = map->get_tower_2_dbase();
	size = sizeof(target);
	for (i=0;i<size;i++)
		target[i]->upgrade(level);	
	result = sprintf(HIR"%s的箭塔顺利提升了一级，目前等级为%d级。", name, level);
	FAMILY_D->org_channel( name1, 0, result);
	FAMILY_D->org_channel( name2, 0, result);	
}