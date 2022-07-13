
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 6; }
// 有自己的do_look函数
int is_self_look() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return 5403; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Y Dược");
        set_city_name("Tân Thủ Thôn");

        set_2( "good", ([
                "01" : "/item/91/9100",
                "02" : "/item/91/9101",
                "03" : "/item/91/9110",
                "04" : "/item/91/9111",
                "05" : "/item/stuff/0106",
        ]) );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level", 2);
//        set("legend", ({ 42 }));
	set("mpLegend",([0:({32*49+21,}),]));
	set("mpLegend2",([0:({32*48+10,32*49+23}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	"/quest/help"->send_help_tips(who, 42);
	result = sprintf(" %s :\n "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
//	if ( (who->get_legend(TASK_NEWBIE_01, 7) && !who->get_legend(TASK_NEWBIE_01, 8))||(who->get_legend(TASK_NEWBIE_01, 8) && !who->get_legend(TASK_NEWBIE_01, 9)) )
	if ( who->get_legend(TASK_48, 9) && !who->get_legend(TASK_48, 10) )
	{
		result = result + sprintf( ESC  +HIY+ "Ngọc bội gia tộc\ntalk %x# welcome.1\n", getoid(me) );
	}
//	if ( !who->get_legend(TASK_NEWBIE_01, 11) )
	if ( who->get_legend(TASK_48, 10) && !who->get_legend(TASK_48, 11) )
	{
		result = result + sprintf( ESC  +HIY+ "探望病人\ntalk %x# welcome.3\n", getoid(me) );
	}
	if ( who->get_legend(TASK_48, 11) && !who->get_legend(TASK_48, 12) )
	{
		result = result + sprintf( ESC  +HIY+ "探望病人\ntalk %x# welcome.13\n", getoid(me) );
	}
        if( who->get_legend(TASK_40, 24) && !who->get_legend(TASK_40, 25) )
		result += sprintf(ESC +HIY+ "索要灵芝草\ntalk %x# welcome.5\n",getoid(me));
        if( (who->get_legend(TASK_40, 25) && !who->get_legend(TASK_40, 26)) || (who->get_legend(TASK_40, 27) && !who->get_legend(TASK_40, 28)) )
		result += sprintf(ESC +HIY+ "头疼的毛病\ntalk %x# welcome.5\n",getoid(me));
	if ( !who->get_legend(TASK_49,21)||( who->get_legend(TASK_49,22) && !who->get_legend(TASK_49,23) ) )
		result +=  sprintf(ESC +HIY+ "消灭稻草人\ntalk %x# welcome.9\n",getoid(me));

	result = result + sprintf( ESC "Giao dịch\nlist %x#\n" ESC "Ta chỉ tiện xem qua\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%s", ':', result );

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
        string cmd1, cmd2, cmd3, cmd4, cmd5, result;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
//		if ( who->get_legend(TASK_NEWBIE_01, 8) && !who->get_legend(TASK_NEWBIE_01, 9))
		if ( who->get_legend(TASK_48,9) && !who->get_legend(TASK_48, 10))
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf(" %s :\n Vài hôm trước có vài người kì quái nói với ta, vài ngày nữa sẽ có một người gọi là %s đem Gia Tộc Ngọc Bội đã thất lạc của ta đếm tìm, cuối cùng cũng đến, chính là ngươi ! Quá tốt rồi, ta thật lòng hậu tạ ngươi !\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.2\n",me->get_name(),who->get_name(),getoid(me)));
//		else if ( (who->get_legend(TASK_NEWBIE_01, 7) && !who->get_legend(TASK_NEWBIE_01, 8)))
//			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    是不是那个奇怪的人叫你来的？看见我的家族玉佩了吗？\n"ESC"离开",me->get_name(),));
		break;
	case 2 :
//		if ( !who->get_legend(TASK_NEWBIE_01, 8) || who->get_legend(TASK_NEWBIE_01, 9))
//			return ;
//		if ( who->get_legend(TASK_48,9) && objectp( item = present("Gia Tộc Ngọc Bội", who, 1, MAX_CARRY) ))
		if ( who->get_legend(TASK_48,9) && !who->get_legend(TASK_48, 10))
		{
			if( !objectp( item = present("Gia Tộc Ngọc Bội", who, 1, MAX_CARRY) ) || item->is_xunbao() != 1 )
			{
				send_user(who,"%c%s",'!',"你的家族玉佩呢?");
				return;
			}
	
			item->remove_from_user();
			destruct(item);			
				
			item = new( "/item/86/9999" );
//			if ( !item )
//				return ;
//			item->set_amount(10);
	                p =item->move(who, -1);
	                if ( p == 0 )
	                {
	                	destruct(item); 
	                	send_user( who, "%c%s", '!', "您身上没有足够的空位！");
	                	return ;
	                }	
	                item->add_to_user(p);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_48, 10);
			who->add_exp(260);
			who->add_potential(30);
			who->add_cash(500);
			send_user(who,"%c%s",';',"Gia Tộc Ngọc Bội Kinh nghiệm 260 Tiềm năng 30 Ngân lượng 500 Tân Thủ Hạng Liên 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,104,"" );			
		me->do_welcome(3);
		}
		break;
	case 3:
		if ( who->get_legend(TASK_48, 10) )
		{
				send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    前几天来了个重病之人，我给他开了几副药就叫人送回去了，他已是病入膏肓，可怜呀，不知他现在情况如何，这事也只有驿站老板能打听得到，他那里每天来来往往的人比较多，消息很灵通，劳驾你替我跑上这一趟，很近，就在我南边。\n"ESC"接受任务\ntalk %x# welcome.4\n",me->get_name(),getoid(me)));
		}
		break;
	case 13:
		if ( who->get_legend(TASK_48, 11) )
		{
				send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    驿站老板怎么说？打听到他的消息了吗？我准备给他捎点药过去呢，你可得尽快，别耽误了别人治病！\n"ESC"离开",me->get_name()));
		}
		break;
	case 4:
//		if ( !who->get_legend(TASK_NEWBIE_01, 10) )
		if ( who->get_legend(TASK_48, 10) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_48, 11);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,105,"Thăm Bệnh Nhân" );
			send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Thăm Bệnh Nhân"NOR".");
		}			
		break;
	case 5:
		if( who->get_legend(TASK_40, 24) && !who->get_legend(TASK_40, 25) )
			send_user(who,"%c%s",':',sprintf("%s:\n    灵芝草何等珍贵，怎能说给就给！要灵芝草是要付出代价的，你想好了再来找我吧。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开",me->get_name(),getoid(me)));
		else if( who->get_legend(TASK_40, 25) && !who->get_legend(TASK_40, 26) )
			send_user(who,"%c%s",':',sprintf("%s:\n    其实我的要求并不高，前几天一群小野兔来我这里捣蛋，将我的药物全部弄洒，并且还偷走了一部分很名贵的药品，当时我只忙着去治疗一位病人去了，没来得及教训它们，后来看到一片狼藉，真是气死我了。\n    我想必须得教训它们，它们才有可能收敛，你去替我办这件事吧，你能办到的话，我一定会将灵芝草交给你。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开",me->get_name(),getoid(me)));
		else if( who->get_legend(TASK_40, 27) && !who->get_legend(TASK_40, 28) )
			send_user(who,"%c%s",':',sprintf("%s:\n    还算你遵守诺言，给我教训了它们，那我当然也不会食言，你拿着这颗灵芝草交给当铺老板去吧！\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开",me->get_name(),getoid(me)));
			
		break;
	case 6:
		if( who->get_legend(TASK_40, 24) && !who->get_legend(TASK_40, 25) )
		{
			who->add_exp(150);
			who->add_potential(20);
			send_user(who,"%c%s",';',"头疼的毛病（1） 经验 150 潜能 20");
			who->set_legend(TASK_40, 25);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,24,"" );
			me->do_welcome(5);
		}
		break;	
	case 7:
        	if ( who->get_legend(TASK_40, 25) && !who->get_legend(TASK_40, 26) )
        	{
        		who->set_legend(TASK_40,26);
        		who->delete_save("ydlbxiaoyt");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,25,"头疼的毛病（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"头疼的毛病（2）");
        	}
        	break;
        case 8:
        	if ( who->get_legend(TASK_40,27) && !who->get_legend(TASK_40,28) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/98/0198",1);
			who->set_legend(TASK_40,28);
        		who->delete_save("ydlbxiaoyt");
			who->add_exp(300);
			who->add_potential(30);
			who->add_cash(1800);
			send_user(who,"%c%s",';',"头疼的毛病（2） 经验 300 潜能 30 金钱 1800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,26,"头疼的毛病（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"头疼的毛病（3）");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,25,"" );
        	}
        	break;   
        case 9:
		if( !who->get_legend(TASK_49, 21) )
        		send_user(who,"%c%s",':',sprintf("%s\n    怪事年年有，今年特别多。新手村外那些稻草人原来不过是农夫扎来吓唬麻雀，保护农田的装饰，没想到现在居然都活了。昨天村外的李大叔下地劳动，还被一个稻草人袭击扭伤了腰。你看起来好象懂点武艺，去消灭3个稻草人，替李大叔出口气。\n"ESC"接受\ntalk %x# welcome.10\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_49, 22) && !who->get_legend(TASK_49, 23) )
        		send_user(who,"%c%s",':',sprintf("%s\n    这么快就做完了，年轻人武艺不错，将来一定大有前途。你好象受伤了，这些行军散拿去用吧。\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开",me->get_name(),getoid(me)));
        	break;
	case 10:
		if( !who->get_legend(TASK_49, 21) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_49, 21);
			who->delete_save("yaodian_daocaoren");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,47,"消灭稻草人" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"消灭稻草人");	
		}
		break;
	case 11:
		if ( who->get_legend(TASK_49, 22) && !who->get_legend(TASK_49, 23) )
		{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;
			TASK_LEGEND_D->give_item(who,"item/91/9100",5); 
			TASK_LEGEND_D->task_finish(who);
			who->delete_save("yaodian_daocaoren");
			who->add_exp(150);
			who->add_potential(20);
			who->add_cash(500);
			who->set_legend(TASK_49, 23);
			send_user(who,"%c%s",';',"消灭稻草人 经验150 潜能25 金钱500 行军散5");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,47,"" );			
		}
		break;
	}
}	  