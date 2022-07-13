#include <npc.h>
#include <cmd.h>
#include <time.h>
#include <ansi.h>
#include <chia_kenh.h>
#define FILE_SAVE "data/mingren" SAVE_EXTENSION
#define FILE_SHOUXI "sys/school/shouxi"
#define FILE_TITLE "sys/sys/title"
#define FILE_ENERGY "sys/user/energy"
#define FILE_UPDATE "mingren_update.txt"
#define DEBUG(arg) ; //if(find_char("1")) tell_user(find_char("1"),arg);

inherit DBASE_F;
inherit SAVE_F;

static string *SchoolName = ({
	"Đào Hoa Nguyên",
	"Cấm Vệ Quân",
	"Thục Sơn",
	"Côn Luân",
	"Mao Sơn",
	"Vân Mộng Cốc",
	"Đường Môn",
});
mapping Exp_players, Cash_players, Teacher_players, Gongde_players, Dizi_players;
mapping Enable_id = ([]);

int xy_get_fam_id(string name);
void delete_mingren_title(object who, string titlecode);
int get_sum_skills_level(object who);
int get_mingren_power(object who);
void send_mingren_data(object who, mapping players, string type);

// 函数：生成二进制码
void SAVE_BINARY() {}

//排行数据保存
string get_save_file() { return FILE_SAVE; }

//初始化对象
void create()
{
	restore();
}
//对话处理
void do_look(object who)
{
	int i, size, level, point, xy_family;
	string name, family;
	if (!mapp(Exp_players) && !mapp(Cash_players) && !mapp(Teacher_players) && !mapp(Gongde_players) && !mapp(Dizi_players))
	{
		notify(HIY "Danh nhân đường trước mắt không thay đổi");
		return;
	}
	send_user(who, "%c%c", 0xA9, 0);
	send_mingren_data(who, Exp_players, "power");		//发送实力表
	send_mingren_data(who, Cash_players, "cash");		//发送财富表
	send_mingren_data(who, Teacher_players, "teacher"); //发送名师表
	send_mingren_data(who, Gongde_players, "gongde");	//发送功德表
	if (mapp(Dizi_players))								//首席大弟子
	{
		size = sizeof(SchoolName);
		DEBUG(sprintf("测试-->Dizi_players size=%d", size));
		for (i = 0; i < size; i++)
		{
			if (!mapp(Dizi_players[SchoolName[i]]))
				continue;
			family = Dizi_players[SchoolName[i]]["family"];
			xy_family = xy_get_fam_id(family);
			name = Dizi_players[SchoolName[i]]["name"];
			DEBUG(sprintf("测试-->Dizi_players name=%s", name));
			level = Dizi_players[SchoolName[i]]["level"];
			point = Dizi_players[SchoolName[i]]["point"];
			send_user(who, "%c%c%c%c%d%s", 0xA9, 5, xy_family, level, point, name);
		}
	}
	DEBUG(sprintf("测试-->do_look "));
}

void do_look1(object who)
{
	int i, size, level, point, xy_family;
	string name, family;
	if (!mapp(Exp_players))
	{
		//	notify( HIY"Bảng xếp hạng Thực Lực trước mắt không thay đổi");
		return;
	}
	send_user(who, "%c%c", 0xA9, 0);
	send_mingren_data(who, Exp_players, "power");
	DEBUG(sprintf("测试-->do_look1 "));
}
void do_look2(object who)
{
	int i, size, level, point, xy_family;
	string name, family;
	if (!mapp(Cash_players))
	{
		//	notify( HIY"Bảng xếp hạng Phú hộ trước mắt không thay đổi");
		return;
	}
	send_user(who, "%c%c", 0xA9, 0);
	send_mingren_data(who, Cash_players, "cash");
	DEBUG(sprintf("测试-->do_look2 "));
}
void do_look3(object who)
{
	int i, size, level, point, xy_family;
	string name, family;
	if (!mapp(Teacher_players))
	{
		//	notify( HIY"Bảng xếp hạng Danh Sư trước mắt không thay đổi");
		return;
	}
	send_user(who, "%c%c", 0xA9, 0);
	send_mingren_data(who, Teacher_players, "teacher");
	DEBUG(sprintf("测试-->do_look3 "));
}
void do_look4(object who)
{
	int i, size, level, point, xy_family;
	string name, family;
	if (!mapp(Gongde_players))
	{
		//	notify( HIY"Bảng xếp hạng Công Đức trước mắt không thay đổi");
		return;
	}
	send_user(who, "%c%c", 0xA9, 0);
	send_mingren_data(who, Gongde_players, "gongde");
	DEBUG(sprintf("测试-->do_look4 "));
}
void do_look5(object who)
{
	int i, size, level, point, xy_family;
	string name, family;
	if (!mapp(Dizi_players))
	{
		//	notify( HIY"Bảng xếp hạng Đại Đệ Tử Môn Phái trước mắt không thay đổi");
		return;
	}
	send_user(who, "%c%c", 0xA9, 0);
	//	send_mingren_data(who,Dizi_players,"winners");
	if (mapp(Dizi_players)) //首席大弟子
	{
		size = sizeof(SchoolName);
		DEBUG(sprintf("测试-->Dizi_players size=%d", size));
		for (i = 0; i < size; i++)
		{
			if (!mapp(Dizi_players[SchoolName[i]]))
				continue;
			family = Dizi_players[SchoolName[i]]["family"];
			xy_family = xy_get_fam_id(family);
			name = Dizi_players[SchoolName[i]]["name"];
			DEBUG(sprintf("测试-->Dizi_players name=%s", name));
			level = Dizi_players[SchoolName[i]]["level"];
			point = Dizi_players[SchoolName[i]]["point"];
			send_user(who, "%c%c%c%c%d%s", 0xA9, 5, xy_family, level, point, name);
		}
	}
	DEBUG(sprintf("测试-->do_look5 "));
}
//设置排行榜更新时间
void check_time()
{
	int i, size;
	object *user;
	mixed mixtime;

	mixtime = localtime(get_party_time());
	DEBUG(sprintf("check_time,当前游戏时间 %s", short_time(get_party_time())));
	if (!arrayp(user = USER_D->get_user()))
		return;
	//发布排行榜前对所有在线玩家再次统计
	size = sizeof(user);
	for (i = 0; i < size; i++)
	{
		DEBUG("测试-->发布前最后一次对所有在线玩家更新排行榜");
		DEBUG(sprintf("测试-->当前在线玩家数目录%d", size));
		__FILE__->check_mingren_downline(user[i]);
	}
	__FILE__->create_mingren_board();
}

//创建名人堂
void create_mingren_board()
{
	int i, j, size1, size2, id;
	mapping expTmp, cashTmp, teacherTmp, gongdeTmp, diziTmp;
	string *key, *xy_delete_id = ({});
	string *titlecode = ({"A020", "A021", "A022", "A023"});
	object who;
	if (MAIN_D->get_kenh() == KENH_BANG)
	{
		return;
	}
	//创建前清空所有玩家称谓
	xy_delete_id = keys(Enable_id);
	size1 = sizeof(xy_delete_id);
	size2 = sizeof(titlecode);
	DEBUG(sprintf("size=%d ", size1));
	if (size1)
	{
		for (i = 0; i < size1; i++)
		{
			if (objectp(who = find_char(xy_delete_id[i])))
			{
				for (j = 0; j < size2; j++)
				{
					delete_mingren_title(who, titlecode[j]);
				}
			}
		}
	}

	Enable_id = ([]);
	if (mapp(expTmp = get_save_2("exp_player")))
	{
		Exp_players = copy(expTmp);
		__FILE__->add_mingren_title(expTmp, "A020");
	}
	if (mapp(cashTmp = get_save_2("cash_player")))
	{
		Cash_players = copy(cashTmp);
		__FILE__->add_mingren_title(cashTmp, "A021");
	}
	if (mapp(gongdeTmp = get_save_2("gongde_player")))
	{
		Gongde_players = copy(gongdeTmp);
		__FILE__->add_mingren_title(gongdeTmp, "A022");
	}
	if (mapp(teacherTmp = get_save_2("teacher_player")))
	{
		Teacher_players = copy(teacherTmp);
		__FILE__->add_mingren_title(teacherTmp, "A023");
	}

	if (mapp(diziTmp = FILE_SHOUXI->get_save_2("winners")))
		Dizi_players = copy(diziTmp);
	log_file(FILE_UPDATE, sprintf("%s Danh nhân đường đổi mới\n", short_time(get_party_time())));
	save();
	DEBUG("测试-->创建名人堂成功");
}

//添加称谓
void add_mingren_title(mapping players, string title)
{
	int id, *arr_id = ({});
	int ap, cp;
	object who;
	if (MAIN_D->get_kenh() == KENH_BANG)
	{
		return;
	}
	if (mapp(players))
	{
		id = players["pos"][sprintf("%d", 1)];
		//mapping 方式保存有效id的称号
		if (!(arr_id = Enable_id[sprintf("%d", id)]))
		{
			DEBUG(sprintf("测试-->Enable_id为空 titlecode=%s", title));
			arr_id = ({title});
		}
		else
		{
			DEBUG(sprintf("测试-->Enable_id不为空 titlecode=%s", title));
			arr_id += ({title});
		}
		//为当前在线玩家添加称谓
		if (objectp(who = find_char(sprintf("%d", id))))
		{
			who->add_title(title);
			who->show_title(title);
			DEBUG("测试-->为在线玩家添加称谓成功");
		};
		Enable_id[sprintf("%d", id)] = arr_id;
		save();
	}
}

//检查更新名人堂
void check_mingren_downline(object who)
{
	int i, size, id, id1, pos;
	mapping power = ([]);
	if (!objectp(who))
		return;
	power["tudi"] = sizeof(who->get_apprentice());

	__FILE__->sort_mingren_power(who, "exp_player");	  //实力表更新
	__FILE__->sort_board(who, "cash_player", "cash");	  //财富表更新
	__FILE__->sort_board(who, "gongde_player", "gongde"); //功德表更新
	if (power["tudi"] > 0)								  //名师表更新
	{
		__FILE__->sort_board(who, "teacher_player", "tudi");
	}
}

//上线称谓玩家提示提示
void check_mingren_upline(object who)
{
	int i, size;
	string *xy_titlecode = ({"A020", "A021", "A022", "A023"});
	string *dizi_titlecode = ({
		"F001",
		"F002",
		"F003",
		"F004",
		"F005",
		"F006",
		"F007",
	});
	size = sizeof(xy_titlecode);
	if (!objectp(who))
		return;
	for (i = 0; i < size; i++)
	{
		__FILE__->check_mingren_upline_title(who, xy_titlecode[i]);
	}
	//首席弟子上线判断
	size = sizeof(dizi_titlecode);
	for (i = 0; i < size; i++)
	{
		if (who->have_title(dizi_titlecode[i]))
			__FILE__->show_msg(who, dizi_titlecode[i]);
	}
}

/************************************************内部函数********************************/

//检查上线玩家称谓的合法性
void check_mingren_upline_title(object who, string titlecode)
{
	int i, size, id, ap, cp;
	string *xy_id_table, *xy_titlecode_table;
	if (!objectp(who))
		return;
	id = who->get_number();
	xy_id_table = keys(Enable_id);
	xy_titlecode_table = Enable_id[sprintf("%d", id)];
	DEBUG(sprintf("测试-->xy_check_upline_title() id=%d sizeof(xy_id_table)=%d titlecode=%s", id, sizeof(xy_id_table), titlecode));
	if (who->have_title(titlecode))
	{
		if ((member_array(sprintf("%d", id), xy_id_table) != -1) && (member_array(titlecode, xy_titlecode_table) != -1))
		{
			__FILE__->show_msg(who, titlecode);
			DEBUG("测试-->发送有已有称谓玩家上线信息成功");
			return;
		}
		else
		{
			__FILE__->delete_mingren_title(who, titlecode);
			return;
		}
	}
	else if ((member_array(sprintf("%d", id), xy_id_table) != -1) && (member_array(titlecode, xy_titlecode_table) != -1))
	{
		who->add_title(titlecode);
		who->show_title(titlecode);
		__FILE__->show_msg(who, titlecode);
		DEBUG("测试-->发送首次有称谓玩家上线信息成功");
		return;
	}
	else
	{
		DEBUG("测试-->无任何称谓玩家上线");
		return;
	}
}

//系统提示
void show_msg(object who, string titlecode)
{
	string msg;
	if (!objectp(who))
		return;
	msg = sprintf(HIR "%s " HIY "%s" NOR " đã đăng nhập!", FILE_TITLE->get_titlename(titlecode), who->get_name());
	CHAT_D->sys_channel(0, msg);
	DEBUG("测试-->有称谓玩家上线提示成功");
}

//返回门派编号
int xy_get_fam_id(string name)
{
	switch (name)
	{
	case "Vô Môn Phái":
		return 0;
		break;
	case "Đào Hoa Nguyên":
		return 1;
		break;
	case "Thục Sơn":
		return 2;
		break;
	case "Cấm Vệ Quân":
		return 3;
		break;
	case "Đường Môn":
		return 4;
		break;
	case "Mao Sơn":
		return 5;
		break;
	case "Côn Luân":
		return 6;
		break;
	case "Vân Mộng Cốc":
		return 7;
		break;
	}
}

//获取玩家技能级别总和
int get_sum_skills_level(object who)
{
	int i, size, skill, sum_level = 0, level;
	string *name;
	mapping skills;
	if (!objectp(who))
		return;
	if (!sizeof(skills = who->get_skill_dbase()))
		return 0;
	name = sort_array(keys(skills), 1);
	for (i = 0, size = sizeof(name); i < size; i++)
	{
		skill = to_int(name[i]);
		level = who->get_skill(skill);
		sum_level += level;
	}
	return sum_level;
}

//实力榜实力体现 //包括玩家级别、技能总等级、总经验
mapping get_mingren_power(object who)
{
	int level, skills_level, exp;
	mapping mingren_power = ([]);
	if (!objectp(who))
		return;
	level = who->get_level();
	skills_level = get_sum_skills_level(who);
	if (who->get_billion_exp())
		exp = who->get_exp() + BILLION_NUMBER;
	else
		exp = who->get_exp();
	mingren_power["level"] = level;
	mingren_power["skills_level"] = skills_level;
	mingren_power["sum_exp"] = exp;
	return mingren_power;
}
//实力榜排行更新
void sort_mingren_power(object who, string type)
{
	int i, size, id, id1, pos;
	int level, skills_level, sum_exp;
	mapping power = ([]);
	if (!objectp(who))
		return;
	if (MAIN_D->get_kenh() == KENH_BANG)
	{
		return;
	}
	power = get_mingren_power(who);
	level = power["level"];
	skills_level = power["skills_level"];
	sum_exp = power["sum_exp"];
	id = who->get_number();
	DEBUG(sprintf("测试-->实力榜更新当前玩家id=%d level=%d skills_level=%d sum_exp=%d", id, level, skills_level, sum_exp));
	if (get_save_2(sprintf("%s.%d", type, id)))
	{
		if (get_save_2(sprintf("%s.%d.level", type, id)) < level)
		{
			set_save_2(sprintf("%s.%d.level", type, id), level);
			pos = get_save_2(sprintf("%s.%d.pos", type, id)); //当前玩家第pos名
		}
		if (get_save_2(sprintf("%s.%d.skills_level", type, id)) < skills_level)
		{
			set_save_2(sprintf("%s.%d.skills_level", type, id), skills_level);
			pos = get_save_2(sprintf("%s.%d.pos", type, id)); //当前玩家第pos名
		}
		if (get_save_2(sprintf("%s.%d.sum_exp", type, id)) < sum_exp)
		{
			set_save_2(sprintf("%s.%d.sum_exp", type, id), sum_exp);
			pos = get_save_2(sprintf("%s.%d.pos", type, id)); //当前玩家第pos名
		}
		DEBUG(sprintf("测试-->if当前玩家%s name=%s", type, who->get_name()));
	}
	else if ((size = get_save_2(sprintf("%s.size", type))) < 10)
	{

		pos = size + 1;
		set_save_2(sprintf("%s.pos.%d", type, pos), id); //在pos位置上记录玩家id
		set_save_2(sprintf("%s.size", type), pos);		 //设置当前列表大小
		//记录pos位置上新玩家信息
		set_save_2(sprintf("%s.%d.skills_level", type, id), skills_level);
		set_save_2(sprintf("%s.%d.sum_exp", type, id), sum_exp);
		set_save_2(sprintf("%s.%d.pos", type, id), pos);
		set_save_2(sprintf("%s.%d.level", type, id), who->get_level());
		set_save_2(sprintf("%s.%d.account", type, id), who->get_id());
		set_save_2(sprintf("%s.%d.id", type, id), who->get_number());
		set_save_2(sprintf("%s.%d.name", type, id), who->get_name());
		set_save_2(sprintf("%s.%d.family", type, id), who->get_fam_name());
		DEBUG(sprintf("测试-->else if当前玩家%s name=%s", type, who->get_name()));
		DEBUG(sprintf("测试-->else if当前玩家id=%d,size=%d,pos=%d", id, size, pos));
	}
	else
	{
		id1 = get_save_2(sprintf("%s.pos.%d", type, size)); //取最后一个位置上玩家的ID
		if (get_save_2(sprintf("%s.%d.level", type, id1)) > level)
			return;
		else if (((get_save_2(sprintf("%s.%d.level", type, id1)) == level)))
		{
			if (get_save_2(sprintf("%s.%d.skills_level", type, id1)) > skills_level)
				return;
			if (get_save_2(sprintf("%s.%d.skills_level", type, id1)) == skills_level)
			{
				if (get_save_2(sprintf("%s.%d.sum_exp", type, id1)) > sum_exp)
					return;
			}
		}
		else
		{
			pos = size;
			delete_save_2(sprintf("%s.%d", type, id1)); //删除最后位置上玩家信息
			set_save_2(sprintf("%s.size", type), pos);	//重设当前表数记录数
			//记录最后位置上新玩家信息
			set_save_2(sprintf("%s.pos.%d", type, pos), id);
			set_save_2(sprintf("%s.%d.skills_level", type, id), skills_level);
			set_save_2(sprintf("%s.%d.sum_exp", type, id), sum_exp);
			set_save_2(sprintf("%s.%d.pos", type, id), pos); //排名
			set_save_2(sprintf("%s.%d.level", type, id), who->get_level());
			set_save_2(sprintf("%s.%d.account", type, id), who->get_id());
			set_save_2(sprintf("%s.%d.id", type, id), who->get_number());
			set_save_2(sprintf("%s.%d.name", type, id), who->get_name());
			set_save_2(sprintf("%s.%d.family", type, id), who->get_fam_name());
		}
		DEBUG(sprintf("测试-->else 实力榜玩家%s name=%s", type, who->get_name()));
		DEBUG(sprintf("测试-->else 当前玩家id=%d,size=%d,pos=%d", id, size, pos));
	}
	if (pos) //重新对列表进行排序
	{
		for (i = pos; i > 1; i--)
		{
			id = get_save_2(sprintf("%s.pos.%d", type, i));
			DEBUG(sprintf("%s　重新排序-->id=%d,pos=%d i=%d", type, id, pos, i));
			id1 = get_save_2(sprintf("%s.pos.%d", type, i - 1));
			if (get_save_2(sprintf("%s.%d.level", type, id1)) > get_save_2(sprintf("%s.%d.level", type, id)))
				return;
			else if (get_save_2(sprintf("%s.%d.level", type, id1)) > get_save_2(sprintf("%s.%d.level", type, id)))
			{
				if (get_save_2(sprintf("%s.%d.skills_level", type, id1)) > get_save_2(sprintf("%s.%d.skills_level", type, id)))
					return;
				if (get_save_2(sprintf("%s.%d.skills_level", type, id1)) == get_save_2(sprintf("%s.%d.skills_level", type, id)))
				{
					if (get_save_2(sprintf("%s.%d.sum_exp", type, id1)) > get_save_2(sprintf("%s.%d.sum_exp", type, id)))
						return;
				}
			}
			set_save_2(sprintf("%s.pos.%d", type, i), id1);
			set_save_2(sprintf("%s.%d.pos", type, id1), i);
			set_save_2(sprintf("%s.pos.%d", type, i - 1), id);
			set_save_2(sprintf("%s.%d.pos", type, id), i - 1);
		}
	}
	DEBUG(sprintf("测试-->else %s表更新成功", type));
	save();
}
//删除所有称谓
void delete_mingren_title(object who, string titlecode)
{
	if (!objectp(who))
		return;
	if (!(who->have_title(titlecode)))
		return;
	who->delete_title(titlecode);
	DEBUG(sprintf("测试删除称谓成功 "));
}
//排序更新名人表
void sort_board(object who, string type, string power_name)
{
	int i, size, id, id1, id2, pos, tmp_pos;
	mapping power = ([]);
	if (!objectp(who))
		return;
	if (MAIN_D->get_kenh() == KENH_BANG)
	{
		return;
	}
	id = who->get_number();
	power["cash"] = who->get_savings() + who->get_cash();
	power["tudi"] = sizeof(who->get_apprentice());
	power["gongde"] = who->get_total_bonus();
	DEBUG(sprintf("测试-->当前玩家name=%s  cash=%d\n tudi=%d gongde=%d ", who->get_name(), power["cash"], power["tudi"], power["gongde"]));
	if (get_save_2(sprintf("%s.%d", type, id)))
	{
		if (get_save_2(sprintf("%s.%d.%s", type, id, power_name)) != power[power_name])
		{
			DEBUG(sprintf("测试-->%s.%d.%s=%d", type, id, power_name, power[power_name]));
			set_save_2(sprintf("%s.%d.%s", type, id, power_name), power[power_name]);
			pos = get_save_2(sprintf("%s.%d.pos", type, id)); //当前玩家第pos名
			DEBUG(sprintf("测试-->同ID不同金钱位置pos=%d", pos));
		}
		DEBUG(sprintf("测试-->if当前玩家%s name=%s", type, who->get_name()));
	}
	else if ((size = get_save_2(sprintf("%s.size", type))) < 10)
	{

		pos = size + 1;
		set_save_2(sprintf("%s.pos.%d", type, pos), id); //在pos位置上记录玩家id
		set_save_2(sprintf("%s.size", type), pos);		 //设置当前列表大小
		//记录pos位置上新玩家信息
		set_save_2(sprintf("%s.%d.%s", type, id, power_name), power[power_name]);
		set_save_2(sprintf("%s.%d.pos", type, id), pos);
		set_save_2(sprintf("%s.%d.level", type, id), who->get_level());
		set_save_2(sprintf("%s.%d.account", type, id), who->get_id());
		set_save_2(sprintf("%s.%d.id", type, id), who->get_number());
		set_save_2(sprintf("%s.%d.name", type, id), who->get_name());
		set_save_2(sprintf("%s.%d.family", type, id), who->get_fam_name());
		DEBUG(sprintf("测试-->else if当前玩家%s name=%s", type, who->get_name()));
		DEBUG(sprintf("测试-->else if当前玩家id=%d,size=%d,pos=%d", id, size, pos));
	}
	else
	{
		id1 = get_save_2(sprintf("%s.pos.%d", type, size)); //取最后一个位置上玩家的ID
		if (get_save_2(sprintf("%s.%d.%s", type, id1, power_name)) < power[power_name])
		{
			pos = size;
			delete_save_2(sprintf("%s.%d", type, id1)); //删除最后位置上玩家信息
			set_save_2(sprintf("%s.size", type), pos);	//重设当前表数记录数
			//记录最后位置上新玩家信息
			set_save_2(sprintf("%s.pos.%d", type, pos), id);
			set_save_2(sprintf("%s.%d.%s", type, id, power_name), power[power_name]);
			set_save_2(sprintf("%s.%d.pos", type, id), pos); //排名
			set_save_2(sprintf("%s.%d.level", type, id), who->get_level());
			set_save_2(sprintf("%s.%d.account", type, id), who->get_id());
			set_save_2(sprintf("%s.%d.id", type, id), who->get_number());
			set_save_2(sprintf("%s.%d.name", type, id), who->get_name());
			set_save_2(sprintf("%s.%d.family", type, id), who->get_fam_name());
		}
		DEBUG(sprintf("测试-->else 当前玩家%s name=%s", type, who->get_name()));
		DEBUG(sprintf("测试-->else 当前玩家id=%d,size=%d,pos=%d", id, size, pos));
	}
	if (pos) //重新对列表进行排序
	{
		id = get_save_2(sprintf("%s.pos.%d", type, pos));
		id1 = get_save_2(sprintf("%s.pos.%d", type, pos + 1));
		id2 = get_save_2(sprintf("%s.pos.%d", type, pos - 1));
		if (get_save_2(sprintf("%s.%d.%s", type, id1, power_name)) && (get_save_2(sprintf("%s.%d.%s", type, id, power_name)) < get_save_2(sprintf("%s.%d.%s", type, id1, power_name))))
		{
			size = get_save_2(sprintf("%s.size", type));
			for (i = pos; i < size; i++)
			{
				DEBUG(sprintf("测试向右转-->size=%d pos=%d", size, pos));
				id = get_save_2(sprintf("%s.pos.%d", type, i));
				id1 = get_save_2(sprintf("%s.pos.%d", type, i + 1));
				if (get_save_2(sprintf("%s.%d.%s", type, id, power_name)) < get_save_2(sprintf("%s.%d.%s", type, id1, power_name)))
				{
					set_save_2(sprintf("%s.pos.%d", type, i), id1);
					set_save_2(sprintf("%s.%d.pos", type, id1), i);
					set_save_2(sprintf("%s.pos.%d", type, i + 1), id);
					set_save_2(sprintf("%s.%d.pos", type, id), i + 1);
				}
			}
		}
		else
		{
			for (i = pos; i > 1; i--)
			{
				DEBUG(sprintf("测试向左转-->pos=%d", pos));
				id = get_save_2(sprintf("%s.pos.%d", type, i));
				DEBUG(sprintf("%s　重新排序-->id=%d,pos=%d i=%d", type, id, pos, i));
				id2 = get_save_2(sprintf("%s.pos.%d", type, i - 1));
				if (get_save_2(sprintf("%s.%d.%s", type, id, power_name)) > get_save_2(sprintf("%s.%d.%s", type, id2, power_name)))
				{
					set_save_2(sprintf("%s.pos.%d", type, i), id2);
					set_save_2(sprintf("%s.%d.pos", type, id2), i);
					set_save_2(sprintf("%s.pos.%d", type, i - 1), id);
					set_save_2(sprintf("%s.%d.pos", type, id), i - 1);
				}
			}
		}
	}
	DEBUG(sprintf("测试-->else %s表更新成功", type));
	save();
}
//发送显示数据
void send_mingren_data(object who, mapping players, string type)
{
	int i, size, id, level, pos, tudi, point, xy_family;
	string name, family;
	if (!objectp(who))
		return;
	restore();
	if (mapp(players))
	{
		size = players["size"];
		for (i = 0; i < size; i++)
		{
			id = players["pos"][sprintf("%d", i + 1)];
			pos = players[sprintf("%d", id)]["pos"];
			name = players[sprintf("%d", id)]["name"];
			family = players[sprintf("%d", id)]["family"];
			xy_family = xy_get_fam_id(family);
			switch (type)
			{
			case "power":
				send_user(who, "%c%c%c%c%s", 0xA9, 1, pos, xy_family, name);
				break;
			case "cash":
				send_user(who, "%c%c%c%c%s", 0xA9, 2, pos, xy_family, name);
				break;
			case "gongde":
				send_user(who, "%c%c%c%c%s", 0xA9, 3, pos, xy_family, name);
				break;
			case "teacher":
				if (!tudi = players[sprintf("%d", id)]["tudi"])
					break;
				send_user(who, "%c%c%c%c%d%s", 0xA9, 4, pos, xy_family, tudi, name);
				break;
			}
		}
	}
}
/************************************************内部函数********************************/
