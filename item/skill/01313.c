
// 自动生成：/make/item/make95

inherit "/inh/item/book4";

// 函数：构造处理
void create()
{
        set_name("Bery Hoa Châm");
        set_picid_1(9808);
        set_picid_2(9808);
        set_unit("本");
        set_value(3000);
        set_amount(1);
		set_no_give(1);		
        set_no_sell(1);
		set_no_drop(0);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Bộ sách ghi lại Pháp thuật cấp 1 của Vô môn phái \nSau khi sử dụng sẽ học được kĩ năng cấp 1 Bery Hoa Châm \nCơ Bản Kiếm Pháp."; 
}

// 函数：获取门派名称
//string get_family_name() { return " Vô Môn Phái."; }

// 函数：获取技能号码
int get_skill_id() { return 0131; }

// 函数：获取技能要求等级
int get_skill_level() { return 1; }

// 函数：获取特技标志
string get_perform_id() { return "01313"; }

// 函数：获取技能名称
string get_skill_name() { return "Cơ Bản Kiếm Pháp"; }
