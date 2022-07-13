
// 自动生成：/make/npc/make8001

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

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
        set_name("Triệu Vương");
	set_real_name("Triệu Vương Thiên");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "policy"        : (: do_policy :),
                "relation"      : (: do_relation :),
                "master"        : (: do_master :),
                "advice"        : (: do_advice :),
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",101);
//        set("legend",({32*36+1}));
 	set("mpLegend",([100:({32*36+1}),115:({32*45+18})]));
 	set("mpLegend2",([0:({32*21+23,32*41+27,32*42+22,32*43+4,32*43+16,}),50:({32*38+4,}),100:({32*36+10,32*38+24,}),110:({32*39+8,}),115:({32*45+20,32*45+30,})]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who ) 
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_21,22) && !who->get_legend(TASK_21,23) )
	{
		tmp += sprintf(ESC HIY "面见赵王\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,23) && !who->get_legend(TASK_21,24) )
	{
		tmp += sprintf(ESC HIY "回奏秦王\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_level() >= 50 && who->get_legend(TASK_38,3) && !who->get_legend(TASK_38,4) )
	{
		tmp += sprintf(ESC HIY "丢失的夜明珠\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( who->get_level() >= 100 && who->get_legend(TASK_38,23) && !who->get_legend(TASK_38,24) )
	{
		tmp += sprintf(ESC HIY "讨好\ntalk %x# welcome.6\n",getoid(me));
	}
	if ( who->get_level() >= 110 && who->get_legend(TASK_39,7) && !who->get_legend(TASK_39,8) )
	{
		tmp += sprintf(ESC HIY "交好\ntalk %x# welcome.8\n",getoid(me));
	}
	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,1) )
		tmp += sprintf(ESC HIY "完美宝石\ntalk %x# welcome.10\n",getoid(me));
	if ( who->get_legend(TASK_36,9) && !who->get_legend(TASK_36,10) )
		tmp += sprintf(ESC HIY "完美宝石\ntalk %x# welcome.10\n",getoid(me));
	if ( who->get_legend(TASK_41,26) && !who->get_legend(TASK_41,27) )
		tmp += sprintf(ESC HIY "上奏赵王\ntalk %x# welcome.17\n",getoid(me));
	if ( who->get_legend(TASK_42,21) && !who->get_legend(TASK_42,22) )
		tmp += sprintf(ESC HIY "禀报赵王\ntalk %x# welcome.19\n",getoid(me));
	if ( who->get_legend(TASK_43,3) && !who->get_legend(TASK_43,4) )
		tmp += sprintf(ESC HIY "施行仁政\ntalk %x# welcome.21\n",getoid(me));
	if ( who->get_legend(TASK_43,15) && !who->get_legend(TASK_43,16) )
		tmp += sprintf(ESC HIY "完成使命\ntalk %x# welcome.23\n",getoid(me));
	if ( (who->get_level() >= 115 && !who->get_legend(TASK_45,18)) || (who->get_legend(TASK_45,18) && !who->get_legend(TASK_45,20)) )
		tmp += sprintf(ESC HIY "如意玉牌\ntalk %x# welcome.25\n",getoid(me));
	if ( who->get_legend(TASK_45,20) && !who->get_legend(TASK_45,21) )
		tmp += sprintf(ESC HIY "询问鬼谷子\ntalk %x# welcome.25\n",getoid(me));
	if ( who->get_legend(TASK_45,29) && !who->get_legend(TASK_45,30) )
		tmp += sprintf(ESC HIY "世子的病\ntalk %x# welcome.25\n",getoid(me));

	if ( me->get_city_name() == who->get_city_name() )
	{
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			tmp += sprintf(ESC HIY "制作王之号角\ntalk %x# welcome.13\n",getoid(me));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			tmp += sprintf(ESC HIY "王之号角的雕琢\ntalk %x# welcome.13\n",getoid(me));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16)&& gone_time(who->get_save("wangzhhj"))>=86400 )
			tmp += sprintf(ESC HIY "索取王之号角\ntalk %x# welcome.13\n",getoid(me));
	}
	if ( who->get("master.type") != 69 && sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( " %s :\n "+"/quest/word"->get_country_word(me) + "\n"ESC"Đối thoại\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"Rời khỏi");
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
        string *nTmp,tmp;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_21,22) && !who->get_legend(TASK_21,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    秦赵本是兄弟之邦，秦王赢政如此诚心与本国交善，本王自是大喜，不过秦赵结盟之事非同小可，寡人还得与众臣细细商议才是。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_21,23) && !who->get_legend(TASK_21,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本王与众臣商议再三，已经草拟了一份秦赵结盟的事项在回信函之内，还望你代寡人转交秦王赢政。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
 
        	break;
	case 2:
        	if ( who->get_legend(TASK_21,22) && !who->get_legend(TASK_21,23) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/63023",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,23);
			who->add_exp(17500);
			who->add_potential(380);
			who->add_cash(19000);
			send_user(who,"%c%s",';',"面见赵王 经验 17500 潜能 380 金钱 19000 救急丹图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,36,"" );
			me->do_welcome(1);
        	}
        	break;
	case 3:
        	if ( who->get_legend(TASK_21,23) && !who->get_legend(TASK_21,24) )
        	{
 			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
 			item = new("/item/98/0099");
 			p = item->move(who,-1);
 			if ( !p )
 			{
 				destruct(item);
 				send_user(who,"%c%s", '!', "你携带的物品太多了");	
 				return ;
 			}
 			item->add_to_user(p);
        		who->set_legend(TASK_21,24);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,37,"回奏秦王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"回奏秦王");
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 50 && who->get_legend(TASK_38,3) && !who->get_legend(TASK_38,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没想到我遗失在燕国的夜明珠，居然还能找回来，燕国的臣民真是高风亮节啊！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
        case 5:
		if ( who->get_level() >= 50 && who->get_legend(TASK_38,3) && !who->get_legend(TASK_38,4) )
		{
        		if (TASK_LEGEND_D->check_task_item(who,"夜明珠",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_38,4);
			who->add_exp(5500);
			who->add_potential(230);
			who->add_cash(5000);
			send_user(who,"%c%s",';',"丢失的夜明珠 经验 5500 潜能 230 金钱 5000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,54,"" );
        	} 
        	break;
	case 6:
		if ( who->get_level() >= 100 && who->get_legend(TASK_38,23) && !who->get_legend(TASK_38,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，居然是樱桃！你居然给我送来了樱桃！我一定要好好的赏赐你！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 7:
		if ( who->get_level() >= 100 && who->get_legend(TASK_38,23) && !who->get_legend(TASK_38,24) )
		{
        		if (TASK_LEGEND_D->check_task_item(who,"樱桃",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_38,24);
			who->add_exp(40000);
			who->add_potential(605);
			who->add_cash(38000);
			send_user(who,"%c%s",';',"讨好 经验 40000 潜能 605 金钱 38000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,76,"" );
        	} 
        	break;
	case 8:
		if ( who->get_level() >= 110 && who->get_legend(TASK_39,7) && !who->get_legend(TASK_39,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这个方法果然不错！哈哈哈哈哈！或许我与楚还能联合起来攻打秦呢！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 9:
		if ( who->get_level() >= 110 && who->get_legend(TASK_39,7) && !who->get_legend(TASK_39,8) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_39,8);
			who->add_exp(50000);
			who->add_potential(620);
			who->add_cash(48000);
			send_user(who,"%c%s",';',"交好 经验 50000 潜能 620 金钱 48000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,46,"" );
        	} 
        	break;
        case 10:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,1)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本王鹤妃上次为本王挡刺客不幸身亡，本王伤心不已，一直将她保存在水晶棺中，常常看着她鲜活的面容仿佛就在昨日尚在把臂赏菊，共话婵娟。刚刚听得人说齐王田建得到一种宝石，可以令人起死回生，本王急欲得到这种宝石，只要我爱妃能重生，不论付出任何代价，这位壮士能否作为本王特使走一趟向齐王田建求取宝石?\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
	        else if ( who->get_legend(TASK_36,9) && !who->get_legend(TASK_36,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    噢，我的宝石，我的爱妃，啊什么，必须人刚死的时候使用，还要有王血的辅助？呃，这个，本王知道了，噢什么，活人使用可以延年益寿，噢，太好了，本王会重重的赏你，哦，本王爱妃啊，本王爱妃多的是，你说哪个？\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 11:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,1)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_36,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,57,"完美宝石（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"完美宝石（1）");
        	}
        	break;
	case 12:
        	if ( who->get_legend(TASK_36,9) && !who->get_legend(TASK_36,10) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"完美橙晶石",1) != 1 )
        			return;
 			nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),100,NECK_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1); 		
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_36,10);
			who->add_exp(200000);
			who->add_potential(2250);
			who->add_cash(200000);
			send_user(who,"%c%s",';',sprintf("完美宝石（4） 经验 200000 潜能 2250 金钱 200000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,89,"" );
        	}
        	break;	

	case 13:
		if ( me->get_city_name() != who->get_city_name() )
			return;
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是的，宫廷里的工匠可以帮助你将普通的号角加工为王之号角，你将号角交给我，我替你咨询下工匠，看还需要做哪些准备。\n"ESC"完成任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠说将普通的号角雕琢成为王之号角需要花费很多珍贵的材料，他需要一些钱来购买这些材料，而单靠他一个人的力量是不可能拿出这么多钱的，我想你应该要帮助他承担一部分，他说雕琢王之号角对他来说也是一项挑战，所以他不收你一文的加工费，只需要你给他100万的材料费就够了。如果你还想雕琢王之号角的话，就将钱交给我吧，我会转交给工匠的。\n    你交钱24小时后就可以来找我索取王之号角了，我想24小时已经足够让工匠来做这件事情了。\n"ESC"接受任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16) && gone_time(who->get_save("wangzhhj"))>=86400 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠通宵达旦地工作，终于在你来之前将王之号角雕琢好了，你拿去看看吧。\n"ESC"完成任务\ntalk %x# welcome.16\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 14:
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
	case 15:
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
	case 16:
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
	case 17:
		if ( who->get_legend(TASK_41,26) && !who->get_legend(TASK_41,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，大将军有此豪气固然可喜，不过秦国攻打我国乃是空穴来风之音，你让大将军不必心焦！\n"ESC"完成任务\ntalk %x# welcome.18\n"ESC"离开", me->get_name(),getoid(me)));
	
		break;
	case 18:
		if ( who->get_legend(TASK_41,26) && !who->get_legend(TASK_41,27) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"请战书",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64173",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_41,27);
			who->add_exp(93000);
			who->add_potential(1600);
			who->add_cash(83000);
			send_user(who,"%c%s",';',"上奏赵王 经验 93000 潜能 1600 金钱 83000 斥云冠图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,72,"" );
        	}	
		break;
	case 19:
		if ( who->get_legend(TASK_42,21) && !who->get_legend(TASK_42,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    感谢爱卿为了本王的安危如此劳心费神，本王会召开王府内苑扩大会议讨论一下典狱官建设性的建议并予以贯彻实施，再次本王代表本国国民以及本王本人对于壮士在此次粉碎刺杀行动中的智勇双全，表示由衷的感谢和深刻的问候，对于受了蒙蔽，走了错误路线而跟随刺客的太极门众表示，如果他们能就此认清错误，不再站在国家和人民的对立面，本王可以给他们改过自新，立功赎罪的机会，对于本次特别行动作出了杰出贡献的赵国百姓吴姬，本王将颁发第一国师的荣誉称号，另相关奖励请咨询内政官。\n"ESC"完成任务\ntalk %x# welcome.20\n"ESC"离开", me->get_name(),getoid(me)));
		break;		
	case 20:
		if ( who->get_legend(TASK_42,21) && !who->get_legend(TASK_42,22) )
		{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/62089",1);
        		who->set_legend(TASK_42,22);
			who->add_exp(98000);
			who->add_potential(1750);
			who->add_cash(88000);
			send_user(who,"%c%s",';',"禀报赵王 经验 98000 潜能 1750 金钱 88000 破空刀图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,82,"" );
        	}	
		break;
	case 21:
		if ( who->get_legend(TASK_43,3) && !who->get_legend(TASK_43,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    爱卿用心良苦，本王必定励精图治，使得政清吏明。\n"ESC"完成任务\ntalk %x# welcome.22\n"ESC"离开", me->get_name(),getoid(me)));
		break;		
	case 22:
		if ( who->get_legend(TASK_43,3) && !who->get_legend(TASK_43,4) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"施政奏章",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/62090",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_43,4);
			who->add_exp(96000);
			who->add_potential(1900);
			who->add_cash(92000);
			send_user(who,"%c%s",';',"施行仁政 经验 96000 潜能 1900 金钱 92000 霸王枪图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,87,"" );
        	}	
		break;
	case 23:
		if ( who->get_legend(TASK_43,15) && !who->get_legend(TASK_43,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来应该进行一场持续深刻的扫除我国毒瘤的运动了。\n"ESC"完成任务\ntalk %x# welcome.24\n"ESC"离开", me->get_name(),getoid(me)));
		break;		
	case 24:
		if ( who->get_legend(TASK_43,15) && !who->get_legend(TASK_43,16) )
		{
			nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),110,WAIST_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			if (TASK_LEGEND_D->check_task_item(who,"调查奏章",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,tmp,1); 
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_43,16);
			who->add_exp(120000);
			who->add_potential(2000);
			who->add_cash(92000);
			send_user(who,"%c%s",';',sprintf("完成使命 经验 120000 潜能 2000 金钱 92000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,92,"" );
        	}	
		break;
	case 25:
        	if (who->get_level() >= 115 && !who->get_legend(TASK_45,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不知道为何，世子突然间病倒了，一连几日高烧不退，精神恍惚，并且急速消瘦下去，据说晚上还梦呓不止，招来宫中所有御医都束手无策，前日来了个钦阳道长，他说上古遗物如意玉牌对于可以平缓这种病状，但是寡人招募了数十名壮士前去诛仙阵刀魂身上取都有去无回，眼看爱子垂危，寡人心焦，寡人的千里江山谁堪继承啊，不知道这位壮士能否为寡人世子前去取如意玉牌，本王定有重赏！\n"ESC"接受任务\ntalk %x# welcome.26\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,18) && !who->get_legend(TASK_45,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如今世子病情愈发严重，寡人一日心焦一日，不知壮士可速去否？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_45,19) && !who->get_legend(TASK_45,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如意玉牌虽说不能治根，好歹也能先救世子一命，多谢壮士援手。\n"ESC"完成任务\ntalk %x# welcome.27\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,20) && !who->get_legend(TASK_45,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    徐福道长前来用了如意玉牌世子果然病情大为好转，他向寡人提起云梦泽中有一位隐世神医，唤作鬼谷子，据说能活死人，肉白骨，世间尚无他不可治之病，你可代本王前去求医，看他能否为世子除去病根。如若事谐，本王必当重赏。\n"ESC"接受任务\ntalk %x# welcome.28\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,29) && !who->get_legend(TASK_45,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    解降的药（赵王迁沉吟片刻，眉头跳了跳，接过御风丹转身交给等待的御医）多谢义士代本王求药，王储待得好转，本王必再多封赏。总管带他下去领取赏银吧。（言毕赵王迁起身已向后宫走去，仿佛转眼已将辛苦为他求药的人忘在脑后。）\n"ESC"完成任务\ntalk %x# welcome.29\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 26:
        	if (who->get_level() >= 115 && !who->get_legend(TASK_45,18) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_45,18);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,60,"求医（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"求医（1）");
        	}
        	break;
	case 27:
		if ( who->get_legend(TASK_45,19) && !who->get_legend(TASK_45,20) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"如意玉牌",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_45,20);
			who->add_exp(51500);
			who->add_potential(780);
			who->add_cash(51000);
			send_user(who,"%c%s",';',"求医（1）经验 51500 潜能 780 金钱 51000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,60,"" );
        		me->do_welcome(25);
        	}	
		break;
	case 28:
        	if ( who->get_legend(TASK_45,20) && !who->get_legend(TASK_45,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_45,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,61,"求医（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"求医（2）");
        	}
        	break;
	case 29:
		if ( who->get_legend(TASK_45,29) && !who->get_legend(TASK_45,30) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"御风丹",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64180",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_45,30);
			who->add_exp(230000);
			who->add_potential(2450);
			who->add_cash(225000);
			send_user(who,"%c%s",';',"求医（5）经验 230000 潜能 2450 金钱 225000 冥光鞋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YUNMENZE,3,"" );
        	}	
		break;
	case 99:
 		EMPEROR_D->do_look( who, me); 
 		break;
        }
}
