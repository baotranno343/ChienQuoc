
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

        set_level(1);
        set_value(5000);
        set_max_lasting(8099);
        set("hp", 20);  
        set("mp", 20);  
        set("ap", 5);  
        set("dp", 5);  
        set("cp", 5);  
        set("pp", 5);  
        set("sp", 5);  

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "增加人物属性";
}
