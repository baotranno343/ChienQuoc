
// 自动生成：/make/npc/make8020
#include <ansi.h>
#include <npc.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0452; }
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
        set_name("Ngụy Quốc Công Tượng");
        set_real_name("Luyện Đơn 61~80");
        set_city_name("Ngụy Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",112);
//	set("legend",({32*44+4}));
	set("mpLegend",([110:({32*44+4}),]));
	set("mpLegend2",([110:({32*44+6,32*44+9,32*44+12,}),]));
	set_skill(0630, 39);
        set_2( "good", ([
                "01" : "/item/product/63023",
                "02" : "/item/product/63024",
                "03" : "/item/product/63025",
                "04" : "/item/product/63026",
                "05" : "/item/product/63027",
                "06" : "/item/product/63028",
                "07" : "/item/product/63029",
                "08" : "/item/product/63030",
                "09" : "/item/product/63031",
                "10" : "/item/product/63032",        
                "11" : "/item/product/63033",
                "12" : "/item/product/63034",
                "13" : "/item/product/63035",
                "14" : "/item/product/63036",
                "15" : "/item/product/63037",
                "16" : "/item/product/63038",
                "17" : "/item/product/63039",                                             
        ]) );	
        setup();
}

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( (who->get_level() >= 110 && !who->get_legend(TASK_44,4)) || (who->get_legend(TASK_44,4) && !who->get_legend(TASK_44,6)) )
		tmp += sprintf(ESC HIY "做床的木头\ntalk %x# welcome.1\n",getoid(me));
	if ( (who->get_legend(TASK_44,6) && !who->get_legend(TASK_44,7)) || (who->get_legend(TASK_44,7) && !who->get_legend(TASK_44,9)) )
		tmp += sprintf(ESC HIY "锯子\ntalk %x# welcome.1\n",getoid(me));
	if ( (who->get_legend(TASK_44,9) && !who->get_legend(TASK_44,10)) || (who->get_legend(TASK_44,10) && !who->get_legend(TASK_44,12)) )
		tmp += sprintf(ESC HIY "黄晶石\ntalk %x# welcome.1\n",getoid(me));

	tmp += sprintf(ESC"学习生活技能\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"购买Luyện Đơn 技能等级61-80级的配方\nlist %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 8 ); }

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
			if ( who->get_level() >= 110 && !who->get_legend(TASK_44,4) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我的女儿快要出嫁了，我这个当老爹的怎么也得拿出点像样的嫁妆吧，我最为自豪的就是我的手艺了，但是平时雕刻的东西我还不够满意，我一定要拿出压箱子的宝贝来，我师傅曾经传授了我一张图纸，唤作鹊缘床，据说睡上去能保佑夫妻夫妻恩爱，多得贵子。不知道大侠可愿意帮我达成这个心愿？首先我需要30个长一丈，宽三寸，没有树疙瘩的的美人松木头，不知道大侠有没有这个能力搞到？听说天门阵出产美人松木头，大侠可以前往看看。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
			else if ( who->get_legend(TASK_44,4) && !who->get_legend(TASK_44,5) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    找不到美人松么？莫非我的心愿竟然要落空了么？唉，我真的不是个好老爹啊，这点嫁妆都不能给我闺女备好。\n"ESC"离开", me->get_name()));
			else if ( who->get_legend(TASK_44,5) && !who->get_legend(TASK_44,6) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    果然厉害，木材大小都一点不差，但是现在我却遇到了一个意料之外的麻烦。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			else if ( who->get_legend(TASK_44,6) && !who->get_legend(TASK_44,7) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，不怕贼偷就怕贼惦记，我的锯子可是大师欧治子为了答谢我帮他做鹊缘床亲自锻造的，我本来一向为人低调，有宝也不外露，怎么那天酒醉了就说出来了呢，结果一向嗜宝如命的杜毒听说，昨天硬是闯我我家抢走了，我等安分小民哪里打的过不知道到哪里学了乱七八糟武艺的杜毒啊，看大侠你天庭饱满，气宇轩昂，定能帮我抢回宝物吧，小民在此多谢了。杜毒就在白马庄的紫竹小居，他家里可是有不少宝物，平时他巧取豪夺，相信没人关心他的宝物得失的。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
			else if ( who->get_legend(TASK_44,7) && !who->get_legend(TASK_44,8) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，难道杜毒三脚猫的功夫大侠你都拿他没有办法吗？\n"ESC"离开", me->get_name()));
			else if ( who->get_legend(TASK_44,8) && !who->get_legend(TASK_44,9) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，早就看出大侠是神龙再世，定能帮我夺回宝物，（一脸贼兮兮的靠近，嗅了嗅，低低说了声）大侠神光护体，好宝气啊。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
			else if ( who->get_legend(TASK_44,9) && !who->get_legend(TASK_44,10) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿嘿，要是仅仅是美人松做的当然还不能发挥那些功效，要不我怎么能担当神匠呢，我要在床上刻上符咒和阵法，而黄晶石可是必要的法器载体，据说上古遗阵诛仙阵里有当初神魔战争残留的黄晶石，虽然说不比当初仙人用的法器那么威力巨大，可是用来做我的鹊缘床可是绰绰有余。你可敢闯诛仙阵，为我取来黄晶石？你要问我怎么刻，呵呵，独门手艺，恕不外传，要不我怎么叫神匠呢？\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
			else if ( who->get_legend(TASK_44,10) && !who->get_legend(TASK_44,11) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n   呃，既然是仙人们留下来的东西，当然没有那么容易找到，你再耐心找找吧。\n"ESC"离开", me->get_name()));
			else if ( who->get_legend(TASK_44,11) && !who->get_legend(TASK_44,12) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，终于最重要的东西也凑齐了，我可以再一次体验一下完成鹊缘床的成就感了，喂，你那小子还站这里干嘛，走开走开，我的独门技艺可不能被你偷学了去，我不是已经给你钱了么，（摸摸口袋）啊，拿去拿去，我们两清了，记住，千万别来偷看，要不别怪老儿不客气！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));

	        	break; 
	        case 2:
	        	if ( who->get_level() >= 110 && !who->get_legend(TASK_44,4) )
	        	{
	        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
	        		who->set_legend(TASK_44,4);
	        		who->delete_save("wggjmutou");
				send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,62,"漂亮的床（1）" );
				send_user( who, "%c%s", '!', "得到任务 "HIY"漂亮的床（1）");
	        	}
	        	break;         	
		case 3:
	        	if ( who->get_legend(TASK_44,5) && !who->get_legend(TASK_44,6) )
	        	{
	        		if (TASK_LEGEND_D->check_task_item(who,"做床的木头",30) != 1 )
	        			return;
				TASK_LEGEND_D->task_finish(who);
				who->set_legend(TASK_44,6);
	        		who->delete_save("wggjmutou");
				who->add_exp(50000);
				who->add_potential(700);
				who->add_cash(48000);
				send_user(who,"%c%s",';',"漂亮的床（1） 经验 50000 潜能 700 金钱 48000");
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,62,"" );
		      		me->do_welcome(1);
		      	}
	        	break;
	        case 4:
	        	if ( who->get_legend(TASK_44,6) && !who->get_legend(TASK_44,7) )
	        	{
	        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
	        		who->set_legend(TASK_44,7);
				send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,63,"漂亮的床（2）" );
				send_user( who, "%c%s", '!', "得到任务 "HIY"漂亮的床（2）");
	        	}
	        	break;         	
		case 5:
	        	if ( who->get_legend(TASK_44,8) && !who->get_legend(TASK_44,9) )
	        	{
	        		if (TASK_LEGEND_D->check_task_item(who,"做床的锯子",1) != 1 )
	        			return;
				TASK_LEGEND_D->task_finish(who);
				who->set_legend(TASK_44,9);
				who->add_exp(50000);
				who->add_potential(700);
				who->add_cash(48000);
				send_user(who,"%c%s",';',"漂亮的床（2） 经验 50000 潜能 700 金钱 48000");
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,63,"" );
		      		me->do_welcome(1);
		      	}
	        	break;
	        case 6:
	        	if ( who->get_legend(TASK_44,9) && !who->get_legend(TASK_44,10) )
	        	{
	        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
	        		who->set_legend(TASK_44,10);
	        		who->delete_save("wggjhuangjs");
				send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,64,"漂亮的床（3）" );
				send_user( who, "%c%s", '!', "得到任务 "HIY"漂亮的床（3）");
	        	}
	        	break;         	
		case 7:
	        	if ( who->get_legend(TASK_44,11) && !who->get_legend(TASK_44,12) )
	        	{
	        		if (TASK_LEGEND_D->check_task_item(who,"漂亮的黄晶石",8) != 1 )
	        			return;
	        		TASK_LEGEND_D->give_item(who,"item/product/62092",1);
				TASK_LEGEND_D->task_finish(who);
				who->set_legend(TASK_44,12);
				who->delete_save("wggjhuangjs");
				who->add_exp(180000);
				who->add_potential(1400);
				who->add_cash(190000);
				send_user(who,"%c%s",';',"漂亮的床（3） 经验 180000 潜能 1400 金钱 190000 透魂钉图纸 1");
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,64,"" );
		      	}
	        	break;
        }
}