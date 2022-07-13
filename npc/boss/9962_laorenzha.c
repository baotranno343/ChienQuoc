/*----------------------------------------------------------------*\
	名称；NPC -- 老人渣
	作者：由cjxx 创建用来配合活动“惊天大爆装”
	性质：活动专用PK得奖励的 BOSS 
\*----------------------------------------------------------------*/
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <effect.h>
#include <cmd.h>
#include <skill.h>

inherit NPC;

#define _DEBUG(str) 		  ;//if(objectp(find_char("-1"))) tell_user(find_char("1"),str);

private string *familys = ({"桃花源","蜀山","禁卫军","唐门","茅山","昆仑山","云梦泽"});		//	门派属性，掉宝时使用
private int rand_say_time =0;			//	随机说话的时间
private int auto_jump_time=0;			//	瞬间移动的时间

int summon_slave( object me );			//	召唤售的处理
void drop_items( object me, object who );	//	掉宝奖励函数

int cannot_enter_city() {
	return 1;
}

//	构造函数
void create() {
	set_name("老人渣");
	set_char_picid(9962);
	set_level(80);
	set_char_type(FIGHTER_TYPE);
	set("birthday",time());
	setup();
}

//	回调:判断是否可以攻击
int can_fight( object who ) { 
        object owner;
        string leader, id;
	if( who->is_die() ) {
		set_enemy(0);
		return 0;
	}
	if( who->is_npc() && objectp(owner = who->get_owner()) ) {
		who = owner;
	}
	if( who->is_npc() ) {
		set_enemy(0);
		return 0;
	}
	return ::can_fight(who);
}

//	回调：判断是否可以被攻击
int can_be_fighted( object who ) { 
        object owner;
        string leader, id;
	if( who->is_npc() && objectp(owner = who->get_owner()) ) {
		who = owner;
	}
	if( who->is_npc() ) {
		set_enemy(0);
		return 0;
	}
	return ::can_be_fighted(who);
}

//	回调：心跳处理
void heart_beat_walk() {
	object me,enemy;
	me    = this_object();
	enemy = get_enemy();
	if(objectp(enemy)) {
		if(gone_time(rand_say_time) >= 30 ) {
			rand_say_time = time();
			if(random(2)) {
				switch(random(6)) {
					default:
					case 0:
						SAY_CMD->say(me,"你打我啊打我啊，我靠你还真打！尝尝我的佛山香港脚！");
						break;
					case 1:
						SAY_CMD->say(me,"哎呀!身上的宝贝太多了,都拿不动了!咦……谁的金装掉了?");						
						break;
					case 2:
						SAY_CMD->say(me,"朋友,省省吧,就你这三脚猫的功夫还想杀我,看来那100件宝贝不属于你……");
						break;
					case 3:
						SAY_CMD->say(me,"打我呀!打我呀!你倒是打我呀!");
						break;						
					case 4:
						SAY_CMD->say(me,"我靠!真下黑手啊!别怪我翻脸无情，尝尝我的茅山无影脚!");
						break;						
					case 5:
						SAY_CMD->say(me,"唉,被人打真舒服啊……舒活舒活筋骨,抖擞抖擞精神!诶,兄弟,你倒是用点力啊!");
						break;			
				}
			}
		}
		if(enemy->is_die()) {
			set_enemy(0);
		}
	}
	return ::heart_beat_walk();
}

//	回调：自动战斗
//void auto_fight( object who ) {}
//	回调：复位函数 -- 正常的超时处理定义在函数外部这里防止服务器重起发生错误
void reset() {
        if( gone_time( get("birthday") ) >= 3600 &&  !objectp(get_enemy())) {
        	_DEBUG("时间到，退离场景");
                remove_from_scene();
                destruct( this_object() );
        }
}

//	回调：特技攻击函数 -- 此函数参见 npc/task/8210.c 里面的同名函数
int perform_action(object who) {
	int rate;
	object me = this_object();
	if( get_z(who)!= get_z(me) || !inside_screen_2(me, who) || distance_between(me,who)> get_max_seek()+2) {
		return 0;	
	}
	rate  = random(100);
	switch(me->get("robber.type")) {
		default:			
		case 1:		//	低物防高敏
			if ( rate < 5 ) {
				return PF_FILE_03483->perform_action_npc(me, who);
			} else if ( rate < 17 ) {
				return PF_FILE_02512->perform_action_npc(me, who);
			} else if ( rate < 20 ) {
				return PF_FILE_02416->perform_action_npc(me, who);
			}
			break;
		case 2:		//	高物防低法防
			if ( rate < 8 ) {
				return PF_FILE_02216->perform_action_npc(me, who);
			} else if ( rate < 16 ) {
				return PF_FILE_02313->perform_action_npc(me, who);
			} else if ( rate < 24 ) {
				return PF_FILE_02314->perform_action_npc(me, who);			
			}
			break;
		case 3:		//	高法防低物防
			if( get_effect(me, EFFECT_CHAR_NO_PF) ) {
				return 0;
			}
			if ( get_effect(me, EFFECT_CHAR_CHANGE) < 1) {
				PF_FILE_04251->cast_done_npc(me);			
			}
			if ( rate < 70 ) {
				return PF_FILE_04231->perform_action_npc(me, who);
			} else if ( rate < 90 ) {
				return PF_FILE_04232->perform_action_npc(me, who);
			} else if ( rate < 97 ) {
				return PF_FILE_04234->perform_action_npc(me, who);
			} else {
				return PF_FILE_04243->perform_action_npc(me, who);
			}
			break;
		case 4:		//	长血
			if( !me->get_perform("03173") ) {
				PF_FILE_03173->perform_action_npc(me,who);
			}
			if ( rate < 5 ) {
				return PF_FILE_02118->perform_action_npc(me, who);
			} else if ( rate < 13 ) {
				return PF_FILE_02114->perform_action_npc(me, who);
			} else if ( rate < 25 ) {
				return PF_FILE_02115->perform_action_npc(me, who);
			}
			break;
		case 5:		//	长血高物防高法防
			if( !me->get_effect(me, EFFECT_USER_HURT) ) {
				PF_FILE_03632->cast_done_npc(me);
			}
			if ( rate < 10 ) {
				return PF_FILE_02616->perform_action_npc(me, who);
			} else if ( rate < 20 ) {
				return PF_FILE_02615->perform_action_npc(me, who);			
			}
			break;
		case 6:		//	强攻加召唤
			summon_slave(me);
			if( get_effect(me, EFFECT_CHAR_NO_PF) ) {
				return 0;
			}
			if ( rate < 6 ) {
				return PF_FILE_04143->perform_action_npc(me, who);
			} else if ( rate < 12 ) {
				return PF_FILE_04144->perform_action_npc(me, who);
			} else if ( rate < 15 ) {
				return PF_FILE_04145->perform_action_npc(me, who);
			}
			break;
	}
	return 0;
}

//	回调：战斗中间状态（杀掉了一个敌人时）
void stop_fight() {
	object enemy = get_enemy();
	_DEBUG("杀死了一个敌人，现在在加血");	
	if ( enemy && enemy->get_hp()==0 )
		add_hp(50000);
	::stop_fight();		
}

//-----------------------------------------远程调用-------------------------------------//
//	回调：战斗胜利后的奖励处理
void win_bonus(object who) {
	__FILE__->win_bonus_callout(this_object(), who);
}
//	win_bonus 的调用函数 -- 处理BOSS 死后的物品掉落信息
void win_bonus_callout(object me, object who) {
	_DEBUG(sprintf("DEBUG -- Z-%d X-%d Y-%d 老人渣被杀死了",get_z(me),get_x(me),get_y(me)));
	drop_items(me,who);
}
//	掉宝奖励函数
void drop_items( object me, object who ) {
	int i,x,y,z,p,count;
	string *item_info;
	object item;
	_DEBUG("开始奖励掉宝物品");
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	//	有几率出的物品：1件80—120级随机部位金色装备（包括武器）：100
	if(random(10000) <= 100) {
		for(i=0,count=0;i<100;i++) {
			if(p  = get_valid_xy(z,x,y,IS_ITEM_BLOCK)) {
				item_info = WEAPON_FILE->get_family_equip(familys[random(7)],0,(random(5)+8)*10,HEAD_TYPE+random(6));
				item = new(item_info[random(sizeof(item_info))]);
				if(!item) {
					continue;
				}
				ITEM_EQUIP_D->init_equip_prop_3(item);
				item->add_to_scene(z,p/1000,p%1000);
				item->set("time",time());
				if(++count>=1) {
					break;
				}				
			}
		}		
	}	
	//	有几率出的物品：1件100—120级随机部位蓝色装备：100
	if(random(10000) <= 100) {
		for(i=0,count=0;i<100;i++) {
			if(p  = get_valid_xy(z,x,y,IS_ITEM_BLOCK)) {
				item_info = WEAPON_FILE->get_family_equip(familys[random(7)],0,(random(3)+10)*10,HEAD_TYPE+random(6));
				item = new(item_info[random(sizeof(item_info))]);
				if(!item) {
					continue;
				}
				ITEM_EQUIP_D->init_equip_prop_1(item);
				item->add_to_scene(z,p/1000,p%1000);
				item->set("time",time());
				if(++count>=1) {
					break;
				}
			}
		}
	}
	//	必出物品 -- 1件50—120级随机部位金色装备（包括武器）
	for(i=0,count=0;i<100;i++) {
		if(p = get_valid_xy(z,x,y,IS_ITEM_BLOCK)) {
			item_info = WEAPON_FILE->get_family_equip(familys[random(7)],0,(random(8)+5)*10,HEAD_TYPE+random(6));
			item = new(item_info[random(sizeof(item_info))]);
			if(!item) {
				continue;
			}
			ITEM_EQUIP_D->init_equip_prop_3(item);
			item->add_to_scene(z,p/1000,p%1000);
			item->set("time",time());
			if(++count>=1) {
				break;
			}
		}
	}
	//	必出物品 -- 31件30—120级随机部位蓝色装备
	for(i=0,count=0;i<100;i++) {
		if(p = get_valid_xy(z,x,y,IS_ITEM_BLOCK)) {
			item_info = WEAPON_FILE->get_family_equip(familys[random(7)],0,(random(10)+3)*10,HEAD_TYPE+random(6));
			item = new(item_info[random(sizeof(item_info))]);
			if(!item) {
				continue;
			}
			ITEM_EQUIP_D->init_equip_prop_1(item);
			item->add_to_scene(z, p/1000,p %1000);
			item->set("time",time());
			if(++count>=31) {
				break;
			}
		}
	}
	//	必出物品 -- 25 堆 10000 游戏币
	for(i=0,count=0;i<100;i++) {
		if(p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) {
                        item = new( "/item/std/0001" );
                        item->set_value(10000);
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set( "time", time());
			if(++count>=25) {
				break;
			}
		}
	}	
	//	必出物品 -- 43件30—120级随机部位白色装备
	for(i=0,count=0;i<100;i++) {
		if(p = get_valid_xy(z,x,y,IS_ITEM_BLOCK)) {
			item_info = WEAPON_FILE->get_family_equip(familys[random(7)],0,(random(10)+3)*10,HEAD_TYPE+random(6));
			item = new(item_info[random(sizeof(item_info))]);
			if(!item) {
				continue;
			}
			// 此句去掉，去掉变蓝的可能性 ITEM_EQUIP_D->init_equip_prop(item);
		        item->add_to_scene(z, p / 1000, p % 1000);
		        item->set( "time", time() );
			if(++count>=43) {
				break;
			}
		}
	}
}
//	召唤兽 -- 上限为 5 个 此函数参见 npc/task/8210.c 中同名函数
int summon_slave( object me ) {
        object npc;
        string arg;
        int z, x, y, x0, y0, p;
        int level, cp, pp, i, size;
	if ( me->get("robber.slave") >= 5 ) {
		return 0;
	}
        level = me->get_level()-5;
        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);

        if( p = get_valid_xy(z, x0 + random(3) - 1, y0 + random(3) - 1, IS_CHAR_BLOCK) ) {
                npc = new( "/npc/boss/9962_dashou" );
		if ( !objectp(npc) ) {
			return;
		}
		npc->set("level", level);
		NPC_ENERGY_D->init_level(npc, level);
		if ( random(2) ) {
			npc->set_char_picid(52);
		} else {
			npc->set_char_picid(201);
		}
                npc->set_walk_speed(6);
                npc->set_attack_speed(15);	
                npc->set_max_seek(8);                	
                npc->add_max_hp(100);    // 小心准备 me
		npc->add_hp(100);
		npc->add_dp(level);
		npc->add_pp(level);		
                npc->set_owner(me);		
		npc->set_char_type(FIGHTER_TYPE);
                x = p / 1000;  y = p % 1000;
                npc->add_to_scene( z, x, y, get_front_xy(x, y, x0, y0) );
                send_user( get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc), 
                        41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE ); 
                me->add("robber.slave", 1);
                npc->set("robber.id",sprintf( "%x#", getoid(me)) );
                NPC_SLAVE_D->find_enemy(npc);    // 寻找敌人
        }
        return 1;    // 执行成功
}