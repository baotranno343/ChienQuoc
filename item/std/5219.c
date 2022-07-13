
#include <effect.h>
#include <skill.h>

inherit "/inh/item/poison";

// 函数：构造处理
void create()
{
        set_name( "麻沸散" );
        set_picid_1(5219);
        set_picid_2(5219);
        set_unit( "包" );
        set_value(2000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "能使中毒者全身麻痹，失去知觉。药效会持续3秒。";
}

// 函数：使用效果
int get_poison_effect( object me, object who ) { return __FILE__ ->get_poison_effect_callout(me, who); }

// 函数：使用效果(在线更新)
int get_poison_effect_callout( object me, object who )
{
        object *user;

        if(    !get_effect(who, EFFECT_CHAR_FAINT_2)
        &&     !get_effect(who, EFFECT_CHAR_FAINT_3)
        &&     !get_effect(who, EFFECT_CHAR_9145)    // 清心丹
        &&      random(100) < 100 - who->get_immunity() )
        {
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_FAINT_2, 3);
                CHAR_CHAR_D->stop_loop_perform_faint(who);
                send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT_2), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );
        }

        return 1;
}
