
// 自动生成：/make/item/make96

inherit "/inh/item/book2";
int get_item_color() { return 2; }
// 函数：构造处理
void create()
{
        set_name("Bí kíp Chu Thiên Vạn Chuyển");
        set_picid_1(9604);
        set_picid_2(9604);
        set_unit("本");
        set_value(50000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Bí kiếp võ công, thăng lên 1 cấp kỹ năng"; 
}

// 函数：获取门派名称
string get_family_name() { return " Đào Hoa Nguyên"; }

// 函数：获取技能号码
int get_skill_id() { return 0319; }

// 函数：获取技能名称
string get_skill_name() { return "Chu Thiên Vạn Chuyển"; }
