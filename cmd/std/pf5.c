//宠物使用技能
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
int main( object me, string arg )
{
        object file, what,pet;
        string id, item, family;
        int busy, pf, x, y, which;

	if ( !(pet=me->get("showbeast")) )
	{
                notify( "您要使用哪个宠物？" );
		return 1;
	}
        if( me->is_store_open() )
        {
                notify( "您在摆摊，不能打架。" );
                return 1;
        }
        if( gone_time( pet->get_time("pf") ) < 1 )    // 时间限制
        {
                return 1;
        }
//      me->set_time( "pf", time() );    // 由 pf 成功后设置

        if(     get_effect(pet, EFFECT_CHAR_FAINT) 
        ||      get_effect(pet, EFFECT_CHAR_FAINT_2)
        ||      get_effect(pet, EFFECT_SLEEP)
        ||      get_effect(pet, EFFECT_MAGIC_4243)
        ||      get_effect(pet, EFFECT_CHAR_FREEZE)
        ||      get_effect(pet, EFFECT_CHAR_DREAM_1)
        ||      get_effect(pet, EFFECT_CHAR_DREAM) ) return 1;

//        if( get_heart_count_2(me) > 0 )
//        {
//                me->set_force_command("pf " + arg);    // 暂存特殊技命令
//                return 1;
//        }

//        CHAR_CHAR_D->stop_loop_perform_9(me);    // 中断持续效果(其它)

        if( get_effect(pet, EFFECT_CHAR_INVISIBLE) ) 
        {
        	set_effect_2(pet, EFFECT_CHAR_INVISIBLE, 1, 1 );    // 隐身(中断)
        }

        if( !arg ) return 1;

        if( me->get_char_action() != DEFAULT_ACT ) me->set_char_action(DEFAULT_ACT);    // 恢复站立状态(中止小动作)



        if( sscanf( arg, "%d %d,%d", pf, x, y ) == 3 )		//对座标
        {
                if(   ( file = load_object( SKILL->get_perform_file(pf) ) )
                &&      file->get_perform_type() == ON_XY_P )
                        file->perform_action_npc(pet, 0, x, y, "");
        }
        else if( sscanf( arg, "%d %s", pf, arg ) == 2 )
        {
                if(   ( file = load_object( SKILL->get_perform_file(pf) ) )
                &&      file->get_perform_type() == ON_CHAR_P 
                &&    ( what = find_char(arg) ) )
                {
                	if (what!=pet)
                	{
                		// 不能锁定隐身的人
                		if (get_effect(what, EFFECT_CHAR_INVISIBLE)) return 1;
                	}
                        if ( file->perform_action_npc(pet, what) )
                        	pet->set_enemy_3(what);
		}                       
        }        
        else if( pf = to_int(arg) )
        {
                if(   ( file = load_object( SKILL->get_perform_file(pf) ) )
                &&      file->get_perform_type() == ON_ME_P )
                        file->perform_action_npc(pet, 0);
        }
        
        return 1;
}
