
// 多体远程技能	 TIPS:[PF_CAST_AREA]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define	BASIC_SKILL	0501
#define	THIS_SKILL	0511
#define	THIS_PERFORM	05113
#define	PF_START       "05113"
#define	PF_NAME	       "Khiết Vân Quyết"

#define	SKILL_LEVEL	31
#define	TIME_INTERVAL	2
#define	SUB_MP		( 72 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL)	/ 14 * 26 )
#define	ADD_EFFECT	( 650 +	( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 14 *	120 )


// 函数：获取描述
string get_desc( object	me )
{
	int level = me->get_skill(THIS_SKILL);
	int cur_level;
	string result;
	if (level<SKILL_LEVEL)
		return HIR + PF_NAME +"\n Võ công yêu cầu: 31 cấp\n    Y thuật trung cấp, có thể hồi phục 650 điểm Khí Huyết cho toàn bộ đồng đội trong phạm vi 3×3 ô";
	cur_level = (level - SKILL_LEVEL)/14 + 1;
	result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n	  Y thuật trung cấp, có thể hồi phục %d điểm Khí Huyết cho toàn bộ đồng đội trong phạm vi 3×3 ô.\n " HIC"Cấp tiếp theo:\n "NOR"Võ công yêu cầu: " HIR "Cấp %d " NOR"\n	Y thuật trung cấp, có thể hồi phục %d điểm Khí Huyết cho toàn bộ đồng đội trong phạm vi 3×3 ô.",
		PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL,	ADD_EFFECT, cur_level*14+SKILL_LEVEL, ADD_EFFECT+90 );
	return result;
}

// 函数：命令处理
int main( object me, object who, int x,	int y, string arg )
{
	int z;
	int level, mp;

	if( ( level = me->get_skill(THIS_SKILL)	) < SKILL_LEVEL	) return 1;

	if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;
        if ( me->get_perform("05016#"))
	{
                printf( ECHO "Sử dụng \"Đấu Chuyển Tinh Di\" không thể sử dụng \""PF_NAME"\"." );
                return 1;		
	}
	if( me->get_mp() < ( mp	= SUB_MP ) )	// 小心准备 me
	{
		printf(	ECHO "Sử dụng \"" PF_NAME "\" cần %d điểm pháp lực", mp );
		return 1;
	}

	if( who	)
	{
		if( !inside_screen_2(me, who) )	return 1;

		z = get_z(who);	 x = get_x(who);  y = get_y(who);
	}
	else
	{
		if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;

		z = get_z(me);
	}

	me->to_front_xy(x, y);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(),	MAGIC_ACT_BEGIN	);

	me->add_mp(-mp);

	set_heart_state(me, MAGIC_STAT);
	set_heart_count_2(me, 5);
	me->add_2("go_count.count2",5);
	me->set_cast_file(__FILE__);
	me->set_cast_arg( sprintf( "%d,%d,%d,%d", level, z, x, y ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
	me->set_perform( PF_START, time() );
	return 1;
}

// 函数：法术处理
int cast_done( object me )
{
	object *char, who, owner,item;
	string arg;
	int z, x, y;
	int level, cp, hp1, hp2, i, size;	

	if( !stringp( arg = me->get_cast_arg() ) || sscanf(arg,	"%d,%d,%d,%d", level, z, x, y) != 4 ) return 1;

	send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y, 51131, 1, OVER_BODY, PF_ONCE );

	cp = me->get_cp();
	hp1 = ADD_EFFECT;    //	小心准备 me, cp
	if( objectp(item=me->get_equip(WEAPON_TYPE)) && item->get_name()=="Ngọc Thần Bảo Kiếm" )
		hp1 += random(51);
	if( objectp(item=me->get_equip(WEAPON_TYPE)) && item->get_name()=="Lục Tiên Kiếm" )
		hp1 += 50 + random(51);
	if( objectp(item=me->get_equip(WEAPON_TYPE)) && item->get_name()=="Phá Pháp Chi Kiếm" )
		hp1 += 400 + random(101);	
	char = get_range_object(z, x, y, 2, USER_TYPE) + get_range_object(z, x, y, 2, CHAR_TYPE);	  // - ({ me });

	for( i = 0, size = sizeof(char); i < size; i ++	) if( who = char[i] )
	{
		if ("/sys/user/attack"->can_use_help(me, who)==0) continue;
		if( who->can_be_fighted(me) && me->can_fight(who) ) continue;    // 执行成功
		if (who->get_owner()) owner = who->get_owner();
		else owner = who;
		hp2 = hp1;
		if( get_effect(who, EFFECT_CHAR_GOOD_BAD) )
        		hp2 /= 2;
        	hp2 += me->get("add_magic_heal");
			hp2 += hp1*me->get("trilieu")/100;
		if (random100()<me->get_double_rate_2()/100)
		{
			hp2 *= 2;
			send_user( ({ me, owner	}), "%c%d%w%c%d%w%c", 0x4a, getoid(who), -hp2, get_d(who), getoid(who), 1 );
		}
		else
			send_user( ({ me, owner	}), "%c%d%w", 0x68, getoid(who), -hp2 );
		if (!who->no_recover() && !get_effect_3(who, EFFECT_USER_BURN))	who->add_hp(hp2);
       		CHAR_FIGHT_D->set_enmity2(me,who,50+hp2);	
	}

	return 2;    //	执行成功
}

// 函数：获取特技类型
int get_perform_type() { return	ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
	int interval;
	string name;

	if( me->get_skill(THIS_SKILL) <	SKILL_LEVEL )
	{
		send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
		return;
	}
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/14+1);
	interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START)	);
	if( interval < 0 )
		send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
	else	send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval,	name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0,10, MAGIC_ACT_BEGIN, 0, 5, 0);
}
