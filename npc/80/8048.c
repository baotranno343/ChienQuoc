
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
int get_char_picid() { return 5505; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Đinh Hạc Niên");
        set_city_name("Yên Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",94);
//	set("legend",({32*32+26}));
 	set("mpLegend",([90:({32*32+26}),]));
 	set("mpLegend2",([0:({32*33+6}),90:({32*32+28}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	int id;
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
	id = getoid(this_object());
        tmp += CHAIN_D->get_chain_menu(who,this_object());
	if ( ( who->get_level() >= 90 && !who->get_legend(TASK_32,26) ) || ( who->get_legend(TASK_32,26) && !who->get_legend(TASK_32,28) ) )
		tmp += sprintf(ESC HIY "祖父的遗产\ntalk %x# welcome.1\n",id);
	if ( who->get_legend(TASK_33,5) && !who->get_legend(TASK_33,6) )
		tmp += sprintf(ESC HIY "祖父的遗产\ntalk %x# welcome.1\n",getoid(this_object()));

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
	string *nTmp,tmp;
        
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,26)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听我父亲说，我祖父当年也是个非常了不起的英雄，可惜不知为何客死他乡，临死之前委托故人传来一帛书，居中画着一个骷髅，周围画中隐含着我们家族才懂的密语，翻译过来就是困魔阵三层魔神祭坛。我想一切秘密都在那里了，可惜我祖父临去只是我父亲尚在从军，没能够及时起出遗物，后来父亲年老还乡已经没有力气去寻了，我作为他唯一的儿子，势必要弄清楚当年事情的原委，但是可惜我父亲却没能学到祖父本事的十之一二，而我天生体弱，更不能习武，最近与壮士把腕论交，颇为相得，不知能否帮我起出祖父遗物，追查当年真相？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_32,26) && !who->get_legend(TASK_32,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    莫非我真看错了你，你竟然隐匿了我祖父的宝物？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_32,27) && !who->get_legend(TASK_32,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    噢，金钥匙!，可以卖好多钱了，那张什么书你自己留着看吧，当我送你了！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_33,5) && !who->get_legend(TASK_33,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我等了你好久，你终于给我带来了好消息，之后的事情可能得需要我自己去办了，多谢你的帮忙。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,26)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_32,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,49,"祖父的遗产（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"祖父的遗产（1）");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_32,27) && !who->get_legend(TASK_32,28) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"金钥匙",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_32,28);
			who->add_exp(36000);
			who->add_potential(630);
			who->add_cash(33000);
			send_user(who,"%c%s",';',"祖父的遗产（1） 经验 36000 潜能 630 金钱 33000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,49,"" );
			me->do_welcome(1);
        	}
        	break;
        case 4:
        	if ( who->get_legend(TASK_33,5) && !who->get_legend(TASK_33,6) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),90,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"遗产的宝箱",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,tmp,1);    
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_33,6);
			who->add_exp(160000);
			who->add_potential(2000);
			who->add_cash(150000);
			send_user(who,"%c%s",';',sprintf("祖父的遗产（4） 经验 160000 潜能 2000 金钱 150000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,34,"" );
        	}
        	break;
        }

}
