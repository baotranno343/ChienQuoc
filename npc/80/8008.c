
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
void do_welcome(string arg);


//void do_task_finish();
int get_char_picid() { return 5401; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tề Quản Gia");
        set_city_name("Tề Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));
//	set("level",102);
//	set("legend",({32*36+23}) );
 	set("mpLegend",([100:({32*36+23}),110:({32*44+13})]));
 	set("mpLegend2",([100:({32*36+25,}),110:({32*39+6,32*44+15,32*44+23,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string tmp="";
	
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}
        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}        
	

        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( who->get_level() >= 110 && who->get_legend(TASK_39,5) && !who->get_legend(TASK_39,6) )
		tmp += sprintf(ESC HIY "手巧的工匠\ntalk %x# welcome.1\n",getoid(me));

	if ( (who->get_level() >=100 && !who->get_legend(TASK_36,23)) || (who->get_legend(TASK_36,23) && !who->get_legend(TASK_36,25)) )
		tmp += sprintf(ESC HIY "叛徒\ntalk %x# welcome.3\n",getoid(me));
	if ( (who->get_level() >= 110 && !who->get_legend(TASK_44,13)) || (who->get_legend(TASK_44,13) && !who->get_legend(TASK_44,15)) )
		tmp += sprintf(ESC HIY "锻炼身体\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_legend(TASK_44,15) && !who->get_legend(TASK_44,16) )
		tmp += sprintf(ESC HIY "游历\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_legend(TASK_44,22) && !who->get_legend(TASK_44,23) )
		tmp += sprintf(ESC HIY "策略\ntalk %x# welcome.6\n",getoid(me));

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
        int flag,i,size,p,amount;
        object who,item, *inv;     
       	string *nTmp,tmp;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
		if ( who->get_level() >= 110 && who->get_legend(TASK_39,5) && !who->get_legend(TASK_39,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    果然没有找错人，我早就听说Ngụy Quốc工匠手艺不错，果然不失所望啊！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 110 && who->get_legend(TASK_39,5) && !who->get_legend(TASK_39,6) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"首饰箱",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_39,6);
			who->add_exp(50000);
			who->add_potential(615);
			who->add_cash(48000);
			send_user(who,"%c%s",';',"手巧的工匠 经验 50000 潜能 615 金钱 48000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,68,"" );
        	}
        	break; 
        case 3:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,23)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我晕我晕我晕晕晕，Tần Quốc也太牛了吧，居然能够让人变身为怪物？嘘，这可是顶级机密，前段时间听闻有大战，而跑到Tần Quốc去避难的百姓不知道受了什么蛊惑，有些接受了Tần Quốc的特殊训练，居然能够维持一段时间的怪物外形，又潜回我Quốc九曲桥附近为Tần Quốc做内应，孰可忍，孰不可忍！一定要让他们知道叛徒的下场，一定要彻底摧毁Tần Quốc的这个阴谋！你看到那些像破罐子一样的东西了吗？是的，你去杀掉它们，你干掉10只罐中仙，我倒要看看，Tần Quốc还有什么招术！\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_36,23) && !who->get_legend(TASK_36,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不要管他们是不是Tề Quốc百姓，记住，叛Quốc者死！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_36,24) && !who->get_legend(TASK_36,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    叛徒死不足惜，我倒要看看，Tần Quốc还有什么招术！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 4:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,23)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_36,23);
        		who->delete_save("qgjguanzx");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,57,"叛徒" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"叛徒");
        	}
        	break;
	case 5:
        	if ( who->get_legend(TASK_36,24) && !who->get_legend(TASK_36,25) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_36,25);
        		who->delete_save("qgjguanzx");
			who->add_exp(80000);
			who->add_potential(955);
			who->add_cash(70000);
			send_user(who,"%c%s",';',"叛徒 经验 80000 潜能 955 金钱 70000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,57,"" );
        	}
        	break; 
	case 6:
		if ( who->get_level() >= 110 && !who->get_legend(TASK_44,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看你走路昂首阔步，一定觉得自己已经不错了吧，但是年轻人，百炼才能成钢，趁年轻多经历风雨，多历练些总是好的，看样子你练功已经遇到瓶颈了吧，听闻上古遗阵诛仙阵里多有上古仙兵凝结成的魂气，对于你现在的成长是很有好处的，可能还有意料之外的收获哦。\n    你先去消灭刀魂、剑魂各8只证明证明自己的能力吧。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_44,13) && !who->get_legend(TASK_44,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    莫非你的修为只是投机取巧么？连去诛仙阵的胆气都没有了？练功首先要练心，你现在练心都做不到，怎么能指望突破瓶颈呢？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_44,14) && !who->get_legend(TASK_44,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    年轻人，此番诛仙阵之行获益匪浅吧，孺子可教也，如果你还想再接再厉，还可以来找我。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_44,15) && !who->get_legend(TASK_44,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在天下七分，困守一地无异于故步自封，你得趁年轻到处看看，汲取各地军事文化的精髓，方能够高屋建瓴，得到更大的发展，光从军事领域来说，Tần Quốc无疑是现在最强的Quốc家，而秦长城在抵御外虏的作用上是首屈一指的，若是抛除Quốc籍的成见，驻守的蒙恬、王离将军对于避免Quốc民遭受外虏侵袭上可是功不可没。如今秦赵交恶，我也不能给你更多指引，听闻秦总管善待有才之士，你去问问他秦长城的情况，应该他会乐于介绍，不至于难为你。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_44,22) && !who->get_legend(TASK_44,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此番游历，获益匪浅吧，来来来，我们细细谈谈……\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));

		break;
        case 7:
        	if ( who->get_level() >= 110 && !who->get_legend(TASK_44,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_44,13);
        		who->delete_save("qgjdaohun");
        		who->delete_save("qgjjianhun");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,64,"热心的建议（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"热心的建议（1）");
        	}
        	break;         	
	case 8:
        	if ( who->get_legend(TASK_44,14) && !who->get_legend(TASK_44,15) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_44,15);
        		who->delete_save("qgjdaohun");
        		who->delete_save("qgjjianhun");
			who->add_exp(51000);
			who->add_potential(778);
			who->add_cash(50300);
			send_user(who,"%c%s",';',"热心的建议（1） 经验 51000 潜能 778 金钱 50300");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,64,"" );
	      		me->do_welcome(6);
	      	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_44,15) && !who->get_legend(TASK_44,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_44,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,65,"热心的建议（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"热心的建议（2）");
        	}
        	break; 
	case 10:
        	if ( who->get_legend(TASK_44,22) && !who->get_legend(TASK_44,23) )
        	{
			if ( !sizeof(who->get_fam_name()) )
			{
				send_user(who,"%c%s",'!',"无门无派可交不了任务哦～");
				return;	
			}
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),110,BOOTS_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_44,23);
        		who->delete_save("qzgdismzs");
        		who->delete_save("qzgtaijmzs");
        		who->delete_save("qzgjinj");
        		who->delete_save("qzgdaohun");
			who->add_exp(51000);
			who->add_potential(778);
			who->add_cash(50300);
			send_user(who,"%c%s",';',sprintf("热心的建议（4） 经验 230000 潜能 2400 金钱 220000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,62,"" );
	      	}
        	break;
        }

}
