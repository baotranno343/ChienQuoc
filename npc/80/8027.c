
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 7805; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Hứa Thị");
        set_city_name("Ngụy Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",25);
//	set("legend",({32*6+16,32*6+19}));
 	set("mpLegend",([25:({32*6+16,32*6+19}),]));
 	set("mpLegend2",([25:({32*6+18,32*6+21,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, this_object() ); 
		return ;
	}
        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, this_object() ); 
		return ;
	}        
	
        tmp += CHAIN_D->get_chain_menu(who,this_object());
	if ( ( who->get_level() >= 20 && !who->get_legend(TASK_06,16) ) || ( who->get_legend(TASK_06,16) && !who->get_legend(TASK_06,18) ) )
		tmp += sprintf(ESC HIY "山谷里的回音\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( ( who->get_level() >= 20 && !who->get_legend(TASK_06,19) ) || ( who->get_legend(TASK_06,19) && !who->get_legend(TASK_06,21) ) )
		tmp += sprintf(ESC HIY "神灵的怨恨\ntalk %x# welcome.4\n",getoid(this_object()));

	send_user(who,"%c%s",':',sprintf( "%s：\n    %s\n", get_name(), TalkTable[ random(sizeof(TalkTable))] ) 
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
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,16)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    易水闹鬼，你听说过吗？\n    最初听人说起易水闹鬼，我还不太相信，可是前段日子我在易水的狼牙山采药，听见山谷传来阵阵鬼哭狼嚎，我往那山谷里望了一眼，居然看到有一个山洞前迷雾着团团黑烟，那阵阵的回音似乎就从山洞里传来的，我清楚的记得，这可不是山洞里的普通动物在叫唤，很奇怪的声音，一直在山谷里回荡，我吓得当时就跑下山，后来听说那一带有个幽明鬼魂经常出来害人，你能将它除掉吗？\n    穿过桂陵、平原就到易水了，你快去快回吧。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_06,16) && !who->get_legend(TASK_06,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我以后再也不能去狼牙山采药了，稍不小心被鬼缠上可就不得了了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_06,17) && !who->get_legend(TASK_06,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可好了，以后可以安安心心去那里采药了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,16)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_06,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,24,"山谷里的回音" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"山谷里的回音");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_06,17) && !who->get_legend(TASK_06,18) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),0,20,NECK_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_06,18);
			who->add_exp(1700);
			who->add_potential(70);
			who->add_cash(1500);
			send_user(who,"%c%s",';',sprintf("山谷里的回音 经验 1700 潜能 70 金钱 1500 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,24,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,19)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    易水的神灵真是个仁慈之人，那夜明鬼实在是太过分，他从最开始的捉弄发展到恶意的骚扰，搅得神灵鸡犬不宁，依神灵的本事完全可以将他“喀嚓”掉，但是神灵很仁慈，不想用武力解决问题，找他谈了好几次，他都无动于衷，我只是一个局外人，可神灵受如此欺负，实在是看不下去，易水的神灵是专门负责保护那里百姓的神，为了百姓，你将那个夜明鬼赶走吧。\n    从桂陵、平原过去就到易水了。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_06,19) && !who->get_legend(TASK_06,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下那里的百姓可要遭殃了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_06,20) && !who->get_legend(TASK_06,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    易水神灵得到安宁，那里的百姓也可以安宁了。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 5:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,19)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_06,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,25,"神灵的怨恨" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"神灵的怨恨");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_06,20) && !who->get_legend(TASK_06,21) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/65010",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_06,21);
			who->add_exp(1800);
			who->add_potential(60);
			who->add_cash(1300);
			send_user(who,"%c%s",';',"神灵的怨恨 经验 1800 潜能 60 金钱 1300 金项链图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,25,"" );
        	}
        	break;
        }
}