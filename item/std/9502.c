
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

        set_level(2);
        set_value(10000);
        set_max_lasting(16099);
        set("hp", 40);  
        set("mp", 40);  
        set("ap", 10);  
        set("dp", 10);  
        set("cp", 10);  
        set("pp", 10);  
        set("sp", 10);  

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "增加人物属性";
}
