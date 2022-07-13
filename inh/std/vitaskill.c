#include <effect.h>
#include <skill.h>
private int Skill;                     	// 大技能编号
private int Type;                     	// 技能类别
private int Number;                     // 技能序号
private int Level;                     	// 技能要求等级
private int Tool;                     	// 技能要求工具
private string Name;			// 技能名字
private string Final;			// 制作的结果
private int Temp;                     	// 是否临时标志
private string Master;			// 需要师傅
private int Color;                     	// 成品颜色
private int Rate;                     	// 成功率
private mapping Product;		// 原材料
private int Count;			// 成品的数量
private int Tili;			// 消耗体力

// 函数：基本技能
int is_vita_perform() { return 1; }

// -------------------------------------------------------------

// 函数：获取技能号码
int get_number() { return Number; }

// 函数：设置技能号码
int set_number( int id ) { return Number = id; }

// 函数：获取技能序号
int get_skill() { return Skill; }

// 函数：设置技能号码
int set_skill( int id ) { return Skill = id; }

// 函数：获取工具
int get_tool() { return Tool; }

// 函数：设置技能号码
int set_tool( int id ) { return Tool = id; }

// 函数：获取成品数量
int get_count() { return Count; }

// 函数：设置成品数量
int set_count( int id ) { return Count = id; }

// 函数：获取技能名称
string get_name() { return Name; }

// 函数：设置技能名称
string set_name( string name ) { return Name = name; }

// 函数：获取技能产品
string get_final() { return Final; }

// 函数：设置技能名称
string set_final( string name ) { return Final = name; }

// 函数：获取所需工匠
string get_master() { return Master; }

// 函数：设置所需工匠
string set_master( string name ) { return Master = name; }

// 函数：获取所需材料
mapping get_product() { return copy(Product); }

// 函数：设置所需材料
mapping set_product( mapping name ) { return Product = copy(name); }

// 函数：获取技能类别
int get_skill_type() { return Type; }
// 函数：设置技能类别
int set_skill_type( int type ) { return Type = type; }

int get_skill_level(){ return Level; }
int set_skill_level(int level){ return Level = level; }

int get_tili(){ return Tili; }
int set_tili(int level){ return Tili = level; }

int get_skill_color(){ return Color;}
int set_skill_color(int color){ return Color = color;}

int get_skill_temp(){ return Temp;}
int set_skill_temp(int temp){ return Temp = temp;}

int get_base_rate(){ return Rate;}
int set_base_rate(int rate){ return Rate = rate;}

void effect_break(object me, string arg)
{
	send_user(me, "%c%c%c", 0x5a, 1, 0);
	set_effect_2(me, EFFECT_PROGRESS, 0, 0);	
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 发送详细要求
void send_detail( object me )
{
	object file, who;
	int pf, size, type;
	string * name;
	string result;
	mapping product;
	who = this_object();
	file = load_object(who->get_final());
	if (file)
	{
		pf = who->get_skill() * 100 + who->get_number();
		product = who->get_product();
		name = keys(product);
		size = sizeof(name);
		type = file->get_fin_type();
		if (type==0) type = file->get_stuff_type();
		if (size==0) return;
		switch(size)
		{
		case 1:
			send_user(me, "%c%c%w%w%d%w%c%c%w%w%w", 0x60, 8, who->get_skill(), who->get_skill_type(), pf, type, 0, 1, who->get_tool(), to_int(name[0]), Product[name[0]]);
			break;
		case 2:
			send_user(me, "%c%c%w%w%d%w%c%c%w%w%w%w%w", 0x60, 8, who->get_skill(), who->get_skill_type(), pf, type, 0, 1, who->get_tool(), to_int(name[0]), Product[name[0]], to_int(name[1]), Product[name[1]]);
			break;
		case 3:
			send_user(me, "%c%c%w%w%d%w%c%c%w%w%w%w%w%w%w", 0x60, 8, who->get_skill(), who->get_skill_type(), pf, type, 0, 1, who->get_tool(), to_int(name[0]), Product[name[0]], to_int(name[1]), Product[name[1]], to_int(name[2]), Product[name[2]]);
			break;	
		case 4:
			send_user(me, "%c%c%w%w%d%w%c%c%w%w%w%w%w%w%w%w%w", 0x60, 8, who->get_skill(), who->get_skill_type(), pf, type, 0, 1, who->get_tool(), to_int(name[0]), Product[name[0]], to_int(name[1]), Product[name[1]], to_int(name[2]), Product[name[2]], to_int(name[3]), Product[name[3]]);
			break;	
		case 5:
			send_user(me, "%c%c%w%w%d%w%c%c%w%w%w%w%w%w%w%w%w%w%w", 0x60, 8, who->get_skill(), who->get_skill_type(), pf, type, 0, 1, who->get_tool(), to_int(name[0]), Product[name[0]], to_int(name[1]), Product[name[1]], to_int(name[2]), Product[name[2]], to_int(name[3]), Product[name[3]], to_int(name[4]), Product[name[4]]);
			break;	
		case 6:
			send_user(me, "%c%c%w%w%d%w%c%c%w%w%w%w%w%w%w%w%w%w%w%w%w", 0x60, 8, who->get_skill(), who->get_skill_type(), pf, type, 0, 1, who->get_tool(), to_int(name[0]), Product[name[0]], to_int(name[1]), Product[name[1]], to_int(name[2]), Product[name[2]], to_int(name[3]), Product[name[3]], to_int(name[4]), Product[name[4]], to_int(name[5]), Product[name[5]]);
			break;						
		}		
		send_user(me, "%c%c%w%w%d%w%w", 0x60, 7, who->get_skill(), who->get_skill_type(), pf, who->get_skill_level(), 0);			
	}
	
}

// 函数：能否使用特技
void can_perform( object me )
{
	int pf;
	object who = this_object();
	pf = who->get_skill() * 100 + who->get_number();
	send_user(me, "%c%c%w%w%d%s", 0x60, 6, who->get_skill(), who->get_skill_type(), pf, who->get_name());
	send_detail(me);
}

void into_effect(object me, string arg)
{
	"/sys/item/vitaskill"->into_effect(me, this_object(), arg);
}

int main( object me, int count, string sex, object diamond1, object diamond2, object diamond3 )
{
	return "/sys/item/vitaskill"->main(me, this_object(), count, sex, diamond1, diamond2, diamond3);
}