
#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>
#include <item.h>
#include <skill.h>

inherit OFFICER;

int pic_id;					//人物造型
int this_skill;					//对应的技能类型
int skill_level;				//技能等级
int skill_exp;					//采集经验奖励
int reset_time;					//刷新时间
int tool_level;					//工具等级
int stuff_number;				//资源编号
int stuff_number2;				//付加资源编号
string pf_name;					//技能名称
int tool_type;					//工具类型
string reset_file;				//刷新文件

string set_reset_file(string file){return reset_file = file;}	// 函数：设置刷新文件
                                                                             
string get_reset_file(string file){return reset_file;}		// 函数：获取刷新文件

int set_tool_type(int type){return tool_type = type;}		// 函数：设置工具类型
                                                                             
int get_tool_type(){return tool_type;}				// 函数：获取工具类型

string set_pf_name(string name){return pf_name = name;}		// 函数：设置技能名称
                                                                             
string get_pf_name(){return pf_name;}				// 函数：获取技能名称

int set_stuff_number2(int num){return stuff_number2 = num;}	// 函数：设置附加资源编号
                                                                             
int get_stuff_number2(){return stuff_number2;}			// 函数：获取附加资源编号

int set_stuff_number(int num){return stuff_number = num;}	// 函数：设置资源编号
                                                                             
int get_stuff_number(){return stuff_number;}			// 函数：获取资源编号

int set_tool_level(int lv){return tool_level = lv;}		// 函数：设置工具等级
                                                                             
int get_tool_level(){return tool_level;}			// 函数：获取工具等级

int set_reset_time(int t){return reset_time = t;}		// 函数：设置刷新时间
                                                                             
int get_reset_time(){return reset_time;}			// 函数：获取刷新时间

int set_skill_exp(int exp){return skill_exp = exp;}		// 函数：设置采集经验奖励
                                                                             
int get_skill_exp(){return skill_exp;}				// 函数：获取采集经验奖励

int set_skill_level(int slv){return skill_level = slv;}		// 函数：设置对应的技能等级
                                            
int get_skill_level(){return skill_level;}			// 函数：获取对应的技能等级

int set_this_skill(int sk){return this_skill = sk;}		// 函数：设置对应的技能类型
                                            
int get_this_skill(){return this_skill;}			// 函数：获取对应的技能类型

int set_char_picid(int pic){return pic_id = pic;}			// 函数：设置人物造型

int get_char_picid() { return pic_id;}				// 函数：获取人物造型

// 有自己的do_look函数
int is_self_look() { return 1; }



int add_aobj2(object who, object me, string item_str, string unit_str, string pf_name)
{
	object item;
	int p, total, amount;	
	item = new (item_str);
	if (item)
	{
		if(pf_name =="采药"||pf_name =="食材"){item->set_amount(me->get("time"));}
		if( ( total = USER_INVENTORY_D->can_carry(who, item) ) < 1 )
		{	
			send_user( who, "%c%s", '!', "您身上没有空位!");
	                destruct(item);
	                return 0;     			
		}
		else
		{
			printf( ECHO "您获得%s%d%s.", item->get_name(), item->get_amount(), unit_str);
			if( total > item->get_amount()) total = item->get_amount();
			amount = USER_INVENTORY_D->carry_combined_item(who, item, total);
	                if( amount > 0 && item->set_amount(amount))
	                {         	
	                        if( p = item->move(who, -1) )
	                        {
	                                item->add_to_user(p);
	                        }
	                }
	                else    item->add_amount( -total );
	                return 1;	
		}		               
	}
	return 0;	
}

int add_aobj(object who, object me, string item_str, string unit_str, string pf_name)
{
	return __FILE__->add_aobj2(who,me,item_str,unit_str,pf_name);
}

// 函数：对话处理
void do_look2( object who, object me, int this_skill, int skill_level, string pf_name, int skill_exp, int tool_level, int tool_type )
{
	object item;
	if( get_effect(who, EFFECT_CHAR_INVISIBLE) ) set_effect_2(who, EFFECT_CHAR_INVISIBLE, 1, 1 );
	if (get_z(me)!=get_z(who)||abs(get_x(me)-get_x(who))>5||abs(get_y(me)-get_y(who))>5) return;
	if (who->get_skill(this_skill)<skill_level) 
	{
		send_user( who, "%c%s", '!', sprintf("您的%s技能不足%d级!", pf_name, skill_level));
		return;
	}
	if (who->get_skill_degree(this_skill)<skill_exp) 
	{
		send_user( who, "%c%s", '!', sprintf("您的%s熟练度不足%d!", pf_name, skill_exp));
		return;
	}
	item = who->get_equip(107);
	if (!item || item->get_item_type_2()!=tool_type || item->get_level()< tool_level || item->get_lasting()< 100) item = 0;
	if (!item) 
	{
		send_user( who, "%c%s", '!', sprintf("您没有%d级以上的%s工具!", tool_level, pf_name));
		return;
	}
	
	if (get_effect(who, EFFECT_PROGRESS2)) return ;
	if(pf_name =="采药"){if (get_effect_3(who, EFFECT_PROGRESS)) {return ;}}
        set_effect(who, EFFECT_PROGRESS2, 6 );
        who->set_progress_file(get_file_name(me));	
        who->set_progress_arg( me->get_char_id());
	send_user(who, "%c%c%w%s", 0x5a, 0, 6, pf_name+"中...");	
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 02011, 10, OVER_BODY, PF_LOOP );
	item->add_lasting(-100);
}

void do_look( object who )
{
	object me = this_object();
	return __FILE__->do_look2(who,me,this_skill,skill_level,pf_name,skill_exp,tool_level,tool_type);
}


// 函数：状态处理
void into_effect2( object who, string arg, string pf_name, int tool_level,int tool_type, int stuff_number,int stuff_number2 )
{
	object me, item;	
	string unit_str;

	if(pf_name =="采药"||pf_name =="食材"){unit_str = "个";}
	if(pf_name =="采矿"){unit_str = "块";}
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 02011, 0, OVER_BODY, PF_STOP );
	if( !objectp( me = find_char(arg) ) )
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}
	if (get_z(me)!=get_z(who)||abs(get_x(me)-get_x(who))>5||abs(get_y(me)-get_y(who))>5)
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}		
	
	send_user(who, "%c%c%c", 0x5a, 1, 1);
	if(!add_aobj(who,me,sprintf("/item/stuff/%04d", stuff_number),unit_str,pf_name)){return;}
	if(pf_name =="采药"||pf_name =="食材"){me->set("time", 0);}
	if(pf_name =="采矿")
	{
		if (random100()<20)
		{
			if(!add_aobj(who,me,sprintf("/item/stuff/%04d", stuff_number2),unit_str,pf_name)){return;}
		}
		me->add("time", -1);
	}
	if (me->get("time")<=0)
	{
		if ( me->get("never_refresh") )		//不刷新
		{
			me->remove_from_scene();
			destruct(me);
		}
		else
			me->wait_for_reset(me);		
		return;
	}
	// 检查是否已采完
	item = who->get_equip(107);
	if (!item || item->get_item_type_2()!=tool_type || item->get_level()< tool_level || item->get_lasting()< 100) item = 0;
	if (!item) return;	
	set_effect(who, EFFECT_PROGRESS2, 6 );
	send_user(who, "%c%c%w%s", 0x5a, 0, 6, pf_name + "中...");
	item->add_lasting(-100);
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 02011, 10, OVER_BODY, PF_LOOP );
}

void into_effect( object who, string arg )
{
	return __FILE__->into_effect2(who,arg,pf_name,tool_level,tool_type,stuff_number, stuff_number2);
}


void effect_break2(object who, string arg)
{
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 02011, 0, OVER_BODY, PF_STOP );
	set_effect(who, EFFECT_PROGRESS2, 0);
	send_user(who, "%c%c%c", 0x5a, 1, 0);
}

void effect_break(object who, string arg)
{
	return __FILE__->effect_break2(who,arg);
}


void wait_for_reset2(object me,int reset_time)
{
	me->remove_from_scene();
	call_out( "reset_stuff", reset_time, me);
}

void wait_for_reset(object me)
{
	return __FILE__->wait_for_reset2(me,reset_time);
}


void reset_stuff2(object me,string reset_file,string pf_name)
{
	int z, p;

	z = me->get("z");
	if (z==0) 
	{
		z = 281;
		me->set("z", 281);
	}
	p = reset_file->get_xy(z);
	me->add_to_scene(z, p / 1000, p % 1000, 3);
	if(pf_name =="采药"||pf_name =="食材"){me->set("time", 1+random(3));}
	if(pf_name =="采矿"){me->set("time", 1);}	
}

void reset_stuff(object me)
{
	return __FILE__->reset_stuff2(me,reset_file,pf_name);
}