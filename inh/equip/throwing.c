
#include <ansi.h>
#include <equip.h>

inherit WEAPON;

// 函数：设置耐久度
int set_lasting( int time )
{
        object who, obj;
/*
        if( time < 1 )    // 耐久为 0 消失
        {
                obj = this_object();
                if( who = obj->get_owner() ) 
                {
                        write_user( who, HIR "您装备的%s用完了！", obj->get_name() );
                        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w", 0x7c, getoid(who), UNARMED );
                }
                obj->remove_from_user();
                destruct(obj);
        }
        else    
*/        
        ::set_lasting(time);

        return time;
}
