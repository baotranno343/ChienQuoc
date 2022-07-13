/*******宠物********/
//只包含属性及属性存取函数，其他函数在sys/npc/pet.c

#include <public.h>
#include <skill.h>

inherit NPC;
inherit SAVE_F;

private
string pet_id; //宠物ID
private
int FirstOwnerId; // 最初获得者ID
private
string FirstOwnerName; // 最初获得者昵称
private
int birthday; // 出生时间（可以和最初获得者ID一起组成宠物的唯一标识）
private
int OwnerTime; // 获得时间
private
string FirstName; // 宠物原始名字（玩家不可以修改，用以识别）
private
string OwnerName; // 主人昵称
private
string OwnerAccount; // 主人帐号
private
int OwnerNumber; // 主人对象(Number)

private
int Reincarnation; // 转生次数
private
int lifetime; // 寿命
private
int faith; // 忠诚度
private
int blood; // 血统（野生 0，宝宝 1）

private
int Experience; // 总经验
private
int GiftPoint; // 可分配属性点
private
int dead_time; // 死亡时间
private
int weakness; // 虚弱

private
int iPortrait; //宠物造型

private
int con_grow; //体魄成长系数
private
int str_grow; //力量成长系数
private
int cps_grow; //耐力成长系数
private
int mp_grow; //法力成长系数
private
int ma_grow; //法攻成长系数
private
int md_grow; //法防成长系数
private
int dex_grow; //敏捷(躲闪)成长系数

private
static int NewAttackSpeed; //新的攻击速度
private
static int Caster; //远程攻击标志
private
static int DflSkill; //默认使用技能(对其他人使用)
private
static int DflSkill1; //默认使用技能(对己使用)

// 函数：获取体魄成长系数
int get_con_grow() { return con_grow; }
// 函数：获取力量成长系数
int get_str_grow() { return str_grow; }
// 函数：获取耐力成长系数
int get_cps_grow() { return cps_grow; }
// 函数：获取法力成长系数
int get_mp_grow() { return mp_grow; }
// 函数：获取法攻成长系数
int get_ma_grow() { return ma_grow; }
// 函数：获取法防成长系数
int get_md_grow() { return md_grow; }
// 函数：获取敏捷成长系数
int get_dex_grow() { return dex_grow; }

// 函数：设置体魄成长系数
int set_con_grow(int i) { return con_grow = i; }
// 函数：设置力量成长系数
int set_str_grow(int i) { return str_grow = i; }
// 函数：设置耐力成长系数
int set_cps_grow(int i) { return cps_grow = i; }
// 函数：设置法力成长系数
int set_mp_grow(int i) { return mp_grow = i; }
// 函数：设置法攻成长系数
int set_ma_grow(int i) { return ma_grow = i; }
// 函数：设置法防成长系数
int set_md_grow(int i) { return md_grow = i; }
// 函数：设置敏捷成长系数
int set_dex_grow(int i) { return dex_grow = i; }

// 函数：取存盘文件名
string get_save_file()
{
	if (!stringp(OwnerAccount) || !FirstOwnerId || !birthday || !stringp(pet_id))
	{
		return 0;
	}
	return sprintf("data/%c/%c/%c/%s/%s" SAVE_EXTENSION, OwnerAccount[0], OwnerAccount[1], OwnerAccount[2], OwnerAccount, pet_id);
}
int restore()
{
	int i;

	i = ::restore();
	if (!i)
		return i;
	if (!mapp(get_save_dbase()))
	{
		init_save_dbase();
	}
	if (!mapp(get_save_dbase_2()))
	{
		init_save_dbase_2();
	}
	return i;
}
//获取宠物ID
string get_pet_id()
{
	return pet_id;
}
//设置宠物ID
string set_pet_id(string flag)
{
	return pet_id = flag;
}
//获取宠物生日
int get_birthday() { return birthday; }
//设置宠物生日
int set_birthday(int i) { return birthday = i; }
//获得时间
int get_ownertime() { return OwnerTime; }

//获取宠物形象
int get_portrait() { return iPortrait; }
//设置宠物形象
int set_portrait(int i) { return iPortrait = i; }

//获取宠物死亡时间
int get_dead_time() { return dead_time; }
//设置宠物死亡时间
int set_dead_time(int i) { return dead_time = i; }

//设置宠物虚弱
int set_weakness(int i) { return weakness = i; }

//获取宠物原始名字
string get_firstname() { return FirstName; }
//设置宠物原始名字
string set_firstname(string cName) { return FirstName = cName; }
//获取宠物血统
int get_blood() { return blood; }
//设置宠物血统
int set_blood(int i) { return blood = i; }
//获取可分配属性点
int get_giftpoint() { return GiftPoint; }
//设置可分配属性点
int set_giftpoint(int i) { return GiftPoint = i; }
//增加可分配属性点
int add_giftpoint(int i) { return GiftPoint += i; }
// 函数：获取人物名称
string get_short()
{
	object me = this_object();
	if (OwnerName)
		return sprintf("%s (%s)", me->get_name(), OwnerName);
	else
		return get_name();
}
// 函数：宠物 识别函数
int is_pet() { return 1; }

// 函数：设置主人对象
object set_owner(object char)
{
	if (!objectp(char))
	{
		OwnerNumber = 0;
		OwnerName = "";
		OwnerAccount = "";
		OwnerTime = 0;
	}
	else if (!OwnerNumber)
	{
		OwnerNumber = char->get_number();
		OwnerName = char->get_name();
		OwnerAccount = char->get_id();
		if (!OwnerTime)
			OwnerTime = time();
		if (!stringp(pet_id))
		{
			FirstOwnerId = OwnerNumber;
			FirstOwnerName = OwnerName;
			birthday = OwnerTime;
			pet_id = NPC_PET_D->get_pet_id(FirstOwnerId);
		}
	}
	return ::set_owner(char);
}

// 函数：判断可以战斗
int can_fight(object who)
{
	return NPC_PET_D->can_fight(this_object(), who);
}

// 函数：可以接受战斗
int can_be_fighted(object who)
{
	return NPC_PET_D->can_be_fighted(this_object(), who);
}

// 函数：获取最高人物等级
int get_max_pet_level()
{
	return 150;
	//        switch( Reincarnation )
	//        {
	//      default : return 120;
	//       case 1 : return 130;
	//       case 2 : return 150;
	//        }
}
// 函数：获取升级经验
int get_upgrade_exp() { return NPC_PET_D->get_level_exp(get_level()); }
// 函数：获取经验属性
int get_exp() { return Experience; }
// 函数：增添经验属性
int add_exp(int exp)
{
	int level;
	object owner;
	if (exp <= 0)
		return 0;
	owner = get_owner();
	if (!owner)
		return 0;
	level = get_level();
	if (level >= owner->get_level() || level >= get_max_pet_level())
		return 0;
	Experience += exp;
	if (Experience >= get_upgrade_exp()) //升级
	{
		Experience = 0;
		NPC_PET_D->upgrade(this_object());
	}
	else
		send_user(owner, "%c%c%d%d", 0xA1, 5, getoid(this_object()), Experience);

	return Experience;
}
// 函数：设置经验属性(一般用add_exp())
int set_exp(int exp)
{
	if (exp < 0)
		return Experience;
	return Experience = exp;
}

// 函数：获取寿命
int get_life() { return lifetime; }
// 函数：设置寿命
int set_life(int point)
{
	object me = this_object(), owner;
	lifetime = range_value(point, 1, 12000);
	owner = me->get_owner();
	if (owner)
		send_user(owner, "%c%c%d%d", 0xA1, 7, getoid(me), lifetime);
	return lifetime;
}
// 函数：增添寿命
int add_life(int point)
{
	return set_life(lifetime + point);
}
// 函数：获取忠诚度
int get_faith() { return faith; }
// 函数：设置忠诚度
int set_faith(int point)
{
	object me = this_object(), owner;
	faith = range_value(point, 1, 100);
	owner = me->get_owner();
	if (owner)
		send_user(owner, "%c%c%d%d", 0xA1, 8, getoid(me), faith);
	return faith;
}
// 函数：增添忠诚度
int add_faith(int point)
{
	return set_faith(faith + point);
}

// 函数：走路处理(心跳之中调用)
void heart_beat_walk()
{
	NPC_PET_D->heart_beat_walk(this_object());
}

// 函数：获取远程攻击模式
int is_caster() { return Caster; }

// 函数：设置远程攻击模式
int set_caster(int flag) { return Caster = flag; }

//发送具体属性给主人
void send_info()
{
	int id, i, size, picid;
	string *nSkill, file;
	mapping mpSkill;
	object pet = this_object(), obj, owner;

	id = getoid(pet);
	owner = pet->get_owner();
	picid = pet->get_char_picid();
	if (!picid)
		picid = pet->get_portrait();
	send_user(owner, "%c%c%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%c%s", 0xA1, 1, id, pet->get_ownertime(), pet->get_level(), pet->get_hp(), pet->get_max_hp(), pet->get_mp(), pet->get_max_mp(), pet->get_ap_0(), pet->get_ap(), pet->get_dp_0(), pet->get_dp(), pet->get_cp_0(), pet->get_cp(), pet->get_pp_0(), pet->get_pp(), pet->get_sp(), pet->get_double_rate(), pet->get_con(), pet->get_spi(), pet->get_str(), pet->get_cps(), pet->get_dex(), pet->get_giftpoint(), pet->get_faith(), pet->get_exp(), pet->get_upgrade_exp(), picid, pet->get_blood(), pet->get_name());
	send_user(owner, "%c%c%d%d%d%d%d%d%d%d%d", 0xA1, 2, id, str_grow, cps_grow, ma_grow, md_grow, mp_grow, dex_grow, con_grow, lifetime);
	send_user(owner, "%c%c%d%d", 0xA1, 26, id, pet->get_head_color());
	if (pet->get_save("no_give"))
		send_user(owner, "%c%c%d%d", 0xA1, 28, id, 1);
	if ((i = time() - pet->get_dead_time()) < 600)
		send_user(owner, "%c%c%d%d", 0xA1, 4, id, 600 - i);
	mpSkill = pet->get_skill_dbase();
	if (!mapp(mpSkill))
		return;
	nSkill = keys(mpSkill);
	for (i = 0, size = sizeof(nSkill); i < size; i++)
	{
		if (obj = load_object(SKILL->get_perform_file(to_int(nSkill[i]))))
			obj->can_perform(owner, pet);
	}
}
//发送属性给指定玩家
void send_info_to(object who)
{
	int id, i, size, *nSki, picid;
	object pet = this_object();
	string *nSki1, tmp;

	id = getoid(pet);
	nSki1 = keys(pet->get_skill_dbase());
	picid = pet->get_char_picid();
	if (!picid)
		picid = pet->get_portrait();
	send_user(who, "%c%c%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%c%s", 0xA1, 23,
			  id, pet->get_level(), pet->get_hp(), pet->get_max_hp(), pet->get_mp(), pet->get_max_mp(), pet->get_ap_0(), pet->get_ap(), pet->get_dp_0(), pet->get_dp(), pet->get_cp_0(), pet->get_cp(), pet->get_pp_0(), pet->get_pp(), pet->get_sp(), pet->get_double_rate(), pet->get_con(), pet->get_spi(), pet->get_str(), pet->get_cps(), pet->get_dex(), pet->get_giftpoint(), pet->get_faith(), pet->get_exp(), pet->get_upgrade_exp(), picid, pet->get_blood(), pet->get_name());
	send_user(who, "%c%c%d%d%d%d%d%d%d%d%d", 0xA1, 24, id, str_grow, cps_grow, ma_grow, md_grow, mp_grow, dex_grow, con_grow, lifetime);
	send_user(who, "%c%c%d%d", 0xA1, 26, id, pet->get_head_color());
	size = sizeof(nSki1);
	if (!size)
		return;
	tmp = "%c%c%d";
	nSki = ({0xA1, 25, id});
	for (i = 0; i < size; i++)
	{
		tmp += "%d";
		nSki += ({to_int(nSki1[i])});
	}
	send_user(who, tmp, nSki);
}
//有关气血，法力的操作
int set_hp(int point)
{
	object pet = this_object();
	point = ::set_hp(point);
	if (pet->get_owner())
		send_user(pet->get_owner(), "%c%c%d%d%d", 0xA1, 11, getoid(pet), point, pet->get_max_hp());
	return point;
}
int add_hp(int point)
{
	object pet = this_object();
	point += get_hp();
	point = set_hp(point);
	return point;
}
int set_max_hp(int point)
{
	object pet = this_object();
	point = ::set_max_hp(point);
	if (pet->get_owner())
		send_user(pet->get_owner(), "%c%c%d%d%d", 0xA1, 11, getoid(pet), pet->get_hp(), point);
	return point;
}
int add_max_hp(int point)
{
	object pet = this_object();
	point += get_max_hp();
	point = set_max_hp(point);
	return point;
}
int set_mp(int point)
{
	object pet = this_object();
	point = ::set_mp(point);
	if (pet->get_owner())
		send_user(pet->get_owner(), "%c%c%d%d%d", 0xA1, 12, getoid(pet), point, pet->get_max_mp());
	return point;
}
int add_mp(int point)
{
	object pet = this_object();
	point += get_mp();
	point = set_mp(point);
	return point;
}
int set_max_mp(int point)
{
	object pet = this_object();
	point = ::set_max_mp(point);
	if (pet->get_owner())
		send_user(pet->get_owner(), "%c%c%d%d%d", 0xA1, 12, getoid(pet), pet->get_mp(), point);
	return point;
}
int add_max_mp(int point)
{
	object pet = this_object();
	point += get_max_mp();
	point = set_max_mp(point);
	return point;
}
// 函数：获取物理攻击
int get_ap() { return ::get_ap_0(); }
// 函数：获取物理防御
int get_dp() { return ::get_dp_0(); }
// 函数：获取法术攻击
int get_cp() { return ::get_cp_0(); }
// 函数：获取法术防御
int get_pp() { return ::get_pp_0(); }
// 函数：获取物理攻击(基值)
int get_ap_0()
{
	int ap;
	ap = get_ap();
	return range_value(ap - 35, 1, ap);
}
// 函数：获取物理防御(基值)
int get_dp_0()
{
	int dp;
	dp = get_dp();
	return range_value(dp - 35, 1, dp);
}
// 函数：获取法术攻击(基值)
int get_cp_0()
{
	int cp;
	cp = get_cp();
	return range_value(cp - 35, 1, cp);
}
// 函数：获取法术防御(基值)
int get_pp_0()
{
	int pp;
	pp = get_pp();
	return range_value(pp - 35, 1, pp);
}
// 函数：设置物理攻击
int set_ap(int point)
{
	object pet = this_object();
	point = ::set_ap(point);
	if (pet->get_owner())
		send_user(pet->get_owner(), "%c%c%d%d%d", 0xA1, 13, getoid(pet), pet->get_ap_0(), point);
	return point;
}
int add_ap(int point)
{
	point += get_ap();
	point = set_ap(point);
	return point;
}
// 函数：设置物理防御
int set_dp(int point)
{
	object pet = this_object();
	point = ::set_dp(point);
	if (pet->get_owner())
		send_user(pet->get_owner(), "%c%c%d%d%d", 0xA1, 14, getoid(pet), pet->get_dp_0(), point);
	return point;
}
int add_dp(int point)
{
	point += get_dp();
	point = set_dp(point);
	return point;
}
// 函数：设置法术攻击
int set_cp(int point)
{
	object pet = this_object();
	point = ::set_cp(point);
	if (pet->get_owner())
		send_user(pet->get_owner(), "%c%c%d%d%d", 0xA1, 15, getoid(pet), pet->get_cp_0(), point);
	return point;
}
int add_cp(int point)
{
	point += get_cp();
	point = set_cp(point);
	return point;
}
// 函数：设置法术防御
int set_pp(int point)
{
	object pet = this_object();
	point = ::set_pp(point);
	if (pet->get_owner())
		send_user(pet->get_owner(), "%c%c%d%d%d", 0xA1, 16, getoid(pet), pet->get_pp_0(), point);
	return point;
}
int add_pp(int point)
{
	point += get_pp();
	point = set_pp(point);
	return point;
}
// 函数：设置法术防御
int set_sp(int point)
{
	object pet = this_object();
	point = ::set_sp(point);
	if (pet->get_owner())
		send_user(pet->get_owner(), "%c%c%d%d", 0xA1, 17, getoid(pet), point);
	return point;
}
int add_sp(int point)
{
	point += ::get_sp();
	point = set_sp(point);
	return point;
}
// 函数：设置物理暴击率
int set_double_rate(int point)
{
	object pet = this_object();
	point = ::set_double_rate(point);
	if (pet->get_owner())
		send_user(pet->get_owner(), "%c%c%d%d", 0xA1, 20, getoid(pet), point);
	return point;
}
//技能影响
void skill_effect(int skill)
{
	object oSki;
	if (!(oSki = load_object(SKILL->get_perform_file(skill))))
		return;
	oSki->skill_effect(this_object(), this_object()->get_owner());
}
//删除技能影响
void remove_skill_effect(int skill)
{
	object oSki;
	if (!(oSki = load_object(SKILL->get_perform_file(skill))))
		return;
	oSki->remove_skill_effect(this_object(), this_object()->get_owner());
}
//设定默认使用技能
int set_default_skill(int iSki)
{
	int iSpeed;
	object oSki, me;

	me = this_object();
	Caster = 0;
	DflSkill = 0;
	DflSkill1 = 0;
	NewAttackSpeed = 0;
	if (iSki)
		oSki = load_object(SKILL->get_perform_file(iSki));
	if (!oSki)
		return 0;
	Caster = oSki->is_caster();
	if (oSki->get_perform_type() == ON_ME_P) //对己使用的法术
		DflSkill1 = iSki;
	else
		DflSkill = iSki;
	iSpeed = oSki->get_attack_speed();
	if (!iSpeed)
		NewAttackSpeed = 25;
	return iSki;
}
//获取默认使用技能
int get_default_skill()
{
	return DflSkill;
}
//获取默认对己使用技能
int get_default_skill1()
{
	return DflSkill1;
}
//宠物技能攻击
int perform_action(object who)
{
	return NPC_PET_D->perform_action(this_object(), who);
}
// 函数：删除技能等级
void delete_skill(int skill)
{
	::delete_skill(skill);
	remove_skill_effect(skill);
	send_user(this_object()->get_owner(), "%c%c%d%d%c", 0xA1, 19, getoid(this_object()), skill, 0);
}
// 函数：设置技能等级
int set_skill(int skill, int level)
{
	object oSki;
	if (level > 0)
	{
		level = ::set_skill(skill, level);
		{
			if ((oSki = load_object(SKILL->get_perform_file(skill))) && this_object()->get_owner())
				oSki->can_perform(this_object()->get_owner(), this_object());
			skill_effect(skill);
		}
	}
	else
	{
		delete_skill(skill);
	}
	return level;
}
// 函数：获取攻击速度(秒)
int get_attack_speed()
{
	int iSpeed, rate;
	object me = this_object();

	if (NewAttackSpeed)
		return NewAttackSpeed;
	iSpeed = ::get_attack_speed();
	if (me->get("sk74214"))
		rate = 40;
	else if (me->get("sk74123"))
		rate = 20;
	iSpeed = iSpeed * (100 - rate) / 100;
	return range_value(iSpeed, 10, MAX_NUMBER);
}