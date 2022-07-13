
inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 90; }

// 函数：法宝识别
int get_talisman_type() { return 5; }

// 函数：构造处理
void create()
{
        set_name( "驱神令" );
        set_picid_1(9541);
        set_picid_2(9541);
        set_unit( "块" );

        set_level(3);
        set_value(20000);
        set_max_lasting(12099);

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "传送其它玩家到当前场景的随机位置";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：使用法宝效果
int get_use_effect_2( object me, object who, string arg ) { return __DIR__ "9541" ->get_use_effect_2_callout( me, who, this_object(), arg ); }
