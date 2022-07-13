
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0405);
        set_name( "Tu Tâm" );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_max_mp(me); }

// 函数：获取描述
string get_desc() 
{
        return "［Minh Tư］ Phương pháp tu luyện tinh thần, mỗi cấp gia tăng 1% Pháp Lực.\n";
}
