#include <ansi.h>
#include <skill.h>
#include <task.h>
#include <effect.h>

#define TIME_INTERVAL   20
#define CASH_BONUS	200
#define EXP_BONUS	50
#define POT_BONUS	5
#define SUB_STR		20

// 函数：生成二进制码
void SAVE_BINARY() { }

//开始打工
void begin_work(object me,int iType)
{
	int iTime;
	me->set("work_type",iType);
	iTime = me->get_strength();
	set_effect_2(me, EFFECT_USER_WORK,  iTime/SUB_STR+2, TIME_INTERVAL);	//20秒调用一次
	send_user(me, "%c%c%w%s", 0x5a, 0,iTime/SUB_STR*TIME_INTERVAL, "辛勤劳动中……");
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 02011, 10, OVER_BODY, PF_LOOP );
}
//中断打工
void effect_work_break(object me)
{
	set_effect(me, EFFECT_USER_WORK, 0);
	send_user(me, "%c%c%c", 0x5a, 1, 0);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 02011, 0, OVER_BODY, PF_STOP );
	me->delete("work_type");
}
//打工报酬
void work_bonus(object me)
{
	int iType, money;
	iType = me->get("work_type");
	if ( me->get_strength(me) < SUB_STR )
	{
		effect_work_break(me);
		return ;
	}
	me->add_strength(-SUB_STR);
	if ( iType == NEWBIE_WORK )	//新手村
	{
		me->add_exp(EXP_BONUS);
		me->add_potential(POT_BONUS);
		me->add_cash(CASH_BONUS/2);
		me->add_log("&newbiework", EXP_BONUS);
		me->add_log("*newbiework", POT_BONUS);
		me->add_log("$newbiework", CASH_BONUS/2);
		me->add_log("#newbiework", 1);	
		money = CASH_BONUS/2;
		write_user( me, ECHO "通过辛勤的劳动，你获得了"+EXP_BONUS+"点经验值、"+money+"金和"+POT_BONUS+"点潜能。");		
	}
	else if ( iType == ZHOU_WORK )	//Chu Quốc
	{
		me->add_exp(EXP_BONUS);
		me->add_cash(CASH_BONUS);
		me->log_money("工作", CASH_BONUS);                
		"/sys/sys/count"->add_income("work", CASH_BONUS);
		me->add_log("&newbiework", EXP_BONUS);
		me->add_log("$newbiework", CASH_BONUS);
		me->add_log("#newbiework", 1);			
		write_user( me, ECHO "通过辛勤的劳动，你获得了"+EXP_BONUS+"点经验值和"+CASH_BONUS+"金。");		
	}			
	if ( me->get_strength(me) <= 0 )
	{
		effect_work_break(me);
		return ;
	}	
}
