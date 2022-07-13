
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0436);
        set_name( "Cường Hoá Dược Liệu" );
}

int get_learn_money() {return 20000; }

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_other(me); }

// 函数：获取描述
string get_desc() 
{
        return "[Cường Hoá Dược Liệu] Gia tăng hiệu quả hồi phục của thuốc, mỗi cấp tăng 4%, giảm thời gian sử dụng các loại thuốc 1 giây / 1 cấp.\n";
}
