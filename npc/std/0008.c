#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <ansi.h>
#include <task.h>
#include <cmd.h>

inherit BADMAN;

int saytime;

// 函数：远程攻击的怪
// int is_caster() { return 1; }

// 函数：是否允许移动
   int is_moveable() { return 0; }    // 禁止使用 go 命令

// 函数：跟随对手(心跳之中调用)
   void follow_user() { }    // 禁止跟随敌人

// 函数：获取人物造型
int get_char_picid() { return 0012; }

// 函数：构造处理
void create()
{
        set_name("Luyện Công Bù Nhìn");

        set_char_type(FIGHTER_TYPE);    // init_level 要用到
        
        set_head_color(0x0);

        NPC_ENERGY_D->init_level( this_object(), 1+ random(2) );    // 
        set_max_seek(4);

        setup();
	set("anti_05311",1);
        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action( object who ) { return 0; }    // XXXXX->perform_action_npc( this_object(), who ); }

// 函数：自动战斗(遇玩家时调用)
   void auto_fight( object who ) { }

int can_fight( object who )
{
	return 0;	//不能打人
}

int is_trainer() { return 1; }

void heart_beat_walk()
{
	object me=this_object();
	
	if ( gone_time(saytime) >=120 )
	{
		saytime = time();
		if ( random(2) )
		{
			switch(random(6))
			{
				case 0:
					SAY_CMD->say(me, "Tất cả mọi người đều chê ta xấu xí #15"); 
					break;
				case 1:
					SAY_CMD->say(me, "Trước đây rất buồn, bây giờ ta có bạn rồi #54"); 
					break;
				case 2:
					SAY_CMD->say(me, "Ta phụ trách sự yên ổn của đồng ruộng #11"); 
					break;
				case 3:
					SAY_CMD->say(me, "Nghe nói đánh ta sẽ được kinh nghiệm ! Đánh thử xem #23"); 
					break;
				case 4:
					SAY_CMD->say(me, "Cao nhân mà ta mong đợi đã đến rồi sao #5"); 
					break;
				default:
					SAY_CMD->say(me, "Tết năm nay không vui chút nào #50."); 
					break;
			}
		}
	}
//	::heart_beat_walk();
}

int beat(object who) 
{
	return __FILE__->beat_it(who,this_object());	
}

int beat_it(object who,object me)
{
	int level1,level2,exp,damage;
	object owner;
	
	if ( who->is_user() == 0 )
		return 0;
	level1 = who->get_level();
	level2 = me->get_level();

	if( who->is_user() ) owner = who;
	else owner = who->get_owner();
        if (owner) send_user( owner, "%c%d%w%c%d%w%c", 0x48, getoid(me), 1, get_d(who), getoid(me),
                HIT_NORMAL, 2 );
	
	if ( random100() < 101 )// * who->get_online_rate() / 100 )
	{
		switch(level2)
		{
		default:
		/*case 0:
			exp = 100+random(50);
			break;*/
		case 20:
			exp = 100+random(50);
			break;
		case 40:
			exp = 300+random(50);
			break;
		case 50:
			exp = 500+random(50);
			break;
		case 60:
			exp = 700+random(50);
			break;
		case 70:
			exp = 900+random(50);
			break;
		case 80:
			exp = 1100+random(50);
			break;
		case 100:
			exp = 1500+random(50);
			break;
		case 130:
			exp = 2100+random(50);
			break;
		case 150:
			exp = 2500+random(50);
			break;	
		}
		who->add_exp(exp);
		who->add_log("&trainer", exp);

	}
	if ( (damage=level2-level1) > 0 )
	{
		if( who->is_user() ) owner = who;
		else owner = who->get_owner();
                if (owner) send_user( owner, "%c%d%w%c%d%w%c", 0x48, getoid(who), damage*1000, get_d(me), getoid(who),
                        HIT_NORMAL, 2 );
        	CHAR_DIE_D->is_enemy_die(me, who, damage*1000);
	}
	return 1;
}