
#include <skill.h>
#include <effect.h>

inherit "/inh/item/poison";

// 函数：构造处理
void create()
{
        set_name( "软筋散" );
        set_picid_1(5215);
        set_picid_2(5215);
        set_unit( "包" );
        set_value(2000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "一种常见的毒药，能使目标全身无力，物理攻击力会下降50点，持续40秒。";
}

// 函数：使用效果
int get_poison_effect( object me, object who, int poison ) { return __FILE__ ->get_poison_effect_callout(me, who); }

// 函数：使用效果(在线更新)
int get_poison_effect_callout( object me, object who )
{
        if(    !get_effect(who, EFFECT_CHAR_5215)
        &&     !get_effect(who, EFFECT_CHAR_9140)    // 辟毒散
        &&      random(100) < 100 - who->get_anti_poison() )
        {
                set_effect(who, EFFECT_CHAR_5215, 30);

                if( who->is_user() ) 
                {
                        who->set_save( "5215", PF_FILE_05211->get_sub_ap(me) );
                        USER_ENERGY_D->count_ap(who);
                }
                else    who->add_ap( - PF_FILE_05211->get_sub_ap(me) );
        }
        return 1;
}
