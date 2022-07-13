
inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 75; }

// 函数：生效时间
int get_time_interval() { return 300; }

// 函数：法宝识别
int get_talisman_type() { return 7; }

// 函数：构造处理
void create()
{
        set_name( "撼天钟" );
        set_picid_1(9561);
        set_picid_2(9561);
        set_unit( "个" );

        set_level(2);
        set_value(10000);
        set_max_lasting(2099);

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "压制对方法宝，使其在一段时间内失去效用";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：使用法宝效果
int get_use_effect_2( object me, object who, string arg ) { return __DIR__ "9561" ->get_use_effect_2_callout( me, who, this_object(), arg ); }
