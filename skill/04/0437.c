
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0437);
        set_name( "Cường Hoá Chính Xác" );
}

int get_learn_money() {return 28000; }

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_hit_rate(me); }

// 函数：获取描述
string get_desc() 
{
        return "[Cường Hoá Chính Xác] Gia tăng chính xác khi tấn công cho bản thân.\n";
}
