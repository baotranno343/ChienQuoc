
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
string get_fam_name() { return "Đào Hoa Nguyên"; }

// 函数：获取升级顺序
int get_fam_order() { return 2; }

// 函数：获取人物造型
int get_char_picid() { return 9112; }

// 函数：小贩识别
int is_seller() { return 1; }

// 有自己的do_look函数
int is_self_look() { return 1; }

int get_level() { return 120; }

void do_skill();
void do_quest();
void do_giveup();
void do_giveup2();
void do_apprentice(string arg);
void accept_quest();
void task_info();
void valentine( string arg );
void valentine2();
// 函数：构造处理
void create()
{
        set_name( "Vong Tình Bà Bà" );
        
        set_skill(0211, 120);
        set_skill(0371, 120);
        set_skill(0212, 120);
        set_skill(0372, 120);
        set_skill(0316, 120);
        set_skill(0373, 120);
        set_skill(0317, 120);
        set_skill(0374, 120);
        set_skill(0319, 120);
        set_skill(0375, 120);
        set_2( "talk", ([
                "skills"                : (: do_skill :),
                "quest"                 : (: do_quest :),
                "giveup"                : (: do_giveup :),
                "giveup2"               : (: do_giveup2 :),
                "apprentice"            : (: do_apprentice :),                        
                "accept_quest"            : (: accept_quest :),
                "task_info"             : (: task_info :),                  	
                "valentine"             : (: valentine :),                  	
                "valentine2"             : (: valentine2 :),                  	
        ]));
        set_2( "good", ([
        	"01" : "/item/70/0010",
        	"02" : "/item/70/1020",                
        	"03" : "/item/60/0010",
        	"04" : "/item/60/1020",
        	"05" : "/item/61/0010",
        	"06" : "/item/61/1020",
        	"07" : "/item/65/0010",
        	"08" : "/item/65/1020",
        	"09" : "/item/66/0010",
        	"10" : "/item/66/1020",                
        	"11" : "/item/88/0010",
        	"12" : "/item/88/1020",
        	"13" : "/item/87/1010",
        	"14" : "/item/87/1020",              
        ]) ); 
        setup();
}

// 函数：点击出现界面
void do_look( object who )
 {
	object npc,me=this_object();
	int i,id = getoid( me );
	object item;
	string cmd,tmp ="";
	string cmds ="：\n这位小朋友找我这个老太婆有什么事？老婆子我可是很忙的，真有什么要事的话先找我的两个徒弟吧。\n";
 	if( who->get_quest("valentine.flag") == 5)
	{
        cmd = sprintf( "talk %x# valentine.1\n", id );
	tmp = ESC "情人节的传说\n" + cmd;
	send_user( who, "%c%s", ':', get_name() + cmds +
                        tmp +
                        ESC "离开\nCLOSE\n" );	
     	}
 	else if( who->get_quest("valentine.flag") == 6 && who->get_quest("valentine.type")!= 1)
	{
        cmd = sprintf( "talk %x# valentine.3\n", id );
	tmp = ESC "天使爱美丽\n" + cmd;
	send_user( who, "%c%s", ':', get_name() + cmds +
                        tmp +
                        ESC "离开\nCLOSE\n" );	
     	}
 	else if( who->get_quest("valentine.flag") == 6 && who->get_quest("valentine.bonus") == 1 && objectp( item = present("忘情婆婆要的胭脂", who, 1, MAX_CARRY)) && objectp( item = present("忘情婆婆要的梳子", who, 1, MAX_CARRY)) && objectp( item = present("忘情婆婆要的头钗", who, 1, MAX_CARRY)))
	{
        cmd = sprintf( "talk %x# valentine.4\n", id );
	tmp = ESC "天使爱美丽\n" + cmd;
	send_user( who, "%c%s", ':', get_name() + cmds +
                        tmp +
                        ESC "离开\nCLOSE\n" );	
     	}
 	else if( who->get_quest("valentine.flag") == 7 && !objectp( item = present("巧克力豆", who, 1, MAX_CARRY)))
	{
        cmd = sprintf( "talk %x# valentine.6\n", id );
	tmp = ESC "巧克力豆\n" + cmd;
	send_user( who, "%c%s", ':', get_name() + cmds +
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


void valentine( string arg )
{
        object me = this_object();
        __FILE__ ->do_valentine(me, arg);
}

void do_valentine( object me, string arg )
{
	int flag,p,i,x,y,z,id;
	object who,item,map,item214_1,item214_2,item214_3;
        string cmd,cWord,tmp="";	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        	case 1:
        		if( who->get_quest("valentine.flag") == 5)
        		{
	        		cWord = sprintf(me->get_name() + "：\n    可爱的小姑娘，来找婆婆是不是询问有关情人节的事情啊？\n    唉，想当年我也是万人迷的天使级少女啊，情人节快到了，我也想打扮一下呢，小姑娘有什么好的化妆品推荐给我吗？\n");
				send_user( who, "%c%s", ':', cWord +"\n"+
				ESC +sprintf("完成任务。\ntalk %x# valentine.2\n",getoid(me)) +
				ESC "离开。\nCLOSE\n" ); 
        		}
			break;
        	case 2:
			if( who->get_quest("valentine.flag") == 5)
			{
	        		if( who->get_quest("valentine.flag") == 5)
	        		{
		     	     	     	who->add_exp(500);
		     	     	     	who->set_quest( "valentine.flag", 6 );
		     	     	     	who->set_quest( "valentine.type", 0 );
		             	     	send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_VALENTINE,5,0,"" );
			     	     	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,5,"" ); 
			     	     	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"" ); 
	        		}
			}
			break;
        	case 3:
			if( who->get_quest("valentine.flag") == 6 && who->get_quest("valentine.type")!= 1)
			{
				z = ({10,20,30,40,50,60,70})[random(7)];
				if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) ) return ;
			        x = ( p % 1000000 ) / 1000;  y = p % 1000;
				if( !objectp( map = get_map_object(z) ) || !map->is_scene() ) return;
				who->set_quest("valentine.name","情人节流氓");
				who->set("valentine.x",x);
				who->set("valentine.y",y);
				who->set("valentine.z",z);        		
	        		cWord = sprintf(me->get_name() + "：\n    唉，想当年我也是万人迷的天使级少女啊，情人节快到了，我也想打扮一下呢，小姑娘有什么好的化妆品推荐给我吗？\n    如果没有的话，不如去一趟%s国的（%d，%d）吧，去城外找找那些流氓，他们身上或许就带着用来讨好女孩子的胭脂、梳子和头钗呢！\n",map->get_name(),x,y);
				send_user( who, "%c%s", ':', cWord +"\n"+
				ESC +sprintf("接受任务。\ntalk %x# valentine2\n",getoid(me)) +
				ESC "离开。\nCLOSE\n" ); 
			}
			break;
        	case 4:
			if( who->get_quest("valentine.flag") == 6 && who->get_quest("valentine.bonus") == 1 && objectp( item = present("忘情婆婆要的胭脂", who, 1, MAX_CARRY)) && objectp( item = present("忘情婆婆要的梳子", who, 1, MAX_CARRY)) && objectp( item = present("忘情婆婆要的头钗", who, 1, MAX_CARRY)))
			{
	        		cWord = sprintf(me->get_name() + "：\n    对对对，就是这些东西，我得好好打扮一下，你过会儿再来找我，我会告诉你怎样才能得到巧克力的。\n");
				send_user( who, "%c%s", ':', cWord +"\n"+
				ESC +sprintf("完成任务。\ntalk %x# valentine.5\n",getoid(me)) +
				ESC "离开。\nCLOSE\n" ); 
			}
			break;
        	case 5:
			if( who->get_quest("valentine.flag") == 6 && who->get_quest("valentine.bonus") == 1 && objectp( item = present("忘情婆婆要的胭脂", who, 1, MAX_CARRY)) && objectp( item = present("忘情婆婆要的梳子", who, 1, MAX_CARRY)) && objectp( item = present("忘情婆婆要的头钗", who, 1, MAX_CARRY)))
			{
				if( !objectp( item214_1 = present("忘情婆婆要的胭脂", who, 1, MAX_CARRY) ) )
				{
					send_user( who, "%c%s", '!', "您身上没有忘情婆婆要的胭脂");
					return;
				}          
				if( !objectp( item214_1 = present("忘情婆婆要的梳子", who, 1, MAX_CARRY) ) )
				{
					send_user( who, "%c%s", '!', "您身上没有忘情婆婆要的梳子");
					return;
				} 
				if( !objectp( item214_1 = present("忘情婆婆要的头钗", who, 1, MAX_CARRY) ) )
				{
					send_user( who, "%c%s", '!', "您身上没有忘情婆婆要的头钗");
					return;
				} 
				if( objectp( item214_1 = present("忘情婆婆要的胭脂", who, 1, MAX_CARRY) ) )
				{
					item214_1->remove_from_user();
					destruct(item214_1); 
				}          
				if( objectp( item214_1 = present("忘情婆婆要的梳子", who, 1, MAX_CARRY) ) )
				{
					item214_1->remove_from_user();
					destruct(item214_1); 
				} 
				if( objectp( item214_1 = present("忘情婆婆要的头钗", who, 1, MAX_CARRY) ) )
				{
					item214_1->remove_from_user();
					destruct(item214_1); 
				} 
	     	     	     	who->add_exp(500);
	     	     	     	who->add_potential(10);
	     	     	     	who->set_quest( "valentine.flag", 7 );
	             	     	send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_VALENTINE,6,0,"" );
		     	     	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,6,"" ); 
		     	     	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"" ); 
			}
			break;
        	case 6:
			if( who->get_quest("valentine.flag") == 7 && !objectp( item = present("巧克力豆", who, 1, MAX_CARRY)))
			{
	        		cWord = sprintf(me->get_name() + "：\n    谢谢你了，小姑娘！至于情人节嘛，最重要的一点就是男生送女生玫瑰花，女生送男生巧克力！喔？你问巧克力去那里买？这个我可不知道，不过我这里有点巧克力豆，我想红娘应该知道怎样把巧克力豆做成巧克力的。\n");
				send_user( who, "%c%s", ':', cWord +"\n"+
				ESC +sprintf("接受任务。\ntalk %x# valentine.7\n",getoid(me)) +
				ESC "离开。\nCLOSE\n" ); 
			}
			break;
        	case 7:
			if( who->get_quest("valentine.flag") == 7 && !objectp( item = present("巧克力豆", who, 1, MAX_CARRY)))
			{
	        		item214_1 = new ("item/04/0425");    //巧克力豆
	                        if (item214_1)
	                        {
	                                if( USER_INVENTORY_D->can_carry(who, item214_1)  >=1 )
	                                {
	                                        p =item214_1->move(who, -1);
	                                        item214_1->add_to_user(p);
			                        send_user( who, "%c%s", '!', "得到"HIR"巧克力豆"NOR"一些");
						send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
						send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,7,"巧克力豆" ); 		                        
						send_user( who, "%c%s", '!', "你领取了情人节任务————巧克力豆！");
	                                }       
	                                else
	                                {
	                                	destruct(item214_1); 
	                                	send_user( who, "%c%s", '!', "您身上没有空位！");
	                                }
	                        }
			}
			break;
       	}
}

void valentine2(  ) { "/sys/party/valentine"->do_valentine5_call( this_player(), this_object() ); }

