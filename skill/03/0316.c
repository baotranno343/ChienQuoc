
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0316);
        set_name("Kim Cương Bất Hoại");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "03161"->can_perform(me);
        __DIR__ "03162"->can_perform(me);
        // __DIR__ "03163"->can_perform(me);
        // __DIR__ "03164"->can_perform(me);
        // __DIR__ "03165"->can_perform(me);
        // __DIR__ "03166"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 03161);
        send_user(me, "%c%w%w", 0x50, 0xffff, 03162);
}

// 函数：重计属性
void recount_char(object me) { USER_ENERGY_D->count_anti_hurt(me); }

// 函数：获取描述
string get_desc()
{
        return "[Kim Cương Bất Hoại]Tâm pháp bí truyền rèn luyện cơ thể. Giảm bớt sát thương Ngoại Công nhận được.\n";
}
