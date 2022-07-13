
#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
        int rate;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        rate = to_int(arg);

        me->set_ap_0( me->get_ap() * rate / 100 );
        me->set_dp_0( me->get_dp() * rate / 100 );
        me->set_cp_0( me->get_cp() * rate / 100 );
        me->set_pp_0( me->get_pp() * rate / 100 );
//      me->set_sp_0( me->get_sp() * rate / 100 );

        tell_user( me, "设置最小／最大比率为 %d％。", rate );

        return 1;
}
