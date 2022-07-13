
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0104);
        set_name( "Nhập môn Thân Thủ Vô Ảnh" );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_dodge_rate(me); }

// 函数：获取描述
string get_desc() 
{
        return "[Vô Ảnh Thần Bộ] Là loại khinh công tâm pháp, có thể tăng cao khả năng tránh đòn của người tập luyện. Mỗi cấp tăng 0.15% né tránh.\n";
}
