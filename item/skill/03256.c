
// 自动生成：/make/item/make95

inherit "/inh/item/book3";

// 函数：构造处理
void create()
{
        set_name("Thiên Địa Kiếm Khí");
        set_picid_1(9808);
        set_picid_2(9808);
        set_unit("本");
        set_value(3000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Bộ sách ghi lại Pháp thuật cấp 150 của Thục Sơn \nSau khi sử dụng sẽ học được kĩ năng cấp 150 Thiên Địa Kiếm Khí \nHỗn Nguyên Chân Khí"; 
}

// 函数：获取门派名称
string get_family_name() { return " Thục Sơn"; }

// 函数：获取技能号码
int get_skill_id() { return 0325; }

// 函数：获取技能要求等级
int get_skill_level() { return 150; }

// 函数：获取特技标志
string get_perform_id() { return "03256"; }

// 函数：获取技能名称
string get_skill_name() { return "Hỗn Nguyên Chân Khí"; }
