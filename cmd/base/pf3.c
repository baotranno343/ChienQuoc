// 专用于归元术
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数:命令处理
int main( object me, string arg )
{
        object file, what;
        string id, item;
        int busy, pf, x, y, which;


        if( !arg ) return 1;
        if( !me->is_die() ) return 1;
        if (arg!="3293" ) return 1;

	if( pf = to_int(arg) )
        {
                if(   ( file = load_object( SKILL->get_perform_file(pf) ) )
                &&    ( file->get_perform_type() == ON_ME_7 || file->get_perform_type() == ON_TALISMAN ) )
                        file->main(me, 0, 0, 0, "");
        }

        return 1;
}
