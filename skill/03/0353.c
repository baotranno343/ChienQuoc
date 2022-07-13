
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0353);
        set_name( "Cường Hóa Thương Côn Bộ Pháp" );
}

// 函数：重计属性
void recount_char( object me ) 
{ 
	USER_ENERGY_D->count_dp(me); 
}

// 函数：获取描述
string get_desc() 
{
        return "[Cường Hóa Thương Côn Bộ Pháp] 提升使用枪和棍的防御力，每级提升2点";
}
