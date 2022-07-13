
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
void do_task_start();
void do_task_cancel();

// 函数：获取人物造型
int get_char_picid() { return 5401; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tần Tổng Quản");
        set_city_name("Tần Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
	set("mpLegend2",([0:({32*22+9,32*22+12,32*44+17,32*44+20,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who ) 
{
	string tmp="";
	object me=this_object();
	if ("/sys/task/master"->do_look_quest10(who, me)>0) return;
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}
        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了 //国
        {
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}        
	
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( who->get_legend(TASK_22,8) && !who->get_legend(TASK_22,9 ) )
		tmp += sprintf(ESC HIY "道听途说\ntalk %x# welcome.1\n",getoid(me));
	if ( (who->get_legend(TASK_22,9) && !who->get_legend(TASK_22,10)) || (who->get_legend(TASK_22,10) && !who->get_legend(TASK_22,12)) )
		tmp += sprintf(ESC HIY "证实传闻\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_22,12) && !who->get_legend(TASK_22,13) )
		tmp += sprintf(ESC HIY "牵连之罪\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_44,16) && !who->get_legend(TASK_44,17) )
		tmp += sprintf(ESC HIY "游历\ntalk %x# welcome.6\n",getoid(me));
	if ( (who->get_legend(TASK_44,17) && !who->get_legend(TASK_44,18)) || (who->get_legend(TASK_44,18) && !who->get_legend(TASK_44,20)) )
		tmp += sprintf(ESC HIY "细心\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_legend(TASK_44,20) && !who->get_legend(TASK_44,21) )
		tmp += sprintf(ESC HIY "策略\ntalk %x# welcome.6\n",getoid(me));

	send_user(who,"%c%s",':',sprintf( "%s：\n    %s\n", get_name(), TalkTable[ random(sizeof(TalkTable))] ) 
			+ tmp +
			ESC"离开"
			);

}

// 函数：开始任务
// void do_task_start() { TASK_ESCORT_D->do_task_start( this_player(), this_object() ); }
// 函数：取消任务
// void do_task_cancel() { TASK_ESCORT_D->do_task_cancel( this_player(), this_object() ); }

int accept_money(object who, int gold)
{
	return "/sys/task/master"->accept_money(this_object(), who, gold);
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
		if ( who->get_legend(TASK_22,8) && !who->get_legend(TASK_22,9 ) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呃……（一脸为难状），壮士片刻后前来，我必将给你一个答复。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_22,9) && !who->get_legend(TASK_22,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，这位壮士我也不瞒你了，秦宫的确时有妖魔作祟，似乎有一个柔媚的男子迷住了我们的太子殿下，可是王后找来的道士去指出他是千年树妖所化，而太子殿下却极力护住他，反而将那道士赶出宫去，不过架不住我们王后隔三茬五的找来不同的会些道术的人暗地里对付他，而那千年树妖所化成的美男子在破了几个会些道术人的法之后可能觉得秦宫非久留之地，径自离开了，但是王后仍旧发现太子殿下常常会找借口出宫去到秦长城匝道一带，有人发现原来太子殿下还是与千年树妖所化的男子在一起，而那些自称的道术大家又不是那个树妖的对手，敢问壮士可能斩妖除魔，救我们的太子殿下？\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_22,10) && !who->get_legend(TASK_22,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此树妖不除，恐怕秦宫将永无安宁之日。\n"ESC"离开", me->get_name()));
         	else if ( who->get_legend(TASK_22,11) && !who->get_legend(TASK_22,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……本官一定会上奏大王重谢于你。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_22,12) && !who->get_legend(TASK_22,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王得知树妖长时间与太子殿下在秦长城幽会而自己士兵全部装聋作哑，而不劝回王子，诛杀树妖时，感觉到非常震怒，他下令赐死秦长城上10个Tần Quốc刀盾兵、10个Tần Quốc枪兵、10个Tần Quốc弓兵以儆效尤。杀完之后报Tần Quốc典狱官备案。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
          		
        	break; 
        case 2:
        	if ( who->get_legend(TASK_22,8) && !who->get_legend(TASK_22,9 ) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,9);
			who->add_exp(22000);
			who->add_potential(410);
			who->add_cash(21000);
			send_user(who,"%c%s",';',"道听途说 经验 22000 潜能 410 金钱 21000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,43,"" );
			me->do_welcome(1);
        	}
        	break;         	
        case 3:
        	if ( who->get_legend(TASK_22,9) && !who->get_legend(TASK_22,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_22,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,44,"证实传闻" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"证实传闻");
        	}
        	break; 
        case 4:
        	if ( who->get_legend(TASK_22,11) && !who->get_legend(TASK_22,12 ) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,12);
			who->add_exp(23000);
			who->add_potential(430);
			who->add_cash(23000);
			send_user(who,"%c%s",';',"证实传闻 经验 23000 潜能 430 金钱 23000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,44,"" );
			me->do_welcome(1);
        	}
        	break;    
        case 5:
        	if ( who->get_legend(TASK_22,12) && !who->get_legend(TASK_22,13) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->delete_save_2("qzgdaodunbing");
			who->delete_save_2("qzgqiangbing");
			who->delete_save_2("qzggongbing");
        		who->set_legend(TASK_22,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,45,"牵连之罪" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"牵连之罪");
        	}
        	break; 
	case 6:
		if ( who->get_legend(TASK_44,16) && !who->get_legend(TASK_44,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不知道你周游列国感想如何？光就招贤纳士的政策来说我们大王是最开明的，哪怕凡夫走卒只要有能力我们大王都是唯才是举，不知道你可愿意为我去办件小事？\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_44,17) && !who->get_legend(TASK_44,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    ŪȡɋԽҪԐըʶìԐՄzìϸфҲۜטҪìࠀìʏՎϒȥׯЉֳѰ֒ĳٶҸܪքʱ۲޹ȻԶսʏڅїܪȮǦì܅æ֮Ђֻփԃ؉ѐݞƜ·ìܘ4עЖёزɋݻպϒȥǫںٺòքșѦիքѥۨ֫ٸִ՚ńٶއäìɧޱزɋږدìϒÿɕܘݒּܡ񶌽һٶʱӽӔʏքزɋŮפճרìࠠһ߰ҔìЖ՚߼ҩţքܺܡսìɧڻţŜȥսׯЉֳһӣһ͋ٸϒ֒ܘѥۨ֫ìߍ֤ķţߟѸϸф֢ٶ͵ݾcţࠉփߴؐϸìܲѭߍ՚ĳٶѦФocoĦքնܪݣܪۜԐݫݰսքɎێ֫Ϸ؅޸ѦФӘǰ4ք|ۃϰڟì̻ćӔΪ؅޸ѦФ֫Ϸߍˇؔܺքì̹ӔҪСф̻ćք٥ܷìׁԚׯЉֳߍ՚Փ̫٫خì޸ȥ۳һֱιǰ؟ìۜɝӗߍעЖìҲѭߍ՚ŇٶٸքƔҟìʏՎߍ՚ŇoԶսŇٶїܪȮǦքìһڽţ؅фì̻ˇһܡԶЖքìӲΪ̻Oճߝ˵ӑޭё̼˕ܘȥc\n"ESC"ޓ˜Ɏϱ\ntalk %x# welcome.8\n"ESC"kߪ", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_44,18) && !who->get_legend(TASK_44,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    年轻人，你的细心呢？我对你的前途不看好哦。（凑近耳边）小子给我快点啊，你看本总管的耳朵上的老茧多厚了，你都不知道体恤一下老人！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_44,19) && !who->get_legend(TASK_44,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不错不错，年轻人，你够胆，够博，够细，你想想还差什么吧，想好了再来找我，我们大王最喜欢你这种进取的年轻人了，如果你都具备了各种条件，说不定封候拜相也是指日可待！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_44,20) && !who->get_legend(TASK_44,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我们大王赏识的人，除了有胆识、有阅历、细心之外，还需要谋略，现在地煞门、太极门匪类聚众在天门阵对抗国家，骚扰百姓，实乃一大祸害，现今我国军队无暇顾及这些匪类，这就要看你能不能运用谋略，击杀地煞门、太极门众守各8个，虚陵洞金精10个，刀魂4个，并且能全身而退，待得你成功之后，去找齐管家老儿吧，并且对他说，本总管谢谢他送来这么个壮士，他的良苦用心本总管明白。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
			
		break;
	case 7:
        	if ( who->get_legend(TASK_44,16) && !who->get_legend(TASK_44,17) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_44,17);
			who->add_exp(48000);
			who->add_potential(750);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"热心的建议（2） 经验 48000 潜能 750 金钱 50000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,65,"" );
	      		me->do_welcome(6);
	      	}
        	break;
	case 8:
        	if ( who->get_legend(TASK_44,17) && !who->get_legend(TASK_44,18) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_44,18);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,61,"热心的建议（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"热心的建议（3）");
        	}
        	break;
	case 9:
        	if ( who->get_legend(TASK_44,19) && !who->get_legend(TASK_44,20) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"秦总管的绣花针",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_44,20);
			who->add_exp(51000);
			who->add_potential(778);
			who->add_cash(50300);
			send_user(who,"%c%s",';',"热心的建议（3） 经验 51000 潜能 778 金钱 50300");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,61,"" );
	      		me->do_welcome(6);
	      	}
        	break;        	 
	case 10:
        	if ( who->get_legend(TASK_44,20) && !who->get_legend(TASK_44,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_44,21);
        		who->delete_save("qzgdismzs");
        		who->delete_save("qzgtaijmzs");
        		who->delete_save("qzgjinj");
        		who->delete_save("qzgdaohun");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,62,"热心的建议（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"热心的建议（4）");
        	}
        	break;
        }
}