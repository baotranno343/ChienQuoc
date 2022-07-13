
// 自动生成：/make/item/make95

inherit "/inh/item/book";
int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);
        set_unit("%s");
        set_value(%d);
}

// 函数：获取描述
string get_desc() 
{ 
        return "武功书籍，提升技能熟练度"; 
}

// 函数：获取门派名称
string get_family_name() { return "%s"; }

// 函数：获取技能号码
int get_skill_id() { return %04d; }

// 函数：获取技能名称
string get_skill_name() { return "%s"; }
