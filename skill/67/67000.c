
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      670				// 技能名字
#define THIS_SORT      	1				// 小类别
#define THIS_PERFORM    0				
#define PF_NAME        "Đồng Quáng Dã Luyện"

#define SKILL_LEVEL     1
#define SKILL_EXP     	0	
#define SKILL_TOOL	0	
#define SUB_TILI	1				// 体力需求
#define SKILL_FINAL	"/item/stuff/0009"		// 制作的结果
#define SKILL_SEX	0				// 是否区分男女性别
#define SKILL_TEMP	0				// 是否一次性使用的技能
#define MASTER_NEED	"Chủ Tiệm Sửa Chữa"

int get_skill_level()
{
	return SKILL_LEVEL;
}

mapping product = ([
	"1"	: 	1, 
	]);

// 函数：基本技能
int is_vita_perform() { return 1; }

void effect_break(object me, string arg);

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        result = sprintf(HIC"%s\n" NOR "Kĩ năng yâu cầu：%d cấp\nĐộ thuần thục yêu cầu：%d\nThể lực yêu cầu：%d\n    Chế tác đồng kiếm", 
        	PF_NAME, SKILL_LEVEL, SKILL_EXP, SUB_TILI);
        return result;
}

// 发送详细要求
void send_detail( object me )
{
	object file;
	int pf, size, type;
	string * name;
	string result;
	file = load_object(SKILL_FINAL);
	if (file)
	{
		pf = THIS_SKILL * 100 + THIS_PERFORM;
		name = keys(product);
		size = sizeof(name);
		type = file->get_fin_type();
		if (type==0) type = file->get_stuff_type();
		if (size==0) return;
		switch(size)
		{
		case 1:
			send_user(me, "%c%c%w%w%d%w%c%c%w%w%w", 0x60, 8, THIS_SKILL, THIS_SORT, pf, type, SKILL_SEX, SUB_TILI, SKILL_TOOL, to_int(name[0]), product[name[0]]);
			break;
		case 2:
			send_user(me, "%c%c%w%w%d%w%c%c%w%w%w%w%w", 0x60, 8, THIS_SKILL, THIS_SORT, pf, type, SKILL_SEX, SUB_TILI, SKILL_TOOL, to_int(name[0]), product[name[0]], to_int(name[1]), product[name[1]]);
			break;
		case 3:
			send_user(me, "%c%c%w%w%d%w%c%c%w%w%w%w%w%w%w", 0x60, 8, THIS_SKILL, THIS_SORT, pf, type, SKILL_SEX, SUB_TILI, SKILL_TOOL, to_int(name[0]), product[name[0]], to_int(name[1]), product[name[1]], to_int(name[2]), product[name[2]]);
			break;						
		}	
		send_user(me, "%c%c%w%w%d%w%w", 0x60, 7, THIS_SKILL, THIS_SORT, pf, SKILL_LEVEL, SKILL_EXP);				
	}
	
}

// 函数：命令处理
int main( object me, int count, string sex, object diamond1, object diamond2, object diamond3 )
{
        int level, mp, size, i, stuff, tool_type, tool_level, x, y, z, flag;
        string * name;
        object file, *char, tool;
	level = me->get_skill(THIS_SKILL);	
	if (level<SKILL_LEVEL) 
	{
		printf( ECHO "使用“" PF_NAME "”技能等级不足。" );
		return 1;
	}
	if (me->get_skill_degree(THIS_SKILL)<SKILL_EXP) 
	{
		printf( ECHO "使用“" PF_NAME "”技能熟练度不足。" );
		return 1;
	}
	// 检查有无相应技能
	if (count<0) 
	{
		printf( ECHO "使用“" PF_NAME "”需指定制作数量。" );
		return 1;
	}
	if ("/sys/item/product"->check_vita_skill(me, THIS_SKILL * 100 + THIS_PERFORM)==0)
	{
		printf( ECHO "你还没学会“" PF_NAME "”。" );
		return 1;
	}
	if (me->get_strength()<SUB_TILI)
	{
		printf( ECHO "使用“" PF_NAME "”体力不足。" );
		return 1;
	}
	// 检查原料是否齐全	
	name = keys(product);		
	size = sizeof(name);
	for (i=0;i<size;i++)
	{
		stuff = to_int(name[i]);
		if ("/sys/item/product"->find_stuff(me, stuff)<product[name[i]])
		{
			printf( ECHO "使用“" PF_NAME "”材料不足。" );
			return 1;
		}
	}
	// 检查工具
	if (SKILL_TOOL)
	{
		tool = me->get_equip(107);
		if (!tool)
		{
			printf( ECHO "使用“" PF_NAME "”缺少工具。" );
			return 1;			
		}
		file = load_object(sprintf("/item/stuff/%04d", SKILL_TOOL));
		if (file)
		{
			tool_type = file->get_tool_type();
			tool_level = file->get_tool_level();
			if (tool_type!=tool->get_tool_type())
			{
				printf( ECHO "使用“" PF_NAME "”的工具不对。" );
				return 1;				
			}
			if (tool_level>tool->get_tool_level())
			{
				printf( ECHO "使用“" PF_NAME "”的工具的等级过低。" );
				return 1;				
			}			
		}
	}
	// 检查是否需要师父
	if (MASTER_NEED)
	{
		z = get_z(me); x = get_x(me); y = get_y(me);
		char = get_range_object(z, x, y, 5, CHAR_TYPE);
		size = sizeof(char);
		flag = 0;
		for (i=0;i<size;i++)
		{
			if (file = char[i])
			{
				if (file->get_name()==MASTER_NEED)
				{
					flag = 1;
					break;
				}
			}
		}
		if (flag==0)
		{
			printf( ECHO "Sử dụng “" PF_NAME "” cần ở bên cạnh " + MASTER_NEED + "" );
			return 1;				
		}
	}
	if( sizeof_inventory(me, 1, MAX_CARRY) >= MAX_CARRY )
	{
		printf( ECHO "使用“" PF_NAME "”道具栏至少需要有一个空位。" );
		effect_break(me, "");
		return 1;
	}	
        set_effect_2(me, EFFECT_PROGRESS, count, 3);
        me->set_progress_file(__FILE__);
        me->set_progress_arg(sex);
        me->set("progress", ({tool, diamond1, diamond2, diamond3}));
        send_user(me, "%c%c%w%s", 0x5a, 0, 3, PF_NAME+"Tiến hành....");	
        me->add_strength(-SUB_TILI);
        return 1;
}

void into_effect(object me, string arg)
{
	object tool, diamond1, diamond2, diamond3, *temp, item;
	string * name;
	int i, size, rate, stuff, p, total, amount;
	temp = me->get("progress");
	// 检查空位	
	if (sizeof(temp)==3)
	{
		tool = temp[0];
		diamond1 = temp[1];
		diamond2 = temp[2];
		diamond3 = temp[3];
	}
	// 检查东西还在不在
	name = keys(product);		
	size = sizeof(name);
	for (i=0;i<size;i++)
	{
		stuff = to_int(name[i]);
		if ("/sys/item/product"->find_stuff(me, stuff)<product[name[i]])
		{
			effect_break(me, "");
			return ;
		}
	}
	for (i=0;i<size;i++)
	{
		stuff = to_int(name[i]);
		"/sys/item/product"->sub_stuff(me, stuff, product[name[i]]);
	}	
	// 检查工具以及宝石
	if (tool)
	{
		if (tool->is_in_user(me)==0)
		{
			effect_break(me, "");
			return ;
		}				
	}	
	if (diamond1)
	{
		if (diamond1->is_in_user(me)==0)
		{
			effect_break(me, "");
			return ;
		}				
	}	
	if (diamond2)
	{
		if (diamond2->is_in_user(me)==0)
		{
			effect_break(me, "");
			return ;
		}		
	}	
	if (diamond3)
	{
		if (diamond3->is_in_user(me)==0)
		{
			effect_break(me, "");
			return ;
		}		
	}	
	// 计算成功率和极品率
	rate = 100;
	if (random(100)<rate)
	{
		item = new (SKILL_FINAL);
		if (item)
		{		
			printf( ECHO "您使用“" PF_NAME "”炼出" +item->get_name()+ "。" );
			if( ( total = USER_INVENTORY_D->can_carry(me, item) ) < 1 )
			{
	                        send_user( me, "%c%s", '!', "您身上没有空位！");
	                        destruct(item);       
	                        effect_break(me, "");
	                        return ;  			
			}			
			total = 1;	
			amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
	                if( amount > 0 && item->set_amount(amount) )
	                {              	
	                        if( p = item->move(me, -1) )
	                        {
	                                item->add_to_user(p);
	                        }
	                }
	                else    item->add_amount( -total );		
		}
	}
	if (tool) tool->add_lasting(-100);
	if (diamond1) diamond1->add_amount(-1);
	if (diamond2) diamond2->add_amount(-1);
	if (diamond3) diamond3->add_amount(-1);
	if (me->get_strength()<SUB_TILI)
	{
		effect_break(me, "");
		return;
	}	
	if( !get_effect_3(me, EFFECT_PROGRESS) ) 
	{
		send_user(me, "%c%c%c", 0x5a, 1, 1);
		me->set("progress", 0 );
	}
	else	
	{
        	me->set("progress", ({tool, diamond1, diamond2, diamond3}));
        	send_user(me, "%c%c%w%s", 0x5a, 0, 3, PF_NAME+"Tiến hành....");	
        	me->add_strength(-SUB_TILI);
        }
	// 重新设定 progress_arg
}

void effect_break(object me, string arg)
{
	object who, owner;
	int add, time;
	send_user(me, "%c%c%c", 0x5a, 1, 0);
	set_effect_2(me, EFFECT_PROGRESS, 0, 0);	
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
	int pf;
	pf = THIS_SKILL * 100 + THIS_PERFORM;
	send_user(me, "%c%c%w%w%d%s", 0x60, 6, THIS_SKILL, THIS_SORT, pf, PF_NAME);
	send_detail(me);
}
