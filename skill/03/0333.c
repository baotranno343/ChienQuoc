
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0333);
        set_name( "Cường Hoá Hỗn Nguyên Chân Khí" );
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
        return "［Cường Hoá Hỗn Nguyên Chân Khí］Gia tăng pháp lực,mỗi cấp tăng 2.5 điểm.Gia tăng Nội kháng,mỗi cấp tăng 1.5 điẻm.";
}
