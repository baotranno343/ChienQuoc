
#include <npc.h>
#include <skill.h>
#include <effect.h>

inherit CHAR;

inherit "/inh/npc/gift";
inherit "/inh/npc/energy";
inherit "/inh/char/energy2";
inherit "/inh/char/dbase5";
inherit "/inh/char/attack";
inherit "/inh/npc/attack2";
inherit "/inh/char/cmd";
inherit "/inh/char/group";
inherit "/inh/npc/skill";
inherit "/inh/npc/equip";

private string Name;                    // 中文名字
private int PicId;                      // 人物造型


private static int Action_Mode = 1;		// 攻击类型  0 被动类型 1 主动攻击型 2 防御型
private static int Action = 1;	// 动作模式  0 待机 1 有动作(对召唤兽来说就是跟随) 2: 返回主人身边
private static int NextAction = 1;		// 保存着的旧有模式


private object Owner;                   // 主人对象
private int OwnerNumber;                // 主人对象(Number)

private int Level;                      // 等级

// 函数：NPC 识别函数
int is_npc() { return 1; }

// -------------------------------------------------------------

// 函数：获取人物名称
string get_name() { return Name; }

// 函数：设置人物名称
string set_name( string name ) 
{ 
        if( Name != name ) 
        {
        	Name = name;
        	send_user( get_scene_object_2( this_object(), USER_TYPE ), "%c%c%d%s", 0x3d, 5, getoid( this_object() ), get_short() );
        }
        return Name ; 
}

// 函数：获取人物名称
string get_short() 
{ 
        if (this_object()->get_level()) return sprintf(" %s ( Cấp %d )",get_name(), this_object()->get_level() );
        return get_name(); 
}

// 函数：物体识别处理
int id( string arg ) 
{ 
        if( !arg || arg == "" ) return 0;
        if( arg[<1] == '#' ) return arg != sprintf( "%x#", getoid( this_object() ) ) ? 0 : 1;
        return arg != get_name() ? 0 : 1;
}

// 函数：获取人物造型
int get_char_picid() { return PicId; }

// 函数：设置人物造型
int set_char_picid( int id ) { return PicId = id; }

// 函数：获取主人对象
object get_owner() { return Owner; }

// 函数：设置主人对象
object set_owner( object char ) 
{ 
        if( !objectp(char) ) OwnerNumber = 0;
        else OwnerNumber = char->get_number();
        return Owner = char; 
}

// 函数：获取主人对象(Number)
int get_owner_number() { return OwnerNumber; }

// 函数：设置主人对象(Number)
int set_owner_number( int number ) { return OwnerNumber = number; }

// 函数：获取最高人物等级
int get_max_char_level() { return 150; }

// 函数：获取最高技能等级
int get_max_skill_level() { return 150; }

// 函数：获取等级属性
int get_level() { return Level; }

// 函数：设置等级属性
int set_level( int level ) { return Level = range_value( level, 0, get_max_char_level() ); }

// -------------------------------------------------------------

// 函数：人物设置函数
void setup()
{
        object me = this_object();

        set_char_type(NPC_TYPE);
        enable_player();

        if( !clonep(me) ) return;

        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 10);    // 循环心跳：１秒钟
        me->heart_beat();
        set_heart_beat(1);
}

// 函数：允许走路
int is_moveable() { return 1; }    // 能使用 go 命令

// 函数：获取攻击状态
int get_action() { return Action; }

// 函数：设置行动状态
int set_action( int flag ) 
{ 
	object owner;
	object me = this_object();
	int ret, old_flag;
	owner = me->get_owner();	
	old_flag = Action;
	if (owner&&flag<2 && old_flag!=flag)
	{
		if (flag ==0) ret = 3;
		else
		ret = 2;		
		send_user(owner, "%c%c%d%c", 0x2c, 5, getoid(me), ret);
	}	
	return Action = flag; 
}

// 函数：获取行动模式
int get_action_mode() { return Action_Mode; }

// 函数：设置攻击状态
int set_action_mode( int flag ) 
{ 
	object owner;
	object me = this_object();
	owner = me->get_owner();
	if (owner)
	{
		send_user(owner, "%c%c%d%c", 0x2c, 6, getoid(me), flag);
	}
	return Action_Mode = flag; 
}

// 函数：获取行动模式
int get_next_action() { return NextAction; }

// 函数：设置攻击状态
int set_next_action( int flag ) 
{
	 return NextAction = flag;
}

// 函数：心跳处理
void heart_beat() { __FILE__ ->heart_beat_callout( this_object() ); }

// 函数：心跳处理(在线更新)
void heart_beat_callout( object me )    // 每 0.1 秒 heart_timer + 1, 当 heart_count 为 0 时进入
{
        object who;
        string file;
        int heart, count, speed,ret,rate;

        heart = get_heart_timer(me);    // 获取心跳时钟(主)
        count = get_heart_count_2(me);    // 获取心跳标记
        count = set_heart_count_2( me, count - abs( heart - get_heart_timer_2(me) ) );    // 主辅心跳之差

        if( count < 1 )
        {
                switch( get_heart_state(me) )
                {
      case FIGHT_STAT : // 普通攻击, 特殊技(动作)
                        set_heart_state(me, FIGHT_STAT_DONE);
                        set_heart_count_2(me, 2);
                        if( who = me->get_enemy_3() )
                        {
                                if(     stringp( file = me->get_perform_file() ) 
                                &&      load_object(file)
                                &&      file->perform_done_npc(me, who) == 2 )    // 特技攻击(完成)
                                        ;

                                else if( stringp( file = me->get_perform_2_file() ) 
                                &&      load_object(file)
                                &&      file->perform_done_npc(me, who) == 2 )    // 特技攻击(循环)(完成)
                                        ;

                                else
                                {
                                	ret = CHAR_FIGHT_D->attack_done(me, who, HIT_NORMAL);    // 普通攻击(完成)
                        		if( !me ) return;    // 死亡退出
					if ( ret && who && !who->is_die() && (rate=me->get("double_attack")) && random(100) < rate )	//2次攻击
						CHAR_FIGHT_D->attack_done(me, who, HIT_NORMAL);

                                	if ( ret && me && !me->is_die() && who && !who->is_die() && me->get("sk74215") && random(100)<20 && !get_effect_3(who, EFFECT_CHAR_DREAM) )
                                	{
				                set_effect_2(who, EFFECT_CHAR_BLOOD, 5, 2);
				                send_user( who, "%c%w%w%c", 0x81, 9022, get_effect_3(who, EFFECT_CHAR_BLOOD), EFFECT_BAD );
				                send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9022, 1, OVER_BODY, PF_LOOP );
				                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9022, 1, EFFECT_BAD );        	
				                CHAR_CHAR_D->init_loop_perform(who);
				                who->set_save("char_blood", 20);
                                	}                                		
                                }
                        }
                        if( !me ) return;    // 死亡退出
                        me->set_perform_file(0);    // 重要：清除非法特技
                        // 设置后续攻击的时间
                        if(     get_effect(me, EFFECT_CHAR_LAZY)
                        ||      get_effect(me, EFFECT_CHAR_SLOW) )    // 战斗速度减半(漫天缤纷)
                                speed = me->get_attack_speed() * 2;
                        else    speed = me->get_attack_speed();     
                        set_heart_count(me, speed - 7 );        
                        set_heart_count_2(me, speed - 7 );           
                        break;

      case MAGIC_STAT : // 发放法术(动作)
                        set_heart_state(me, WALK_STAT);
                        NPC_HEART_D->heart_beat_cast(me);
                        if( !me ) return;    // 死亡退出
                        // 设置后续攻击的时间
                        if(     get_effect(me, EFFECT_CHAR_LAZY)
                        ||      get_effect(me, EFFECT_CHAR_SLOW) )    // 战斗速度减半(漫天缤纷)
                                speed = me->get_attack_speed() * 2;
                        else    speed = me->get_attack_speed();     
                        set_heart_count(me, speed - 9 );        
                        set_heart_count_2(me, speed - 9 );                              
                      	break;

              default : if( me->is_caster() )    // 远程攻击的怪
                        {
                                if(     get_effect(me, EFFECT_CHAR_LAZY)
                                ||      get_effect(me, EFFECT_CHAR_SLOW) )    // 战斗速度减半(漫天缤纷)
                                        speed = me->get_attack_speed() * 2;
                                else    speed = me->get_attack_speed();

//                                if( heart % speed == 0 ) 
                                {
                                        me->heart_beat_attack();
                                        if( !me ) return;    // 死亡退出
                                }
//                                set_heart_count(me, speed - heart % speed);    // 重设心跳标志(主), 0.? 秒进入心跳(战斗)
                                set_heart_count(me, speed);

                                if( get_heart_count_2(me) < 1 )
                                {
                                        if( get_effect(me, EFFECT_CHAR_LAZY) )
                                                speed = me->get_walk_speed() * 2;
                                        else    speed = me->get_walk_speed();

//                                        if( heart % speed == 0 ) 
                                        {
                                                me->heart_beat_walk();
                                                if( !me ) return;    // 死亡退出
                                        }
  //                                      set_heart_count(me, speed - heart % speed);    // 重设心跳标志(主), 0.? 秒进入心跳(走路)
                                        set_heart_count(me, speed);
                                }
                                if( !me ) return;    // 死亡退出
                        }
                        else    // 近身攻击的怪
                        {
                                if( get_effect(me, EFFECT_CHAR_LAZY) )
                                        speed = me->get_walk_speed() * 2;
                                else    speed = me->get_walk_speed();

//                                if( heart % speed == 0 ) 
                                {
                                        me->heart_beat_walk();
                                        if( !me ) return;    // 死亡退出
                                }
//                                set_heart_count(me, speed - heart % speed);    // 重设心跳标志(主), 0.? 秒进入心跳(走路)
                                set_heart_count(me, speed);

                                if( get_heart_count_2(me) < 1 )
                                {
                                        if(     get_effect(me, EFFECT_CHAR_LAZY)
                                        ||      get_effect(me, EFFECT_CHAR_SLOW) )    // 战斗速度减半(漫天缤纷)
                                                speed = me->get_attack_speed() * 2;
                                        else    speed = me->get_attack_speed();

//                                        if( heart % speed == 0 ) 
                                        {
                                                me->heart_beat_attack();
                                                if( !me ) return;    // 死亡退出
                                        }
//                                        set_heart_count(me, speed - heart % speed);    // 重设心跳标志(主), 0.? 秒进入心跳(战斗)
                                      	set_heart_count(me, speed);
                                }
                                if( !me ) return;    // 死亡退出
                        }
                        break;
                }

        }
        else    set_heart_count(me, count);    // 重设心跳标志(主), 0.? 秒进入心跳

        set_heart_timer_2(me, heart);    // 更新心跳时钟(辅), 表示其已处理
}

private static int HeartSec = 0;        // 心跳计时

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec( int point ) { return HeartSec = point; }

// 函数：增添心跳计时
int add_heart_sec( int point ) { return set_heart_sec(HeartSec + point); }

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１秒处理
{
        NPC_EFFECT_D->into_effect(me, effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8);    // 征状处理
        if( !me ) return;    // 死亡退出

        NPC_HEART_D->heart_beat_other(me);
        if( !me ) return;    // 死亡退出

        if( me->add_heart_sec(1) % 8 == 0 ) NPC_HEART_D->heart_beat_8sec(me);    // 每８秒处理
}

// 函数：清除空闲心跳
void init_heart_beat_idle() { set_heart_idle( this_object(), 0 ); }

// 函数：走路处理(心跳之中调用)
void heart_beat_walk() { NPC_HEART_D->heart_beat_walk( this_object() ); }

// 函数：攻击处理(心跳之中调用)
void heart_beat_attack() { NPC_HEART_D->heart_beat_attack( this_object() ); }

// 函数：跟随对手(心跳之中调用)
void follow_user() { NPC_HEART_D->follow_user( this_object() ); }

// 函数：判断可以战斗
int can_fight( object who ) { return NPC_ATTACK_D->can_fight( this_object(), who ); }

// 函数：可以接受战斗
int can_be_fighted( object who ) { return NPC_ATTACK_D->can_be_fighted( this_object(), who ); }

// 函数：自动战斗(遇玩家时调用)
void auto_fight( object who ) { NPC_ATTACK_D->auto_fight( this_object(), who ); }

// -------------------------------------------------------------

// 函数：修正奖励队伍
object *correct_bonus_team( object *team ) { return NPC_NPC_D->correct_bonus_team( this_object(), team ); }
// 函数：根据距离修正奖励队伍
object *correct_bonus_team1( object *team,int iDistance ) { return NPC_NPC_D->correct_bonus_team1( this_object(), team,iDistance ); }

// 函数：修正经验奖励
int correct_exp_bonus( int level, int level2, int exp ) { return NPC_NPC_D->correct_exp_bonus(level, level2, exp); }

// 函数：修正掉宝率
int correct_drop_rate( int level ) { return NPC_NPC_D->correct_drop_rate(level); }

// 函数：修正boss掉宝率
int correct_drop_rate_2( int level ) { return NPC_NPC_D->correct_drop_rate_2(level); }

// 函数：死亡奖励
void win_bonus( object who ) { NPC_NPC_D->win_bonus( this_object(), who ); }
