
inherit SKILL;

// 函数：构造处理
void create()
{
	set_number(0242);
	set_name("Thương Côn Bộ Pháp");
}

// 函数：能否特殊技
void can_perform(object me)
{
	__DIR__ "02421"->can_perform(me);
	__DIR__ "02422"->can_perform(me);
	// 	__DIR__ "02423"->can_perform(me);
	// 	__DIR__ "02424"->can_perform(me);
	// //	__DIR__ "02425"->can_perform(me);
	// 	__DIR__ "02426"->can_perform(me);
	// 	__DIR__ "02427"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
	send_user(me, "%c%w%w", 0x50, 0xffff, 02421);
	send_user(me, "%c%w%w", 0x50, 0xffff, 02422);
	//		send_user( me, "%c%w%w", 0x50, 0xffff, 02425 );
}

// 函数：重计属性
void recount_char(object me)
{
	USER_ENERGY_D->count_dp(me);
}

// 函数：获取描述
string get_desc()
{
	return "[Thương Côn Bộ Pháp] Tâm pháp rèn luyện các chiêu thức Thương và Côn. Mỗi cấp tăng 0.6 điểm phòng thủ.\n";
}
