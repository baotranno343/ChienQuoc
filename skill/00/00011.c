
#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM 00011
#define PF_NAME "Đi theo"

// 函数：获取描述
string get_desc(object me)
{
        return "[ " PF_NAME " ]\n Di chuyển theo người chơi khác. \n ";
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        //	object obj;
        //
        //	if ( me->is_store_open() )
        //	{
        //		send_user(me,"%c%s",'!',"你在摆摊，不能跟随！");
        //		return 1;
        //	}
        //	if ( me == who )
        //	{
        //		send_user(me,"%c%s",'!',"不能跟随自己！");
        //		return 1;
        //	}
        //	if ( !me->get_team_id() )
        //	{
        //		send_user(me,"%c%s",'!',"你必须加入队伍才能选择跟随！");
        //		return 1;
        //	}
        //	if ( !me->get_team_id() || me->get_team_id() != who->get_team_id() )
        //	{
        //		send_user(me,"%c%s",'!',"对方不是你的队伍成员！");
        //		return 1;
        //	}
        //	while(obj=find_char(sprintf("%d",who->get("team_followed"))))
        //		who=obj;
        //	if ( !who || distance(me,who) > 15 )
        //	{
        //		send_user(me,"%c%s",'!',"你距离太远，请靠近些再跟随。");
        //		return 1;
        //	}
        //	who->set("team_followed",me->get_number());
        //	me->set("team_follow",who->get_number());
        //
        //	send_user(who,"%c%s",'!',"玩家"+me->get_name()+"进入跟随。");
        //	send_user(me,"%c%s",'!',"你进入跟随状态");
        //	send_user( me, "%c%w%w%c", 0x81, 0011, -1, EFFECT_GOOD );

        return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_CHAR_7; }

// 函数：能否使用指令
void can_perform(object me)
{
        send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME);
}
