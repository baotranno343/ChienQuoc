
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0435);
        set_name("Cường Hoá Bạo Kích");
}

int get_learn_money() { return 30000; }

// 函数：重计属性
void recount_char(object me) { USER_ENERGY_D->count_hit_rate(me); }

// 函数：获取描述
string get_desc()
{
        return "[Cường Hoá Bạo Kích] Gia tăng Bạo Kích khi công kích.\n";
}
