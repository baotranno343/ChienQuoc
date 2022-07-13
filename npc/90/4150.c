
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <cmd.h>
#include <ansi.h>
#include <task.h>
inherit OFFICER;

// 函数：师父识别
int is_master() { return 1; }

// 函数：获取门派名称
string get_fam_name() { return "Đường Môn"; }

// 函数：获取人物造型
int get_char_picid() { return 9415; }

// 函数：获取升级顺序
int get_fam_order() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

// 有自己的do_look函数
int is_self_look() { return 1; }

int get_level() { return 150; }

void do_skill();
void do_quest();
void do_giveup();
void do_giveup2();
void do_apprentice(string arg);
void accept_quest();
void task_info();
void do_valentine();
void do_valentine2();
void do_valentine3();
void do_valentine4();
void do_valentine5();
void do_valentine6();
void do_valentine7();
void do_valentine8();
// 函数：构造处理
void create()
{
        set_name( "Đường Lão Gia" );
        set_skill(0261, 150);
        set_skill(0381, 150);
        set_skill(0363, 150);
        set_skill(0382, 150);
        set_skill(0364, 150);
        set_skill(0383, 150);
        set_skill(0365, 150);
        set_skill(0384, 150);
        set_skill(0368, 150);
        set_skill(0385, 150);
        set_2( "talk", ([
                "skills"                : (: do_skill :),
                "quest"                 : (: do_quest :),
                "giveup"                : (: do_giveup :),
                "giveup2"               : (: do_giveup2 :),
                "apprentice"            : (: do_apprentice :),    
                "accept_quest"            : (: accept_quest :),
                "task_info"             : (: task_info :),
                "valentine"             : (: do_valentine :),
                "valentine2"             : (: do_valentine2 :),
                "valentine3"             : (: do_valentine3 :),
                "valentine4"             : (: do_valentine4 :),
                "valentine5"             : (: do_valentine5 :),
                "valentine6"             : (: do_valentine6 :),
                "valentine7"             : (: do_valentine7 :),
                "valentine8"             : (: do_valentine8 :),
        ]));
        set_2( "good", ([
                "01" : "/item/71/1010",
                "02" : "/item/71/1020",                
                "03" : "/item/60/0010",
                "04" : "/item/60/4020",
                "05" : "/item/61/0010",
                "06" : "/item/61/4020",
                "07" : "/item/65/0010",
                "08" : "/item/65/4020",
                "09" : "/item/66/0010",
                "10" : "/item/66/4020",                
                "11" : "/item/88/0010",
                "12" : "/item/88/4020",
                "13" : "/item/87/4010",
                "14" : "/item/87/4020",              
        ]) );
        setup();
}

// 函数：点击出现界面
void do_look( object who ) 
{ 
	object item;
 	if( objectp( item = present("月老给的包裹", who, 1, MAX_CARRY) ) && who->get_quest("valentine.flag") == 1)
	{
	object npc,me=this_object();
	int id = getoid( me ),i;
        string cmd = sprintf( "talk %x# valentine\n", id );
	string tmp ="";
	tmp = ESC "神秘的种子\n" + cmd;
	send_user( who, "%c%s", ':', get_name() + "：\n……\n" +
                        tmp +
                        ESC "离开\nCLOSE\n" );	
     	}
 	else if( who->get_quest("valentine.flag") == 2 && who->get_quest("valentine.type") != 1)
	{
	object npc,me=this_object();
	int id = getoid( me ),i;
        string cmd = sprintf( "talk %x# valentine3\n", id );
	string tmp ="";
	tmp = ESC "诡异的飞贼\n" + cmd;
	send_user( who, "%c%s", ':', get_name() + "：\n……\n" +
                        tmp +
                        ESC "离开\nCLOSE\n" );	
     	}
 	else if( who->get_quest("valentine.flag") == 2 && who->get_quest("valentine.bonus") == 1)
	{
	object npc,me=this_object();
	int id = getoid( me ),i;
        string cmd = sprintf( "talk %x# valentine5\n", id );
	string tmp ="";
	tmp = ESC "诡异的飞贼\n" + cmd;
	send_user( who, "%c%s", ':', get_name() + "：\n……\n" +
                        tmp +
                        ESC "离开\nCLOSE\n" );	
     	}
 	else if( !objectp( item = present("神秘的种子", who, 1, MAX_CARRY) ) && who->get_quest("valentine.flag") == 3)
	{
	object npc,me=this_object();
	int id = getoid( me ),i;
        string cmd = sprintf( "talk %x# valentine7\n", id );
	string tmp ="";
	tmp = ESC "求索\n" + cmd;
	send_user( who, "%c%s", ':', get_name() + "：\n……\n" +
                        tmp +
                        ESC "离开\nCLOSE\n" );	
     	}
     	else 
	TASK_MASTER_D->do_look( who, this_object() ); 
}

// 函数：技能学习界面
void do_skill(  ) { LEARN_CMD->learn_menu( this_player(), this_object() ); }

// 函数：领取任务
void do_quest(  ) { TASK_MASTER_D->do_quest( this_player(), this_object() ); }

// 函数：取消任务
void do_giveup(  ) { TASK_MASTER_D->do_giveup( this_player(), this_object() ); }

// 函数：取消任务2
void do_giveup2(  ) { TASK_MASTER_D->do_giveup2( this_player(), this_object() ); }

// 函数：拜师
void do_apprentice( string arg  ) { TASK_APPRENTICE_D->do_apprentice( this_player(), this_object(), arg ); }
//接受任务
void accept_quest(  ) { TASK_MASTER_D->accept_quest( this_player(), this_object() ); }
//任务信息
void task_info(  ) { TASK_MASTER_D->task_info( this_player(), this_object() ); }

// 接收心爱物品
int accept_object( object player, object obj ) 
{
	object who = this_object();
	return TASK_MASTER_D->accept_object( who, player, obj ); 
}

// 函数：删除师门技能
void delete_family_skill( object who )
{
        mapping skls;
        object file;
        string *name, result;
        int skill, level, i, size;

        skls = get_skill_dbase();
        name = keys(skls);
        size = sizeof(name);
        result = sprintf( "您决定脱离“%s”门下！损失：", get_fam_name() );
        for( i = 0; i < size; i ++ )
        {
                skill = to_int( name[i] );
                if( level = who->get_skill(skill) )
                {
                        if( file = load_object( SKILL->get_skill_file(skill) ) ) 
                                result = sprintf("%s%s(%d) ", result, file->get_name(), level);
                        else    result = sprintf("%s%s(%d) ", result, name[i], level);
                }
                who->delete_skill(skill);
        }

        who->log_legend(result);
}

void do_valentine()
{
	object who=this_player(); 
	object me = this_object();
        __FILE__ ->do_valentine_call(who, me);
}
void do_valentine_call( object who, object me )
{
	object item;
 	if( objectp( item = present("月老给的包裹", who, 1, MAX_CARRY) ) && who->get_quest("valentine.flag") == 1)
	{
		int id = getoid( me ),i;
	        string cmd = sprintf( "talk %x# valentine2\n", id );
		string tmp ="";
		tmp = ESC "完成任务\n" + cmd;
		send_user( who, "%c%s", ':', get_name() + "：\n    喔～包裹我收下了，谢谢你！看来你也是一个有诚心的小伙子，但是这神秘的种子在几日前就已经被偷走了，如果你很想要得到的话，你考虑清楚后再来找我吧！\n" +
	                        tmp +
	                        ESC "离开\nCLOSE\n" );
	}
}

void do_valentine2()
{
	object who=this_player(); 
	object me = this_object();
        __FILE__ ->do_valentine2_call(who, me);
}
void do_valentine2_call( object who, object me )
{
	object item;
 	if( objectp( item = present("月老给的包裹", who, 1, MAX_CARRY) ) && who->get_quest("valentine.flag") == 1)
	{
	     	item->remove_from_user();
	     	destruct(item);  
	     	who->add_exp(500);
	     	who->set_quest( "valentine.flag", 2 );
	
	        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_VALENTINE,1,0,"" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,1,"" ); 
		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"" ); 
	}
}

void do_valentine3()
{
	object who=this_player(); 
	object me = this_object();
        __FILE__ ->do_valentine3_call(who, me);
}
void do_valentine3_call( object who, object me )
{
	int p,x,y,z;
        string cmd,cWord,tmp="";
	object map;
	if( who->get_quest("valentine.flag") == 2 && who->get_quest("valentine.type") != 1)
	{
		z = ({10,20,30,40,50,60,70})[random(7)];
		if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) ) return ;
	        x = ( p % 1000000 ) / 1000;  y = p % 1000;
		if( !objectp( map = get_map_object(z) ) || !map->is_scene() ) return;
	        cWord = sprintf(me->get_name() + "：\n    真是不凑巧啊，仅有的一袋神秘种子在几日前已经被偷走了，据我们的线报称偷走种子的贼似乎在%s国的（%d，%d）出没。如果你能拿回种子，自然就归你了！\n",map->get_name(),x,y);
		who->set_quest("valentine.name","诡异的飞贼");
		who->set("valentine.x",x);
		who->set("valentine.y",y);
		who->set("valentine.z",z);
	
		send_user( who, "%c%s", ':', cWord +"\n"+
			ESC +sprintf("接受任务。\ntalk %x# valentine4\n",getoid(me)) +
			ESC "离开。\nCLOSE\n" ); 
	}
}

void do_valentine4()
{
"/sys/party/valentine"->do_valentine4_call( this_player(), this_object() ) ; 
}

void do_valentine5()
{
	object who=this_player(); 
	object me = this_object();
        __FILE__ ->do_valentine5_call(who, me);
}
void do_valentine5_call( object who, object me )
{
        string cmd,cWord,tmp="";
	if( who->get_quest("valentine.flag") == 2 && who->get_quest("valentine.bonus") == 1)
	{
	        cWord = sprintf(me->get_name() + "：\n    种子是你想要的，你拿去吧！");
		who->set_quest("valentine.name","诡异的飞贼");
		send_user( who, "%c%s", ':', cWord +"\n"+
			ESC +sprintf("完成任务。\ntalk %x# valentine6\n",getoid(me)) +
			ESC "离开。\nCLOSE\n" ); 
	}
}

void do_valentine6()
{
	object who=this_player(); 
	object me = this_object();
        __FILE__ ->do_valentine6_call(who, me);
}
void do_valentine6_call( object who, object me )
{
        object map, npc, item;
        string name;
        int level, i, size;
        int z, x, y, p,iType,x1,y1;
	if( who->get_quest("valentine.flag") == 2 && who->get_quest("valentine.bonus") == 1)
	{
	     	if( !objectp( item = present("神秘的种子", who, 1, MAX_CARRY) ) )
	     	{
	     		send_user( who, "%c%s", '!', "您身上没有神秘的种子");
	                return;
	        }          
	     	item->remove_from_user();
	     	destruct(item);  
	     	who->add_exp(500);
	     	who->add_potential(10);
	     	who->set_quest( "valentine.flag", 3 );
	
	        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_VALENTINE,2,0,"" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,2,"" ); 
		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"" ); 
	}
}

void do_valentine7()
{
	object who=this_player(); 
	object me = this_object();
        __FILE__ ->do_valentine7_call(who, me);
}
void do_valentine7_call( object who, object me )
{

        string cmd,cWord,tmp="";
	object item;
	if( !objectp( item = present("神秘的种子", who, 1, MAX_CARRY) ) && who->get_quest("valentine.flag") == 3)
	{
	        cWord = sprintf(me->get_name() + "：\n    将这神秘的种子拿去交给月老吧，我想他应该知道要怎样做的！");
		send_user( who, "%c%s", ':', cWord +"\n"+
			ESC +sprintf("接受任务。\ntalk %x# valentine8\n",getoid(me)) +
			ESC "离开。\nCLOSE\n" ); 
	}
}

void do_valentine8()
{
	object who=this_player(); 
	object me = this_object();
        __FILE__ ->do_valentine8_call(who, me);
}
void do_valentine8_call( object who, object me )
{
object item;
	if( !objectp( item = present("神秘的种子", who, 1, MAX_CARRY) ) && who->get_quest("valentine.flag") == 3)
	{
		object item214_1 = new ("item/04/0421");    //神秘的种子
		string name214_1 = "item/04/0414";
                if (item214_1)
                {
                        if( USER_INVENTORY_D->can_carry(who, item214_1)  >=1 )
                        {
                                int p =item214_1->move(who, -1);
                                item214_1->add_to_user(p);
	                        send_user( who, "%c%s", '!', "得到"HIR"神秘的种子"NOR"一袋");
//				who->set_quest( "valentine.name", name214_1 );
				send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,3,"求索" ); 		                        
				send_user( who, "%c%s", '!', "你领取了情人节任务————求索！");
                        }       
                        else
                        {
                        	destruct(item214_1); 
                        	send_user( who, "%c%s", '!', "您身上没有空位！");
                        }
                }  
	}
}
