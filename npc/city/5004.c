
// 自动生成：/make/npc/make8004

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

void do_build( string arg );
void do_upgrade( string arg );
void do_plant( string arg );
void do_food( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tần Quốc Nội Chính Quan");
	set_real_name("Cam La");
        set_city_name("Tần Quốc");

        set_2( "talk", ([
                "build"         : (: do_build :),
                "upgrade"       : (: do_upgrade :),
                "plant"         : (: do_plant :),
                "food"          : (: do_food:),
                "welcome"	: (: do_welcome :),	
        ]) );
//	set("level",41);
//	set("legend",({32*10+20,32*10+23}));
	set("mpLegend",([40:({32*10+20,})]));
	set("mpLegend2",([0:({32*21+2,32*21+4,32*21+14,32*21+27,32*21+30,32*22+17,}),40:({32*10+22,32*10+25,}),]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 40 && !who->get_legend(TASK_10,20) ) || ( who->get_legend(TASK_10,20) && !who->get_legend(TASK_10,22) ) )
	{
		tmp += sprintf(ESC HIY "逃跑的壮丁\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_legend(TASK_10,22) && !who->get_legend(TASK_10,23) ) || ( who->get_legend(TASK_10,23) && !who->get_legend(TASK_10,25) ) )
	{
		tmp += sprintf(ESC HIY "叛乱的苦役\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,1) && !who->get_legend(TASK_21,2) )
	{
		tmp += sprintf(ESC HIY "破土动工\ntalk %x# welcome.9\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,3) && !who->get_legend(TASK_21,4) )
	{
		tmp += sprintf(ESC HIY "打听消息\ntalk %x# welcome.7\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,13) && !who->get_legend(TASK_21,14) )
	{
		tmp += sprintf(ESC HIY "寻求支持\ntalk %x# welcome.7\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,26) && !who->get_legend(TASK_21,27) )
	{
		tmp += sprintf(ESC HIY "秦将辟谣\ntalk %x# welcome.12\n",getoid(me));
	}
	if ( (who->get_legend(TASK_21,27) && !who->get_legend(TASK_21,28)) || (who->get_legend(TASK_21,28) && !who->get_legend(TASK_21,30)) )
	{
		tmp += sprintf(ESC HIY "诽谤真凶\ntalk %x# welcome.12\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,30) && !who->get_legend(TASK_22,1) )
	{
		tmp += sprintf(ESC HIY "陈述冤情\ntalk %x# welcome.12\n",getoid(me));
	}
	if ( who->get_legend(TASK_22,16) && !who->get_legend(TASK_22,17) )
		tmp += sprintf(ESC HIY "劝谏秦王\ntalk %x# welcome.17\n",getoid(this_object()));
	if ( who->get_legend(TASK_22,17) && !who->get_legend(TASK_22,18) )
		tmp += sprintf(ESC HIY "上书之难\ntalk %x# welcome.17\n",getoid(this_object()));
	if ("/sys/sys/count"->get_refine()&&who->get_city_name()==me->get_city_name())
		tmp += sprintf(ESC"收妖壶任务\ntalk %x# welcome.1000\n",getoid(me)); 
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		INTERIOR_D->do_look( who, me ); 
	
}
void do_build( string arg ) { INTERIOR_D->do_build( this_player(), this_object(), arg ); }
void do_upgrade( string arg ) { INTERIOR_D->do_upgrade( this_player(), this_object(), arg ); }
void do_plant( string arg ) { INTERIOR_D->do_plant( this_player(), this_object(), arg ); }
void do_food( string arg ) { INTERIOR_D->do_food( this_player(), this_object(), arg ); }

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object( who, this_object(), obj ); }
void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p;
        object who,item,obj;  
        string cmd1;
       	string *nTmp,tmp;     
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        if (flag>=1000)
        {
        	"/sys/user/refine"->do_welcome(who, me, arg);
        	return;
        }        
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 40 && !who->get_legend(TASK_10,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    修筑长城时，曾有一群壮丁和苦役密谋造反，他们策划了很久，终于从工地上逃了出来，并且在逃出来之前，埋好了炸药，当天晚上，在工地上施工的农民们死伤惨重，这群害人的刁民，一定要治治他们！\n    你去将他们干掉吧！就在郑国渠，30个壮丁，记得了！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_10,20) && !who->get_legend(TASK_10,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不捉拿这群叛徒，以后会造成更大的影响！\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_10,21) && !who->get_legend(TASK_10,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    除了这被你干掉的30个壮丁，还有一批苦役，你要愿意去的话，你再来找我。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 2:
        	if ( who->get_level() >= 40 && !who->get_legend(TASK_10,20) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,20);
        		who->delete_save_2("tpzuangding");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,1,"逃跑的壮丁" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"逃跑的壮丁");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_10,21) && !who->get_legend(TASK_10,22) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_10,22);
        		who->delete_save_2("tpzuangding");
			who->add_exp(4700);
			who->add_potential(150);
			who->add_cash(3800);
			send_user(who,"%c%s",';',"逃跑的壮丁 经验 4700 潜能 150 金钱 3800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,1,"" );
			me->do_welcome(4);
        	}
        	break;
        case 4:
        	if ( who->get_legend(TASK_10,22) && !who->get_legend(TASK_10,23) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    修筑长城时，曾有一群壮丁和苦役密谋造反，他们策划了很久，终于从工地上逃了出来，并且在逃出来之前，埋好了炸药，当天晚上，在工地上施工的农民们死伤惨重，这群害人的刁民，一定要治治他们！\n    你去将他们干掉吧！就在郑国渠，30个苦役，记得了！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_10,23) && !who->get_legend(TASK_10,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不捉拿这群叛徒，以后会造成更大的影响！\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_10,24) && !who->get_legend(TASK_10,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    干掉了这批壮丁和苦役，以后可安稳得多了，有需要我再叫你吧！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 5:
        	if ( who->get_legend(TASK_10,22) && !who->get_legend(TASK_10,23) ) 
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,23);
        		who->delete_save_2("plkuyi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,2,"叛乱的苦役" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"叛乱的苦役");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_10,24) && !who->get_legend(TASK_10,25) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),40,ARMOR_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_10,25);
        		who->delete_save_2("plkuyi");
			who->add_exp(5000);
			who->add_potential(160);
			who->add_cash(3500);
			send_user(who,"%c%s",';',sprintf("叛乱的苦役 经验 5000 潜能 160 金钱 3500 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,2,"" );
        	}
        	break;
        case 7:
        	if ( who->get_legend(TASK_21,3) && !who->get_legend(TASK_21,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王最近确有此意，至于具体怎么去实施，本官还不太清楚，不过你可以先告诉那工匠，让他可以先做好准备。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_21,13) && !who->get_legend(TASK_21,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本官定当按照程序一丝不苟的办理，大王关注之事，本官自然尽心竭力。\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 8:
        	if ( who->get_legend(TASK_21,3) && !who->get_legend(TASK_21,4) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,4);
			who->add_exp(13000);
			who->add_potential(350);
			who->add_cash(12000);
			send_user(who,"%c%s",';',"打听消息 经验 13000 潜能 350 金钱 12000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,28,"" );
        	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_21,1) && !who->get_legend(TASK_21,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本官现在下令，冀阙宫开始修缮。\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
        case 10:
        	if ( who->get_legend(TASK_21,1) && !who->get_legend(TASK_21,2) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64104",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,2);
			who->add_exp(15000);
			who->add_potential(360);
			who->add_cash(13000);
			send_user(who,"%c%s",';',"破土动工 经验 15000 潜能 360 金钱 13000 翠玉袍图纸 1",);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,27,"" );
        	}
        	break; 
        case 11:
        	if ( who->get_legend(TASK_21,13) && !who->get_legend(TASK_21,14) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/62051",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,14);
			who->add_exp(16000);
			who->add_potential(380);
			who->add_cash(15500);
			send_user(who,"%c%s",';',"寻求支持 经验 16000 潜能 380 金钱 15500 血饮狂刀图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,32,"" );
        	}
        	break; 
        case 12:
        	if ( who->get_legend(TASK_21,26) && !who->get_legend(TASK_21,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此事我已知道，请容我思量一下，好好想想应对之策。\n"ESC"完成任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_21,27) && !who->get_legend(TASK_21,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近确实有不少小人在大王面前恶言中伤大将军，经过我仔细打听，发现在台前跳的最欢就是奸贼叶九，他职位不高，平时也有不少仇家，现今他独自一个人在秦长城烽火台一带似乎又有什么事情要密谋，你装作刺客将他刺杀了，到时候引后面的大鱼落网。杀掉之后躲我这里来，我为你打点好之后再筹划下一步。\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_21,28) && !who->get_legend(TASK_21,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此奸贼不除，恐怕难还大将军清白。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_21,29) && !who->get_legend(TASK_21,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我们只需以静制动，静候大鱼露出马脚来就好了。\n"ESC"完成任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_21,30) && !who->get_legend(TASK_22,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    要想彻底为大将军洗清冤屈，还须将此事向御史说清楚，由他奏明大王，方是上策。\n"ESC"接受任务\ntalk %x# welcome.16\n"ESC"离开", me->get_name(),getoid(me)));
		
        	break;
        case 13:
        	if ( who->get_legend(TASK_21,26) && !who->get_legend(TASK_21,27) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"将军函",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,27);
			who->add_exp(19000);
			who->add_potential(390);
			who->add_cash(20000);
			send_user(who,"%c%s",';',"寻求支持 经验 19000 潜能 390 金钱 20000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,38,"" );
			me->do_welcome(12);
        	}
        	break; 
	case 14:
        	if ( who->get_legend(TASK_21,27) && !who->get_legend(TASK_21,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_21,28);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,39,"诽谤真凶" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"诽谤真凶");
        	}
        	break;     
        case 15:
        	if ( who->get_legend(TASK_21,29) && !who->get_legend(TASK_21,30) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,30);
			who->add_exp(20000);
			who->add_potential(400);
			who->add_cash(21000);
			send_user(who,"%c%s",';',"诽谤真凶 经验 20000 潜能 400 金钱 21000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,39,"" );
			me->do_welcome(12);
        	}
        	break; 
	case 16:
        	if ( who->get_legend(TASK_21,30) && !who->get_legend(TASK_22,1) )
        	{
 			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
 			item = new("/item/98/0101");
 			p = item->move(who,-1);
 			if ( !p )
 			{
 				destruct(item);
 				send_user(who,"%c%s", '!', "你携带的物品太多了");	
 				return ;
 			}
 			item->add_to_user(p);
        		who->set_legend(TASK_22,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,40,"陈述冤情" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"陈述冤情");
        	}
        	break;
	case 17:
		if ( who->get_legend(TASK_22,16) && !who->get_legend(TASK_22,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王此次的确会失去军心民心，本官一定找准机会面谏大王。\n"ESC"完成任务\ntalk %x# welcome.18\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_22,17) && !who->get_legend(TASK_22,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本官最近家人常常受到匪徒的恐吓，要本官不再理会这次杀戮兵丁之事，虽然想不通幕后主使是何来路，但是那恐吓之人本官却是打听清楚了，就是在秦长城匝道一带打劫过往行人的匪徒武三，你去帮我质问质问他究竟是何人主谋？\n"ESC"接受任务\ntalk %x# welcome.19\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 18:
        	if ( who->get_legend(TASK_22,16) && !who->get_legend(TASK_22,17) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"劝谏书",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/66036",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,17);
			who->add_exp(25000);
			who->add_potential(420);
			who->add_cash(24000);
			send_user(who,"%c%s",';',"劝谏秦王 经验 25000 潜能 420 金钱 24000 玄铁锄头图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,46,"" );
        	}
        	break; 
	case 19:
        	if ( who->get_legend(TASK_22,17) && !who->get_legend(TASK_22,18) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_22,18);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,47,"上书之难" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"上书之难");
        	}
        	break;        	

        case 99:	
		INTERIOR_D->do_look( who, me); 
        	break;
        }

}
