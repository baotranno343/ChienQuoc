
#include <skill.h>
#include <effect.h>

inherit "/inh/item/poison";

// 函数：成品编号
int get_fin_type() { return 1816; }

// 函数：构造处理
void create()
{
        set_name( "Mê Thần Tán" );
        set_picid_1(5216);
        set_picid_2(5216);
        set_unit( "包" );
        set_value(2000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm cần dùng của Vân Mộng Cốc, hiệu quả gây mộng du 30 giây";
}

// 函数：使用效果
int get_poison_effect( object me, object who, int poison ) { return __FILE__ ->get_poison_effect_callout(me, who); }

// 函数：使用效果(在线更新)
int get_poison_effect_callout( object me, object who )
{
        if(    !who->get("anti_dream")
        &&     !get_effect(who, EFFECT_CHAR_DREAM_0)
        &&     !get_effect(who, EFFECT_CHAR_DREAM_1)
        &&     !get_effect(who, EFFECT_CHAR_DREAM)
        &&     !get_effect(who, EFFECT_CHAR_9140)    // 辟毒散
        &&      random(100) < 100 - who->get_anti_poison() )
        {
                send_user(who, "%c%c%c", 0x3d, 240, 1);    // 系统端走路
                set_effect(who, EFFECT_CHAR_DREAM_1, 2);    // set_effect_2(who, EFFECT_CHAR_DREAM, 8, 1);
                CHAR_CHAR_D->stop_loop_perform_faint(who);
                send_user( who, "%c%w%w%c", 0x81, 9016, get_effect_3(who, EFFECT_CHAR_DREAM_1), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9016, 1, EFFECT_BAD );
        }
        return 1;
}
