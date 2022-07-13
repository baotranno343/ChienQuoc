
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0433);
        set_name( "Cường Hoá Nội Kháng" );
}

int get_learn_money() {return 33000; }

// 函数：重计属性
//void recount_char( object me ) { USER_ENERGY_D->count_max_mp(me); }

// 函数：获取描述
string get_desc() 
{
        return "[Cường Hoá Nội Kháng] Giảm sát thương Nội Công nhận được khi bị công kích.\n";
}
