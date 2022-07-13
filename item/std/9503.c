
inherit TALISMAN;

// 函数：法宝识别
int get_talisman_type() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "灵通宝玉" );
        set_picid_1(9501);
        set_picid_2(9501);
        set_unit( "块" );

        set_level(3);
        set_value(20000);
        set_max_lasting(24099);
        set("hp", 80);  
        set("mp", 80);  
        set("ap", 20);  
        set("dp", 20);  
        set("cp", 20);  
        set("pp", 20);  
        set("sp", 20);  

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "增加人物属性";
}
