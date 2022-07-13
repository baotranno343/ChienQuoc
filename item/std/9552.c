
inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 100; }

// 函数：法宝识别
int get_talisman_type() { return 6; }

// 函数：构造处理
void create()
{
        set_name( "土行珠" );
        set_picid_1(9551);
        set_picid_2(9551);
        set_unit( "颗" );

        set_level(2);
        set_value(10000);
        set_max_lasting(3099);

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "传送自己到当前场景的指定坐标";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：使用法宝效果
int get_use_effect_2( object me, object who, string arg ) { return __DIR__ "9551" ->get_use_effect_2_callout( me, who, this_object(), arg ); }
