
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>
inherit DBASE_F;

#define THIS_SKILL 0363
#define THIS_PERFORM 03633
#define PF_START "03633"
#define PF_TIME "03633#"
#define PF_NAME "Hỗn Ma Độc"

#define SKILL_LEVEL 12
#define TIME_INTERVAL 10
#define SUB_MP 30
#define ADD_INTERVAL 15

int is_self_seal()
{
	return 1;
}

void show_to_user_2(object who);
void remove_to_user_2(object who);
void check_seal(object item);

// 函数:获取描述
string get_desc(object me)
{
	int level = me->get_skill(THIS_SKILL);
	string result;
	if (level < SKILL_LEVEL)
		return HIR + PF_NAME + "\n Võ công yêu cầu: 12 cấp\n Vật phẩm yêu cầu: Thuốc độc\n    Tung ra 1 đám khói độc, khiến tất cả mục tiêu trong phạm vi ảnh hưởng sẽ bị Trúng Độc và không thể di chuyển trong 6 giây.";
	result = sprintf(HIC " %s \n " NOR "Võ công yêu cầu: Cấp %d \n Vật phẩm yêu cầu : Thuốc độc \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Tung ra 1 đám khói độc, khiến tất cả mục tiêu trong phạm vi ảnh hưởng sẽ bị Trúng Độc và không thể di chuyển trong 6 giây.\n",
					 PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL);
	return result;
}

// 函数:获取描述(持续)
string get_loop_desc(object me)
{
	if (me->get_perform(PF_START))
		return PF_NAME ":\n　　Trạng thái Trúng Độc.\n";
	else
		return sprintf(PF_NAME "\n");
}

// 函数:命令处理
int main(object me, object who, int x, int y, string arg)
{
	int level, interval, mp;
	object item, item1;
	int z, d;
	int i, size, poison;
	mixed *nXy;

	if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
		return 1;

	interval = TIME_INTERVAL;

	if (gone_time(me->get_perform(PF_START)) < interval)
		return 1; // 小心准备 me

	if (me->get_mp() < (mp = SUB_MP)) // 小心准备 me
	{
		printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
		return 1;
	}
	if (!objectp(item = me->get_equip(HAND_TYPE)) || !item->is_poison())
	{
		printf(ECHO "Sử dụng \" %s \"phải có Độc dược.", PF_NAME);
		return 1;
	}
	/*	if( !objectp( item = me->get_equip(WEAPON_TYPE) ) || !item->get_poison() ) 
        {
                printf( ECHO "Sử dụng \" %s \"phải mang Vũ Khí có tẩm độc.",PF_NAME );
                return 1;
        }*/
	poison = item->get_poison();
	if (objectp(item1 = me->get_equip(WEAPON_TYPE)) && item1->get_name() == "Bích Hỏa Hàn Nguyệt Hoàn")
		poison += 1000;
	if (objectp(item1 = me->get_equip(WEAPON_TYPE)) && item1->get_name() == "Thần Tiên Hạc Kim")
		poison += 3000;
	if (objectp(item1 = me->get_equip(WEAPON_TYPE)) && item1->get_name() == "Bá Vương Tiễn")
		poison += 5000;
	if (objectp(item1 = me->get_equip(WEAPON_TYPE)) && item1->get_name() == "Độc Long Tiễn")
		poison += 3000;
	send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 2); // 所有出招２秒后能使用
	me->set_time("pf", time());

	send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
	send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END);

	CHAR_FIGHT_D->set_enmity1(me, 70);

	me->add_mp(-mp);
	//item->add_amount(-1);
	item->add_lasting(-100);

	set_heart_state(me, MAGIC_STAT);
	set_heart_count_2(me, 9);
	me->add_2("go_count.count2", 9);
	send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
	me->set_perform(PF_START, time());

	x = get_x(me);
	y = get_y(me);
	z = get_z(me);

	d = get_d(me);
	switch (d)
	{
	case 1:
		nXy = ({({x + 1, y}), ({x + 1, y - 1}), ({x + 1, y + 1})});
		break;
	case 2:
		nXy = ({({x + 1, y - 1}), ({x + 2, y}), ({x, y - 2})});
		break;
	case 3:
		nXy = ({({x, y - 1}), ({x - 1, y - 1}), ({x + 1, y - 1})});
		break;
	case 4:
		nXy = ({({x - 1, y - 1}), ({x - 2, y}), ({x, y - 2})});
		break;
	case 5:
		nXy = ({({x - 1, y}), ({x - 1, y + 1}), ({x - 1, y - 1})});
		break;
	case 6:
		nXy = ({({x - 1, y + 1}), ({x, y + 2}), ({x - 2, y})});
		break;
	case 7:
		nXy = ({({x, y + 1}), ({x - 1, y + 1}), ({x + 1, y + 1})});
		break;
	case 8:
		nXy = ({({x + 1, y + 1}), ({x, y + 2}), ({x + 2, y})});
		break;
	}
	for (i = 0, size = sizeof(nXy); i < size; i++)
	{
		if ((get_block(z, nXy[i][0], nXy[i][1], ) & SEAL_BLOCK))
		{
			printf(ECHO "Nơi này không thể phóng độc");
			return 2;
		}
	}
	level = me->get_skill(THIS_SKILL);

	item = new ("/skill/03/03633");

	item->set("begin", time());
	item->set("xy", nXy);
	item->set("owner", me);
	item->set("level", poison);
	item->set("interval", ADD_INTERVAL);
	set_z(item, z);
	set_x(item, x);
	set_y(item, y);

	item->do_start(me);
	move_object(item, z, x, y, CHAR_TYPE);

	for (i = 0, size = sizeof(nXy); i < size; i++)
	{
		send_user(get_scene_object_2(me, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, nXy[i][0], nXy[i][1],
				  3633, 1, OVER_BODY, PF_LOOP);
		set_block(z, nXy[i][0], nXy[i][1], SEAL_BLOCK);
	}

	return 1;
}

// 函数:法术处理
int cast_done(object me)
{
	object item;
	int z, x, y, d, level;
	int i, size;
	mixed *nXy;
	/*	
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
	
	x = get_x(me); y = get_y(me); z = get_z(me); 

	d=get_d(me);	
	switch(d)
	{
		case 1:
			nXy = ({({x+1,y}),({x+1,y-1}),({x+1,y+1})});
			break;
		case 2:
			nXy = ({({x+1,y-1}),({x+2,y}),({x,y-2})});
			break;
		case 3:
			nXy = ({({x,y-1}),({x-1,y-1}),({x+1,y-1})});
			break;
		case 4:
			nXy = ({({x-1,y-1}),({x-2,y}),({x,y-2})});
			break;
		case 5:
			nXy = ({({x-1,y}),({x-1,y+1}),({x-1,y-1})});
			break;
		case 6:
			nXy = ({({x-1,y+1}),({x,y+2}),({x-2,y})});
			break;
		case 7:
			nXy = ({({x,y+1}),({x-1,y+1}),({x+1,y+1})});
			break;
		case 8:
			nXy = ({({x+1,y+1}),({x,y+2}),({x+2,y})});
			break;				
	}
	for(i=0,size=sizeof(nXy);i<size;i++)
	{
		if(   ( get_block(z, nXy[i][0], nXy[i][1],) & SEAL_BLOCK ) )
		{
			printf( ECHO "这里不能放毒." );
                	return 2;
		}
	}
	level = me->get_skill(THIS_SKILL);

        item = new( "/skill/03/03633" );

	item->set("begin",time());
	item->set("xy",nXy);	
        item->set("owner",me);
	item->set("level",level);
	item->set("interval",ADD_INTERVAL);
        set_z(item, z);  set_x(item, x);  set_y(item, y); 

        item->do_start(me);
	move_seal(item, z, x, y);
	
	for(i=0,size=sizeof(nXy);i<size;i++)
	{
	        send_user( get_scene_object_2(me, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, nXy[i][0], nXy[i][1], 
                36331, 1, OVER_BODY, 36332, 1, OVER_BODY, PF_LOOP );         
                set_block(z, nXy[i][0], nXy[i][1],SEAL_BLOCK);       	
	}
*/
	return 2; // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform(object me)
{
	int interval;

	if (me->get_skill(THIS_SKILL) < SKILL_LEVEL)
	{
		send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME);
		return;
	}

	interval = me->get_perform(PF_TIME) - gone_time(me->get_perform(PF_START));
	if (interval < 0)
		send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, PF_NAME);
	else
		send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, PF_NAME);
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 9, 0);
}

int do_start(object who)
{
	object item = this_object();
	check_seal(item);
}

void check_seal(object item) // 每1秒处理
{
	object *char = ({}), *tmp, owner, who, *user, item1, me;
	int z, i, size, level;
	mixed *nXy;
	remove_call_out("check_seal");
	nXy = item->get("xy");
	if (!sizeof(nXy) || !(owner = item->get("owner")) || gone_time(item->get("begin")) > item->get("interval")) // 阵法完否
	{

		char = get_scene_object_2(item, USER_TYPE);
		z = get_z(item);
		for (i = 0, size = sizeof(nXy); i < size; i++)
		{
			remove_block(z, nXy[i][0], nXy[i][1], SEAL_BLOCK);
			send_user(char, "%c%w%w%w%c%c%c", 0x4f, nXy[i][0], nXy[i][1],
					  3633, 1, OVER_BODY, PF_STOP);
		}
		destruct(item);
		return;
	}
	z = get_z(item);
	for (i = 0, size = sizeof(nXy); i < size; i++)
	{
		if (sizeof(nXy[i]) != 2)
			continue;
		tmp = get_range_object(z, nXy[i][0], nXy[i][1], 0, USER_TYPE) + get_range_object(z, nXy[i][0], nXy[i][1], 0, CHAR_TYPE) - ({owner});
		if (arrayp(tmp))
			char += tmp;
	}

	level = item->get("level");
	for (i = 0, size = sizeof(char); i < size; i++)
		if (who = char[i])
		{
			if (!who->can_be_fighted(owner) || !owner->can_fight(who))
				continue;
			if (who->is_anti_effect())
				continue;
			if (random(100) < who->get_anti_poison())
				continue;
			if (!get_effect(who, EFFECT_CHAR_9140) && !get_effect(who, EFFECT_CHAR_POISON_2))
			{
				who->set_poison_2(level / 10);
				set_effect_2(who, EFFECT_CHAR_POISON_2, 10, 0);
				send_user(who, "%c%w%w%c", 0x81, 9096, get_effect_3(who, EFFECT_CHAR_POISON_2), EFFECT_BAD);
				send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9096, 1, EFFECT_BAD);
			}
			if (!get_effect(who, EFFECT_CHAR_NO_MOVE) && !get_effect(who, EFFECT_CHAR_FAINT_0))
			{
				if (who->get_perform("02222#"))
					continue;
				user = get_scene_object_2(who, USER_TYPE);
				set_effect(who, EFFECT_CHAR_NO_MOVE, 6); // 小心准备 me
				set_effect(who, EFFECT_CHAR_FAINT_0, 8);
				CHAR_CHAR_D->init_loop_perform(who);
				if (get_heart_state(who) == MAGIC_STAT)
					send_user(user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END); // 结束施法动作
				send_user(who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_NO_MOVE), EFFECT_BAD);
				send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD);
				send_user(user, "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 34721, 10, UNDER_FOOT, 34722, 10, UNDER_FOOT, PF_LOOP);
				CHAR_CHAR_D->init_loop_perform(who);
			}
		}
	call_out("check_seal", 2, item);
}

// 函数:列示给新玩家(对方进场景)
void show_to_user(object who)
{
	mixed *nXy;
	int i, size;
	object item = this_object();
	nXy = item->get("xy");
	for (i = 0, size = sizeof(nXy); i < size; i++)
	{
		send_user(who, "%c%w%w%w%c%c%c", 0x4f, nXy[i][0], nXy[i][1],
				  3633, 1, OVER_BODY, PF_LOOP);
	}
}

// 函数:删除给玩家看(对方离场景)
void remove_to_user(object who)
{
	mixed *nXy;
	int i, size;
	object item = this_object();
	nXy = item->get("xy");
	for (i = 0, size = sizeof(nXy); i < size; i++)
	{
		send_user(who, "%c%w%w%w%c%c%c", 0x4f, nXy[i][0], nXy[i][1],
				  3633, 1, OVER_BODY, PF_STOP);
	}
}
