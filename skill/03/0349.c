
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0349);
        set_name( "Ma Luyện" );
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
        return "[Khổ Luyện] Tâm pháp rèn luyện. Mỗi cấp tăng thêm 5 điểm Khí Huyết tối đa và tăng thêm 3 sát thương.";
}
