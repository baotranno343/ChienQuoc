
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0544);
        set_name( "Cường Hoá Mê Hồn Quyết" );
}

// 函数：重计属性
void recount_char( object me ) 
{ 
//	USER_ENERGY_D->count_max_hp(me); 
	USER_ENERGY_D->count_hit_rate(me); 
}

// 函数：获取描述
string get_desc() 
{
        return "［Cường Hoá Mê Hồn Quyết］云梦泽的特殊技法，每级追加0.09％的法术爆击效果";
}
