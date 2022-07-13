/*------------------------------------
	NPC Can Tương by Ben
	item/sell/6032 : Tái tạo thạch
------------------------------------*/	
#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 9959; }
void do_welcome(string arg);
void do_nhannv(string arg);
void do_accept(string arg);
int is_cantuong_nangcaptb() { return 1; }
void create()
{	  
        set_name("Can Tương");
		set_real_name("Thiên Địa Đại Sư");
		set_2( "talk", ([
                "welcome"	:( : do_welcome :),
				"giaotrangbi"         : (: do_accept :),
				"nhannv"         : (: do_nhannv :),
             ]));
        setup();

}
void do_nhannv( string arg )
{
	"/sys/user/cantuong"->do_gift(this_player(),this_object(),arg);
}
void do_welcome( string arg )
{
	__FILE__->do_welcome2(this_object(),arg);
}
void do_welcome2( object npc, string arg )
{
	int flag,p,i,size,sao,ben,ben123,s;
	object player  = this_player(),item,item2,item3;
	string name,name2,name3,name4,thanbinh,ss,forge="",nhat123,nhat1234;
	flag = to_int(arg);
	switch(flag)
	{
		case 1:
	        send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(),sprintf(npc->get_name() + ":\n"+"Nếu muốn trang bị tốt hơn hiện tại, có thể đến gặp ta. Ta sẽ giúp ngươi rèn lại trang bị, nếu may mắn, ngươi có thể đạt được trang bị tinh luyện vượt mức đến 8 sao. Tuy nhiên điều này còn tuỳ thuộc vào vận may nữa, ta không dám nói trước.\n" 
	        ESC "ALT+G để giao trang bị\ntalk %x# welcome.200\n"
			ESC "Thoát ra\nCLOSE\n",getoid(npc))); 
			break;
		case 200:
	        send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(),npc->get_name() + ":\n"+"Sử dụng ALT + G để đưa trang bị cho tôi !\n" 
	        ESC "Ta hiểu rồi\nCLOSE\n"
			ESC "Thoát ra\nCLOSE\n");	
			break;
		case 300:
	        send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(),sprintf(npc->get_name() + ":\n"+"Thần binh tuyệt thế tưởng chừng chỉ là vũ khí có trong truyền thuyết, nhưng ngươi biết không? Nó có thật đấy! Nếu ngươi có trong tay Thần Binh Phổ, hãy mang đến đây, ta sẽ đúc nó cho ngươi.\n" 
	        ESC "Đúc thần binh Trụ Thiên Quyền Thủ\ntalk %x# welcome.1001\n"
	        ESC "Đúc thần binh Đoạt Mệnh Ma Khí\ntalk %x# welcome.1002\n"
	        ESC "Đúc thần binh Càn Khôn Vân Đao\ntalk %x# welcome.1003\n"
	        ESC "Đúc thần binh Huyết Lệ\ntalk %x# welcome.1004\n"
	        ESC "Đúc thần binh Phá Thiên Thương\ntalk %x# welcome.1005\n"
	        ESC "Đúc thần binh Hoả Thiên Côn\ntalk %x# welcome.1006\n"
	        ESC "%s\ntalk %x# nhannv.100\n"
			ESC "Thoát ra\nCLOSE\n",getoid(npc),getoid(npc),getoid(npc),getoid(npc),getoid(npc),getoid(npc),
			player->get_save_2("cantuong.status")<1?HIG"Nhận nhiệm vụ tìm kiếm Thần Binh Phổ":HIC"Nhiệm vụ tìm kiếm Thần Binh Phổ",
			getoid(npc),getoid(npc)));	
			break;
		case 400:
			send_user( player, "%c%c%d", 0x60, 10, getoid(npc) );
			break;
   	/*	case 5:
			send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(),sprintf(npc->get_name() + ":\n"+"Ngoài chức năng phân giải Đoạn Thạch thành các viên Tái Tạo Thạch, ta còn mở thêm chức năng ngược lại giúp cho người chơi có thể dễ dàng trao đổi, giao dịch, mua bán Đoạn Thạch một cách tiện lợi nhất ! Nào ngươi muốn tham gia chức năng này không ?\n" 
	        ESC "1 Tái Tạo Thạch lấy Sơ Cấp Đoạn Thạch\ntalk %x# welcome.501\n"
	        ESC "2 Tái Tạo Thạch lấy Trung Cấp Đoạn Thạch\ntalk %x# welcome.502\n"
	        ESC "3 Tái Tạo Thạch lấy Cao Cấp Đoạn Thạch\ntalk %x# welcome.503\n"
			ESC "Thoát ra\nCLOSE\n",getoid(npc),getoid(npc),getoid(npc),getoid(npc),getoid(npc),getoid(npc)));
			break; 
		case 6:
			send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(),sprintf(npc->get_name() + ":\n"+"Ta sẽ giúp ngươi tách Đoạn Thạch cấp cao thành cấp thấp nếu ngươi cảm thấy có quá nhiều Đoạn Thạch cấp cao ! Nào ngươi muốn tham gia chức năng này không ?\n" 
	        ESC "Tách Cao Cấp Thành 2 Trung Cấp\ntalk %x# welcome.601\n"
	        ESC "Tách Trung Cấp Thành 2 Sơ Cấp\ntalk %x# welcome.602\n"
//	        ESC "3 Tái Tạo Thạch lấy Cao Cấp Đoạn Thạch\ntalk %x# welcome.503\n"
			ESC "Thoát ra\nCLOSE\n",getoid(npc),getoid(npc),getoid(npc),getoid(npc),getoid(npc),getoid(npc)));
			break; */
	/*	case 501:	
		case 502:	
		case 503:	
			if ( flag==501 ){ben123=1;nhat123="Tái Tạo Thạch";nhat1234="item/sell/0032";}
			else if ( flag==502 ){ben123=2;nhat123="Tái Tạo Thạch";nhat1234="item/sell/1032";}
			else if ( flag==503 ){ben123=3;nhat123="Tái Tạo Thạch";nhat1234="item/sell/2032";}
		if( USER_INVENTORY_D->get_free_count(player) < 1 )
		{
			send_user(player,"%c%c%w%s",':',3,9959, "Can Tương: \nHành trang của ngươi không đủ 1 ô trống, hãy thu xếp hành trang rồi đến gặp ta ! \n"ESC"Xác nhận");
			return;
		}
			if ( TASK_LEGEND_D->check_task_item_amount(player,nhat123) < ben123 )
			{
				send_user(player,"%c%c%w%s",':',3,9959, "Can Tương: \nNgươi không có đủ "+ben123+" Tái Tạo Thạch ! \n"ESC"Xác nhận");
				return;
			}
			TASK_LEGEND_D->check_task_item1(player,nhat123,ben123);
			item=new(nhat1234);
			p=item->move2(player,-1);
			item->add_to_user(p);
			send_user(player,"%c%c%w%s",':',3,9959, "Can Tương: \nNgươi nhận được "+item->get_name()+", "+nhat123+" của ngươi bị trừ đi "+ben123+" viên ! \n"ESC"Xác nhận");
			break; */
	/*	case 601:	
		case 602:		
			if ( flag==601 ){ben123=1;nhat123="Cao Cấp Đoạn Thạch";nhat1234="item/sell/1032";}
			else if ( flag==602 ){ben123=1;nhat123="Trung Cấp Đoạn Thạch";nhat1234="item/sell/0032";}
		if( USER_INVENTORY_D->get_free_count(player) < 2 )
		{
			send_user(player,"%c%c%w%s",':',3,9959, "Can Tương: \nHành trang của ngươi không đủ 2 ô trống, hãy thu xếp hành trang rồi đến gặp ta ! \n"ESC"Xác nhận");
			return;
		}
			if ( TASK_LEGEND_D->check_task_item_amount(player,nhat123) < ben123 )
			{
				send_user(player,"%c%c%w%s",':',3,9959, "Can Tương: \nNgươi không có đủ "+nhat123+"  ! \n"ESC"Xác nhận");
				return;
			}
			TASK_LEGEND_D->check_task_item1(player,nhat123,ben123); 
			item=new(nhat1234);
			p=item->move2(player,-1);
			item->add_to_user(p);
	
			item2=new(nhat1234);
			s=item2->move2(player,-1);
			item2->add_to_user(s);
			send_user(player,"%c%c%w%s",':',3,9959, "Can Tương: \nNgươi đã Tách thành công! Chúc mừng!\n"ESC"Xác nhận");
			break; */
			
		case 1001:	
		case 1002:	
		case 1003:	
		case 1004:	
		case 1005:	
		case 1006:
			if ( flag==1001 ){ben=2001;name = "Ngọc La Quyền Thủ";name2 = "Trụ Thiên Quyền Thủ";name3 = sprintf("Thần Binh Phổ - %s",name2);}
			else if ( flag==1002 ){ben=2002;name = "Thần Tiên Hạc Kim";name2 = "Đoạt Mệnh Ma Khí";name3 = sprintf("Thần Binh Phổ - %s",name2);}
			else if ( flag==1003 ){ben=2003;name = "Đao Tử Vân";name2 = "Càn Khôn Vân Đao";name3 = sprintf("Thần Binh Phổ - %s",name2);}
			else if ( flag==1004 ){ben=2004;name = "Lục Tiên Kiếm";name2 = "Huyết Lệ";name3 = sprintf("Thần Binh Phổ - %s",name2);}
			else if ( flag==1005 ){ben=2005;name = "Lục Thần Thương";name2 = "Phá Thiên Thương";name3 = sprintf("Thần Binh Phổ - %s",name2);}
			else if ( flag==1006 ){ben=2006;name = "Phàn Thiên Côn";name2 = "Hoả Thiên Côn";name3 = sprintf("Thần Binh Phổ - %s",name2);}
			if ( !objectp( item = present(name, player, 1, MAX_CARRY*4) ) )
			{
				send_user(player,"%c%c%w%s",':',3,9959, sprintf("Can Tương: \nNgươi không có trong tay thần binh %s, không thể đúc Tuyệt thế thần binh %s ! \n"ESC"Xác nhận",name,name2));
				return;
			}
			if ( TASK_LEGEND_D->check_task_item_amount(player,name) > 1 )
			{
				send_user(player,"%c%c%w%s",':',3,9959, sprintf("Can Tương: \nHành trang của ngươi quá có nhiều %s, ta không thể phân biệt được vũ khí nào mới là vũ khí mà ngươi ưng ý nhất ! \n"ESC"Xác nhận",name));
				return;
			}
			ss = item->get("forge");
			sao = strlen(ss);
			if ( TASK_LEGEND_D->check_task_item_amount(player,name3) < 1 ||
			TASK_LEGEND_D->check_task_item_amount(player,"Tái Tạo Thạch") < (sao+1)*12 ||
			TASK_LEGEND_D->check_task_item_amount(player,"Lỗ Ban Bảo Thạch") < 300 )
			{
				send_user(player,"%c%c%w%s",':',3,9959,sprintf("Can Tương: \n Nguyên liệu của ngươi không đủ! Đúc %s cần các loại nguyên liệu sau:\n "+name+", %s"NOR ", %s"NOR ", %s"NOR ".\n"ESC"Rời khỏi",
				name2,TASK_LEGEND_D->check_task_item_amount(player,"Lỗ Ban Bảo Thạch")<300?HIR "300 viên Lỗ Ban":"300 viên Lỗ Ban",
				TASK_LEGEND_D->check_task_item_amount(player,"Tái Tạo Thạch")<(sao+1)*12?sprintf(HIR "%d Tái Tạo Thạch",(sao+1)*12):sprintf("%d Tái Tạo Thạch",(sao+1)*12),
				TASK_LEGEND_D->check_task_item_amount(player,name3)<1?HIR+name3:name3));
				return ;	
			}
		if( USER_INVENTORY_D->get_free_count(player) < 1 )
		{
			send_user(player,"%c%c%w%s",':',3,9959, "Can Tương: \nHành trang của ngươi không đủ 1 ô trống, hãy thu xếp hành trang rồi đến gặp ta ! \n"ESC"Xác nhận");
			return;
		}
			send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(),sprintf(npc->get_name() + ":\n"+"Ngươi xác nhận phải đúc ra một Thần binh tuyệt thế %s không ?\n" 
	        ESC "Xác nhận\ntalk %x# welcome.%d\n"
			ESC "Huỷ bỏ\nCLOSE\n",name2,getoid(npc),ben));	
			break;
		case 2001:	
		case 2002:	
		case 2003:	
		case 2004:	
		case 2005:	
		case 2006:
			if ( flag==2001 ){name = "Ngọc La Quyền Thủ";name2 = "Trụ Thiên Quyền Thủ";name3 = sprintf("Thần Binh Phổ - %s",name2);thanbinh = "/item/70/9130";}
			else if ( flag==2002 ){name = "Thần Tiên Hạc Kim";name2 = "Đoạt Mệnh Ma Khí";name3 = sprintf("Thần Binh Phổ - %s",name2);thanbinh = "/item/71/9130";}
			else if ( flag==2003 ){name = "Đao Tử Vân";name2 = "Càn Khôn Vân Đao";name3 = sprintf("Thần Binh Phổ - %s",name2);thanbinh = "/item/72/9130";}
			else if ( flag==2004 ){name = "Lục Tiên Kiếm";name2 = "Huyết Lệ";name3 = sprintf("Thần Binh Phổ - %s",name2);thanbinh = "/item/73/9130";}
			else if ( flag==2005 ){name = "Lục Thần Thương";name2 = "Phá Thiên Thương";name3 = sprintf("Thần Binh Phổ - %s",name2);thanbinh = "/item/74/9130";}
			else if ( flag==2006 ){name = "Phàn Thiên Côn";name2 = "Hoả Thiên Côn";name3 = sprintf("Thần Binh Phổ - %s",name2);thanbinh = "/item/75/9130";}
			if ( !objectp( item = present(name, player, 1, MAX_CARRY*4) ) )
			{
				send_user(player,"%c%c%w%s",':',3,9959, sprintf("Can Tương: \nNgươi không có trong tay thần binh %s, không thể đúc Tuyệt thế thần binh %s ! \n"ESC"Xác nhận",name,name2));
				return;
			}
			if ( TASK_LEGEND_D->check_task_item_amount(player,name) > 1 )
			{
				send_user(player,"%c%c%w%s",':',3,9959, sprintf("Can Tương: \nHành trang của ngươi quá có nhiều %s, ta không thể phân biệt được vũ khí nào mới là vũ khí mà ngươi ưng ý nhất ! \n"ESC"Xác nhận",name));
				return;
			}
			ss = item->get("forge");
			sao = strlen(ss);
			if ( TASK_LEGEND_D->check_task_item_amount(player,name3) < 1 ||
			TASK_LEGEND_D->check_task_item_amount(player,"Tái Tạo Thạch") < (sao+1)*12 ||
			TASK_LEGEND_D->check_task_item_amount(player,"Lỗ Ban Bảo Thạch") < 300 )
			{
				send_user(player,"%c%c%w%s",':',3,9959,sprintf("Can Tương: \n Nguyên liệu của ngươi không đủ! Đúc %s cần các loại nguyên liệu sau:\n "+name+", %s"NOR ", %s"NOR ", %s"NOR ".\n"ESC"Rời khỏi",
				name2,TASK_LEGEND_D->check_task_item_amount(player,"Lỗ Ban Bảo Thạch")<300?HIR "300 viên Lỗ Ban":"300 viên Lỗ Ban",
				TASK_LEGEND_D->check_task_item_amount(player,"Tái Tạo Thạch")<(sao+1)*12?sprintf(HIR "%d Tái Tạo Thạch",(sao+1)*12):sprintf("%d Tái Tạo Thạch",(sao+1)*12),
				TASK_LEGEND_D->check_task_item_amount(player,name3)<1?HIR+name3:name3));
				return ;	
			}
		if( USER_INVENTORY_D->get_free_count(player) < 1 )
		{
			send_user(player,"%c%c%w%s",':',3,9959, "Can Tương: \nHành trang của ngươi không đủ 1 ô trống, hãy thu xếp hành trang rồi đến gặp ta ! \n"ESC"Xác nhận");
			return;
		}	
		TASK_LEGEND_D->check_task_item1(player,name3,1);
		TASK_LEGEND_D->check_task_item1(player,"Tái Tạo Thạch",(sao+1)*12);
		TASK_LEGEND_D->check_task_item1(player,"Lỗ Ban Bảo Thạch",300);
			CHAT_D->sys_channel(0,sprintf("Can Tương vừa từ lò rèn lấy ra một Tuyệt thế thần binh "HIR "%s"NOR ", đưa cho %s. Đất trời bỗng rung chuyển dữ dội, phải chăng sắp có đại loạn?",name2,player->get_name()));
			send_user(player,"%c%s",';',sprintf("Bạn nhận được Tuyệt thế thần binh "HIY"%s"NOR " !",name2));
			send_user(player,"%c%c%w%s",':',3,9959, sprintf("Can Tương: \nXin chúc mừng! Ngươi đã đúc được Tuyệt thế thần binh %s ! \n"ESC"Xác nhận\nCLOSE\n"ESC"Rời khỏi",name2));
		item2 = new(thanbinh);
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item2);
			forge += "1";
			item2->set("forge", forge);
		}
		item2->set_hide(0);
		p = item2->move2(player,-1);
		item2->add_to_user(p);
			item->remove_from_user();
			destruct(item);
			break;	
	}
}
void do_look( object player )
{
	object npc = this_object();
	
	send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(), sprintf( "%s :\n"+"Xưa đại sư Âu Dã Tử rèn kiếm, quặng sắt không chảy phải để một người phụ nữ nhảy vào lò thì việc rèn sau mới thành công. Ngươi hiểu ý nghĩa của việc này chứ? Haha! \n"
        ESC "Rèn lại trang bị\ntalk %x# welcome.1\n"
        ESC "Đúc Tuyệt thế thần binh\ntalk %x# welcome.300\n"
	//	ESC "Tách Đoạn Thạch\ntalk %x# welcome.6\n"
        ESC HIC"Phân giải Đoạn Thạch\ntalk %x# welcome.400\n"
     //  ESC HIG"Đổi Đoạn Thạch\ntalk %x# welcome.5\n"
        ESC "Rời khỏi\nCLOSE\n", npc->get_name(), getoid(npc), getoid(npc), getoid(npc), getoid(npc) ) );
}
// 函数：用锻造石生成蓝色装备
void sosao( object item )
{
	int pos, family, level, ran, i, less, value, point, begin, end;
	string forge;
        if( !clonep(item) ) return;    // 只对复制物品！
        forge = item->get("forge");
        if (forge==0) level = 0;
        else level = strlen(forge);
        begin = 100; end = 100;
        for (i=4;i<level;i++) 
        {
        	begin  = begin * 6 / 5;
        }
        switch(item->get_equip_type())
        {
        case WEAPON_TYPE:
        	switch(level)
        	{
        	case 0:
        		item->add("ap2", 20);
        		item->add("cp2", 20);
        		break;
        	case 1:
        		item->add("ap2", 25);
        		item->add("cp2", 25);
        		break;
        	case 2:
        		item->add("ap2", 45);
        		item->add("cp2", 45);
        		break;
        	case 3:
        		item->add("ap2", 50);
        		item->add("cp2", 50);
        		break;
        	default:
        		item->add("ap2", (80+item->get_level()/2)*begin/end);
        		item->add("cp2", (80+item->get_level()/2)*begin/end);
               		break;      		        		        		        		        		
        	}
        	break;
        case ARMOR_TYPE:
        	switch(level)
        	{
        	case 0:
        		item->add("dp2", 10);
        		item->add("pp2", 10);
        		item->add("hp2", 30);
        		break;
        	case 1:
        		item->add("dp2", 13);
        		item->add("pp2", 13);
        		item->add("hp2", 40);
        		break;
        	case 2:
        		item->add("dp2", 23);
        		item->add("pp2", 23);
        		item->add("hp2", 70);
        		break;
        	case 3:
        		item->add("dp2", 30);
        		item->add("pp2", 30);
        		item->add("hp2", 100);
        		break;
        	default:
       			item->add("dp2", (45+item->get_level()/5)*begin/end);
        		item->add("pp2", (45+item->get_level()/5)*begin/end);
        		item->add("hp2", (180+item->get_level())*begin/end);
        		break;
        	}
        	break;    
        case HEAD_TYPE:
        	switch(level)
        	{
        	case 0:
        		item->add("dp2", 10);
        		item->add("pp2", 10);
        		break;
        	case 1:
        		item->add("dp2", 13);
        		item->add("pp2", 13);
        		break;
        	case 2:
        		item->add("dp2", 23);
        		item->add("pp2", 23);
        		break;
        	case 3:
        		item->add("dp2", 30);
        		item->add("pp2", 30);
        		break;
        	default:
        		item->add("dp2", (45+item->get_level()/5)*begin/end);
        		item->add("pp2", (45+item->get_level()/5)*begin/end);
        		break;      		        		        		        		        		
        	}
        	break;   
        case BOOTS_TYPE:      
        	switch(level)
        	{
        	case 0:
        		item->add("dp2", 10);
        		item->add("pp2", 10);
        		item->add("sp2", 10);
        		break;
        	case 1:
        		item->add("dp2", 13);
        		item->add("pp2", 13);
        		item->add("sp2", 15);
        		break;
        	case 2:
        		item->add("dp2", 23);
        		item->add("pp2", 23);
        		item->add("sp2", 25);
        		break;
        	case 3:
        		item->add("dp2", 30);
        		item->add("pp2", 30);
        		item->add("sp2", 35);
        		break;
        	default:
        		item->add("dp2", (45+item->get_level()/5)*begin/end);
        		item->add("pp2", (45+item->get_level()/5)*begin/end);
        		item->add("sp2", (60+item->get_level()/5)*begin/end);
        		break;      		        		        		        		        		
        	}
        	break;              
        case WAIST_TYPE:   	
        	switch(level)
        	{
        	case 0:
        		item->add("dp2", 5);
        		item->add("pp2", 5);
        		item->add("hp2", 50);
        		item->add("mp2", 70);
        		break;
        	case 1:
        		item->add("dp2", 8);
        		item->add("pp2", 8);
        		item->add("hp2", 60);
        		item->add("mp2", 80);
        		break;
        	case 2:
        		item->add("dp2", 13);
        		item->add("pp2", 13);
        		item->add("hp2", 110);
        		item->add("mp2", 150);
        		break;
        	case 3:
        		item->add("dp2", 18);
        		item->add("pp2", 18);
        		item->add("hp2", 150);
        		item->add("mp2", 200);
        		break;
        	default:
        		item->add("dp2", (30+item->get_level()/5)*begin/end);
        		item->add("pp2", (30+item->get_level()/5)*begin/end);
        		item->add("hp2", (270+item->get_level())*begin/end);
        		item->add("mp2", (360+item->get_level())*begin/end);
        		break;     		        		        		        		        		
        	}
        	break;     
        case NECK_TYPE:    
        	switch(level)
        	{
        	case 0:
        		item->add("ap2", 10);
        		item->add("cp2", 10);
        		break;
        	case 1:
        		item->add("ap2", 15);
        		item->add("cp2", 15);
        		break;
        	case 2:
        		item->add("ap2", 25);
        		item->add("cp2", 25);
        		break;
        	case 3:
        		item->add("ap2", 30);
        		item->add("cp2", 30);
        		break;
        	default:
        		item->add("ap2", (50+item->get_level()/2)*begin/end);
        		item->add("cp2", (50+item->get_level()/2)*begin/end);
        		break;      		        		        		        		        		
        	}
        	break;            
        }
}

// 函数:接受物品
int accept_object( object who, object item ){ return __FILE__ ->accept_object_callout( this_object(), who, item ); }

// 函数:接受物品(在线更新)
int accept_object_callout( object me, object who, object item )
{
    int level, p, i, t1, t2, t3, t4, mau, cap, cap1, cap2;
	object item2;
	string sao,ngoc;
        me->to_front_eachother(who);
	if( !item->is_equip() ) return 0;
	if( item->is_equip())
	{
		i=item->get_equip_type();
		if ( i!=WEAPON_TYPE&&i!=ARMOR_TYPE&&i!=HEAD_TYPE&&i!=BOOTS_TYPE&&i!=WAIST_TYPE&&i!=NECK_TYPE) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Can Tương:\nNgươi giao cho ta không phải là trang bị hoặc vũ khí !!!\n"ESC"Xác nhận");
			return -99;
			}
	}
	sao = item->get("forge");
	cap = strlen(sao);
	ngoc = item->get("make");
	cap1 = strlen(ngoc);
	cap2 = item->get_level();
	mau = item->get_item_color();			
	if( item->get_hide() > 0 ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nHãy giám định %s trước khi Tinh luyện !!!\n"ESC"Xác nhận",item->get_name() ));
			return -99;
			}
	if ( mau==1 ) {		
	if( cap < 1 ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nTrang bị %s của ngươi chưa đạt 1 ngôi sao, không thể rèn !!!\n"ESC"Xác nhận",item->get_name() ));
			return -99;
			}
	if( who->get_cash() <  ( cap2*25000/cap )  ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nNgươi không có đủ %d lượng để Rèn lại %s !!!\n"ESC"Xác nhận",( cap2*25000/cap ),item->get_name() ));
			return -99;
			}	
	if ( TASK_LEGEND_D->check_task_item_amount(who,"Tái Tạo Thạch") < 6 ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nNgươi không có đủ 6 Tái Tạo Thạch cần dùng cho việc rèn trang bị !!!\n"ESC"Xác nhận" ));
			return -99;
			}				
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nRèn lại %s cần tiêu hao %d lượng, người muốn rèn không  ?\n"ESC"Xác nhận\ntalk %x# giaotrangbi.%x#\n"ESC"Huỷ bỏ",item->get_name(), ( cap2*25000/cap ) ,getoid(me),getoid(item)));		
	
	}
	else if ( mau==2 ) {		
	if( cap < 1 ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nTrang bị %s của ngươi chưa đạt 1 ngôi sao, không thể rèn !!!\n"ESC"Xác nhận",item->get_name() ));
			return -99;
			}
	if( who->get_cash() <  ( cap2*25000/cap )  ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nNgươi không có đủ %d lượng để Rèn lại %s !!!\n"ESC"Xác nhận",( cap2*25000/cap ),item->get_name() ));
			return -99;
			}	
	if ( TASK_LEGEND_D->check_task_item_amount(who,"Tái Tạo Thạch") < 6 ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nNgươi không có đủ 6 Tái Tạo Thạch cần dùng cho việc rèn trang bị !!!\n"ESC"Xác nhận" ));
			return -99;
			}				
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nRèn lại %s cần tiêu hao %d lượng, người muốn rèn không  ?\n"ESC"Xác nhận\ntalk %x# giaotrangbi.%x#\n"ESC"Huỷ bỏ",item->get_name(), ( cap2*25000/cap ) ,getoid(me),getoid(item)));		
	
	}
	else if ( mau==3 ) {		
	if( cap < 1 ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nTrang bị %s của ngươi chưa đạt 1 ngôi sao, không thể rèn !!!\n"ESC"Xác nhận",item->get_name() ));
			return -99;
			}
	if( who->get_cash() <  ( cap2*25000/cap )  ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nNgươi không có đủ %d lượng để Rèn lại %s !!!\n"ESC"Xác nhận",( cap2*25000/cap ),item->get_name() ));
			return -99;
			}	
	if ( TASK_LEGEND_D->check_task_item_amount(who,"Tái Tạo Thạch") < 6 ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nNgươi không có đủ 6 Tái Tạo Thạch cần dùng cho việc rèn trang bị !!!\n"ESC"Xác nhận" ));
			return -99;
			}				
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nRèn lại %s cần tiêu hao %d lượng, người muốn rèn không  ?\n"ESC"Xác nhận\ntalk %x# giaotrangbi.%x#\n"ESC"Huỷ bỏ",item->get_name(), ( cap2*25000/cap ) ,getoid(me),getoid(item)));		
	
	}
	else if ( mau==4 ) {
		if ( item->get_equip_type()==WEAPON_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Vũ khí "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==ARMOR_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Y phục "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==HEAD_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Nón "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==BOOTS_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Giày "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==WAIST_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Yêu đới "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==NECK_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Hạng liên "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
	}
	else if ( mau==0 ) {
		if ( item->get_equip_type()==WEAPON_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Vũ khí "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==ARMOR_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Y phục "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==HEAD_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Nón "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==BOOTS_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Giày "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==WAIST_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Yêu đới "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==NECK_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Hạng liên "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
	}	
	
	return -99;
}
// Bla bla
void do_accept( string arg ){ return __FILE__ ->do_accept_callout( this_object(), this_player(), arg ); }

// Bla bla
void do_accept_callout(object me,object who, string arg )
{
	int level, p, i, t1, t2, t3, t4, mau, cap, cap1, cap2, itemid, ben;
	object item, item1;
	string sao,ngoc,forge="";
	
	if( !objectp( item = present( arg, who, 1, MAX_CARRY*4 ) ) )
		return 0;
	if( !item->is_equip() ) return 0;
	if( item->is_equip())
	{
		i=item->get_equip_type();
		if ( i!=WEAPON_TYPE&&i!=ARMOR_TYPE&&i!=HEAD_TYPE&&i!=BOOTS_TYPE&&i!=WAIST_TYPE&&i!=NECK_TYPE) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Can Tương:\nNgươi giao cho ta không phải là trang bị hoặc vũ khí !!!\n"ESC"Xác nhận");
			return 0;
			}
	}
	sao = item->get("forge");
	cap = strlen(sao);
	ngoc = item->get("make");
	cap1 = strlen(ngoc);
	cap2 = item->get_level();
	mau = item->get_item_color();
	if( item->get_hide() > 0 ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nHãy giám định %s trước khi Tinh luyện !!!\n"ESC"Xác nhận",item->get_name() ));
			return 0;
			}		
	if ( mau==1 || mau==2 || mau==3 ) {		
	if( cap < 1 ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nTrang bị %s của ngươi chưa đạt 1 ngôi sao, không thể rèn !!!\n"ESC"Xác nhận",item->get_name() ));
			return 0;
			}
	if( who->get_cash() <  ( cap2*25000/cap )  ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nNgươi không có đủ %d lượng để Rèn lại %s !!!\n"ESC"Xác nhận",( cap2*25000/cap ),item->get_name() ));
			return 0;
			}	
	if ( TASK_LEGEND_D->check_task_item_amount(who,"Tái Tạo Thạch") < 6 ) {
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\nNgươi không có đủ 6 Tái Tạo Thạch cần dùng cho việc rèn trang bị !!!\n"ESC"Xác nhận" ));
			return 0;
			}
	if ( !is_god(who) )
	{	
		if ( random(100) < 33 ) ben = 1;
		else if ( random(100) < 51 ) ben = 2;	
		else if ( random(100) < 72 ) ben = 3;	
		else if ( random(100) < 85 ) ben = 4;	
		else if ( random(100) < 97 ) ben = 5;	
		else if ( random(100) < 98 ) ben = 6;	
		else if ( random(100) < 99 ) ben = 7;	
		else ben = 8;	
	}
	else ben = 8;	
		item->delete("forge");	
		"/sys/item/equip"->reset_equip_prop(item);
		for (i = 0; i< ben; i++)
		{
			sosao(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->add_to_user(get_d(item));	
		send_user( who, "%c%d%c", 0x31, getoid(item), 0 );
		
		send_user(who,"%c%s",';',sprintf("Bạn đã dùng %d lượng để Rèn lại %s !",( cap2*25000/cap ),item->get_name()));
		
		if ( ben==8 ) 
		{
	CHAT_D->sys_channel(0,"Bằng hữu "+who->get_name()+" tại Can Tương đã thành công rèn ra "+item->get_name()+" đạt 8 ngôi sao, thật là may mắn !");	
	CHAT_D->sys_channel(0,"Bằng hữu "+who->get_name()+" tại Can Tương đã thành công rèn ra "+item->get_name()+" đạt 8 ngôi sao, thật là may mắn !");	
	CHAT_D->sys_channel(0,"Bằng hữu "+who->get_name()+" tại Can Tương đã thành công rèn ra "+item->get_name()+" đạt 8 ngôi sao, thật là may mắn !");	
		}	
		who->add_cash(- ( cap2*25000/cap ) );
		TASK_LEGEND_D->check_task_item1(who,"Tái Tạo Thạch",6);	
	}	
	else if ( mau==4 ) {
		if ( item->get_equip_type()==WEAPON_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Vũ khí "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==ARMOR_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Y phục "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==HEAD_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Nón "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==BOOTS_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Giày "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==WAIST_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Yêu đới "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==NECK_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Hạng liên "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
	}
	else if ( mau==0 ) {
		if ( item->get_equip_type()==WEAPON_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Vũ khí "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==ARMOR_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Y phục "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==HEAD_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Nón "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==BOOTS_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Giày "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==WAIST_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Yêu đới "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
		else if ( item->get_equip_type()==NECK_TYPE ){
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Can Tương:\n%s không phải là "HIR "Hạng liên "NOR "Lam Kim, Hoàng Kim, Tử Kim !!!\n"ESC"Xác nhận",item->get_name() ));
		}
	}
	return 0;
}