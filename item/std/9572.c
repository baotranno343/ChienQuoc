
inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 60; }

// 函数：法宝识别
int get_talisman_type() { return 8; }

// 函数：构造处理
void create()
{
        set_name( "极乐木鱼" );
        set_picid_1(9571);
        set_picid_2(9571);
        set_unit( "只" );

        set_level(2);
        set_value(10000);
        set_max_lasting(1299);

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "使等待救援的死亡玩家直接复活，相当于“自动复活”";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：使用法宝效果
int get_use_effect_2( object me, object who, string arg ) { return __DIR__ "9571" ->get_use_effect_2_callout( me, who, this_object(), arg ); }
