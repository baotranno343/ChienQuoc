
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0411);
        set_name( "Huyền Học Chính Đạo" );
}

// 函数：能否特殊技
void can_perform( object me )
{
	__DIR__ "04110"->can_perform(me);
}

// 函数：重计属性
void recount_char( object me ) 
{ 
        USER_ENERGY_D->count_max_mp(me); 
        USER_ENERGY_D->count_cp(me); 
}

// 函数：获取描述
string get_desc() 
{
        return "[Huyền Học Chính Đạo] 道家学说的进阶技能，提升法力上限，每级提升 4 点；提升法术攻击力，每级提升 1 点\n";
}
