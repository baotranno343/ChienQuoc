
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5407; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Âu Trị Tử");
		set_real_name("Thần Chú Sư");
        set_2( "talk", ([
				"welcome"          : (: do_welcome :),
        ]));

       setup();
}

// 函数：对话处理
void do_look( object who )
{
	int id = getoid( this_object() );
	send_user(who,"%c%s",':',sprintf("Âu Trị Tử:\n Vơi tai ren đuc siêu viêt thì thần binh lợi khí thông thương chi la chuyên nho. Đáng tiếc duy nhất vân là chưa thể đúc ra một thần binh cái thế. Nếu bạn có thể tìm đu cac loai nguyên liệu, ta sẽ bỏ tâm huyết đúc cho bạn một thần binh thiên ha vô song.\n"
		ESC"Đúc thần binh cấp 100\ntalk %x# welcome.80\n"
		ESC"Công Thưc va Nguôn Gôc cua Thân Binh\ntalk %x# welcome.81\n"
		ESC"Rời khỏi\n",id,id));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,id,p;
	object who,item;
	string cTmp,cFinal,cFile;
	
        who = this_player();
		id = getoid(me);
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
		case 80:
			send_user(who,"%c%s",':',sprintf("Âu Trị Tử:\n Ta có thể đúc ra 6 loại thần binh miên la ngươi phai chuẩn bị đủ nguyên liệu. Hay noi cho ta biêt khi nao ngươi muôn co 1 thân binh thiên ha vô đich tư thương cô chi kim.\n"
				ESC"Đúc thần binh Lục Thần Thương\ntalk %x# welcome.801\n"
				ESC"Đúc thần binh Phàn Thiên Côn\ntalk %x# welcome.802\n"
				ESC"Đúc thần binh Đao Tử Vân\ntalk %x# welcome.803\n"
				ESC"Đúc thần binh Lục Tiên Kiêm\ntalk %x# welcome.804\n"
				ESC"Đúc thần binh Ngọc La Quyên Thu\ntalk %x# welcome.805\n"
				ESC"Đúc thần binh Thần Tiên Hạc Kim\ntalk %x# welcome.806\n"
				ESC"Phản hồi\n",id,id,id,id,id,id));
			break;
		case 81:
			send_user(who,"%c%s",':',sprintf("Âu Trị Tử:\n Ngươi muốn tìm hiểu phương phap ren loai thân binh nao? Ta se cho ngươi biêt nguyên liêu tương ưng.\n"
				ESC"Phương pháp ren thần binh Lục Thần Thương và nguyên liệu tương ưng\ntalk %x# welcome.811\n"
				ESC"Phương pháp ren thần binh Phàn Thiên Côn và nguyên liệu tương ưng\ntalk %x# welcome.821\n"
				ESC"Phương pháp ren thần binh Đao Tử Vân và nguyên liệu tương ưng\ntalk %x# welcome.831\n"
				ESC"Phương pháp ren thần binh Lục Tiên Kiêm và nguyên liệu tương ưng\ntalk %x# welcome.841\n"
				ESC"Phương pháp ren thần binh Ngọc La Quyên Thu và nguyên liệu tương ưng\ntalk %x# welcome.851\n"
				ESC"Phương pháp ren thần binh Thần Tiên Hạc Kim và nguyên liệu tương ưng\ntalk %x# welcome.861\n"
				ESC"Phản hồi\n",id,id,id,id,id,id));
			break;
		case 801:
		case 802:
		case 803:
		case 804:
		case 805:
		case 806:
		if ( flag == 801 )
		{
			cTmp = "Chân Quân Xí Diệm Thương";
			cFile = "item/74/9100";
		}
		else if ( flag == 802 )
		{
			cTmp = "Càn Khôn Vô Cấp Côn";
			cFile = "item/75/9100";
		}
		else if ( flag == 803 )
		{
			cTmp = "Thiên Tôn Bảo Đao";
			cFile = "item/72/9100";
		}
		else if ( flag == 804 )
		{
			cTmp = "Ngọc Thần Bảo Kiếm";
			cFile = "item/73/9100";
		}
		else if ( flag == 805 )
		{
			cTmp = "Anh Kiệt Quyền Nhẫn";
			cFile = "item/70/9100";
		}
		else if ( flag == 806 )
		{
			cTmp = "Bích Hỏa Hàn Nguyệt Hoàn";
			cFile = "item/71/9100";
		}
		if( USER_INVENTORY_D->get_free_count(who) < 1 )
		{
			send_user(who,"%c%s",'!',"Hành trang không đủ chỗ.");
			return 0;
		}
		if ( TASK_LEGEND_D->check_task_item_amount(who,cTmp) == 0 ||
			TASK_LEGEND_D->check_task_item_amount(who,"Đá Tương Uyên") < 60 ||
			TASK_LEGEND_D->check_task_item_amount(who,"Đá Càn Khôn") < 40 ||
			TASK_LEGEND_D->check_task_item_amount(who,"Lỗ Ban Bảo Thạch") < 30 )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Âu Trị Tử:\n Nguyên liệu cua ngươi không đủ! Đúc %s cần cac loai nguyên liêu sau:\n "+cTmp+", 60 viên Đá Tương Uyên, 40 viên Đá Càn Khôn, 30 viên Lỗ Ban.\n"ESC"Rời khỏi",cFile->get_name()));
			return ;	
		}
		TASK_LEGEND_D->check_task_item1(who,cTmp,1);
		TASK_LEGEND_D->check_task_item1(who,"Đá Tương Uyên",60);
		TASK_LEGEND_D->check_task_item1(who,"Đá Càn Khôn",40);
		TASK_LEGEND_D->check_task_item1(who,"Lỗ Ban Bảo Thạch",30);
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
		case 811:
			send_user(who,"%c%s",':',sprintf("Âu Trị Tử:\n Đúc Lục Thần Thương cần 1 Chân quân xí diệm thương, 60 Đá Tương Uyên, 40 Đá Càn Khôn 30 Lỗ Ban.\n Càn Khôn Vô Cấp Côn có thể hợp thành tại nước Chu, Đá Tương Uyên và Đá Càn Khôn co thê tìm thây trong Phong Yêu Kinh. Lỗ Ban có thể mua trong Bảo Khố.\n"ESC"Phản hồi"));
			break;
		case 821:
			send_user(who,"%c%s",':',sprintf("Âu Trị Tử:\n Đúc Phàn Thiên Côn cần 1 Càn khôn vô cấp côn, 60 Đá Tương Uyên, 40 Đá Càn Khôn 30 Lỗ Ban.\n Càn Khôn Vô Cấp Côn có thể hợp thành tại nước Chu, Đá Tương Uyên và Đá Càn Khôn co thê tìm thây trong Phong Yêu Kinh. Lỗ Ban có thể mua trong Bảo Khố.\n"ESC"Phản hồi"));
			break;
		case 831:
			send_user(who,"%c%s",':',sprintf("Âu Trị Tử:\n Đúc Đao Tử Vân cần 1 Thiên tôn bảo đao, 60 Đá Tương Uyên, 40 Đá Càn Khôn 30 Lỗ Ban.\n Càn Khôn Vô Cấp Côn có thể hợp thành tại nước Chu, Đá Tương Uyên và Đá Càn Khôn co thê tìm thây trong Phong Yêu Kinh. Lỗ Ban có thể mua trong Bảo Khố.\n"ESC"Phản hồi"));
			break;
		case 841:
			send_user(who,"%c%s",':',sprintf("Âu Trị Tử:\n Đúc Lục Tiên Kiêm cần 1 Ngọc thần bảo kiếm, 60 Đá Tương Uyên, 40 Đá Càn Khôn 30 Lỗ Ban.\n Càn Khôn Vô Cấp Côn có thể hợp thành tại nước Chu, Đá Tương Uyên và Đá Càn Khôn co thê tìm thây trong Phong Yêu Kinh. Lỗ Ban có thể mua trong Bảo Khố.\n"ESC"Phản hồi"));
			break;
		case 851:
			send_user(who,"%c%s",':',sprintf("Âu Trị Tử:\n Đúc Ngọc La Quyên Thu cần 1 Anh kiệt quyền nhẫn, 60 Đá Tương Uyên, 40 Đá Càn Khôn 30 Lỗ Ban.\n Càn Khôn Vô Cấp Côn có thể hợp thành tại nước Chu, Đá Tương Uyên và Đá Càn Khôn co thê tìm thây trong Phong Yêu Kinh. Lỗ Ban có thể mua trong Bảo Khố.\n"ESC"Phản hồi"));
			break;
		case 861:
			send_user(who,"%c%s",':',sprintf("Âu Trị Tử:\n Đúc Thần Tiên Hạc Kim cần 1 Bích hỏa hàn nguyệt hoàn, 60 Đá Tương Uyên, 40 Đá Càn Khôn 30 Lỗ Ban.\n Càn Khôn Vô Cấp Côn có thể hợp thành tại nước Chu, Đá Tương Uyên và Đá Càn Khôn co thê tìm thây trong Phong Yêu Kinh. Lỗ Ban có thể mua trong Bảo Khố.\n"ESC"Phản hồi"));
			break;
        }	
}
