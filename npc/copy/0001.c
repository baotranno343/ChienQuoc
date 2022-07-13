#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>
#include <task.h>

inherit OFFICER;
int host_type;

// 函数:获取人物造型
int get_char_picid() { return 5501; }
void do_welcome(string arg);
void do_accept(string arg);
void do_query(string arg);

// 函数:构造处理
void create()
{
	object me=this_object();
        set_name("Tả Khâu Minh");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
                 "accept"         : (: do_accept :),
                 "query"         : (: do_query :),
        ]) );
        set("legend", ({ 32 }));
        setup();
	host_type = MAIN_D->get_host_type();
}

void do_look(object who)
{
	int id;
	string cmd="";
	object me=this_object();
	id = getoid(me);
	if ( who->get_legend(TASK_2_00,16) && !who->get_legend(TASK_2_00,17) ) 
		cmd = sprintf(ESC HIY "找我谈谈\ntalk %x# welcome.11\n",id);
	if ( who->get_legend(TASK_2_00,17) && !who->get_legend(TASK_2_00,18) ) 
		cmd = sprintf(ESC HIY "拜访周王\ntalk %x# welcome.13\n",id);
	if ( "sys/sys/count"->get_new_story() == 0 )
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Gần đây, ta lấy được một di vật thượng cổ gọi là Phong Yêu Kính. Bên trong kính này đã niêm phong yêu kính và những tàn phách mang theo rất nhiều bảo vật trên người của mấy trăm năm trước đến giờ được sản sinh ra từ cuộc chiến tranh, nếu như lấy một trang bị quý hiếm đốt hóa làm phép trước gương, thì có thể tiến vào hình phản chiếu của Phong Yêu Kính. Nếu như ngươi cũng muốn đến chỗ hình phản chiếu thám hiểm, thì ngươi lấy một trang bị quý giá cho ta, ta giúp ngươi khai thông con đường vào trong hình phản chiếu!\n"+ cmd +ESC"Tiến vào Phong Yêu Kính\ntalk %x# welcome.1\n"ESC"Phong Yêu Kính là gì\ntalk %x# welcome.2\n"ESC"Diệt trừ hình phản chiếu\ntalk %x# welcome.3\n"ESC"Sự thay đổi mới của Phong Yêu Kính\ntalk %x# welcome.20\n"ESC"Rời khỏi",id,id,id,id));
	else
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Gần đây, ta lấy được một di vật thượng cổ gọi là Phong Yêu Kính. Bên trong kính này đã niêm phong yêu kính và những tàn phách mang theo rất nhiều bảo vật trên người của mấy trăm năm trước đến giờ được sản sinh ra từ cuộc chiến tranh, nếu như lấy một trang bị quý hiếm đốt hóa làm phép trước gương, thì có thể tiến vào hình phản chiếu của Phong Yêu Kính. Nếu như ngươi cũng muốn đến chỗ hình phản chiếu thám hiểm, thì ngươi lấy một trang bị quý giá cho ta, ta giúp ngươi khai thông con đường vào trong hình phản chiếu!\n"+ cmd +ESC"Tiến vào Phong Yêu Kính\ntalk %x# welcome.1\n"ESC"Phong Yêu Kính là gì\ntalk %x# welcome.2\n"ESC"Diệt trừ hình phản chiếu\ntalk %x# welcome.3\n"ESC"Sự thay đổi mới của Phong Yêu Kính\ntalk %x# welcome.20\n"ESC"Đúc lại lục đại vũ khí\ntalk %x# welcome.80\n"ESC"Rời khỏi",id,id,id,id,id));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,id,tId,*nXy;
       	object who, item,map;
       	string cTmp,cFile;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 1:
        	tId = who->get_team_id();
        	if ( tId )
        	{
        		map = TEAM_D->get_copy_scene(tId,COPY_MIRROR);
        		if ( map )
        		{
        			if ( who->get_level() < 35 )
        			{
 					send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Trang bị của ngươi không đủ để bước vào cửa thông Phong Yêu Kính, Ngươi đổi một trang bị khác màu xanh có đẳng cấp 35 cho ta!\n"ESC"Hiểu"));
        				return ;	
        			}
        			nXy = map->get("exit");
        			who->add_to_scene(map->get_id(),nXy[0],nXy[1]);
        			return ;
        		}	
        	}
 		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Muốn tiến nhập vào Phong Yêu Kính thì cần phải mở đường thông bước vào Phong Yêu Kính, muốn mở ra đường thông, thì phải cần lấy một trang bị quí hiếm cấp 15 trở lên đốt hóa trở thành chất xúc tác. Ngươi đưa cho ta một trang bị mức quí báu trở lên, ta giúp ngươi đem chúng đốt hóa thành chất xúc tác mở ra đường thông đi vào trong Phong Yêu Kính! Đưa cho ta trang bị, ngươi hiểu không?\n"ESC"Ta hiểu, đưa cho là ALT+G!"));
        	break;
        case 2:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n    Phong Yêu Kính là 1 nơi nguy hiểm, vì thế ta chỉ có thể cho phép nhân vật đạt cấp 35 trở lên tiến vào mà thôy !!\n"ESC"我该给予你什么等级的装备？\ntalk %x# welcome.4\n"ESC"在里面冒险需要注意些什么？\ntalk %x# welcome.5\n"ESC"封妖镜里面我们会有什么挑战？\ntalk %x# welcome.6\n"ESC"Rời khỏi",id,id,id));
        	break;
        case 3:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Nếu như ngươi muốn diệt trừ hình phản chiếu, ngươi có thể lại đưa cho ta một trang bị quí hiếm dùng làm đốt hóa. Thì có thể có Sức mạnh tái sinh hình phản chiếu mới.\n"ESC"Rời khỏi",id,));
        	break;
        case 4:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n    你焚化作为触媒的珍稀装备最少必须是15级以上蓝色程度的装备，而且你给我的装备的等级是很重要，因为用什么等级的装备作为触媒，就会生成对应等级怪物的聚集的镜像。所以你如果想遇到什么等级的妖怪，你就给予我对应等级的装备作为触媒吧！不过你也不必担心，因为里面遇见的一些残魄身上的宝物也很不错，如果你能打倒他，估计在他身上获得的装备也可以和你焚化的装备抵消了。\n"ESC"返回\ntalk %x# welcome.2\n"ESC"Rời khỏi",id,));
        	break;
        case 5:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Bởi vì Phong Yêu Kính là một nơi tà khí rất nặng, cho nên ngươi cần phải ở nơi đó lúc nào cũng phải giữ đoàn kết đội nhóm của ngươi, một khi ngươi trong hình phản chiếu mất đi đội nhóm, thì ngươi sẽ không thể nào lưu lại trong hình phản chiếu đó được nữa.\n"ESC"Quay về\ntalk %x# welcome.2\n"ESC"Rời khỏi",id,));
        	break;
        case 6:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n    据说里面封印了前几百年以来各个被灭掉的诸侯国家的亡灵的镜像，所以你在里面会遇上许多镜妖。而且听说只要你能把里面的镜像妖怪清除到一定比例，就会出现我所说的残魄。打倒这个残魄就可以获得一些不错的收获了！\n"ESC"返回\ntalk %x# welcome.2\n"ESC"Rời khỏi",id,));
        	break;
        case 7:
        	tId = who->get_team_id();
        	if ( tId )
        	{
        		map = TEAM_D->get_copy_scene(tId,COPY_MIRROR);
        		if ( map )
        		{
        			if ( who->get_level() < 35 )
        			{
 					send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Trang bị của ngươi không đủ để bước vào cửa thông Phong Yêu Kính, Ngươi đổi một trang bị khác màu xanh có đẳng cấp 35 cho ta!\n"));
        				return ;	
        			}
        			nXy = map->get("exit");
        			who->add_to_scene(map->get_id(),nXy[0],nXy[1]);
        			return ;
        		}	
        	}
        	break;
	case 11:
		if ( who->get_legend(TASK_2_00,16) && !who->get_legend(TASK_2_00,17) ) 
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    你也听说了封妖镜的传说？没错，这个宝物就在我手中，等你够强以后再来找我，我教你进入封妖镜的方法。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"Rời khỏi",me->get_name(),getoid(me)));
		break;
	case 12:
		if ( who->get_legend(TASK_2_00,16) && !who->get_legend(TASK_2_00,17) ) 
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_2_00,17);
			who->add_exp(300);
			who->add_potential(35);
			who->add_cash(500);
			send_user(who,"%c%s",';',sprintf("拜访左丘明 经验 300 潜能 35 金钱 500"));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,18,"" );
			me->do_welcome(13);
		}
		break;
	case 13:
		if ( who->get_legend(TASK_2_00,17) && !who->get_legend(TASK_2_00,18) ) 
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    战国乱世，群雄并起，昔日的周王室已经失去了号令天下的能力。当今周王姬延顺应世时，推出一套保险系统，希望能改变周国窘迫的现状，你要是有兴趣就去周王那里看看，会对你有好处的。顺着大路一直朝前走，周王就在尽头的宫殿里。\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"Rời khỏi",me->get_name(),getoid(me)));
		break;		
	case 14:
		if ( who->get_legend(TASK_2_00,17) && !who->get_legend(TASK_2_00,18) ) 
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_2_00,18);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"Chu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,19,"拜访周王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"拜访周王");
		}
		break;	
	case 20:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n    由于最近进入封妖镜镜像内的各国勇士不断努力，封妖镜的内的妖气已经开始减弱。现在，我们可以使用更低级的装备打开更高级的封妖镜镜像了。从现在开始，如果你想要打开一个相应等级的镜像，你只要给予我比你想要打开的相应等级镜像低20级的装备就可以了。\n"ESC"具体镜像开启规则？\ntalk %x# welcome.21\n"ESC"镜像内还有其他改变吗？\ntalk %x# welcome.22\n"ESC"返回\ntalk %x# welcome.2\n"ESC"Rời khỏi",id,id,id));
		break;
	case 21:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n    由于封妖镜内的妖气减弱了，所以从现在开始，如果你想要打开一个相应等级的镜像，你只要给予我比你想要打开的相应等级镜像低20级的装备就可以了。例如你要打开一个50级的镜像的话，你只要给我一个30级的蓝色程度以上装备就可以了。但是，我帮你打开的镜像的等级是不会超过你自身的等级的。\n"ESC"返回\ntalk %x# welcome.20\n"ESC"Rời khỏi",id,));
		break;
	case 22:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n    我听说，有的进入开启镜像的勇士最近曾经在把封妖镜内的镜妖全部清除后，遇见过一些称为“镜像首领”的强力镜妖，据说这些镜妖身上同样藏有非常珍贵的宝物。据我了解这个消息应该不假，勇士你不妨去尝试一下。\n"ESC"返回\ntalk %x# welcome.20\n"ESC"Rời khỏi",id,));
		break;
	case 80:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Theo truyền thuyết bên trong Phong Yêu Kính tiềm tàng 6 loại vũ khí lớn uy lực kinh người, nếu như ngươi có vật liệu tương ứng; ta có thể giúp ngươi đúc lại sáu loại vũ khí này!\n"ESC"Đúc lại Ngọc Thần Bảo Kiếm\ntalk %x# welcome.81\n"ESC"Đúc lại Thiên Tôn Bảo Đao\ntalk %x# welcome.82\n"ESC"Đúc lại Chân Quân Xí Diệm Thương\ntalk %x# welcome.83\n"ESC"Đúc lại Càn Khôn Vô Cấp Côn\ntalk %x# welcome.84\n"ESC"Đúc lại Bích Hỏa Hàn Nguyệt Hoàn\ntalk %x# welcome.85\n"ESC"Đúc lại Anh Kiệt Quyền Nhẫn\ntalk %x# welcome.86\n"ESC"Rời khỏi",id,id,id,id,id,id,));
		break;
	case 81:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Đúc lại Ngọc Thần Bảo Kiếm, vật liệu cần là một cây Ngọc Kiếm, 30 viên Lỗ Ban Bảo Thạch, 20 viên Đá Càn Khôn, 20 viên Đá Tương Uyên, nếu như ngươi có đủ vật liệu, ta có thể giúp ngươi đúc lại Ngọc Thần Bảo Kiếm.\n"ESC"Nộp vật liệu\ntalk %x# welcome.811\n"ESC"Vật liệu có thể tìm được ở đâu?\ntalk %x# welcome.812\n"ESC"Rời khỏi",id,id));
		break;
	case 82:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n    Đúc lại Thiên Tôn Bảo Đao, vật liệu cần là một cây Kim Đao, 30 viên Lỗ Ban Bảo Thạch, 20 viên Đá Càn Khôn, 20 viên Đá Tương Uyên, nếu như ngươi có đủ vật liệu, ta có thể giúp ngươi đúc lại Thiên Tôn Bảo Đao\n"ESC"Nộp vật liệu\ntalk %x# welcome.821\n"ESC"材料在哪里可以找到？\ntalk %x# welcome.822\n"ESC"Rời khỏi",id,id));
		break;
	case 83:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Đúc lại Chân Quân Xí Diệm Thương, vật liệu cần là một cây Xích Anh Thương, 30 viên Lỗ Ban Bảo Thạch, 20 viên Đá Càn Khôn, 20 viên Đá Tương Uyên, nếu như ngươi có đủ vật liệu, ta có thể giúp ngươi đúc lại Chân Quân Xí Diệm Thương.\n"ESC"Nộp vật liệu\ntalk %x# welcome.831\n"ESC"Vật liệu có thể tìm được ở đâu?\ntalk %x# welcome.832\n"ESC"Rời khỏi",id,id));
		break;				
	case 84:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Đúc lại Càn Khôn Vô Cấp Côn, vật liệu cần là Cổ Phương Côn, 30 viên Lỗ Ban Bảo Thạch, 20 viên Đá Càn Khôn, 20 viên Đá Tương Uyên, nấu như ngươi có đủ vật liệu, ta có thể giúp ngươi đúc lại Càn Khôn Vô Cấp Côn.\n"ESC"Nộp vật liệu\ntalk %x# welcome.841\n"ESC"Vật liệu có thể tìm được ở đâu?\ntalk %x# welcome.842\n"ESC"Rời khỏi",id,id));
		break;
	case 85:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n    Đúc lại Bích Hoả Hàn Nguyệt Hoàn, vật liệu cần là một cây Nguyệt Hoàn, 30 viên Lỗ Ban Bảo Thạch, 20 viên Đá Càn Khôn và 20 viên Đá Tương Uyên, nếu như ngươi có đủ vật liệu, ta có thể giúp ngươi đúc lại Bích Hoả Hàn Nguyệt Hoàn.\n"ESC"Nộp vật liệu\ntalk %x# welcome.851\n"ESC"材料在哪里可以找到？\ntalk %x# welcome.852\n"ESC"Rời khỏi",id,id));
		break;
	case 86:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n    Đúc lại Anh Kiệt Quyền Nhẫn, vật liệu cần là 1 cây Thạch Điêu Quyền Nhẫn, 30 viên Lỗ Ban Bảo Thạch, 20 viên Đá Càn Khôn, 20 viên Đá Tương Uyên, nếu như ngươi có đủ vật liệu, ta có thể giúp ngươi đúc lại Anh Kiệt Quyền Nhẫn\n"ESC"Nộp vật liệu\ntalk %x# welcome.861\n"ESC"材料在哪里可以找到？\ntalk %x# welcome.862\n"ESC"Rời khỏi",id,id));
		break;		
	case 811:
	case 821:
	case 831:
	case 841:
	case 851:
	case 861:
		if ( flag == 811 )
		{
			cTmp = "Ngọc Kiếm";
			cFile = "item/73/9075";
		}
		else if ( flag == 821 )
		{
			cTmp = "Kim Đao";
			cFile = "item/72/9075";
		}
		else if ( flag == 831 )
		{
			cTmp = "Xích Anh Thương";
			cFile = "item/74/9075";
		}
		else if ( flag == 841 )
		{
			cTmp = "Cổ Phương Côn";
			cFile = "item/75/9075";
		}
		else if ( flag == 851 )
		{
			cTmp = "Nguyệt Hoàn";
			cFile = "item/71/9075";
		}
		else if ( flag == 861 )
		{
			cTmp = "Thạch Điêu Quyền Nhẫn";
			cFile = "item/70/9075";
		}
		if ( TASK_LEGEND_D->check_task_item_amount(who,cTmp) == 0 ||
			TASK_LEGEND_D->check_task_item_amount(who,"Lỗ Ban Bảo Thạch") < 30 ||
			TASK_LEGEND_D->check_task_item_amount(who,"Đá Càn Khôn") < 20 ||
			TASK_LEGEND_D->check_task_item_amount(who,"Đá Tương Uyên") < 20 )
		{
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n Đúc lại %s cần một cây %s , 30 viên Lỗ Ban Bảo Thạch, 20 viên Đá Càn Khôn, 20 viên Đá Tương Uyên, hình như trên người của ngươi không đủ vật liệu?\n"ESC"Rời khỏi",cFile->get_name(),cTmp));
			return ;	
		}
		TASK_LEGEND_D->check_task_item1(who,cTmp,1);
		TASK_LEGEND_D->check_task_item1(who,"Lỗ Ban Bảo Thạch",30);
		TASK_LEGEND_D->check_task_item1(who,"Đá Càn Khôn",20);
		TASK_LEGEND_D->check_task_item1(who,"Đá Tương Uyên",20);
		item = new(cFile);
		item->set_hide(0);
		item->set_bind(1);
		i = item->move2(who,-1);
		if ( !i )
		{
			destruct(item);
			return ;	
		}
		item->add_to_user(i);
		send_user(who,"%c%s",';',"Chúc mừng bạn đạt được thần khí "HIR+item->get_name());
		break;
	case 812:
	case 822:
	case 832:
	case 842:
	case 852:
	case 862:
		if ( flag == 812 )
			cTmp = "Ngọc Kiếm";
		else if ( flag == 822 )
			cTmp = "Kim Đao";
		else if ( flag == 832 )
			cTmp = "Xích Anh Thương";
		else if ( flag == 842 )
			cTmp = "Cổ Phương Côn";
		else if ( flag == 852 )
			cTmp = "Nguyệt Hoàn";
		else if ( flag == 862 )
			cTmp = "Thạch Điêu Quyền Nhẫn";
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Tả Khâu Minh:\n %s ngươi có thể giành được thông qua việc đánh bại quái vật cấp thủ lĩnh xuất hiện trong Phong Yêu Kính gần đây; Lỗ Ban Bảo Thạch nghe nói là có rất nhiều ở cửa hiệu vàng bạc châu báu nào đó; Đá Càn Khôn ngươi có thể chiến đấu trong Phong Yêu Kính tùy cơ đạt được; Đá Tương Uyên người chỉ cần đánh bại quái vật mạnh trong Phong Yêu Kính, thì có thể lấy được.\n"ESC"Rời khỏi",cTmp));
		break;
        }

}

int accept_object(object who, object item)
{
	return "/sys/copy/mirror"->accept_object(this_object(),who,item);
}

void do_accept( string arg )
{
	"/sys/copy/mirror"->do_accept(this_object(),this_player(),arg);
}

void do_query( string arg )
{
	"/sys/copy/mirror"->do_query(this_object(),this_player(),arg);
}
