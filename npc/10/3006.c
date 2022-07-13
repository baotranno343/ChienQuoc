
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return 5801; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Nguỵ Lão Hán");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*34+10,32*34+13,32*34+16,32*35+16,32*35+19,32*35+22,}),]));
        setup();
}


// 函数：对话处理
void do_look( object who )
{
	int id;
	string tmp="";

	id = getoid(this_object());
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( who->get_legend(TASK_34,9) && !who->get_legend(TASK_34,10) )
		tmp += sprintf(ESC HIY "了解情况\ntalk %x# welcome.1\n",id); 
        if ( ( who->get_legend(TASK_34,10) && !who->get_legend(TASK_34,11) ) || ( who->get_legend(TASK_34,11) && !who->get_legend(TASK_34,13) ) )
		tmp += sprintf(ESC HIY "证实自己\ntalk %x# welcome.1\n",id); 
        if ( ( who->get_legend(TASK_34,13) && !who->get_legend(TASK_34,14) ) || ( who->get_legend(TASK_34,14) && !who->get_legend(TASK_34,16) ) )
		tmp += sprintf(ESC HIY "除掉骗子\ntalk %x# welcome.1\n",id); 
        if ( who->get_legend(TASK_34,16) && !who->get_legend(TASK_34,17) )
		tmp += sprintf(ESC HIY "官府备案\ntalk %x# welcome.1\n",id); 
        if ( who->get_legend(TASK_35,15) && !who->get_legend(TASK_35,16) )
		tmp += sprintf(ESC HIY "探明原因\ntalk %x# welcome.8\n",id); 
        if ( ( who->get_legend(TASK_35,16) && !who->get_legend(TASK_35,17) ) || ( who->get_legend(TASK_35,17) && !who->get_legend(TASK_35,19) ) )
		tmp += sprintf(ESC HIY "勇闯虚陵洞\ntalk %x# welcome.8\n",id); 
        if ( ( who->get_legend(TASK_35,19) && !who->get_legend(TASK_35,20) ) || ( who->get_legend(TASK_35,20) && !who->get_legend(TASK_35,22) ) )
		tmp += sprintf(ESC HIY "铲除祸源\ntalk %x# welcome.8\n",id); 
        if ( who->get_legend(TASK_35,22) && !who->get_legend(TASK_35,23) )
		tmp += sprintf(ESC HIY "通报情况\ntalk %x# welcome.8\n",id); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0121))
        + tmp +
        ESC"离开"
         );
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
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_34,9) && !who->get_legend(TASK_34,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，道仙法力高强，定将你这等肖小打个魂飞魄散，我手执那个如意棍呀，把你打，打你不忠不孝，打你不仁不义……\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_34,10) && !who->get_legend(TASK_34,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你敢诬蔑道仙！看我手执如意棍把你打呀打！道仙洞府在玄真洞，我劝你速速前去认罪，否则道仙发怒就要把你罚！罚你三生三世做牛马，罚你娇妻女儿啊都他嫁！道仙法广施天下，泽被百姓把他夸。水精三十立在左，火精三十立在右，玄真洞府仙灵境，无缘人儿莫寻它！\n    （你暗自思忖，看来魏老汉已经神智不清了，听样子那个水精30和火精30正是助纣为虐的，你先去将他们拔除，再来看魏老汉。）\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_34,11) && !who->get_legend(TASK_34,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    道仙发怒就要把你罚！罚你三生三世做牛马，罚你娇妻女儿啊都他嫁！道仙法广施天下，泽被百姓把他夸。水精三十立在左，火精三十立在右，玄真洞府仙灵境，无缘人儿莫寻它！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_34,12) && !who->get_legend(TASK_34,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，道仙发怒了，你做了什么！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_34,13) && !who->get_legend(TASK_34,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，（魏老汉摇了摇头，仿佛清醒了一点）你快帮我去看看道仙出什么事情了没有，对了，他本家姓名叫做朱老四，原本是我的幼时玩伴，出走多年后回来他已经习得大法，你探视过后告诉我一声。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_34,14) && !who->get_legend(TASK_34,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你快点去探视一下道仙，我怕有坏人要对付他！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_34,15) && !who->get_legend(TASK_34,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊！（魏老汉仿佛彻底清醒了，拉着你絮絮叨叨起来）哎呀，这个朱老四，原来只是装神弄鬼的骗子啊！唉，我给儿子存下娶媳妇的钱还有家里买米的钱统统都给他骗了去，这个天杀的！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_34,16) && !who->get_legend(TASK_34,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你杀了那骗子，最好和魏国典狱官说一声，让他备案并奏请大王全国通缉此类人。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));

	    	break;
        case 2:
        	if ( who->get_legend(TASK_34,9) && !who->get_legend(TASK_34,10) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,10);
			who->add_exp(73000);
			who->add_potential(900);
			who->add_cash(63000);
			send_user(who,"%c%s",';',"了解情况 经验 73000 潜能 900 金钱 63000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,42,"" );
			me->do_welcome(1);
        	}
        	break;   
	case 3:
        	if ( who->get_legend(TASK_34,10) && !who->get_legend(TASK_34,11) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_34,11);
        		who->delete_save("wlhsuijing");
        		who->delete_save("wlhhuojing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"魏国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,43,"证实自己" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"证实自己");
        	}
        	break;  
        case 4:
        	if ( who->get_legend(TASK_34,12) && !who->get_legend(TASK_34,13) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,13);
        		who->delete_save("wlhsuijing");
        		who->delete_save("wlhhuojing");
			who->add_exp(72000);
			who->add_potential(880);
			who->add_cash(62000);
			send_user(who,"%c%s",';',"证实自己 经验 72000 潜能 880 金钱 62000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,43,"" );
			me->do_welcome(1);
        	}
        	break;
	case 5:
        	if ( who->get_legend(TASK_34,13) && !who->get_legend(TASK_34,14) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_34,14);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"魏国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,44,"除掉骗子" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"除掉骗子");
        	}
        	break;  
        case 6:
        	if ( who->get_legend(TASK_34,15) && !who->get_legend(TASK_34,16) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,16);
			who->add_exp(72000);
			who->add_potential(900);
			who->add_cash(61000);
			send_user(who,"%c%s",';',"除掉骗子 经验 72000 潜能 900 金钱 61000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,44,"" );
			me->do_welcome(1);
        	}
        	break;
	case 7:
        	if ( who->get_legend(TASK_34,16) && !who->get_legend(TASK_34,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_34,17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"魏国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,45,"官府备案" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"官府备案");
        	}
        	break; 
        case 8:
        	if ( who->get_legend(TASK_35,15) && !who->get_legend(TASK_35,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    给我点时间，这事一时也说不清楚！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_35,16) && !who->get_legend(TASK_35,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，这次的帮凶似乎是虚陵洞的土精和水精，真的不知道那恶贼都会了什么驾驭精灵之术，你先去剪掉他的羽翼，杀掉30个土精和30个水精再来告诉我吧。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_35,17) && !who->get_legend(TASK_35,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我得禀报御史大人换个得力的人来。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_35,18) && !who->get_legend(TASK_35,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    临河算是有救了。\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_35,19) && !who->get_legend(TASK_35,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近马贼魏小三倒是常常来袭扰村庄，不过上次那种怪异之事倒是不曾有，只不过大家怕被报复，敢怒不敢言，才好似神秘起来，上次有村民看到马贼魏小三在虚陵洞南部一带盘踞，你去把他杀了估计大家又可以睡安稳觉了。\n"ESC"接受任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_35,20) && !who->get_legend(TASK_35,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我劝你还是回家吧！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_35,21) && !who->get_legend(TASK_35,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可以安静了，现在大家宽了心又开始谈论些鸡毛蒜皮的小事了，比如说上次那个石大龙为什么会偷大家的贴身事物和怎么偷的，哈哈……\n"ESC"完成任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_35,22) && !who->get_legend(TASK_35,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在临河安静了，不过不知道又能持续多久的时间，你将最近一系列事情通报御史，看是否应该派个得力的官吏来严防此类事情频繁发生，毕竟京畿也是重中之重啊。\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 9:
        	if ( who->get_legend(TASK_35,15) && !who->get_legend(TASK_35,16) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_35,16);
			who->add_exp(80000);
			who->add_potential(1200);
			who->add_cash(69000);
			send_user(who,"%c%s",';',"探明原因 经验 80000 潜能 1200 金钱 69000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,57,"" );
			me->do_welcome(8);
        	}
        	break;
	case 10:
        	if ( who->get_legend(TASK_35,16) && !who->get_legend(TASK_35,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,17);
        		who->delete_save("wlhtujing1");
        		who->delete_save("wlhsuijing1");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"魏国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,58,"勇闯虚陵洞" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"勇闯虚陵洞");
        	}
        	break; 
        case 11:
        	if ( who->get_legend(TASK_35,18) && !who->get_legend(TASK_35,19) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_35,19);
        		who->delete_save("wlhtujing1");
        		who->delete_save("wlhsuijing1");
			who->add_exp(81000);
			who->add_potential(1200);
			who->add_cash(69000);
			send_user(who,"%c%s",';',"勇闯虚陵洞 经验 81000 潜能 1200 金钱 69000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,58,"" );
			me->do_welcome(8);
        	}
        	break;
	case 12:
        	if ( who->get_legend(TASK_35,19) && !who->get_legend(TASK_35,20) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,20);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"魏国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,59,"铲除祸源" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"铲除祸源");
        	}
        	break; 
        case 13:
        	if ( who->get_legend(TASK_35,21) && !who->get_legend(TASK_35,22) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_35,22);
			who->add_exp(79000);
			who->add_potential(1100);
			who->add_cash(70000);
			send_user(who,"%c%s",';',"铲除祸源 经验 79000 潜能 1100 金钱 70000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,59,"" );
			me->do_welcome(8);
        	}
        	break;
	case 14:
        	if ( who->get_legend(TASK_35,22) && !who->get_legend(TASK_35,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,23);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"魏国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,60,"通报情况" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"通报情况");
        	}
        	break; 
        }
}