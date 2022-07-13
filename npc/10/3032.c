
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>
#include <equip.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5501; }

// 函数：构造处理
void create()
{
        set_name("Tần Dược Sư");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
 	set("mpLegend",([60:({32*19+1}),]));
 	set("mpLegend2",([0:({32*36+8,32*46+14,32*46+17,32*46+27,32*46+30,32*47+5,}),60:({32*19+6,32*19+9,32*19+12,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( (who->get_level() >= 60 && !who->get_legend(TASK_19,1)) || (who->get_legend(TASK_19,1)&&!who->get_legend(TASK_19,2)) ) 
		tmp += sprintf(ESC HIY "寻找大葫芦种子\ntalk %x# welcome.1\n",getoid(this_object())); 
 	if (who->get_legend(TASK_19,5)&&!who->get_legend(TASK_19,6))
 		tmp += sprintf(ESC HIY "寻找大葫芦种子\ntalk %x# welcome.1\n",getoid(this_object())); 
 	if ((who->get_legend(TASK_19,6)&&!who->get_legend(TASK_19,7)) || (who->get_legend(TASK_19,7)&&!who->get_legend(TASK_19,9)) )
 		tmp += sprintf(ESC HIY "特殊的泥土\ntalk %x# welcome.1\n",getoid(this_object())); 
 	if ((who->get_legend(TASK_19,9)&&!who->get_legend(TASK_19,10)) || (who->get_legend(TASK_19,10)&&!who->get_legend(TASK_19,12)) )
 		tmp += sprintf(ESC HIY "找锯子\ntalk %x# welcome.1\n",getoid(this_object())); 
	if ( who->get_legend(TASK_36,6) && !who->get_legend(TASK_36,8) )
		tmp += sprintf(ESC HIY "炼药\ntalk %x# welcome.8\n",getoid(this_object()));
	if ( who->get_legend(TASK_36,8) && !who->get_legend(TASK_36,9) )
		tmp += sprintf(ESC HIY "完美宝石\ntalk %x# welcome.8\n",getoid(this_object()));
        if ( who->get_legend(TASK_46,13)&&!who->get_legend(TASK_46,14) ) 
		tmp += sprintf(ESC HIY "探听消息\ntalk %x# welcome.11\n",getoid(this_object())); 
        if ( who->get_legend(TASK_46,14)&&!who->get_legend(TASK_46,17) ) 
		tmp += sprintf(ESC HIY "磨练勇气\ntalk %x# welcome.11\n",getoid(this_object())); 
        if ( who->get_legend(TASK_46,17)&&!who->get_legend(TASK_46,18) ) 
		tmp += sprintf(ESC HIY "除掉恶匪\ntalk %x# welcome.11\n",getoid(this_object())); 
        if ( who->get_legend(TASK_46,26)&&!who->get_legend(TASK_46,27) ) 
		tmp += sprintf(ESC HIY "拜访之路\ntalk %x# welcome.16\n",getoid(this_object())); 
        if ( who->get_legend(TASK_46,27)&&!who->get_legend(TASK_46,30) ) 
		tmp += sprintf(ESC HIY "闯阵寻草\ntalk %x# welcome.16\n",getoid(this_object())); 
        if ( who->get_legend(TASK_46,30)&&!who->get_legend(TASK_47,1) ) 
		tmp += sprintf(ESC HIY "询问配方\ntalk %x# welcome.16\n",getoid(this_object())); 
        if ( who->get_legend(TASK_47,4)&&!who->get_legend(TASK_47,5) ) 
		tmp += sprintf(ESC HIY "所差之药\ntalk %x# welcome.16\n",getoid(this_object())); 
        if ( who->get_legend(TASK_47,5)&&!who->get_legend(TASK_47,6) ) 
		tmp += sprintf(ESC HIY "解决困难\ntalk %x# welcome.16\n",getoid(this_object())); 
		
        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(1011))
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
        int flag,p;
        object who,item,obj;  
        string cmd1;
       	string *nTmp,tmp;     
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
	       	if ( who->get_level() >= 60 && !who->get_legend(TASK_19,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听说有一种大葫芦，可以装五石米那么多，只有魏国的李大毛那里才有种子，你是否有兴趣替我找他讨点种子，等葫芦种出来后，我定会送你一个！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_19,1) && !who->get_legend(TASK_19,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果错过了播种的季节那可就不好了。\n"ESC"离开", me->get_name()));
       		else if (who->get_legend(TASK_19,5)&&!who->get_legend(TASK_19,6))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你终于找来了大葫芦种子，本来我心焦正准备叫人去催你呢，你别走开，我可不想按部就班的种几个月才能看到大葫芦，还得有事情拜托你。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
       		else if (who->get_legend(TASK_19,6)&&!who->get_legend(TASK_19,7))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听说秦长城的弓兵私藏一种仙土，据说能够催发异种，本来需要几个月的种子一天就能长成，我觉得这种仙土才配的上这种仙葫芦，你去给我弄20斤仙土来，让我们亲眼看看仙葫芦是怎么长成的。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_19,7) && !who->get_legend(TASK_19,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没有这种特殊的泥土，我可不会把种子播种下去，我怕浪费了这些好种子。\n"ESC"离开", me->get_name()));
       		else if (who->get_legend(TASK_19,8)&&!who->get_legend(TASK_19,9))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哇，种子一埋下去刚刚浇水就开始破皮了，看看发芽了，钻出土了，子叶展开了……仙土配仙葫芦，我竟然亲眼目睹了这个奇迹，我太幸福了……\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
       		else if (who->get_legend(TASK_19,9)&&!who->get_legend(TASK_19,10))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，终于结出来了！果然不愧为大葫芦啊，这下部圆大，像个大南瓜，上有一粗短的柄，哇，皮厚得很，敲起来就知道它的皮比城墙还厚。要是锯成两半，作舀水的瓢，或者盛些贵重的药物也好卖个高价， 只是要把它完好的切开，可能还需要一种锋利的锯子，听说秦长城的刀盾兵就有钢锯子，你去找找看。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_19,10) && !who->get_legend(TASK_19,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    虽说这锯子要等到葫芦成熟时才用得着，但你还是早点找来的好！\n"ESC"离开", me->get_name()));
       		else if (who->get_legend(TASK_19,11)&&!who->get_legend(TASK_19,12))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你找来锯子，这是给你的报酬。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
       			
        	break;
	case 2:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_19,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_19,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,54,"大葫芦（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"大葫芦（1）");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_19,5) && !who->get_legend(TASK_19,6) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"大葫芦种子",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_19,6);
			who->add_exp(3830);
			who->add_potential(165);
			who->add_cash(3560);
			send_user(who,"%c%s",';',"大葫芦（3） 经验 3830 潜能 165 金钱 3560");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,10,"" );
       			me->do_welcome(1);
       		}
        	break;
	case 4:
        	if (who->get_legend(TASK_19,6)&&!who->get_legend(TASK_19,7))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_19,7);
        		who->delete_save_2("teshunitu");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,18,"大葫芦（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"大葫芦（4）");
        	}
        	break;  
        case 5:
        	if ( who->get_legend(TASK_19,8) && !who->get_legend(TASK_19,9) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"特殊泥土",20) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/65063",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_19,9);
        		who->delete_save_2("teshunitu");
			who->add_exp(6000);
			who->add_potential(190);
			who->add_cash(3700);
			send_user(who,"%c%s",';',"大葫芦（4） 经验 6000 潜能 190 金钱 3700 紫焰项链图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,18,"" );
       			me->do_welcome(1);
       		}
        	break;
	case 6:
        	if (who->get_legend(TASK_19,9)&&!who->get_legend(TASK_19,10))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_19,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,19,"大葫芦（5）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"大葫芦（5）");
        	}
        	break;  
        case 7:
        	if ( who->get_legend(TASK_19,11) && !who->get_legend(TASK_19,12) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),60,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"锯子",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_19,12);
			who->add_exp(10000);
			who->add_potential(680);
			who->add_cash(15000);
			send_user(who,"%c%s",';',sprintf("大葫芦（5） 经验 10000 潜能 680 金钱 15000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,19,"" );
       		}
        	break;
        case 8:
	        if ( who->get_legend(TASK_36,6) && !who->get_legend(TASK_36,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n   嗯？你来找我干什么，我正在研究新配方，没空理你，走开走开！\n"ESC"离开", me->get_name()));
	        else if ( who->get_legend(TASK_36,7) && !who->get_legend(TASK_36,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，师兄生意太繁忙了，也照顾我做做，刚刚师兄派人送来几块晶石，送来配方，我正思度着是哪位贵人光顾，却原来是齐王田建啊，看来开市大吉，你稍坐一会，我再去熟悉一下配方，很快就可以开炉炼了。（狂汗中……原来还是头一次练啊……你的心扑通扑通跳个不停，但是如今已经是骑虎难下，还是选择相信他吧……）\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
	        else if ( who->get_legend(TASK_36,8) && !who->get_legend(TASK_36,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，老夫居然炼成了，刚才我找马显卜了一卦，他说我开张大吉，果然如此，待会我可得谢谢他，（突然一脸严肃状）咳咳，不过，老夫功力不够，起死回生其实是师兄的宣传手段而已，其实呢，呃这个，随时佩带在身上，也就能让人延年益寿，不过我想聪明如大侠你一定知道如何回禀赵王迁吧，呵呵，一定不会将老夫同你一起扯进这个欺罔之罪吧，再说老夫远在秦国可以置身事外，你回去报告的时候可能会被赵王迁砍脑袋呢。嘿嘿，希望我们合作愉快。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 9:
        	if ( who->get_legend(TASK_36,7) && !who->get_legend(TASK_36,8) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"古石灰",5) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"慈石",7) != 1 )
        		{
				TASK_LEGEND_D->give_item(who,"item/98/0165",3); 
        			return ;
        		}
        		if (TASK_LEGEND_D->check_task_item(who,"雄黄",3) != 1 )
        		{
				TASK_LEGEND_D->give_item(who,"item/98/0165",5); 
				TASK_LEGEND_D->give_item(who,"item/98/0166",7); 
        			return ;
        		}
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_36,8);
        		who->delete_save("qwgushihui");
        		who->delete_save("qwcishi");
        		who->delete_save("qwxionghuang");
			who->add_exp(39000);
			who->add_potential(650);
			who->add_cash(37000);
			send_user(who,"%c%s",';',"完美宝石（3） 经验 39000 潜能 650 金钱 37000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,52,"" );
			me->do_welcome(12);
        	}
        	break;	
	case 10:
        	if ( who->get_legend(TASK_36,8) && !who->get_legend(TASK_36,9) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;        		
			TASK_LEGEND_D->give_item(who,"item/98/0161",1);
          		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
          		who->set_legend(TASK_36,9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,89,"完美宝石（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"完美宝石（4）");
        	}
        	break;
        case 11:
        	if ( who->get_legend(TASK_46,13)&&!who->get_legend(TASK_46,14) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然里正大人都不清楚这些凶杀案的所以然，我等斗升小民如何能知道，你就别消遣老朽了。我今天还有几个受伤的病人，他们都需要静养，请你出去。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,14)&&!who->get_legend(TASK_46,15) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    年轻人，你确定你真的要管这件事？如果你仅仅是好奇就速速离去吧，这件事可不是随便谁都管的了的，要么你就先去诛仙阵中诛杀30个剑魂和30个枪魂，老朽再考虑考虑，如果你认为不值得就不要去了。\n"ESC"接受任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,15)&&!who->get_legend(TASK_46,16) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你只是好奇吧，那就不要来问老朽了，老朽可什么都没有说过。\n"ESC"离开", me->get_name(),));
		else if ( who->get_legend(TASK_46,16)&&!who->get_legend(TASK_46,17) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有正义感，有勇气，有武力，看来能够平复这场混乱的人终于出现了，希望你不要让老夫失望。\n"ESC"完成任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,17)&&!who->get_legend(TASK_46,18) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近平阳附近盘踞了一个恶匪展五，端是个九尺大汉，善使一对黄金锏，生的一声好武力，他纠集了一帮子匪类，窝在诛仙阵二层中部，时时出来我们镇打家劫舍，欺凌妇孺，稍有反抗动辄行凶伤人，周围无人制得他，曾有人想上告竟然不知为何被他得知，被他活生生劈为两段，死状惨不忍睹，自此人人都噤若寒蝉。要不是看你一身正气，又有一身好武艺，老夫为了老骨头和妻儿性命，也断断不敢告诉你的，你前往那里杀掉展五，他手下小喽啰自然会一哄而散，但且记住，未杀掉之前万万不可来再见老夫，否则老夫恐怕惹来杀生之祸。你杀掉之后先去通知程强，他的弟弟就是被展五给杀害的。\n"ESC"接受任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 12:
        	if( who->get_legend(TASK_46,13)&&!who->get_legend(TASK_46,14) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_46,14);
			who->add_exp(89000);
			who->add_potential(950);
			who->add_cash(91000);
			send_user(who,"%c%s",';',"平阳之乱1 经验 89000 潜能 950 金钱 91000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,69,"" );
			me->do_welcome(11);
        	}
        	break;
        case 13:
        	if ( who->get_legend(TASK_46,14)&&!who->get_legend(TASK_46,15) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->delete_save("qysjianhun");
        		who->delete_save("qysqianhun");
        		who->set_legend(TASK_46,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,70,"平阳之乱2" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"平阳之乱2");
       		}
        	break;
        case 14:
        	if( who->get_legend(TASK_46,16)&&!who->get_legend(TASK_46,17) )
        	{
        		who->delete_save("qysjianhun");
        		who->delete_save("qysqianhun");
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_46,17);
			who->add_exp(88000);
			who->add_potential(910);
			who->add_cash(93000);
			send_user(who,"%c%s",';',"平阳之乱2 经验 88000 潜能 910 金钱 93000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,70,"" );
			me->do_welcome(11);
        	}
        	break;
        case 15:
        	if ( who->get_legend(TASK_46,17)&&!who->get_legend(TASK_46,18) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_46,18);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,71,"平阳之乱3" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"平阳之乱3");
       		}
        	break;
        case 16:
        	if ( who->get_legend(TASK_46,26)&&!who->get_legend(TASK_46,27) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太好了，终于有人来帮我寻药了，你等等我看看差哪些东西。\n"ESC"完成任务\ntalk %x# welcome.17\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_46,27)&&!who->get_legend(TASK_46,28) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近我为秦王赢政炼制丹药，如今差一味鱼龙草，我打听多时方知道那东西乃魂气凝结而成，常常附于箱子等器物中，而诛仙阵二层西部的角落的魂气以及阵方位正好适合此类草的生长，你能帮我取来么，那里环境险恶，老夫实在不能前去，要不恐怕没有进去老骨头就交代了。\n"ESC"接受任务\ntalk %x# welcome.18\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_46,28)&&!who->get_legend(TASK_46,29) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来秦管家不关心大王的丹药，只是敷衍我找了个软脚虾来啊，哼哼，我要让秦管家赶紧给我换人，要么我就上告大王。\n"ESC"离开", me->get_name(),));
        	else if ( who->get_legend(TASK_46,29)&&!who->get_legend(TASK_46,30) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵，秦管家果然找了个利索的人啊，年轻人，以后跟着我做，保你招摇撞骗无往不利！\n"ESC"完成任务\ntalk %x# welcome.19\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_46,30)&&!who->get_legend(TASK_47,1) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    夏侯党是老夫多年知交好友，对于药理药性也颇为了解，老夫唯恐有什么考虑不到之处，你将此配方交与他，询问他的见解，归来告诉我。\n"ESC"接受任务\ntalk %x# welcome.20\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_47,4)&&!who->get_legend(TASK_47,5) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原来如此，幸好事先问过夏侯老弟，要不大王吃下去我万死难辞其咎啊！\n"ESC"完成任务\ntalk %x# welcome.21\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_47,5)&&!who->get_legend(TASK_47,6) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了夏侯老弟的一味点睛之药，我终于可以练成仙丹献与大王了，再等个一日一夜丹药就可以出炉，你代我向夏侯老弟致谢，告诉他出炉之日我请他上紫烟阁喝仙柔醉！\n"ESC"接受任务\ntalk %x# welcome.22\n"ESC"离开", me->get_name(),getoid(me)));
 			
        	break; 
        case 17:
        	if( who->get_legend(TASK_46,26)&&!who->get_legend(TASK_46,27) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_46,27);
			who->add_exp(98000);
			who->add_potential(1010);
			who->add_cash(91000);
			send_user(who,"%c%s",';',"炼药之路1 经验 98000 潜能 1010 金钱 91000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,74,"" );
			me->do_welcome(16);
        	}
        	break;        	
        case 18:
        	if ( who->get_legend(TASK_46,27)&&!who->get_legend(TASK_46,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_46,28);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,75,"炼药之路2" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"炼药之路2");
       		}
        	break;
        case 19:
        	if( who->get_legend(TASK_46,29)&&!who->get_legend(TASK_46,30) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"鱼龙草",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_46,30);
			who->add_exp(89000);
			who->add_potential(990);
			who->add_cash(92000);
			send_user(who,"%c%s",';',"炼药之路2 经验 89000 潜能 990 金钱 92000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,75,"" );
			me->do_welcome(16);
        	}
        	break; 
        case 20:
        	if ( who->get_legend(TASK_46,30)&&!who->get_legend(TASK_47,1) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			TASK_LEGEND_D->give_item(who,"item/98/0232",1);
        		who->set_legend(TASK_47,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,76,"炼药之路3" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"炼药之路3");
       		}
        	break;
        case 21:
        	if( who->get_legend(TASK_47,4)&&!who->get_legend(TASK_47,5) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"月见草",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64188",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_47,5);
			who->add_exp(88000);
			who->add_potential(910);
			who->add_cash(93000);
			send_user(who,"%c%s",';',"炼药之路4 经验 88000 潜能 910 金钱 93000 破云行装图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,77,"" );
			me->do_welcome(16);
        	}
        	break;        	
        case 22:
        	if ( who->get_legend(TASK_47,5)&&!who->get_legend(TASK_47,6) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_47,6);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,78,"炼药之路5" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"炼药之路5");
       		}
        	break;
        }
}