
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0354);
        set_name( "Cường Hóa Ma Luyện" );
}

// 函数：重计属性
void recount_char( object me ) 
{ 
	USER_ENERGY_D->count_max_hp(me); 
	USER_ENERGY_D->count_ap(me); 
}

// 函数：获取描述
string get_desc() 
{
        return "[Cường Hóa Ma Luyện] 提升气血上限，每级提升6点；提升装备枪的物理攻击力，每级提升4点；提升装备棍的物理攻击力，每级提升4点";
}
