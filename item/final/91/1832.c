
#include <skill.h>
#include <effect.h>

inherit "/inh/item/poison";

// 函数：获取毒性点数
int get_poison() { return 600; }

// 函数：成品编号
int get_fin_type() { return 1832; }

// 函数：构造处理
void create()
{
        set_name( "Khổng Tước Đàm" );
        set_picid_1(4226);
        set_picid_2(4226);
        set_unit( "包" );
        set_value(300);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Mỗi 2 giây sử dụng làm tiêu hao 60 điểm Khí Huyết, hiệu quả 20 giây";
}

// 函数：使用效果
int get_poison_effect( object me, object who, int poison ) { return __FILE__ ->get_poison_effect_callout(me, who, poison); }

// 函数：使用效果(在线更新)
int get_poison_effect_callout( object me, object who, int poison )
{
        if(    !get_effect(who, EFFECT_CHAR_POISON)
        &&     !get_effect(who, EFFECT_CHAR_9140)    // 辟毒散
        &&      random(100) < 100 - who->get_anti_poison() )
        {
                who->set_poison(poison);
                set_effect_2(who, EFFECT_CHAR_POISON, 10, 2);
                send_user( who, "%c%w%w%c", 0x81, 9096, get_effect_3(who, EFFECT_CHAR_POISON), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9096, 1, EFFECT_BAD );
        }
        return 1;
}
