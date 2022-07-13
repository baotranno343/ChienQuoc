#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <effect.h>
#include <cmd.h>
#include <skill.h>
#include <task.h>

#define _DEBUG(x)	tell_user(find_char("971"),x);

inherit NPC;

int flag;
int saytime,hptime,RelaxTime,pTime,iRelax,go_time;
string cNameColor="";
//string *nFamily = ({"Đào Hoa Nguyên","Thục Sơn","Cấm Vệ Quân","Đường Môn","Mao Sơn","Côn Luân","Vân Mộng Cốc"});
// 函数：是否不能进城
int cannot_enter_city() { return 1; }
//int get_id_color() { return 0x800080; }
//int is_caster () { return 1; }
void summon_guard();

// 函数：修正经验奖励
//int correct_exp_bonus( int level, int level2, int exp ) { return exp; }

// 函数：修正掉宝率
//int correct_drop_rate( int level ) { return 100; }

// 函数：获取人物名称
string get_short() 
{ 
        return cNameColor+this_object()->get_name(); 
}

// 函数：构造处理
void create()
{
	object me = this_object();
        set_name("Quách Khai");
        set_city_name("Triệu Quốc");
//        set_head_color(0x7a0a);
        set_char_picid(5201); 
        set_walk_speed(2);
        set_attack_speed(20);
        set_max_seek(12);
        set_walk_step(2);
        set("no_sk04211",1);	//变身术对其没有效果
        set("anti_sleep",1);	//不会昏迷
        set("anti_no_move",1);	//不会冻结
        
        
        setup();
	set_char_type(FIGHTER_TYPE_2);
        set( "birthday", time() );
        set( "rank",5);
        set_enmity_flag(1);
}

int can_fight( object who ) 
{ 
       return "npc/88/8800"->can_fight(this_object(),who);
}

int can_be_fighted( object who ) 
{ 
       return "npc/88/8800"->can_be_fighted(this_object(),who);
}

void heart_beat_walk()
{
	int i,x,y,z,x0,y0,z0,p,x1,y1,*nXy;
	object enemy,me=this_object();

	if ( iRelax )
		return ;
	enemy = get_enemy();
	
	if ( RelaxTime == 0 )
	{
		RelaxTime = time();
	}

	if ( RelaxTime && gone_time(RelaxTime) >= 120 )
	{
		RelaxTime = 0;	
		iRelax = 1;
		nXy = me->get_2("nPos");
		me->add_to_scene(get_z(me),nXy[0],nXy[1],4);
	}
	if( !get_effect(me, EFFECT_CHAR_NO_PF_0) )		//不沉默
	{
		set_effect(me, EFFECT_CHAR_NO_PF_0, 3600);
	}
	if( !get_effect(me, EFFECT_CHAR_WOUND_0) )		//不负伤
	{
		set_effect(me, EFFECT_CHAR_WOUND_0, 3600);
	}	
	if( !get_effect(me, EFFECT_CHAR_FAINT_0) )		//不眩晕
	{
		set_effect(me, EFFECT_CHAR_FAINT_0, 3600);
	}
	if( !get_effect(me, EFFECT_CHAR_SHUT_0) )		//不囚禁
	{
		set_effect(me, EFFECT_CHAR_SHUT_0, 3600);
	}
	if( !get_effect(me, EFFECT_CHAR_DREAM_0) )		//不囚禁
	{
		set_effect(me, EFFECT_CHAR_DREAM_0, 3600);
	}
	if( !get_effect(me, EFFECT_CHAR_LAZY_0) )		//不延缓
	{
		set_effect(me, EFFECT_CHAR_LAZY_0, 3600);
	}
	if ( gone_time(go_time) >= 5 )				//回到原地
	{
		go_time = time();
		nXy = me->get_2("nPos");
		if ( sizeof(nXy) == 2 )
		{
			if ( abs(get_x(me)-nXy[0]) > 12 || abs(get_y(me)-nXy[1]) > 12 )
			{
				me->add_to_scene(get_z(me),nXy[0],nXy[1],4,9413);		
			}
		}
	}
	if ( gone_time(hptime) >= 15 )
	{
		hptime = time();
		//瞬间移动
		if ( objectp(enemy) )
		{
			z = get_z(enemy);z0=get_z(me);
			
			if( z == z0 && (p=distance_between(me, enemy)) < 20 && p > 1 )
			{
				x = get_x(enemy);y = get_y(enemy);
				x0 = get_x(me);y0 = get_y(me);
			        for( i = 0; i < 10; i ++ )
			        {
			                if( p = get_valid_xy(z, abs( x + random(3) - 1 ), abs( y + random(3) - 1 ), IS_CHAR_BLOCK) )
			                {
			                        x1 = p / 1000;  y1 = p % 1000;  break;
			                }
			        }
			        if ( x1 && y1 && z )
			        {
		                        me->add_to_scene( z, x1, y1,4,9413);
		                        me->to_front_xy(x, y);
				}
			}
			
		}
	}

	::heart_beat_walk();	
}

// 函数：特技攻击对手
int perform_action( object who ) 
{
	int rate,x,y,z,i,size;
	object me = this_object(),*char,*nTarget;

	if( distance_between(me, who) > me->get_max_seek() ) 
	{
		return 0;	
	}
	RelaxTime = 0;
	iRelax = 0;
	if ( gone_time(pTime) > 120 )
	{
		pTime = time();	
		summon_guard();
	}	
	rate = random100();
        	
	if ( rate < 10 )
	{
		set_skill(0211,9);
		return "skill/02/02117"->perform_action_npc(me,who);	//波动拳
	}
	else if ( rate < 20 )
	{
		set_skill(0241,28);
		return "skill/02/02415"->perform_action_npc(me,who);	//孤注一掷
	}
	else if ( rate < 30 )
	{
		set_skill(0251,6);
		return "skill/02/02514"->perform_action_npc(me,who);	//横扫千军
	}

	return 0;	
}

// 函数：死亡奖励
void win_bonus( object who ) { "npc/88/8800" ->win_bonus( this_object(), who ); }

void summon_guard() { "npc/88/8800" ->summon_guard( this_object() ); }
//设置名字颜色
string set_name_color(string cColor)
{
	if ( !stringp(cColor) )
		cColor = "";
	return cNameColor=cColor;
}