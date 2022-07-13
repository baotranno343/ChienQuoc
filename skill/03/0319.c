
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0319);
        set_name("Chu Thiên Vạn Chuyển");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "03191"->can_perform(me);
        __DIR__ "03192"->can_perform(me);
        //	__DIR__ "03193"->can_perform(me);
}

// 函数：重计属性
void recount_char(object me) { USER_ENERGY_D->count_max_hp(me); }

// 函数：获取描述
string get_desc()
{
        return "[Chu Thiên Vạn Chuyển]Bộ tâm pháp rèn luyện nâng cao điểm Khí Huyết tối đa. Mỗi cấp tăng thêm 6 điểm Khí Huyết\n";
}
