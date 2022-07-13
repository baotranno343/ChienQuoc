#define MONEY_RECORD "money.dat"

#define SAVE_FILE "data/city/count" SAVE_EXTENSION

inherit SAVE_F;

static mapping MoneyIncome = ([]);

static mapping MoneyUse = ([]);

static int iMaxUser = 1500;

int boxcount;

int buycount; // 道具的累计编号

int can_gm3; // 允许活动号登录

string *IncomeName = ({});
string *UseName = ({});
static mapping CommandCount = ([]);
static mapping CommandLen = ([]);
string *CommandName = ({});

mapping FamilyCount = ([]);

mapping EquipCount = ([]);

mapping SceneTask = ([]);

mapping Pet = ([]);

int iRefine; // 收妖任务开关

int hefu_time;	// 合服补偿的开关
int hefu_ii;	// 合服次数
int iNewPerson; // 新角色协议开关

int *hp1;
int *hp2;
int *mp1;
int *mp2;
int *ap1;
int *ap2;
int *dp1;
int *dp2;
int *cp1;
int *cp2;
int *pp1;
int *pp2;
int *sp1;
int *sp2;

int firstorg;
static int test_flag;

int war_flag1; // 皇城守卫的开战标志

int new_story_flag; //新资料片开放标志

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：构造处理
void create()
{
	restore_object(SAVE_FILE);
	if (!mapp(FamilyCount))
		FamilyCount = ([]);
	if (!mapp(EquipCount))
		EquipCount = ([]);
	if (!mapp(Pet))
		Pet = ([]);
	if (sizeof(IncomeName) == 0)
		IncomeName = ({});
	if (sizeof(UseName) == 0)
		UseName = ({});
	if (sizeof(CommandName) == 0)
		CommandName = ({});
	hp1 = ({
		32,
		120,
		72,
		84,
		72,
		84,
		72,
		60,
	});
	hp2 = ({
		10,
		10,
		10,
		10,
		10,
		10,
		10,
		10,
	});
	mp1 = ({
		10,
		8,
		56,
		8,
		32,
		56,
		64,
		80,
	});
	mp2 = ({
		10,
		10,
		10,
		10,
		10,
		10,
		10,
		10,
	});
	ap1 = ({
		5,
		7,
		10,
		14,
		8,
		2,
		1,
		2,
	});
	ap2 = ({
		10,
		10,
		10,
		10,
		10,
		10,
		10,
		10,
	});
	dp1 = ({
		16,
		33,
		17,
		23,
		20,
		10,
		10,
		10,
	});
	dp2 = ({
		10,
		10,
		10,
		10,
		10,
		10,
		10,
		10,
	});
	cp1 = ({
		1,
		1,
		7,
		1,
		1,
		7,
		10,
		7,
	});
	cp2 = ({
		10,
		10,
		10,
		10,
		10,
		10,
		10,
		10,
	});
	pp1 = ({
		15,
		17,
		20,
		17,
		17,
		30,
		23,
		26,
	});
	pp2 = ({
		10,
		10,
		10,
		10,
		10,
		10,
		10,
		10,
	});
	sp1 = ({
		13,
		15,
		13,
		20,
		25,
		13,
		13,
		13,
	});
	sp2 = ({
		10,
		10,
		10,
		10,
		10,
		10,
		10,
		10,
	});

	call_out("hour_callout", time() - time() / 1800 * 1800);
}

// 函数：复位处理(半小时)
void hour_callout()
{
	string *key;
	int i, size;
	remove_call_out("hour_callout");
	call_out("hour_callout", 1800);
	log_file(MONEY_RECORD, sprintf("%s income", short_time()));
	if (mapp(MoneyIncome))
	{
		size = sizeof(IncomeName);
		if (size > 0)
		{
			for (i = 0; i < size; i++)
			{
				log_file(MONEY_RECORD, sprintf(" %d", MoneyIncome[IncomeName[i]]));
			}
		}
	}
	log_file(MONEY_RECORD, "\n");
	MoneyIncome = ([]);
	log_file(MONEY_RECORD, sprintf("%s use", short_time()));
	if (mapp(MoneyUse))
	{
		size = sizeof(UseName);
		if (size > 0)
		{
			for (i = 0; i < size; i++)
			{
				log_file(MONEY_RECORD, sprintf(" %d", MoneyUse[UseName[i]]));
			}
		}
	}
	log_file(MONEY_RECORD, "\n");
	MoneyUse = ([]);
	save();
}

void add_income(string type, int money)
{
	if (member_array(type, IncomeName) == -1)
		IncomeName += ({type});
	MoneyIncome[type] += money;
}

void add_use(string type, int money)
{
	if (member_array(type, UseName) == -1)
		UseName += ({type});
	MoneyUse[type] += money;
}

void add_task(string type, int count)
{
	SceneTask[type] += count;
}

mapping get_task()
{
	return copy(SceneTask);
}

void add_pet(string type, int count)
{
	Pet[type] += count;
	save();
}

mapping get_pet()
{
	return copy(Pet);
}

int set_max_user(int count)
{
	return iMaxUser = count;
}

int get_max_user(int count)
{
	if (MAIN_D->get_absolute_random_number() == 0)
		return 20 + random(20);
	return iMaxUser;
}

int get_1(int type, int index)
{
	if (type > 6 || type < 0)
		return 0;
	if (index > 7 || index < 0)
		return 0;
	switch (type)
	{
	case 0:
		return hp1[index];
	case 1:
		return mp1[index];
	case 2:
		return ap1[index];
	case 3:
		return dp1[index];
	case 4:
		return cp1[index];
	case 5:
		return pp1[index];
	case 6:
		return sp1[index];
	}
}

int get_2(int type, int index)
{
	if (type > 6 || type < 0)
		return 0;
	if (index > 7 || index < 0)
		return 0;
	switch (type)
	{
	case 0:
		return hp2[index];
	case 1:
		return mp2[index];
	case 2:
		return ap2[index];
	case 3:
		return dp2[index];
	case 4:
		return cp2[index];
	case 5:
		return pp2[index];
	case 6:
		return sp2[index];
	}
}

int set_1(int type, int index, int value)
{
	if (type > 6 || type < 0)
		return 0;
	if (index > 7 || index < 0)
		return 0;
	switch (type)
	{
	case 0:
		return hp1[index] = value;
	case 1:
		return mp1[index] = value;
	case 2:
		return ap1[index] = value;
	case 3:
		return dp1[index] = value;
	case 4:
		return cp1[index] = value;
	case 5:
		return pp1[index] = value;
	case 6:
		return sp1[index] = value;
	}
}

int set_2(int type, int index, int value)
{
	if (type > 6 || type < 0)
		return 0;
	if (index > 7 || index < 0)
		return 0;
	if (value <= 1)
		value = 1;
	switch (type)
	{
	case 0:
		return hp2[index] = value;
	case 1:
		return mp2[index] = value;
	case 2:
		return ap2[index] = value;
	case 3:
		return dp2[index] = value;
	case 4:
		return cp2[index] = value;
	case 5:
		return pp2[index] = value;
	case 6:
		return sp2[index] = value;
	}
}

// 函数：取存盘文件名
string get_save_file() { return SAVE_FILE; }

void add_family(string fam, int count)
{
	FamilyCount[fam] += count;
}

void add_equip(string type, int count)
{
	EquipCount[type] += count;
}

int get_firstorg() { return firstorg; }

int set_firstorg(int value) { return firstorg = value; }

void add_command(string comm, int count)
{
	if (member_array(comm, CommandName) == -1)
		CommandName += ({comm});
	CommandCount[comm]++;
	CommandLen[comm] += count;
}

void check_command()
{
	int i, size, j, count;
	size = sizeof(CommandName);
	j = 0;
	count = 0;
	for (i = 0; i < size; i++)
	{
		count += CommandCount[CommandName[i]];
		j += CommandLen[CommandName[i]];
	}
	//log_file( "command.dat", sprintf("%s %d/%d\n", short_time(), j, count) );
	j = 0;
	for (i = 0; i < size; i++)
	{
		//	log_file( "command.dat", sprintf("%s: %d/%d", CommandName[i], CommandLen[CommandName[i]], CommandCount[CommandName[i]]   ) );
		CommandCount[CommandName[i]] = 0;
		CommandLen[CommandName[i]] = 0;
		if (j < 4)
		{
			//log_file("command.dat", " ");
			j++;
		}
		else
		{
			//log_file("command.dat", "\n");
			j = 0;
		}
	}
	//log_file("command.dat", "\n");
}

int get_buy_count() { return buycount; }

int add_buy_count(int flag)
{
	buycount += flag;
	save();
	return buycount;
}

int set_buy_count(int flag)
{
	buycount = flag;
	save();
	return buycount;
}

int set_test(int flag)
{
	test_flag = flag;
	return test_flag;
}

int get_test() { return test_flag; }

int set_refine(int flag)
{
	iRefine = flag;
	return iRefine;
}

int get_refine()
{
	return 1;
}

int get_can_gm3() { return can_gm3; }

int set_can_gm3(int flag)
{
	can_gm3 = flag;
	save();
	return can_gm3;
}

int get_boxcount() { return boxcount; }

int add_boxcount(int flag)
{
	boxcount = flag;
	return boxcount;
}

int get_war_flag1()
{
	return war_flag1;
}

int set_war_flag1(int flag)
{
	return war_flag1 = flag;
}

int get_hefu_time()
{
	return hefu_time;
}

int set_hefu_time(int flag)
{
	return hefu_time = flag;
}

int set_hefu_time2(object who, string arg)
{
	int year, mon, day, hour, min, ii;
	string cTmp2;
	if (sscanf(arg, "%d %s", ii, cTmp2) != 2)
	{
		send_user(who, "%c%s", '!', "错误的格式！");
		return 0;
	}
	year = to_int(cTmp2[0..3]);
	mon = to_int(cTmp2[4..5]);
	day = to_int(cTmp2[6..7]);
	hour = to_int(cTmp2[8..9]);
	min = to_int(cTmp2[10..11]);
	hefu_time = mktime(year, mon, day, hour, min, 0); //结束时间
	if (!hefu_time)
	{
		send_user(who, "%c%s", '!', "错误的时间！");
		return 0;
	}
	tell_user(who, "设定第%d次合服的奖励时间为：%s", ii, cTmp2);
	send_user(who, "%c%s", '!', "成功设置合服的奖励时间！");
	hefu_ii = ii;
	save();
	return hefu_time;
}
int get_hefu_ii()
{
	return hefu_ii;
}

int get_new_story()
{
	return 1; //设为开启
			  //	return new_story_flag;
}

int set_new_story(int flag)
{
	new_story_flag = flag;
	save();
	return flag;
}

int get_new_person() { return iNewPerson; }
int set_new_person(int i)
{
	iNewPerson = i;
	save();
	return iNewPerson;
}