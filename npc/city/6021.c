
// 自动生成：/make/npc/make8020
#include <ansi.h>
#include <npc.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0450; }
void do_welcome(string arg);

// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 2; }

int is_self_look() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Sở Quốc Công Tượng");
        set_real_name("Điêu Khắc 31~46");
        set_city_name("Sở Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",95);
//	set("legend",({32*33+22}));
 	set("mpLegend",([95:({32*33+22}),]));
 	set("mpLegend2",([95:({32*33+24,}),]));
	set_skill(0650, 39);
        set_2( "good", ([
                "01" : "/item/product/65022",
                "02" : "/item/product/65023",
                "03" : "/item/product/65024",
                "04" : "/item/product/65025",
                "05" : "/item/product/65026",
                "06" : "/item/product/65027",
                "07" : "/item/product/65028",
                "08" : "/item/product/65029",
                "09" : "/item/product/65030",
                "10" : "/item/product/65031",
                "11" : "/item/product/65032",        
                "12" : "/item/product/65033",
                "13" : "/item/product/65034",
                "14" : "/item/product/65035",
                "15" : "/item/product/65036",      
                "16" : "/item/product/65037",
                "17" : "/item/product/65038",
                "18" : "/item/product/65039",
                "19" : "/item/product/65040",
                "20" : "/item/product/65041",
                "21" : "/item/product/65042",                                                  
        ]) );	
        setup();
}

void do_look( object who )
{
	string tmp="";
        object me = this_object();
	if ( ( who->get_level() >= 95 && !who->get_legend(TASK_33,22) ) || ( who->get_legend(TASK_33,22) && !who->get_legend(TASK_33,24) ) )
	{
		tmp = sprintf(ESC HIY "关于食物的战争\ntalk %x# welcome.1\n",getoid(me));
	}

	tmp += sprintf(ESC"Học kĩ năng\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"Mua công thức Điêu Khắc cấp 31 - 46\nlist %s\n", me->get_char_id());
	send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 2 ); }


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
		if ( who->get_level() >= 95 && !who->get_legend(TASK_33,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，精灵与人之战持续已久，这场战争源起于食物，水精与火精繁衍越来越多，他们周围的食物已经不能满足他们的需求，于是仗着他们会变幻五行的法术，抢走了我们赖以生存的食物，虽然现在食物可能已经被他们吃光了，但是我们都咽不下这口气，所以你去替我消灭掉他们，然后回我这里来。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_33,22) && !who->get_legend(TASK_33,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    出不了这口恶气，我们是绝对不是善罢甘休的！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_33,23) && !who->get_legend(TASK_33,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    终于出了这口恶气，平日里我们都很和善地对待每一个人，没想到它们居然还来欺负我们。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 2:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_33,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_33,22);
        		who->delete_save("cggjsuij");
        		who->delete_save("cggjhuoj");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,40,"源起于食物" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"源起于食物");        		
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_33,23) && !who->get_legend(TASK_33,24) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_33,24);
        		who->delete_save("cggjsuij");
        		who->delete_save("cggjhuoj");
			who->add_exp(72000);
			who->add_potential(935);
			who->add_cash(60000);
			send_user(who,"%c%s",';',"源起于食物 经验 72000 潜能 935 金钱 60000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,40,"" );
        	}
        	break;

        }
}