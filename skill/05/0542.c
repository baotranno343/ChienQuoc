
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0542);
        set_name( "Cường Hoá Y Thuật" );
}

// 函数：重计属性
void recount_char( object me ) 
{ 
	USER_ENERGY_D->count_max_mp(me); 
	USER_ENERGY_D->count_pp(me); 
}

// 函数：获取描述
string get_desc() 
{
        return "［Cường Hoá Y Thuật］提升云梦泽的最大法术力，每级提升4点；提升法术防御力，每级提升2点";
}
