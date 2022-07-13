
#include <ansi.h>
#include <skill.h>
#include <equip.h>

// 函数：命令处理
int main( object me, string arg )
{
        mapping skls;
        object *inv, item;
        string cmd0, cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7;
        string *name, file;
        int family, level, level2, weapon, armor;
        int p, i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }


        if( arg ==0  )
        {
        	cmd1 = "bian 10\n";
        	cmd2 = "bian 11\n";
        	cmd3 = "bian 301\n";
        	cmd4 = "bian 402\n";
        	cmd5 = "bian 4145\n";
        	cmd6 = "bian 4143\n";
        	cmd7 = "bian 1052\n";
        	cmd0 = "bian cancel\n";
                send_user( me, "%c%s", ':', "您想把自己设为哪种门派？\n"
                        ESC "山鸡\n" + cmd1 +
                        ESC "兔子\n" + cmd2 +
                        ESC "蜘蛛\n" + cmd3 +
                        ESC "龟丞相\n" + cmd4 +
                        ESC "豆兵\n" + cmd5 +
                        ESC "天将\n" + cmd6 +
                        ESC "道长\n" + cmd7 +
                        ESC "Huỷ bỏ biến thân\n" + cmd0);
                return 1;
        }
        if (arg=="cancel")
        {
        	me->set_save("temp_act", 0);
        	me->add_to_scene( get_z(me), get_x(me), get_y(me));
        	return 1;
        }
        i = to_int(arg);
        me->set_save("temp_act", i);
        me->add_to_scene( get_z(me), get_x(me), get_y(me));
        return 1;
}
