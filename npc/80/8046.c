
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

void do_welcome(string arg);

//void do_task_finish();
int get_char_picid() { return 5401; }
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
// 函数：构造处理
void create()
{
        set_name("Sở Quản Gia");
        set_city_name("Sở Quốc");

	set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//	set("level",11);
//	set("legend",({32*3+5,}));
	set("mpLegend",([10:({32*3+5}),]));
	set("mpLegend2",([0:({32*50+27}),10:({32*3+6}),]));
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
	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,6) )
		tmp += sprintf(ESC HIY "消灭四脚蛇\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( who->get_legend(TASK_2_00,26) && !who->get_legend(TASK_2_00,27) ) 
		tmp += sprintf(ESC HIY "给楚管家的口信\ntalk %x# welcome.4\n",getoid(this_object()));
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
        int flag, date , status, p, z, x, y, i;
        object who, obj, item;
        string *nTmp,tmp;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,5) )
        		send_user(who,"%c%s",':',sprintf("%s:\n    不知何故，最近华山一带出现了许多四脚蛇，并且还常常袭击过往的旅人和商队。这些该死的畜生严重地阻碍了本府与桃源村正常的商路交往！老爷已经发出悬赏，召集所有的志士前去清剿那些害虫。你也有兴趣加入吗？本府一定会重重有赏的。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
        	else if( who->get_save_2("sijiaose") >= 18 )
        		send_user(who,"%c%s",':',sprintf("%s:\n    相当不错！如此一来我们与桃源村的交通便可畅通无阻了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),getoid(me)));
		else
        		send_user(who,"%c%s",':',sprintf("%s:\n    付出了这么多的银子还没有人能杀掉那些该死的害虫！？不杀够十八只四脚蛇的话一文钱也休想拿到！\n"ESC"离开",me->get_name()));
        	break;
        case 2:
        	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,5) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,3,"消灭四脚蛇" );	
        		who->set_legend(TASK_NEWBIE_03,5);
        		send_user( who, "%c%s", '!', "得到任务 "HIY"消灭四脚蛇");
        	}
        	break;
        case 3:
        	if( !who->get_legend(TASK_NEWBIE_03,6) && who->get_save_2("sijiaose") >= 18  )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,2) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/final/33/1771",2);
//        		nTmp = WEAPON_FILE->get_family_equip("",0,10,WAIST_TYPE);
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),0,10,WAIST_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		item = new(tmp);
        		if ( !item )
        			return;
			ITEM_EQUIP_D->init_equip_prop_1(item);
        		p = item->move(who,-1);
        		if ( !p )
        		{
				send_user( who, "%c%s", '!', "您身上没有空位！");
				destruct(item);
				return;	
        		}
        		item->add_to_user(p);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_03, 6);
			who->delete_save_2("sijiaose");
			who->add_exp(400);
			who->add_potential(40);
			who->add_cash(3000);
			send_user(who,"%c%s",';',sprintf("消灭四脚蛇 经验 400 潜能 40 金钱 3000 %s 1 地瓜解暑汤 2",item->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,3,"" );	        			
        	}
        	break;
	case 4:
		if ( who->get_legend(TASK_2_00,26) && !who->get_legend(TASK_2_00,27) ) 
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    这么多年了没想到周王还记得我，真是让我感动不已。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),getoid(me)));
		break;
        case 5:
		if ( who->get_legend(TASK_2_00,26) && !who->get_legend(TASK_2_00,27) ) 
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_2_00,27);
			who->add_exp(600);
			who->add_potential(35);
			who->add_cash(1000);
			send_user(who,"%c%s",';',sprintf("给楚管家的口信 经验 600 潜能 35 金钱 1000"));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,22,"" );
		}
        	break;
        }
}