
#define SKILL_DIR       "/skill/"

private int Number;                     // 技能标识
private string Name;                    // 技能名称
private int Type;                       // 技能类别

// 函数：技能识别函数
int is_skill() { return 1; }

// -------------------------------------------------------------

// 函数：获取技能号码
int get_number() { return Number; }

// 函数：设置技能号码
int set_number( int id ) { return Number = id; }

// 函数：获取技能名称
string get_name() { return Name; }

// 函数：设置技能名称
string set_name( string name ) { return Name = name; }

// 函数：获取技能类别
int get_skill_type() { return Type; }

// 函数：设置技能类别
int set_skill_type( int type ) { return Type = type; }

// -------------------------------------------------------------

// 函数：获取技能文件
string get_skill_file( int skl ) { return sprintf( SKILL_DIR "%02d/%04d", skl/100, skl ); }

// 函数：获取特殊技文件
string get_perform_file( int pf ) { return sprintf( SKILL_DIR "%02d/%05d", pf/1000, pf ); }

//玩家可以奖励提升的技能
int *get_bonus_skill(object who)
{
	string *nSkill;
	int *nSkill1,i,size,skill,level;
	
	nSkill = keys(who->get_skill_dbase());	
	size = sizeof(nSkill);
	if ( size == 0 )
		return 0;
	nSkill1 = ({});
	level = who->get_level();
	for(i=0;i<size;i++)
	{
		skill = to_int(nSkill[i]);
		if ( who->get_skill(skill) >= level +10 )
			continue;
		nSkill1 += ({skill});
	}
	nSkill1 -= ({430,431,432,433,434,435,436,437,438,439,});	//去除不能增加的技能
	return nSkill1;
}
