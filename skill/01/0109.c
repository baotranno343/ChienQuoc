
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0109);
        set_name( "Kinh Lạc Học Thuyết" );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_max_hp(me); }

// 函数：获取描述
string get_desc() 
{
        return "[Kinh Lạc Học Thuyết] Giúp cho người học đả thông tất cả kinh mạch trên cơ thể. Mỗi cấp tăng 5 điểm Khí Huyết.\n";
}
