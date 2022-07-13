
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0425
#define THIS_PERFORM    04250
#define PF_START       "04250"
#define PF_TIME        "04250#"
#define PF_NAME        "Xoay Chuyển Càn Khôn"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   900
#define SUB_MP          0

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 150\n Khi Khí Huyết giảm xuống dưới 30%% sử dụng sẽ hồi phục toàn bộ máu và pháp lực đồng thời huỷ bỏ tất cả thời gian chờ của tất cả kĩ năng.", PF_NAME);
        result = sprintf(HIY" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Tái sử dụng sau: %d giây\n Khi Khí Huyết giảm xuống dưới 30%% sử dụng sẽ hồi phục toàn bộ máu và pháp lực đồng thời huỷ bỏ tất cả thời gian chờ của tất cả kĩ năng.",
        	PF_NAME, SKILL_LEVEL, TIME_INTERVAL );
	return result;
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, interval, mp;
        object *user;
        object file;
        mapping skls;
        string *name;
        int skill, flag;
        int i, size;        

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("04250")==0) return 1;
		
        interval = TIME_INTERVAL;

        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if (me->get_hp() >= me->get_max_hp()*3/10)
        {
                printf( ECHO "Sử dụng " PF_NAME "\" chỉ khi Khí Huyết dưới 30%%." );
                return 1;        	
        }

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2",9);
        me->init_perform_dbase();
        if( mapp( skls = me->get_skill_dbase() ) && sizeof(skls) )    // 列示特殊技
        {
                name = sort_array( keys(skls), 1 );
                for( i = 0, size = sizeof(name); i < size; i ++ )
                {
                        skill = to_int( name[i] );
                        if ( ( file = load_object( SKILL->get_skill_file(skill) ) ) && file->get_name() )
                        {
                                file->can_perform(me);
                        }
                }
        }                
        me->set_perform( PF_TIME, interval );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
//	me->set_yuan(me->get_max_yuan());
	me->set_hp(me->get_max_hp());
	me->set_mp(me->get_max_mp());
//	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 32521, 1, OVER_BODY, PF_ONCE );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 42511, 2, OVER_BODY, PF_ONCE );
        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
        if (me->get_save("04250")==0) return;
		if( me->get_skill(THIS_SKILL) < SKILL_LEVEL )
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = PF_NAME;
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, MAGIC_ACT_BEGIN, 0, 9, 0);
}
