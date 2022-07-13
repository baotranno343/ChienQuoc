
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
string get_fam_name() { return "Mao Sơn"; }

// 函数：获取人物造型
int get_char_picid() { return 9515; }

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
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name( "Mao Chân Nhân" );
        set_skill(0271, 150);
        set_skill(0461, 150);
//        set_skill(0411, 150);
        set_skill(0413, 150);
        set_skill(0462, 150);
        set_skill(0414, 150);
        set_skill(0463, 150);
        set_skill(0417, 150);
        set_skill(0464, 150);
        set_skill(0418, 150);
        set_skill(0465, 150);
        set_2( "talk", ([
                "skills"                : (: do_skill :),
                "quest"                 : (: do_quest :),
                "giveup"                : (: do_giveup :),
                "giveup2"               : (: do_giveup2 :),
                "apprentice"            : (: do_apprentice :), 
                "accept_quest"            : (: accept_quest :),  
                "task_info"             : (: task_info :),                     
                "welcome"		: (: do_welcome :),
        ]));
        set_2( "good", ([
                "01" : "/item/77/1010",
                "02" : "/item/77/1020",                
                "03" : "/item/60/0010",
                "04" : "/item/60/5020",
                "05" : "/item/61/0010",
                "06" : "/item/61/5020",
                "07" : "/item/65/0010",
                "08" : "/item/65/5020",
                "09" : "/item/66/0010",
                "10" : "/item/66/5020",                
                "11" : "/item/88/0010",
                "12" : "/item/88/5020",
                "13" : "/item/87/5010",
                "14" : "/item/87/5020",              
        ]) ); 
	set("mpLegend2",([0:({32*23+5,32*23+7,32*23+10,32*23+13,32*23+16,32*23+19,}),]));
        setup();
}

// 函数：点击出现界面
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_23,4) && !who->get_legend(TASK_23,5) )
	{
		tmp += sprintf(ESC HIY "游魂\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_23,5) && !who->get_legend(TASK_23,6)) || (who->get_legend(TASK_23,6) && !who->get_legend(TASK_23,7)) )
	{
		tmp += sprintf(ESC HIY "准备作法\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_23,7) && !who->get_legend(TASK_23,8)) || (who->get_legend(TASK_23,8) && !who->get_legend(TASK_23,10)) )
	{
		tmp += sprintf(ESC HIY "调查物证\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_23,10) && !who->get_legend(TASK_23,11)) || (who->get_legend(TASK_23,11) && !who->get_legend(TASK_23,13)) )
	{
		tmp += sprintf(ESC HIY "狗血\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_23,13) && !who->get_legend(TASK_23,14)) || (who->get_legend(TASK_23,14) && !who->get_legend(TASK_23,16)) )
	{
		tmp += sprintf(ESC HIY "茅山叛徒\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_23,16) && !who->get_legend(TASK_23,17)) || (who->get_legend(TASK_23,17) && !who->get_legend(TASK_23,19)) )
	{
		tmp += sprintf(ESC HIY "恶灵\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_23,19) && !who->get_legend(TASK_23,20)) || (who->get_legend(TASK_23,20) && !who->get_legend(TASK_23,21)) )
	{
		tmp += sprintf(ESC HIY "解救游魂\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get("master.type") != 69 && sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		TASK_MASTER_D->do_look( who, me ); 
	
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

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,i,size,p,amount;
        object who,item,pet, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_23,4) && !who->get_legend(TASK_23,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    世间一切皆是因果报应，韩王安有今天孽必有他之前作的恶，正是天理循环，报应不爽啊！但这件事情我们茅山也逃脱不了责任，这次也算是韩王安的造化，我姑且就尽力而为吧。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,5) && !who->get_legend(TASK_23,6))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    韩王安所中的邪术叫做游魂之术，一种已经被我茅山禁止使用多年的法术，当韩王安在梦里游魂的次数达到二十一次的时候，韩王安的灵魂也就会全部被吸光。到现在为止韩王安游魂的次数已经有十七次，如果再不抓紧时间的话韩王安很快就会一命呜呼。现在，我要你去给我找一把桃木剑和10张符纸回来，其他的你不必过问，你只要尽快去把这些东西找齐就可以了，我们所剩的时间已经不多了。\n    路途凶险，还望你能结伴而行。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,6) && !who->get_legend(TASK_23,7))
		{
			if ( TASK_LEGEND_D->check_task_item_amount(who,"桃木剑") == 0 || TASK_LEGEND_D->check_task_item_amount(who,"符纸") < 10 )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    桃木剑和符纸都是很普遍的东西，你要赶快去给我找回来，不然韩王安的生命就危险了。\n"ESC"离开", me->get_name()));
        		else 
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好，我作法所需的道具已经有了，但仅有这些是不够的，我还需要另外一件法器。韩王安现在游魂的次数已经达到18次，你已经没有时间歇息了，你得赶快去帮我把这件法器找回来。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        			
        	}
		else if (who->get_legend(TASK_23,7) && !who->get_legend(TASK_23,8))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    仅有这把桃木剑跟这些符纸的远远不够的，要破解游魂之术我需要一件法器，这法器是一面镜子，现在这面镜子已经遗落在某一个地方，你去弯道2找找，这面镜子应该就在那附近。你找到镜子之后一定要马上把镜子送到我这里来。现在韩王安游魂的次数已经达到18次，你已经没有时间歇息了，你得赶快去帮我把这面镜子找回来。\n    路途凶险，你最好是结伴而行。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,8) && !who->get_legend(TASK_23,9))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    快，尽快去把镜子找回来，它就在弯道2那边，我们的时间不多了。\n"ESC"离开", me->get_name()));
		else if (who->get_legend(TASK_23,9) && !who->get_legend(TASK_23,10))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    很好，这么快就把这面镜子给我找回来了。想要救韩王安需要有一件保存他被吸走的灵魂的器皿，用这面镜子就可以把韩王安被吸取的灵魂吸收到镜子里面保存起来，但是想要找回韩王安被吸走的灵魂，我们先要找出是施法者的所在…….\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,10) && !who->get_legend(TASK_23,11))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    要破解游魂之术，先要找出它的施法者所在地。我要作法祭天地找出施法者的所在地。所以，我需要一只狗作为祭品，而且不可以使用通常作法用的黑狗，我必须要用一只野生的斑点狗来做祭品，你去华山一带捉一只斑点狗来给我。韩王安的性命如何就要看的办事的效率了，赶快去吧。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,11) && !who->get_legend(TASK_23,13) && !objectp(pet=USER_BEAST_D->have_beast(who,"斑点狗")))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    捉斑点狗的时候你可能要用到乾坤绳，乾坤绳在杂货商哪里就有得卖，你如果没有的话就赶快去买一些吧。\n"ESC"离开", me->get_name()));
		else if (who->get_legend(TASK_23,11) && !who->get_legend(TASK_23,13) && objectp(pet=USER_BEAST_D->have_beast(who,"斑点狗")))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了这个斑点狗做祭品我很快就可以找出施法者的所在地了。施法所需要的其他东西我已经准备好了，马上我就要开坛作法祭天地。你就先歇息片刻，等祭治完之后还有最重要的任务要交给你。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,13) && !who->get_legend(TASK_23,14))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    其实对韩王安施游魂之术的是我以前的一个徒弟：马宁。本来马宁是一个性情温顺的人，而且资质优秀，但是因为在三十多年前各国合纵攻齐，他的齐国的双亲都死于韩国兵士之手，所以他对韩王安恨之入骨。后来他为了报仇背叛了我们茅山，入了魔道。这次的邪术，正是他对韩王安的报复。破解游魂之术的唯一方法就是把施法者杀掉，马宁现在已经入了魔道，为了拯救韩国，我们只能把他杀死了，他现在就在太行山附近的神秘山洞一层施法，你去把他杀掉吧。现在韩王安游魂的次数已经达到20次，生命已经危在旦夕了。\n    路途凶险，你最好是结伴而行。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,14) && !who->get_legend(TASK_23,15))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在让已经入魔的马宁重归正道已经不可能，唯一的方法就是把他杀掉，让他再也不可以对韩王安施游魂之术了，你快去吧！在韩王安第二十一次游魂之前把马宁杀掉！\n"ESC"离开", me->get_name()));
		else if (who->get_legend(TASK_23,15) && !who->get_legend(TASK_23,16))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    马宁他曾经是我最喜爱的一个徒弟。入魔后他内心一定相当痛苦，也许把他杀掉，是他最好的解脱，很感谢你替我杀掉马宁。但是，你还有最后一件事情是必须去做的……\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,16) && !who->get_legend(TASK_23,17))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    虽然你成功杀掉了马宁，解除了游魂之术，但是韩王安已经被吸走的20个灵魂还没有收回来，韩王安被吸走的20个灵魂是被马宁封在灵谷洞最下层的恶灵身上，也就是韩王安之前梦见的那个洞穴和那些恶灵。你去马踏湖附近的灵谷洞最下层找出这些恶灵把它们杀掉，我会在这里用之前你找回来的镜子把韩王安的灵魂吸到镜子里面保存。去吧，找出那些恶灵并把它们杀掉，韩王安被吸走的灵魂是20个，你必须杀掉20个恶灵。\n    灵谷洞是个危险地方，你最好结伴而行。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,17) && !who->get_legend(TASK_23,18))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    要韩王安真正得教，你还要把那20个恶灵杀掉，让我把那20个灵魂吸回来到镜子里面才可以。\n"ESC"离开", me->get_name()));
		else if (who->get_legend(TASK_23,18) && !who->get_legend(TASK_23,19))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你终于杀掉那20个恶灵了，现在，这面镜子里面已经存放了20次游魂中韩王安被吸走的灵魂了，你先休息一下，等我先把这面镜子封好，你就可以把这面镜子带回郑城救韩王安了。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,19) && !who->get_legend(TASK_23,20))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这一面就是已经保存了所有韩王安被吸走的灵魂的镜子，现在我把它交给你，你把它交给韩王安然后把镜子上面的红布打开，韩王安被吸走的灵魂就会回到韩王安的身体里面。不必谢我，其实这次的事情里面功劳最大的是你，把镜子拿给韩王安去吧，然后告诉韩王安一定要好好当一个国君，不要再让像马宁这样的悲剧重演了。\n"ESC"接受任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,20) && !who->get_legend(TASK_23,21))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你帮了我那么多忙，现在终于拿到了解禁的铜镜了，为什么还不赶快送去呢？\n"ESC"离开", me->get_name()));

        	break;
        case 2:
        	if ( who->get_legend(TASK_23,4) && !who->get_legend(TASK_23,5) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_23,5);
			who->add_exp(12000);
			who->add_potential(215);
			who->add_cash(11000);
			send_user(who,"%c%s",';',"游魂（1） 经验 12000 潜能 215 金钱 11000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,45,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3:
        	if (who->get_legend(TASK_23,5) && !who->get_legend(TASK_23,6))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_23,6);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_MAOSHAN,"Mao Sơn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,1,"游魂（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"游魂（2）");
        	}
        	break;
        case 4:
		if (who->get_legend(TASK_23,6) && !who->get_legend(TASK_23,7))
		{
			if ( TASK_LEGEND_D->check_task_item_amount(who,"桃木剑") == 0 || TASK_LEGEND_D->check_task_item_amount(who,"符纸") < 10 )
				return ;
			if ( TASK_LEGEND_D->check_task_item1(who,"桃木剑",1) != 1 )
				return ;
			if ( TASK_LEGEND_D->check_task_item1(who,"符纸",10) != 1 )
				return ;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_23,7);
			who->add_exp(12000);
			who->add_potential(215);
			who->add_cash(11000);
			send_user(who,"%c%s",';',"游魂（2） 经验 12000 潜能 215 金钱 11000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,1,"" );
			me->do_welcome(1);				
		}
		break;
        case 5:
        	if (who->get_legend(TASK_23,7) && !who->get_legend(TASK_23,8))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_23,8);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_MAOSHAN,"Mao Sơn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,2,"游魂（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"游魂（3）");
        	}
        	break;
        case 6:
		if (who->get_legend(TASK_23,9) && !who->get_legend(TASK_23,10))
		{
			if ( TASK_LEGEND_D->check_task_item(who,"镜子",1) != 1 )
				return ;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_23,10);
			who->add_exp(16000);
			who->add_potential(260);
			who->add_cash(17000);
			send_user(who,"%c%s",';',"游魂（3） 经验 16000 潜能 260 金钱 17000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,2,"" );
			me->do_welcome(1);				
		}
		break;		
        case 7:
        	if (who->get_legend(TASK_23,10) && !who->get_legend(TASK_23,11))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_23,11);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_MAOSHAN,"Mao Sơn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,3,"游魂（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"游魂（4）");
        	}
        	break;
        case 8:
		if (who->get_legend(TASK_23,11) && !who->get_legend(TASK_23,13) && objectp(pet=USER_BEAST_D->have_beast(who,"斑点狗")))
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_23,13);
			USER_BEAST_D->destruct_pet(who,pet);
			who->add_exp(17000);
			who->add_potential(280);
			who->add_cash(19000);
			send_user(who,"%c%s",';',"游魂（4） 经验 17000 潜能 280 金钱 19000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,3,"" );
			me->do_welcome(1);				
		}
		break;		
        case 9:
        	if (who->get_legend(TASK_23,13) && !who->get_legend(TASK_23,14))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_23,14);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_MAOSHAN,"Mao Sơn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,4,"游魂（5）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"游魂（5）");
        	}
        	break;
        case 10:
		if (who->get_legend(TASK_23,15) && !who->get_legend(TASK_23,16))
		{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64126",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_23,16);
			who->add_exp(17000);
			who->add_potential(280);
			who->add_cash(19000);
			send_user(who,"%c%s",';',"游魂（5） 经验 17000 潜能 280 金钱 19000 混天战盔图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,4,"" );
			me->do_welcome(1);				
		}
		break;		
        case 11:
        	if (who->get_legend(TASK_23,16) && !who->get_legend(TASK_23,17))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_23,17);
        		who->delete_save_2("mzreling");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_MAOSHAN,"Mao Sơn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,5,"游魂（6）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"游魂（6）");
        	}
        	break;
        case 12:
		if (who->get_legend(TASK_23,18) && !who->get_legend(TASK_23,19))
		{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64127",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_23,19);
        		who->delete_save_2("mzreling");
			who->add_exp(17000);
			who->add_potential(280);
			who->add_cash(19000);
			send_user(who,"%c%s",';',"游魂（6） 经验 17000 潜能 280 金钱 19000 神风盔图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,5,"" );
			me->do_welcome(1);				
		}
		break;	
        case 13:
        	if (who->get_legend(TASK_23,19) && !who->get_legend(TASK_23,20))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0108");
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!',"你携带的物品太多了");
        			return ;	
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_23,20);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_MAOSHAN,"Mao Sơn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,6,"游魂（7）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"游魂（7）");
        	}
        	break;
	case 99:
 		TASK_MASTER_D->do_look( who, me );
 		break;
        }
}