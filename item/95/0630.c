
// 自动生成：/make/item/make95

inherit "/inh/item/book";
int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Nhập môn Luyện Đơn");
        set_picid_1(9503);
        set_picid_2(9503);
        set_unit("本");
        set_value(10000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Sách võ công, nâng trình độ thành thạo kỹ năng"; 
}

// 函数：获取门派名称
string get_family_name() { return " －"; }

// 函数：获取技能号码
int get_skill_id() { return 0630; }

// 函数：获取技能名称
string get_skill_name() { return "Luyện Đơn"; }
