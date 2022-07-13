
inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 35; }

// 函数：法宝识别
int get_talisman_type() { return 3; }

// 函数：构造处理
void create()
{
        set_name( "摄魂铃" );
        set_picid_1(9521);
        set_picid_2(9521);
        set_unit( "口" );

        set_level(3);
        set_value(20000);
        set_max_lasting(45099);

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "物理攻击时，可使对方眩晕";
}
