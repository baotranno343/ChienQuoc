
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0365);
        set_name( "Đường Môn Tâm Pháp" );
}
// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_hit_rate(me); }

// 函数：获取描述
string get_desc() 
{
        return "[Đường Môn Tâm Pháp] Tâm pháp độc môn của Đường gia, có thể nâng cao khả năng sử dụng ám khí. Mỗi cấp tăng thêm 0.2%độ chính xác và tăng 0.1%Bạo Kích.\n";
}
