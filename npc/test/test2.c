
#include <npc.h>
#include <ansi.h>
#include <equip.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5402; }
int is_seller() { return 1; }
int is_self_look() { return 1; }
void do_gift( string arg );

// 函数：构造处理
void create()
{
        set_name( "NPC TEST 2" );
        set_2( "good", ([
                "01" : "/item/sell/0032",
                "02" : "/item/sell/1032",
                "03" : "/item/sell/2032",
                "04" : "/item/sell/0034",
 //               "05" : "/item/08/0016",
 //               "06" : "/item/08/0017",              
        ]) );
        set_2( "talk", ([
				"gift"          : (: do_gift :),
        ]));

        setup();
}

void do_look( object who ) 
{
	int id = getoid( this_object() );
	send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Ta có thể giúp gì cho ngươi?\n"
//		ESC"Nhận Chén Bạc\ntalk %x# gift.1\n"
		ESC"Nhận 300000 điểm Chiến Tích\ntalk %x# gift.2\n"
		ESC"Nhận 10000 Kim Bảo\ntalk %x# gift.3\n"
		ESC"Nhận 200 triệu lượng\ntalk %x# gift.4\n"
//		ESC"Nhận trang bị hoàng kim\ntalk %x# gift.5\n"
//		ESC"Nhận thời trang đặc biệt\ntalk %x# gift.6\n"
//		ESC"Tăng điểm PK\ntalk %x# gift.7\n"
//		ESC"Nhận 200 điểm Chuyển Sinh\ntalk %x# gift.8\n"
		ESC"Rời khỏi",get_name(),id,id,id,id,id,id,id,id));
}

void do_gift( string arg )
{
        object me = this_object();
        __FILE__ ->do_gift2(me, arg);
}

void do_gift2( object me, string arg )
{
	int flag,id,i,p;
	object who,item;
	string *nTmp,cFile;
	
        who = this_player();
		id = getoid(me);
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
       	case 1:
			if( USER_INVENTORY_D->count_empty_carry(who) < 1 )
			{
				send_user(who,"%c%s",'!',"Bạn phải có ít nhất 1 ô trống trong hành trang!");
				return 0;
			}
			item = new("item/test/chenbac");
			p = item->move2(who,-1);
			item->add_to_user(p);
			send_user(who,"%c%s",'!',"Bạn nhận được Chén Bạc");
			break;
		case 2:
			who->add_save_2("changping.score",300000);
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn nhận được 300000 điểm Chiến Tích, tổng điểm Chiến Tích hiện tại của bạn là: "HIR " %d "NOR "điểm.\n"
				ESC"Rời khỏi",get_name(),who->get_save_2("changping.score")));
			break;
		case 3:
			"sys/sys/test_db"->add_yuanbao(who,100000);
			send_user(who,"%c%s",'!',"Bạn nhận được 10000 KNB");
			break;
       	case 4:
			who->add_cash(200000000);
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn nhận được 200m.\n"
				ESC"Rời khỏi",get_name()));
			break;
/*		case 5:
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn muốn nhận trang bị hoàng kim đẳng cấp nào?\n"
				ESC"Trang bị hoàng kim đẳng cấp 60\ntalk %x# gift.51\n"
				ESC"Trang bị hoàng kim đẳng cấp 90\ntalk %x# gift.52\n"
				ESC"Trang bị hoàng kim đẳng cấp 120\ntalk %x# gift.53\n"
				ESC"Trang bị hoàng kim đẳng cấp 130\ntalk %x# gift.54\n"
				ESC"Rời khỏi",get_name(),id,id,id,id));
		break;
		case 6:
			if ( who->get_gender() == 1 )
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn muốn nhận thời trang nào?\n"
					ESC"Anh Hùng Y (Nam)\ntalk %x# gift.61\n"
					ESC"Tiêu Dao Thần Võ (Nam)\ntalk %x# gift.62\n"
					ESC"Rời khỏi",get_name(),id,id));
			else
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn muốn nhận thời trang nào?\n"
					ESC"Đào Hoa Thánh Y (Nữ)\ntalk %x# gift.61\n"
					ESC"Tiêu Dao Thánh khiết (Nữ)\ntalk %x# gift.62\n"
					ESC"Rời khỏi",get_name(),id,id));
		break;*/
		case 7:
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn muốn tăng điểm PK hay giảm điẻm PK của bạn bao nhiêu điểm?\n"
				ESC"Tăng 100 điểm PK\ntalk %x# gift.71\n"
				ESC"Giảm 100 điểm PK\ntalk %x# gift.72\n"
				ESC"Rời khỏi",get_name(),id,id));
		break;
		case 8:
			who->add_save_2("chuyensinh.score",200);
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn nhận được 200 điểm Chuyển Sinh, tổng điểm Chuyển Sinh hiện tại của bạn là: "HIR " %d "NOR "điểm.\n"
				ESC"Rời khỏi",get_name(),who->get_save_2("chuyensinh.score")));
			break;
       	case 51:
			if (who->get_fam_name()=="" || !who->get_fam_name())
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn vẫn chưa gia nhập môn phái, hãy gia nhập môn phái rồi quay lại tìm ta.",get_name()));
				return 0;
			}

			if(USER_INVENTORY_D->get_free_count(who) < 6 )
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn hãy chừa ít nhất 6 ô trống trong hành trang.",get_name()));
				return 0;
			}
			for (i = 0; i< 6; i++)
			{
				nTmp = WEAPON_FILE->get_family_equip( who->get_fam_name(),who->get_gender(),60,HEAD_TYPE+i );
				cFile = nTmp[random(sizeof(nTmp))];
				if( load_object(cFile) )
				{
					item = new( cFile );
					ITEM_EQUIP_D->init_equip_prop_3(item);
					item->set_hide(0);
					item->set_bind(4);
					p = item->move2(who,-1);
					item->add_to_user(p);
				}
			}
			send_user(who,"%c%s",'!',"Bạn nhận được bộ trang bị hoàng kim đẳng cấp 60");
			break;
       	case 52:
			if (who->get_fam_name()=="" || !who->get_fam_name())
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn vẫn chưa gia nhập môn phái, hãy gia nhập môn phái rồi quay lại tìm ta.",get_name()));
				return 0;
			}

			if(USER_INVENTORY_D->get_free_count(who) < 6 )
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn hãy chừa ít nhất 6 ô trống trong hành trang.",get_name()));
				return 0;
			}
			for (i = 0; i< 6; i++)
			{
				nTmp = WEAPON_FILE->get_family_equip( who->get_fam_name(),who->get_gender(),90,HEAD_TYPE+i );
				cFile = nTmp[random(sizeof(nTmp))];
				if( load_object(cFile) )
				{
					item = new( cFile );
					ITEM_EQUIP_D->init_equip_prop_3(item);
					item->set_hide(0);
					item->set_bind(4);
					p = item->move2(who,-1);
					item->add_to_user(p);
				}
			}
			send_user(who,"%c%s",'!',"Bạn nhận được bộ trang bị hoàng kim đẳng cấp 90");
			break;
       	case 53:
			if (who->get_fam_name()=="" || !who->get_fam_name())
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn vẫn chưa gia nhập môn phái, hãy gia nhập môn phái rồi quay lại tìm ta.",get_name()));
				return 0;
			}

			if(USER_INVENTORY_D->get_free_count(who) < 6 )
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn hãy chừa ít nhất 6 ô trống trong hành trang.",get_name()));
				return 0;
			}
			for (i = 0; i< 6; i++)
			{
				nTmp = WEAPON_FILE->get_family_equip( who->get_fam_name(),who->get_gender(),120,HEAD_TYPE+i );
				cFile = nTmp[random(sizeof(nTmp))];
				if( load_object(cFile) )
				{
					item = new( cFile );
					ITEM_EQUIP_D->init_equip_prop_3(item);
					item->set_hide(0);
					item->set_bind(4);
					p = item->move2(who,-1);
					item->add_to_user(p);
				}
			}
			send_user(who,"%c%s",'!',"Bạn nhận được bộ trang bị hoàng kim đẳng cấp 120");
			break;
       	case 54:
			if (who->get_fam_name()=="" || !who->get_fam_name())
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn vẫn chưa gia nhập môn phái, hãy gia nhập môn phái rồi quay lại tìm ta.",get_name()));
				return 0;
			}

			if(USER_INVENTORY_D->get_free_count(who) < 6 )
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn hãy chừa ít nhất 6 ô trống trong hành trang.",get_name()));
				return 0;
			}
			for (i = 0; i< 6; i++)
			{
				nTmp = WEAPON_FILE->get_family_equip( who->get_fam_name(),who->get_gender(),130,HEAD_TYPE+i );
				cFile = nTmp[random(sizeof(nTmp))];
				if( load_object(cFile) )
				{
					item = new( cFile );
					ITEM_EQUIP_D->init_equip_prop_3(item);
					item->set_hide(0);
					item->set_bind(4);
					p = item->move2(who,-1);
					item->add_to_user(p);
				}
			}
			send_user(who,"%c%s",'!',"Bạn nhận được bộ trang bị hoàng kim đẳng cấp 130");
			break;
       	case 61:
			if(USER_INVENTORY_D->get_free_count(who) < 1 )
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn hãy chừa ít nhất 1 ô trống trong hành trang.",get_name()));
				return 0;
			}
			if ( who->get_gender() == 1)
			{
				item = new( "item/mop/10052" );	
			}
			else
			{
				item = new( "item/mop/11052" );	
			}
			"/sys/item/equip"->init_equip_prop_3(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			item->set_item_color(2);
			item->set_hide(0);
			item->set("forge", "11111");
			p = item->move2(who,-1);
			item->add_to_user(p);
			send_user(who,"%c%s",'!',"Bạn nhận được "HIR+item->get_name());
			break;
       	case 62:
			if(USER_INVENTORY_D->get_free_count(who) < 1 )
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn hãy chừa ít nhất 1 ô trống trong hành trang.",get_name()));
				return 0;
			}
			if ( who->get_gender() == 1)
			{
				item = new( "item/mop/10053" );	
			}
			else
			{
				item = new( "item/mop/11053" );	
			}
			"/sys/item/equip"->init_equip_prop_3(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			item->set_item_color(2);
			item->set_hide(0);
			item->set("forge", "11111");
			p = item->move2(who,-1);
			item->add_to_user(p);
			send_user(who,"%c%s",'!',"Bạn nhận được "HIR+item->get_name());
			break;
		case 71:
			who->add_pk(100);
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn vừa tăng 100 điểm PK, tổng điểm PK hiện tại của bạn là: "HIR " %d "NOR "điểm.\n"
				ESC"Rời khỏi",get_name(),who->get_pk()));
			break;
		case 72:
			who->add_pk(-100);
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn vừa giảm 100 điểm PK, tổng điểm PK hiện tại của bạn là: "HIR " %d "NOR "điểm.\n"
				ESC"Rời khỏi",get_name(),who->get_pk()));
			break;
		}
}
