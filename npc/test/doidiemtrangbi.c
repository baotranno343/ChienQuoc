/* Code by Pret */
/* Bảng giá đổi 
		100.000 ngân = 1 Điểm Thành Tựu
		200.000 ngân lượng = 3 Điểm Thành Tựu
		500.000 ngân lượng = 8 Điểm Thành Tựu
		1.000.000 ngân lượng = 17 Điểm Thành Tựu
		10.000.000 ngân lượng = 180 Điểm Thành Tựu
		Lam Kim = 2 Điểm Thành Tựu 
		Hoàng Kim = 4 Điểm Thành Tựu 
		Cao Cấp Đoạn Thạch = 20 Điểm Thành Tựu 
*/
#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
inherit OFFICER;

// 函数：获取人物造型
void reset();
int get_char_picid() { return 9971; }
int is_seller() { return 1; }
int is_self_look() { return 1; }
void do_gift( string arg );
void do_accept(string arg);


// 函数：构造处理
void create()
{
        set_name("Đổi Điểm Thành Tựu");
		set_real_name("Cập Phong");
        set_2( "good", ([

        ]) );
        set_2( "talk", ([
				"gift"          : (: do_gift :),
				"accept"         : (: do_accept :),				
        ]));

        setup();
}

void do_look( object who ) 
{
	int id = getoid( this_object() );
	send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Vạn vật trong thế gian đều có thừa có thiếu, vậy làm gì với những thứ thừa và dư đấy! Ta sẽ cho ngươi câu trả lời thích đáng!\n"	
		ESC "Vài điều về đổi Điểm Thành Tựu!\ntalk %x# gift.1\n"
		ESC HIY"Ta muốn đổi Điểm Thành Tựu\ntalk %x# gift.2\n"
		ESC HIG"Ta muốn đổi thưởng\ntalk %x# gift.3\n"
		ESC"Rời khỏi",get_name(),id,id,id,id,id,id));
}

void do_gift( string arg )
{
        object me = this_object();
        __FILE__ ->do_gift2(me, arg);
}

void do_gift2( object me, string arg )
{
	int flag,id,i,p,iTime,iDay,iGio;
	object who,item;
	string *nTmp,cFile,cTmp,cFinal,result;
	mixed *mxTime;

        who = this_player();
		id = getoid(me);
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	    case 1:
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Trong quá trình tham gia Chiến Quốc, có một số vật phẩm và đồ dùng không cần dùng đến mà người chơi thường cất đi. Nếu đem tới chỗ ta để đổi, có thể nhận được điểm Thành tựu có rất nhiều công dụng hữu ích hơn đấy !\n"
		ESC"Rời khỏi",get_name(),id));	
		break;
		 // Đổi điểm thành tựu 
		case 2: 
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy chọn một thứ mà ngươi muốn đổi để lấy điểm Thành Tựu. Điểm Thành Tựu hiện tại của ngươi là "HIR"%d"NOR" điểm!!\n"	
		ESC "Dùng ngân lượng\ntalk %x# gift.20\n"
		ESC "Dùng vật phẩm\ntalk %x# gift.21\n"
		ESC"Rời khỏi",get_name(),who->get_save("diemtt"),id,id,id,id,id,id));
		break;
		
		// Dùng ngân lượng đổi thành tựu
		case 20:
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Ngươi muốn dùng bao nhiêu ngân lượng để đổi? Điểm Thành Tựu hiện tại của ngươi là "HIR"%d"NOR" điểm!!\n"	
		ESC "Dùng 100.000 ngân lượng đổi 1 Điểm Thành Tựu\ntalk %x# gift.200\n"
		ESC "Dùng 200.000 ngân lượng đổi 3 Điểm Thành Tựu\ntalk %x# gift.201\n"
		ESC "Dùng 500.000 ngân lượng đổi 8 Điểm Thành Tựu\ntalk %x# gift.202\n"
		ESC "Dùng 1.000.000 ngân lượng đổi 17 Điểm Thành Tựu\ntalk %x# gift.203\n"
		ESC "Dùng 10.000.000 ngân lượng đổi 180 Điểm Thành Tựu\ntalk %x# gift.204\n"
		ESC"Rời khỏi",get_name(),who->get_save("diemtt"),id,id,id,id,id,id));
		break;
		// 100k - 1
		case 200:
		if(who->get_cash() < 100000 )
			{
				notify( "Ngươi không đủ 100.000 ngân lượng" );
				return ;
			}
		who->add_cash(-100000);
		who->add_save("diemtt",1);
		write_user(who, sprintf(ECHO"Bạn đã đổi thành công điểm thành tựu. Điểm thành tựu hiện tại của bạn là %d điểm.", who->get_save("diemtt") ));
		break;
		// 200k - 3
		case 201:
		if(who->get_cash() < 200000 )
			{
				notify( "Ngươi không đủ 200.000 ngân lượng" );
				return ;
			}
		who->add_cash(-200000);
		who->add_save("diemtt",3);
		write_user(who, sprintf(ECHO"Bạn đã đổi thành công điểm thành tựu. Điểm thành tựu hiện tại của bạn là %d điểm.", who->get_save("diemtt") ));
		break;
		//500k - 8
		case 202:
		if(who->get_cash() < 500000 )
			{
				notify( "Ngươi không đủ 500.000 ngân lượng" );
				return ;
			}
		who->add_cash(-500000);
		who->add_save("diemtt",8);
		write_user(who, sprintf(ECHO"Bạn đã đổi thành công điểm thành tựu. Điểm thành tựu hiện tại của bạn là %d điểm.", who->get_save("diemtt") ));
		break;
		// 1m - 17
		case 203:
		if(who->get_cash() < 1000000 )
			{
				notify( "Ngươi không đủ 1.000.000 ngân lượng" );
				return ;
			}
		who->add_cash(-1000000);
		who->add_save("diemtt",17);
		write_user(who, sprintf(ECHO"Bạn đã đổi thành công điểm thành tựu. Điểm thành tựu hiện tại của bạn là %d điểm.", who->get_save("diemtt") ));
		break;
		// 10m - 180
		case 204:
		if(who->get_cash() < 10000000 )
			{
				notify( "Ngươi không đủ 10.000.000 ngân lượng" );
				return ;
			}
		who->add_cash(-10000000);
		who->add_save("diemtt",180);
		write_user(who, sprintf(ECHO"Bạn đã đổi thành công điểm thành tựu. Điểm thành tựu hiện tại của bạn là %d điểm.", who->get_save("diemtt") ));
		break;
		
		// Thông báo cách thức đổi trang bị lấy điểm Thành Tựu
		case 21:
		send_user(who, "%c%c%w%s", ':',3,get_char_picid(),who->get_name() + ":\n"+"Ta có thể lấy trang bị dư của ngươi để cho ngươi điểm Thành Tựu. Với điều kiện trang bị đó đã trên 1 sao và trang bị phải là trang bị Lam Kim hoặc Hoàng Kim. Ngoài ra cũng có thể dùng Đoạn Thạch Cao Cấp để đổi điểm. Tỉ lệ như sau:\n1.Đồ Lam Kim được 2 điểm Thành Tựu\n2.Đồ Hoàng Kim được 4 điểm Thành Tựu\n3.Cao Cấp Đoạn Thạch được 20 điểm Thành Tựu\n" 
		ESC "Alt + G để giao vật phẩm\nCLOSE\n"
		ESC "Thoát ra\nCLOSE\n"); 
		break;
		
		// Đổi thưởng thành tựu 
		case 3: 
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Điểm Thành Tựu hiện tại của ngươi là "HIR"%d"NOR" điểm!! Ngươi muốn đổi thứ gì ở đây?\n"	
		ESC "Dùng 3 Điểm đổi Mảnh Ghép Huyết Binh\ntalk %x# gift.30\n"
		ESC "Dùng 500 Điểm đổi Túi Huyết Sắc\ntalk %x# gift.31\n"
		ESC "Dùng 600 Điểm đổi Đoạn Thạch Đặc Biệt Trung Cấp\ntalk %x# gift.32\n"
		ESC "Dùng 800 Điểm đổi Đoạn Thạch Đặc Biệt Cao Cấp\ntalk %x# gift.33\n"
		ESC"Rời khỏi",get_name(),who->get_save("diemtt"),id,id,id,id,id,id));
		break;
		// Bảo Để Phù 
		case 30:
		if( who->get_save("diemtt") < 400 )
			{
				notify( "Ngươi không đủ 400 điểm Thành Tựu" );
				return ;
			}
		who->add_save("diemtt",-400);
		item = new("/item/sell/0034");
		i = item->move(who,-1);
		item->add_to_user(i);
		write_user(who, sprintf(ECHO"Bạn đã đổi thành công %s . Điểm thành tựu hiện tại của bạn là %d điểm.", item->get_name(), who->get_save("diemtt") ));
		break;
		// DTDB S 
		case 31:
		if( who->get_save("diemtt") < 500 )
			{
				notify( "Ngươi không đủ 500 điểm Thành Tựu" );
				return ;
			}
		who->add_save("diemtt",-500);
		item = new("/item/sell/4032");
		i = item->move(who,-1);
		item->add_to_user(i);
		write_user(who, sprintf(ECHO"Bạn đã đổi thành công %s . Điểm thành tựu hiện tại của bạn là %d điểm.", item->get_name(), who->get_save("diemtt") ));
		break;
		// DTDB T 
		case 32:
		if( who->get_save("diemtt") < 600 )
			{
				notify( "Ngươi không đủ 600 điểm Thành Tựu" );
				return ;
			}
		who->add_save("diemtt",-600);
		item = new("/item/sell/4032_2");
		i = item->move(who,-1);
		item->add_to_user(i);
		write_user(who, sprintf(ECHO"Bạn đã đổi thành công %s . Điểm thành tựu hiện tại của bạn là %d điểm.", item->get_name(), who->get_save("diemtt") ));
		break;
		// DTDB C 
		case 33:
		if( who->get_save("diemtt") < 800 )
			{
				notify( "Ngươi không đủ 800 điểm Thành Tựu" );
				return ;
			}
		who->add_save("diemtt",-800);
		item = new("/item/sell/4032_3");
		i = item->move(who,-1);
		item->add_to_user(i);
		write_user(who, sprintf(ECHO"Bạn đã đổi thành công %s . Điểm thành tựu hiện tại của bạn là %d điểm.", item->get_name(), who->get_save("diemtt") ));
		break;		
		}
}

// Gọi hàm chấp nhận vật phẩm
int accept_object( object who, object item ){ return __FILE__ ->accept_object_callout( this_object(), who, item ); }

// Thực thi hàm chấp nhận vật phẩm
int accept_object_callout( object me, object who, object item )
{
    int level, p, i, t1, t2, t3, t4, mau , cap, cap1, cap2;
	object item2;
	string sao,ngoc;
    me->to_front_eachother(who);
	
	sao = item->get("forge");
	cap = strlen(sao);
	ngoc = item->get("make");
	cap1 = strlen(ngoc);
	cap2 = item->get_level();
	mau = item->get_item_color();

	// Check Lam kim
	if ( mau==1 ) {
					if ( cap < 1 ) {
					write_user(who,ECHO"Trang bị chưa đạt 1 sao, không thể đổi điểm Thành Tựu");
					return -99;				
									}
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Lưu Hoàng Sư:\nĐổi trang bị này bạn có thể nhận được %d điểm Thành Tựu, bạn thực sự muốn đổi không ?\n"ESC"Xác nhận\ntalk %x# accept.%x#\n"ESC"Huỷ bỏ",2,getoid(me),getoid(item)));
					}
	// Check hoàng kim
	else if ( mau==2 ) {
						if ( cap < 1 )  {
						write_user(who,ECHO"Trang bị chưa đạt 1 sao, không thể đổi điểm Thành Tựu");
						return -99;				
										}
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Lưu Hoàng Sư:\nĐổi trang bị này bạn có thể nhận được %d điểm Thành Tựu, bạn thực sự muốn đổi không ?\n"ESC"Xác nhận\ntalk %x# accept.%x#\n"ESC"Huỷ bỏ",4,getoid(me),getoid(item)));
						}
	// Check đoạn thạch
	else if (objectp( item = present("Cao Cấp Đoạn Thạch", who, 1, MAX_CARRY) )) {
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Lưu Hoàng Sư:\nĐổi Cao Cấp Đoạn Thạch bạn có thể nhận được %d điểm Thành Tựu, bạn thực sự muốn đổi không ?\n"ESC"Xác nhận\ntalk %x# accept.%x#\n"ESC"Huỷ bỏ",20,getoid(me),getoid(item)));
	}
	
	return -99;
}

// Nhận hàm chấp nhận vật phẩm
void do_accept( string arg ){ return __FILE__ ->do_accept_callout( this_object(), this_player(), arg ); }

// Thực thi hàm chấp nhận vật phẩm
void do_accept_callout(object me, object who, string arg )
{
	int level, p, i, t1, t2, t3, t4, mau, cap, cap1, cap2;
	object item;
	string sao,ngoc;
	
	if( !objectp( item = present( arg, who, 1, MAX_CARRY*4 ) ) )
		return 0;

	sao = item->get("forge");
	cap = strlen(sao);
	ngoc = item->get("make");
	cap1 = strlen(ngoc);
	cap2 = item->get_level();
	mau = item->get_item_color();

	if ( mau==1 && cap < 1 ) 
				{
					if ( cap < 1)
				{
					write_user(who,ECHO"Trang bị chưa đạt 1 sao, không thể đổi điểm Thành Tựu");
					return 0;
				}
				who->add_save("diemtt",2);
				write_user(who, sprintf(ECHO"Bạn đổi thành công %s và nhận được %d điểm thành tựu", item->get_name(), 2 ));
				item->remove_from_user();
				destruct(item);
				}
	else if ( mau==2 ) 
				{
					 if ( cap < 1)
				{
					write_user(who,ECHO"Trang bị chưa đạt 1 sao, không thể đổi điểm Thành Tựu");
					return 0;
				}
				who->add_save("diemtt",4);
				write_user(who, sprintf(ECHO"Bạn đổi thành công %s và nhận được %d điểm thành tựu", item->get_name(), 4 ));
				item->remove_from_user();
				destruct(item);
				}
				
	else if (objectp( item = present("Cao Cấp Đoạn Thạch", who, 1, MAX_CARRY) )) {
		who->add_save("diemtt",20);
		write_user(who, sprintf(ECHO"Bạn đổi thành công %s và nhận được %d điểm thành tựu", item->get_name(), 20 ));
		item->remove_from_user();
		destruct(item);
	} 
	
	return 0;
}
