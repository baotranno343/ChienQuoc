
inherit RESOURCE;

// 函数：构造处理
void create()
{
	set_char_picid(%d);			// 函数：设置人物造型
        set_name("%s");				// 函数：设置称谓
        set("time", 1+random(3));		// 函数：设置资源量
        set_reset_file("/sys/item/stuff3");	// 函数：设置刷新文件
        set_tool_type(21);			// 函数：设置工具类型
        set_pf_name("采药");			// 函数：设置技能名称
        set_stuff_number(%d);			// 函数：设置资源编号
        set_tool_level(%d);			// 函数：设置工具等级
        set_reset_time(%d);			// 函数：设置刷新时间
        set_skill_exp(%d);			// 函数：设置采集经验奖励
        set_skill_level(%d);			// 函数：设置对应的技能等级
        set_this_skill(610);			// 函数：设置对应的技能类型
        setup();
}