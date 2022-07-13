
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

// 函数：命令处理
int main( object me, string arg )
{
        mapping skls;
        object *inv, item;
        string cmd0, cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7;
        string cmd10, cmd20, cmd30, cmd40, cmd50, cmd60, cmd70;
        string *name, file;
        int family, level, level2, weapon, armor, skill;
        int p, i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        if( !is_gm2(me) && !is_god(me) && !is_gm3(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }        
        if( !arg )
        {
               return 1;
        }
	if (arg=="0")
	{
                set_effect(me, EFFECT_USER_DIE, 0);
                me->set_die(0);
                me->set_hp( me->get_max_hp() );
                me->set_mp( me->get_max_mp() );

                me->set_login_flag(2);    // 跳转保护
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 2);
		return 1;		
	}
	else
		me->set_die(1);
        return 1;
}
