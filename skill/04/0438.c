
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0438);
        set_name( "Cường Hoá Thể Chất" );
}

int get_learn_money() {return 32000; }

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_max_hp(me); }

// 函数：获取描述
string get_desc() 
{
        return "[Cường Hoá Thể Chất] Gia tăng thể lực cho bản thân, mỗi cấp tăng 1.5% Khí Huyết.\n";
}
