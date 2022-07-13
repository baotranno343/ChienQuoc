
// 开关技能  TIPS:[PF_SWITCH]

#include <ansi.h>
#include <skill.h>

#define THIS_SKILL      0317
#define THIS_PERFORM    03172
#define PF_FLAG        "03172"
#define PF_NAME        "Nguyên Khí Quy Nguyên"

#define SKILL_LEVEL     10

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 10 cấp\n    Phương pháp vận khí điều tức của Đào Hoa Nguyên, tự tiêu hao 100 điểm Khí Huyết để liên tục luyện thành Nguyên Khí trong 30 phút.";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n     Phương pháp vận khí điều tức của Đào Hoa Nguyên, tự tiêu hao 100 điểm Khí Huyết để liên tục luyện thành Nguyên Khí trong 30 phút.", 
        	PF_NAME, SKILL_LEVEL);
        return result;
}

// 函数:获取描述(持续)
string get_loop_desc( object me )
{
        if( me->get_perform(PF_FLAG) )
                return sprintf( PF_NAME ":\n　　Mỗi 2 giây hồi phục 1 điểm nguyên khí.\n" );
        else    return sprintf( PF_NAME "\n" );
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{	
        if( me->get_perform(PF_FLAG) )    // 关闭
        {
                me->delete_perform(PF_FLAG);
                printf( ECHO "Bạn thu hồi \"%s\".", PF_NAME );

                send_user( me, "%c%w%w%c", 0x81, 3172, 0, EFFECT_GOOD );
                send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3172, 0, EFFECT_GOOD );
        }

        else if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) return 1;

        else    // 打开
        {
		if (me->get_hp()<100)
		{
			printf( ECHO "Khí Huyết không đủ 100, không thể sử dụng \"%s\".", PF_NAME );
			return 1;
		}        	
        	me->add_hp(-100);
                me->set_perform(PF_FLAG, time());
                printf( ECHO "Bạn ngưng vận khí \"%s\".", PF_NAME );

                send_user( me, "%c%w%w%c", 0x81, 3172, 1800, EFFECT_GOOD );
                send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3172, 1, EFFECT_GOOD );
		
		CHAR_FIGHT_D->set_enmity1(me, 180 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/10*50);        
        }

        return 1;
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform( object me )
{
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }	
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
