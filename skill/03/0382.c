
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0382);
        set_name( "Cường Hoá Đường Môn Độc Kinh" );
}

// 函数：重计属性
void recount_char( object me ) 
{ 
//	USER_ENERGY_D->count_max_hp(me); 
	USER_ENERGY_D->count_dp(me); 
}

// 函数：获取描述
string get_desc() 
{
        return "［Cường Hoá Đường Môn Độc Kinh］Gia tăng Ngoại Kháng khi trang bị Ám Khí, mỗi cấp tăng lên 2 điểm.";
}
