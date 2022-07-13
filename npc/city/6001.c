
// 自动生成：/make/npc/make8001

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define EMPEROR_D       "/inh/city/emperor"
#define EMPEROR_2_D     "/inh/city/emperor2"

inherit OFFICER;

void do_policy( string arg );
void do_relation( string arg );
void do_master( string arg );
void do_advice( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5101; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Sở Vương");
	set_real_name("Sở Khảo Liệt");
        set_city_name("Sở Quốc");

        set_2( "talk", ([
                "policy"        : (: do_policy :),
                "relation"      : (: do_relation :),
                "master"        : (: do_master :),
                "advice"        : (: do_advice :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",110);
//	set("legend",({32*39+7}));
	set("mpLegend",([105:({32*39+7,}),110:({32*45+15}),]));
	set("mpLegend2",([0:({32*45+14,}),110:({32*45+17,}),]));
        setup();
}

string get_master() { return CITY_CHU->get_master(); }
string get_master_2() { return CITY_CHU->get_master_2(); }
string get_master_3() { return CITY_CHU->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_level() >= 105 && !who->get_legend(TASK_39,7) )
		tmp += sprintf(ESC HIY "交好\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_45,13) && !who->get_legend(TASK_45,14) )
		tmp += sprintf(ESC HIY "云雾茶叶\ntalk %x# welcome.7\n",getoid(me));
	if ( (who->get_level() >= 110 && !who->get_legend(TASK_45,15)) || (who->get_legend(TASK_45,15) && !who->get_legend(TASK_45,17)) )
		tmp += sprintf(ESC HIY "万众敬仰\ntalk %x# welcome.9\n",getoid(me));

	if ( me->get_city_name() == who->get_city_name() )
	{
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			tmp += sprintf(ESC HIY "制作王之号角\ntalk %x# welcome.3\n",getoid(me));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			tmp += sprintf(ESC HIY "王之号角的雕琢\ntalk %x# welcome.3\n",getoid(me));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16)&& gone_time(who->get_save("wangzhhj"))>=86400 )
			tmp += sprintf(ESC HIY "索取王之号角\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( who->get("master.type") != 69 && sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		EMPEROR_D->do_look( who, this_object() ); 
	
}
void do_policy( string arg ) { EMPEROR_D->do_policy( this_player(), this_object(), arg ); }
void do_relation( string arg ) { EMPEROR_2_D->do_relation( this_player(), this_object(), arg ); }    // ## 2 ##
void do_master( string arg ) { EMPEROR_D->do_master( this_player(), this_object(), arg ); }

void do_advice( string arg ) { EMPEROR_D->do_advice( this_player(), this_object(), arg ); }

// 接收心爱物品
int accept_object( object player, object obj ) 
{
	object who = this_object();
	return TASK_MASTER_D->accept_object( who, player, obj ); 
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,i,size,p,amount;
        object who,item, *inv;
        string tmp;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		if ( who->get_level() >= 105 && !who->get_legend(TASK_39,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    秦国逐渐强大，我想如果不及时做出应对措施，我们其余的六个国家会很快被他吞噬！而我思来想去，和赵结盟无疑是一个有效的方法，如果秦攻打赵，那么我楚国也将帮助赵防御，反之亦然。\n    此举真是一举多得，你去赵将我的意思转达给赵王吧。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 2:
        	if ( who->get_level() >= 105 && !who->get_legend(TASK_39,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,46,"交好" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"交好");
        	}
        	break; 
	case 3:
		if ( me->get_city_name() != who->get_city_name() )
			return;
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是的，宫廷里的工匠可以帮助你将普通的号角加工为王之号角，你将号角交给我，我替你咨询下工匠，看还需要做哪些准备。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠说将普通的号角雕琢成为王之号角需要花费很多珍贵的材料，他需要一些钱来购买这些材料，而单靠他一个人的力量是不可能拿出这么多钱的，我想你应该要帮助他承担一部分，他说雕琢王之号角对他来说也是一项挑战，所以他不收你一文的加工费，只需要你给他100万的材料费就够了。如果你还想雕琢王之号角的话，就将钱交给我吧，我会转交给工匠的。\n    你交钱24小时后就可以来找我索取王之号角了，我想24小时已经足够让工匠来做这件事情了。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16) && gone_time(who->get_save("wangzhhj"))>=86400 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠通宵达旦地工作，终于在你来之前将王之号角雕琢好了，你拿去看看吧。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 4:
		if ( me->get_city_name() == who->get_city_name() && who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
		{
        		if (TASK_LEGEND_D->check_task_item(who,"号角",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,14);
			who->add_exp(3000);
			who->add_potential(100);
			who->add_cash(2500);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,13,"" );
			send_user(who,"%c%s",';',"寻求大王的帮助 经验 3000 潜能 100 金钱 2500");
			me->do_welcome(19);
        	}		
		break;
	case 5:
		if ( me->get_city_name() == who->get_city_name() && who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( who->get_cash() < 1000000 )
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你身上的钱不足以让工匠购买雕琢王之号角的材料，请你凑齐了钱再来找我吧。\n"ESC"离开", me->get_name(),getoid(me)));
				return ;	
			}
			who->add_cash(-1000000);
			who->set_save("wangzhhj",time());
        		who->set_legend(TASK_40,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"Chu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,14,"王之号角的雕琢" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"王之号角的雕琢");
        	}		
		break;
	case 6:
		if ( me->get_city_name() == who->get_city_name() && who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16) && gone_time(who->get_save("wangzhhj"))>=86400 )
		{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;        		
			TASK_LEGEND_D->give_item(who,"item/std/0095",1); 			
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,16);
			who->delete_save("wangzhhj");
			who->add_exp(3000);
			who->add_potential(100);
			who->add_cash(2500);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,14,"" );
			send_user(who,"%c%s",';',"王之号角的雕琢 经验 3000 潜能 100 金钱 2500");
		}
		break;
        case 7:
		if ( who->get_legend(TASK_45,13) && !who->get_legend(TASK_45,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，这就是常常有人提及的那种仙山云雾茶么？果然异香扑鼻，一闻就知道不同反响，感谢你为本王带来了仙茶，本王一定要重重赏你。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
		
	case 8:
		if ( who->get_legend(TASK_45,13) && !who->get_legend(TASK_45,14) )
		{
        		if (TASK_LEGEND_D->check_task_item(who,"云雾茶叶",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64179",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_45,14);
			who->add_exp(200000);
			who->add_potential(1500);
			who->add_cash(197000);
			send_user(who,"%c%s",';',"无上的荣耀（3） 经验 200000 潜能 1500 金钱 197000 飞龙鞋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,71,"" );
        	}
        	break;
	case 9:
        	if (who->get_level() >= 110 && !who->get_legend(TASK_45,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你有没有想过成为一个万众敬仰的人，当然德行、操守、仁爱、忠诚都是必不可少的，但是我们这个世界还需要一样，那就是武力。我看你其他方面的修炼都在步入正轨，唯有武力一项，我还需要检验一下，怎么样愿意接受挑战么？前段时间城中居民莫名的头疼经过调查其实都是诛仙阵中的枪魂在捣鬼，如果你能够前去消灭万恶的枪魂12只，到时候我晓谕全城，居民们自然会敬仰你的。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,15) && !who->get_legend(TASK_45,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    万众敬仰的人可是武力仁爱缺一不可，你光有仁爱不够，必须时时锻炼自己啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_45,16) && !who->get_legend(TASK_45,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你果然有勇气有武力，我已经将你的事迹晓谕全城，你出去看吧，他们都在欢呼你呢。怎么样，万众敬仰的感觉不错吧，哈哈，还望你以后能够时时为本王分忧，本王自然会给予你应该得到的。\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 10:
        	if (who->get_level() >= 110 && !who->get_legend(TASK_45,15) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_45,15);
        		who->delete_save("cwqianhun");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,41,"万众敬仰" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"万众敬仰");
        	}
        	break;        
        case 11:
		if ( who->get_legend(TASK_45,16) && !who->get_legend(TASK_45,17) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_45,17);
        		who->delete_save("cwqianhun");
			who->add_exp(91500);
			who->add_potential(988);
			who->add_cash(95000);
			send_user(who,"%c%s",';',"万众敬仰 经验 91500 潜能 988 金钱 95000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,41,"" );
        	}
        	break;
	case 99:
 		EMPEROR_D->do_look( who, me); 
 		break;
        }
        
}