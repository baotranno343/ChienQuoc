
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0431);
        set_name( "Cường Hoá Ngoại Kháng" );
}

int get_learn_money() {return 35000; }

// 函数：重计属性
//void recount_char( object me ) { USER_ENERGY_D->count_max_mp(me); }

// 函数：获取描述
string get_desc() 
{
        return "[Cường Hoá Ngoại Kháng] Giảm sát thương Ngoại Công nhận được khi bị công kích.\n";
}
