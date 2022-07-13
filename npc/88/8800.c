#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <task.h>
#include <skill.h>
#include <time.h>

#define MIN_SIZE 1	//开战的最少人数 1
#define MAX_SIZE 50 //单方的最大人数 50

inherit OFFICER;
inherit DBASE_F;

int WarId;
mapping mpInfo = ([
	  // hp,mp,ap,dp,cp,pp,sp
	  "Bạch Khởi60":({
						1000000,
						1000000,
						700,
						560,
						650,
						510,
						300,
					}),
	  "Bạch Khởi80":({
						1200000,
						1200000,
						900,
						720,
						850,
						670,
						420,
					}),
	 "Bạch Khởi100":({
						1500000,
						1500000,
						1100,
						880,
						1050,
						830,
						540,
					}),
	 "Bạch Khởi120":({
						1900000,
						1900000,
						1300,
						1040,
						1250,
						990,
						660,
					}),
	 "Bạch Khởi150":({
						2500000,
						2500000,
						1600,
						1280,
						1550,
						1230,
						780,
					}),
	 "Vương Ngật60":({
						360000,
						360000,
						650,
						510,
						600,
						460,
						300,
					}),
	 "Vương Ngật80":({
						432000,
						432000,
						850,
						670,
						800,
						620,
						420,
					}),
	"Vương Ngật100":({
						540000,
						540000,
						1050,
						830,
						1000,
						770,
						540,
					}),
	"Vương Ngật120":({
						684000,
						684000,
						1350,
						990,
						1200,
						940,
						660,
					}),
	"Vương Ngật150":({
						900000,
						900000,
						1550,
						1230,
						1500,
						1180,
						780,
					}),
	 "Vương Lăng60":({
						400000,
						400000,
						600,
						510,
						600,
						460,
						300,
					}),
	 "Vương Lăng80":({
						480000,
						480000,
						800,
						670,
						800,
						620,
						420,
					}),
	"Vương Lăng100":({
						600000,
						600000,
						900,
						830,
						1000,
						770,
						540,
					}),
	"Vương Lăng120":({
						760000,
						760000,
						1200,
						990,
						1200,
						940,
						660,
					}),
	"Vương Lăng150":({
						1000000,
						1000000,
						1500,
						1230,
						1500,
						1180,
						780,
					}),
	 "Tư Mã Thác60":({
						400000,
						400000,
						600,
						510,
						600,
						460,
						300,
					}),
	 "Tư Mã Thác80":({
						480000,
						480000,
						800,
						670,
						800,
						620,
						420,
					}),
	"Tư Mã Thác100":({
						600000,
						600000,
						900,
						830,
						1000,
						770,
						540,
					}),
	"Tư Mã Thác120":({
						760000,
						760000,
						1200,
						990,
						1200,
						940,
						660,
					}),
	"Tư Mã Thác150":({
						1000000,
						1000000,
						1500,
						1230,
						1500,
						1180,
						780,
					}),
	  "Mông Ngạo60":({
						400000,
						400000,
						600,
						510,
						600,
						460,
						300,
					}),
	  "Mông Ngạo80":({
						480000,
						480000,
						800,
						670,
						800,
						620,
						420,
					}),
	 "Mông Ngạo100":({
						600000,
						600000,
						900,
						830,
						1000,
						770,
						540,
					}),
	 "Mông Ngạo120":({
						760000,
						760000,
						1200,
						990,
						1200,
						940,
						660,
					}),
	 "Mông Ngạo150":({
						1000000,
						1000000,
						1500,
						1230,
						1500,
						1180,
						780,
					}),
	   "Liêm Pha60":({
						1000000,
						1000000,
						700,
						560,
						650,
						510,
						300,
					}),
	   "Liêm Pha80":({
						1200000,
						1200000,
						900,
						720,
						850,
						670,
						420,
					}),
	  "Liêm Pha100":({
						1500000,
						1500000,
						1100,
						880,
						1050,
						830,
						540,
					}),
	  "Liêm Pha120":({
						1900000,
						1900000,
						1300,
						1040,
						1250,
						990,
						660,
					}),
	  "Liêm Pha150":({
						2500000,
						2500000,
						1600,
						1280,
						1550,
						1230,
						780,
					}),
	 "Triệu Quát60":({
						360000,
						360000,
						650,
						510,
						600,
						460,
						300,
					}),
	 "Triệu Quát80":({
						432000,
						432000,
						850,
						670,
						800,
						620,
						420,
					}),
	"Triệu Quát100":({
						540000,
						540000,
						1050,
						830,
						1000,
						770,
						540,
					}),
	"Triệu Quát120":({
						684000,
						684000,
						1350,
						990,
						1200,
						940,
						660,
					}),
	"Triệu Quát150":({
						900000,
						900000,
						1550,
						1230,
						1500,
						1180,
						780,
					}),
	   "Lạc Thừa60":({
						400000,
						400000,
						600,
						510,
						600,
						460,
						300,
					}),
	   "Lạc Thừa80":({
						480000,
						480000,
						800,
						670,
						800,
						620,
						420,
					}),
	  "Lạc Thừa100":({
						600000,
						600000,
						900,
						830,
						1000,
						770,
						540,
					}),
	  "Lạc Thừa120":({
						760000,
						760000,
						1200,
						990,
						1200,
						940,
						660,
					}),
	  "Lạc Thừa150":({
						1000000,
						1000000,
						1500,
						1230,
						1500,
						1180,
						780,
					}),
	 "Phùng Đình60":({
						400000,
						400000,
						600,
						510,
						600,
						460,
						300,
					}),
	 "Phùng Đình80":({
						480000,
						480000,
						800,
						670,
						800,
						620,
						420,
					}),
	"Phùng Đình100":({
						600000,
						600000,
						900,
						830,
						1000,
						770,
						540,
					}),
	"Phùng Đình120":({
						760000,
						760000,
						1200,
						990,
						1200,
						940,
						660,
					}),
	"Phùng Đình150":({
						1000000,
						1000000,
						1500,
						1230,
						1500,
						1180,
						780,
					}),
	 "Quách Khai60":({
						400000,
						400000,
						600,
						510,
						600,
						460,
						300,
					}),
	 "Quách Khai80":({
						480000,
						480000,
						800,
						670,
						800,
						620,
						420,
					}),
	"Quách Khai100":({
						600000,
						600000,
						900,
						830,
						1000,
						770,
						540,
					}),
	"Quách Khai120":({
						760000,
						760000,
						1200,
						990,
						1200,
						940,
						660,
					}),
	"Quách Khai150":({
						1000000,
						1000000,
						1500,
						1230,
						1500,
						1180,
						780,
					}),
]);

mapping mpNpc = (["Tần Quốc":([1:(["file":"npc/88/1001", "nPos":({63, 50})]),
								 2:(["file":"npc/88/1002", "nPos":({72, 56})]),
								 3:(["file":"npc/88/1003", "nPos":({89, 106})]),
								 4:(["file":"npc/88/1004", "nPos":({99, 75})]),
								 5:(["file":"npc/88/1005", "nPos":({134, 67})]),
]),

				"Triệu Quốc":([1:(["file":"npc/88/2001", "nPos":({185, 142})]),
								 2:(["file":"npc/88/2002", "nPos":({168, 133})]),
								 3:(["file":"npc/88/2003", "nPos":({166, 86})]),
								 4:(["file":"npc/88/2004", "nPos":({156, 117})]),
								 5:(["file":"npc/88/2005", "nPos":({115, 127})]),
]),
]);
int *nRankScore = ({25, 63, 156, 400, 1000, 2500, 6250, 15500, 38250, 95500, 238500});
// 函数:获取人物造型
int get_char_picid() { return 9609; }
void do_welcome(string arg);
void do_nhanthuong(string arg);
void do_bonus(string arg);
void player_sign_up(object me, object who);
void team_sign_up(object me, object who);
int init_npc(object npc, int level);
void check_war_begin(int level, int wId);
void enter_changping(object who);
int check_valid_user(object who);
int count_sign_up(int level, int wId);
void refuse_changping(object who);
void abort_changping(object who);
int change_score(int score);
int kill_score(object who, object map);
void give_title(object me, object who, int iFlag);

// 函数:构造处理
void create()
{
	int i, size;
	string *nKey;
	mapping mpTmp;
	set_name("Trương Quả Lão");
	set_city_name("Chu Quốc");

	set_2("talk", (["welcome":(
								  : do_welcome:),
					  "nhanthuong":(
									   : do_nhanthuong:),
						   "bonus":(
									   : do_bonus:),
	]));
	setup();

	if (clonep(this_object()))
		return;
	WarId = "npc/88/8801"->get_2("warid");
	mpTmp = "npc/88/8801"->get_2("database");
	if (!mapp(mpTmp))
		return;
	nKey = keys(mpTmp);
	for (i = 0, size = sizeof(nKey); i < size; i++)
	{
		set_2(nKey[i], mpTmp[nKey[i]]);
	}
}

// 函数:对话处理
void do_look(object who)
{
	int level, z, wId;
	object me = this_object();
	int id = getoid(me);

	level = who->get_2("changping.level");
	if (level)
	{
		z = __FILE__->get_2(sprintf("%d.%d.z", level, wId = who->get_2("changping.warid")));
		if (!z)
			send_user(who, "%c%s", ':', sprintf("%s:\n    Lão Tiên đã an bài cho ngươi tới Chiến Trường cấp " HIR "%d " NOR "số " HIR "%d " NOR " phe " HIR "%s " NOR ". Hiện tại Chiến Trường đã có " HIR "%d " NOR "người tham gia báo danh. Ngươi cần hỗ trợ gì không ?\n" ESC "Huỷ bỏ đăng ký\ntalk %x# welcome.5\n" ESC "Nhận thưởng Chiến Trường\ntalk %x# welcome.4\n" ESC "Thoát", get_name(), level, wId, who->get_2("changping.country"), __FILE__->count_sign_up(level, wId), id, id));
		else
			send_user(who, "%c%s", ':', sprintf("%s:\n    Lão tiên ta đã sắp xếp cho ngươi đến " NOR "Chiến trường cấp %d  của Trường Bình Huyết Chiến số " HIR "%d" NOR ", phe tham gia là " HIR "%s" NOR ". Bây giờ chiến trường này đã có đã có " HIR "%d người " NOR "tham gia đăng ký. Ngươi còn muốn giúp gì không?\n" ESC "Tiến vào Chiến Trường\ntalk %x# welcome.3\n"
												// ESC "Bạn đã sử dụng 1 Kim Bảo (Tham gia Chiến Trường sẽ nhận được gấp đôi Chiến Tích)\ntalk %x# welcome.17\n"
												ESC "Nhận thưởng Chiến Trường\ntalk %x# welcome.4\n" ESC "Thoát",
												get_name(), level, wId, who->get_2("changping.country"), __FILE__->count_sign_up(level, wId), id, id, id));
		//			send_user(who,"%c%s",':',sprintf( "%s:\n    我是张果老！没错,我的确很老,老得我自己都不记得自己有多老了.不过我记得的事情有很多,例如二十年前的长平之战,我是记得清清楚楚,怎么样？你想去亲身了解一下长平之战吗？我可以把你带到我的记忆里面去参加长平之战,但是我不能确保你会加入赵军方还是秦军方？现在要去吗？\n"
		//				ESC"Tiến vào Trường Bình\ntalk %x# welcome.3\n"
		//				ESC"Bạn đã sử dụng 1 Kim Bảo (Tham gia Trường Bình sẽ nhận được gấp đôi Chiến Tích)\ntalk %x# welcome.17\n"
		//				ESC"Nhận thưởng Chiến Trường\ntalk %x# welcome.4\n"
		//				ESC"Thoát", get_name(),id,id,id )
		//				);
	}
	else
		send_user(who, "%c%s", ':', sprintf("%s:\n    Ta là Trương Quả Lão! Không sai, chính xác ta rất già, già tới mức ta không nhớ nổi mình bao nhiêu tuổi rồi. Thế nhưng chuyện ta nhớ được thì rất nhiều, ví dụ như trận chiến Trường Bình của 20 năm về trước ta vẫn còn nhớ như in. Thế nào? Ngươi muốn tự mình đi tìm hiểu trận chiến Trường Bình à? Ta có thể đưa người vào trong kí ức của ta để tham chiến, nhưng sẽ không đảm bảo ngươi được gia nhập quân Tần hay quân Triệu đâu? Bây giờ có muốn đi không?\n" ESC "Tham gia đơn lẻ\ntalk %x# welcome.1\n" ESC "Tham gia theo nhóm\ntalk %x# welcome.2\n" ESC HIG "Thuyết minh Chiến Tích\ntalk %x# welcome.9\n" ESC "Hoán đổi giải thưởng chiến trường\ntalk %x# welcome.4\n" ESC "Thoát", get_name(), id, id, id, id, id));
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int flag, p, z, level, x, y, wId, score;
	object who, item, obj;
	string cmd1;

	who = this_player();
	flag = to_int(arg);
	who->set_time("talk", 0);
	switch (flag)
	{
	case 1:
		if (who->get_level() < 40)
		{
			send_user(who, "%c%s", ':', me->get_name() + ":\n    Ngươi hiện tại tuổi tác còn quá nhỏ, không thích hợp tham gia Chiến Trường,đợi khi đạt cấp 40 rồi hãy đến tìm ta !\n" ESC "Rời khỏi");
			return;
		}
		player_sign_up(me, who);
		break;
	case 2:
		if (who->get_level() < 40)
		{
			send_user(who, "%c%s", ':', me->get_name() + ":\n    Ngươi hiện tại tuổi tác còn quá nhỏ, không thích hợp tham gia Chiến Trường,đợi khi đạt cấp 40 rồi hãy đến tìm ta !\n" ESC "Rời khỏi");
			return;
		}
		team_sign_up(me, who);
		break;
	case 3:
		enter_changping(who);
		break;
	case 4: //领取奖励
		x = who->get_save_2("changping.win");
		y = who->get_save_2("changping.lose");
		send_user(who, "%c%s", ':', sprintf("%s:\n    Ngươi tổng cộng tham gia " HIR "%d lần " NOR "trận chiến Trường Bình, trong đó thắng lợi " HIR "%d trận " NOR ". Hiện giờ tổng cộng có " HIR "%d điểm " NOR "Chiến Tích, ngươi muốn sử dụng điểm Chiến Tích này để đổi giải thưởng gì?\n" ESC "Đổi Danh Hiệu Chiến Trường\ntalk %x# welcome.7\n" ESC "Đổi Kinh nghiệm\ntalk %x# welcome.13\n" ESC "Hủy", me->get_name(), x + y, x, who->get_save_2("changping.score"), getoid(me), getoid(me), getoid(me), getoid(me)));
		break;
	case 5: // Hủy đăng ký
		send_user(who, "%c%s", ':', sprintf("%s:\n    Ngươi muốn bỏ đăng kí tham gia Trận Chiến Trường Bình đúng không? Nếu đúng như vậy, muốn tham gia trận chiến lần sau ngươi phải đợi ít nhất là 3 phút mới có thể đăng ký lại. Ngươi thật sự muôn hủy đăng ký không?\n" ESC "Xác định\ntalk %x# welcome.6\n" ESC "Hủy", me->get_name(), getoid(me)));
		break;
	case 6:
		abort_changping(who);
		break;
	case 7:
		give_title(me, who, 0);
		break;
	case 8:
		give_title(me, who, 1);
		break;
	case 9:
		send_user(who, "%c%s", ':', sprintf("%s:\n    Trong  Trận Chiến Trường Bình, Chiến Tích là một nhân tố rất quan trọng, nếu ngươi không biết Chiến Tích là gì thì thật đáng tiếc. Hãy chọn các mục dưới đây để tìm hiểu nhé!\n" ESC "Công dụng của Chiến Tích\ntalk %x# welcome.10\n" ESC "Nguồn gốc của Chiến Tích\ntalk %x# welcome.11\n" ESC "Sự thanh lý của Chiến Tích\ntalk %x# welcome.12\n" ESC "Thoát", me->get_name(), getoid(me), getoid(me), getoid(me)));
		break;
	case 10:
		send_user(who, "%c%s", ':', sprintf("%s :\n    Chiến Tích có 2 công dụng rất hữu ích:\n    1. " HIR "Hoán đổi kinh nghiệm: " NOR "Chỉ cần ngươi có Chiến Tích, là có thể đến gặp ta để hoán đổi thành điểm kinh nghiệm rồi.\n2. Để nhận " HIR "Danh Hiệu Chiến Trường " NOR "chỉ cần đạt đủ điểm Chiến Tích tương ứng. Danh hiệu cao cấp nhất sẽ tăng cho người chơi " HIR "600 Nội Công và Ngoại Công" NOR ". Sau khi nhận danh hiệu sẽ không mất điểm Chiến Tích. Tuy nhiên danh hiệu chỉ có thể sử dụng trong thời gian 1 tháng, hết thời gian này danh hiệu sẽ tự động biến mất. " HIR "Lưu ý: Ngày đầu tiên mỗi tháng, điểm Chiến Tích của người chơi sẽ bị giảm 1 nửa.\n", me->get_name()));
		break;
	case 11:
		send_user(who, "%c%s", ':', sprintf("%s :\n    Chỉ có tham gia Trận Chiến Trường Bình mới có thể nhận được Chiến Tích. Trong Trận Chiến Trường Bình, giết tướng lĩnh và người chơi của phe đối địch đều nhận được Chiến Tích, nếu tướng lĩnh bên mình bị giết, cũng sẽ bị trừ đi điểm Chiến Tích tương ứng.\n", me->get_name()));
		break;
	case 12:
		send_user(who, "%c%s", ':', sprintf("%s:\n Vào ngày đầu tiên mỗi tháng, tất cả điểm Chiến Tích sẽ bị giảm một nửa, danh hiệu sẽ bị mất sau 30 ngày kể từ lúc nhận danh hiêu, Người chơi hãy chú ý sử dụng hết tất cả điểm Chiến Tích trước khi bị xóa bởi hệ thống.\n", me->get_name()));
		break;
	case 13:
		send_user(who, "%c%s", ':', sprintf("%s :\n    Người chơi phải đạt được Chiến Tích nhất định mới có thể kinh nghiệm, mỗi lần đổi kinh nghiệm sẽ trừ đi số Chiến Tích tương ứng :\n" ESC "Sử dụng 20 điểm Chiến Tích\ntalk %x# welcome.14\n" ESC "Sử dụng 100 điểm Chiến Tích\ntalk %x# welcome.15\n" ESC "Sử dụng 1000 điểm Chiến Tích\ntalk %x# welcome.16\n" ESC "Hủy", me->get_name(), getoid(me), getoid(me), getoid(me)));
		break;
	case 14:
		if (who->get_save_2("changping.score") < 20)
		{
			notify("Không đủ 20 điểm Chiến Tích");
			return;
		}

		who->add_exp(who->get_level() * 815);
		who->add_save_2("changping.score", -20);
		break;
	case 15:
		if (who->get_save_2("changping.score") < 100)
		{
			notify("Không đủ 100 điểm Chiến Tích");
			return;
		}

		who->add_exp(who->get_level() * 3572);
		who->add_save_2("changping.score", -100);
		break;
	case 16:
		if (who->get_save_2("changping.score") < 1000)
		{
			notify("Không đủ 1000 điểm Chiến Tích");
			return;
		}

		who->add_exp(who->get_level() * 35720);
		who->add_save_2("changping.score", -1000);
		break;
	case 17:
		return;
		if (who->get_save("nhandoict") < 1)
		{
			if ("sys/sys/test_db"->get_yuanbao(who) < 10)
			{
				notify("Không đủ 1 Kim Nguyên Bảo");
				return;
			}
			"sys/sys/test_db"->add_yuanbao(who, -10);
			who->set_save("nhandoict", 1);
			enter_changping(who);
		}

		else
		{
			enter_changping(who);
		}
		break;
		/*	case 18:
		send_user(who,"%c%s",':',sprintf( "%s ：\n    Người chơi phải đạt được Chiến Tích nhất định mới có thể kinh nghiệm, mỗi lần đổi kinh nghiệm sẽ trừ đi số Chiến Tích tương ứng ：\n"
			ESC"Sử dụng 50 điểm chiến tích đổi 5 KNB\ntalk %x# welcome.19\n"
			ESC"Sử dụng 100 điểm chiến tích đổi 10 KNB\ntalk %x# welcome.20\n"
			ESC"Sử dụng 200 điểm Chiến Tích đổi 25 KNB\ntalk %x# welcome.21\n"
			ESC"Hủy", me->get_name(),getoid(me),getoid(me),getoid(me) )
				);
			break;*/
		/*	 case 19:
		 if ( who->get_save_2("changping.score") < 50 )
				{
				notify( "Không đủ 50 điểm Chiến Tích" );
				return ;
				}

		who->add_save("yuanbao",50);
		who->add_save_2("changping.score",-50) ;
USER_D->user_channel(sprintf(HIM"Với nhiều trận chiến anh dũng trên chiến trường "HIY "%s" HIG" đã đổi thành công 5 KNB", who->get_name() ));
		 break;
		 case 20:
		  if ( who->get_save_2("changping.score") < 100 )
				{
				notify( "Không đủ 100 điểm Chiến Tích" );
				return ;
				}

		who->add_save("yuanbao",100);
		who->add_save_2("changping.score",-100) ;
		USER_D->user_channel(sprintf(HIM"Với nhiều trận chiến anh dũng trên chiến trường "HIY "%s" HIG" đã đổi thành công 10 KNB", who->get_name() ));
		 break;
		 case 21:
		  if ( who->get_save_2("changping.score") < 200 )
				{
				notify( "Không đủ 200 điểm Chiến Tích" );
				return ;
				}

		who->add_save("yuanbao",250);
		who->add_save_2("changping.score",-200) ;
		USER_D->user_channel(sprintf(HIM"Với nhiều trận chiến anh dũng trên chiến trường "HIY "%s" HIG" đã đổi thành công 25 KNB", who->get_name() ));
		 break;*/
	}
}
//取得战场编号
int get_war_id(int level)
{
	int *nWar, wId, i, size;
	if (!mapp(get_2(sprintf("%d", level))))
	{
		WarId++;
		wId = WarId;
	}
	else
	{
		nWar = keys(get_2(sprintf("%d", level)));
		for (i = 0, size = sizeof(nWar); i < size; i++)
		{
			wId = to_int(nWar[i]);
			if (sizeof(get_2(sprintf("%d.%d.Tần Quốc", level, wId))) >= MAX_SIZE &&
				sizeof(get_2(sprintf("%d.%d.Triệu Quốc", level, wId))) >= MAX_SIZE)
				continue;
			break;
		}
		if (i >= size) //新开
		{
			WarId++;
			wId = WarId;
		}
	}
	return wId;
}
//个人报名
void player_sign_up(object me, object who)
{
	int level, id, wId, sec;
	int *nMem1, *nMem2, *nMem;
	string cTmp;
	if (localtime(time())[2] >= 0 && localtime(time())[2] <= 7) // 0h đến 7h ko vào đc chiến trường
	{
		send_user(who, "%c%s", '!', "Chiến Trường chỉ hoạt động từ 7 giờ đến 24 giờ");
	}
	level = who->get_level();
	if (level < 40)
		return;
	if (level <= 60)
		level = 60;
	else if (level <= 80)
		level = 80;
	//	else if ( level <= 100 )
	//		level = 100;
	else if (level <= 120)
		level = 120;
	else if (level <= 150)
		level = 150;
	else
		level = 200;
	id = who->get_number();

	if (check_valid_user(who))
	{
		send_user(who, "%c%s", '!', "Ngươi đã báo danh rồi !");
		return;
	}
	if ((sec = gone_time(who->get_2("changping.abort"))) < 5)
	{
		send_user(who, "%c%s", '!', sprintf("Muốn đăng kí lại phải đợi thời gian %d giây", 5 - sec));
		return;
	}
	wId = get_war_id(level);
	nMem1 = get_2(sprintf("%d.%d.Tần Quốc", level, wId));
	nMem2 = get_2(sprintf("%d.%d.Triệu Quốc", level, wId));
	if (!arrayp(nMem1))
		nMem1 = ({});
	if (!arrayp(nMem2))
		nMem2 = ({});

	if (sizeof(nMem1) < sizeof(nMem2))
	{
		nMem = nMem1;
		cTmp = "Tần Quốc";
	}
	else if (sizeof(nMem1) > sizeof(nMem2))
	{
		nMem = nMem2;
		cTmp = "Triệu Quốc";
	}
	else if (random(2))
	{
		nMem = nMem1;
		cTmp = "Tần Quốc";
	}
	else
	{
		nMem = nMem2;
		cTmp = "Triệu Quốc";
	}
	nMem += ({id});
	set_2(sprintf("%d.%d.%s", level, wId, cTmp), nMem);
	who->set_2("changping.level", level);
	who->set_2("changping.country", cTmp);
	who->set_2("changping.warid", wId);
	who->delete_2("changping.start");
	//	send_user(who,"%c%s",';',"你报名加入长平之战！");
	send_user(who, "%c%s", ':', sprintf("%s:\n    Hehe, lão tiên ta đã sắp xếp cho ngươi đến  Chiến Trường cấp %d, Trận Chiến Trường Bình số " HIR "%d, phe tham gia là %s" NOR ", bây giờ bây giờ trận chiến này đã có đã có " HIR "%d người " NOR "tham gia đăng kí.\n" ESC "Thoát", me->get_name(), level, wId, cTmp, sizeof(nMem1 + nMem2) + 1));
	check_war_begin(level, wId);
}
//队伍报名
void team_sign_up(object me, object who)
{
	int i, size, *nMem1, *nMem2, *nMem, level, level1, level2, wId, *nWar, sec;
	object *nTeam, player;
	string cTmp;
	if (localtime(time())[2] >= 0 && localtime(time())[2] <= 7)
	{
		send_user(who, "%c%s", '!', "Chiến Trường chỉ hoạt động từ 7 giờ đến 24 giờ");
	}
	if (!who->is_leader())
	{
		send_user(who, "%c%s", '!', "Ngươi không phải Đội trưởng!");
		return;
	}
	nTeam = who->get_team();
	nTeam -= ({0});
	size = sizeof(nTeam);
	if (!size)
		return;
	level = who->get_level();
	if (level < 40)
		return;
	if (level <= 60)
	{
		level1 = 40;
		level2 = 60;
	}
	else if (level <= 80)
	{
		level1 = 61;
		level2 = 80;
	}
	//	else if ( level <= 100 )
	//	{
	//		level1 = 81;
	//		level2 = 100;
	//	}
	else if (level <= 120)
	{
		level1 = 81;
		level2 = 120;
	}
	else if (level <= 150)
	{
		level1 = 121;
		level2 = 150;
	}
	else
	{
		level1 = 151;
		level2 = 200;
	}
	for (i = 0; i < size; i++)
	{
		player = nTeam[i];
		if (!inside_screen_2(player, who))
		{
			//			send_user(who,"%c%s",':',me->get_name()+":\n    你的队伍有人不在现场,不能报名.\n"ESC"Rời khỏi");
			send_user(who, "%c%s", ':', me->get_name() + ":\n    Thành viên trong nhóm của ngươi " HIR + player->get_name() + NOR " không có mặt, không thể báo danh.\n" ESC "Rời khỏi");
			return;
		}
		if ((level = player->get_level()) < 40)
		{
			//			send_user(who,"%c%s",':',me->get_name()+":\n    你队伍中有人现在年纪还小,不适合参加长平之战,等他40级以后再来吧！\n"ESC"Rời khỏi");
			send_user(who, "%c%s", ':', me->get_name() + ":\n    Thành viên trong nhóm của ngươi " HIR + player->get_name() + NOR " cấp bậc dưới 40, không thể tham gia Chiến Trường\n" ESC "Rời khỏi");
			return;
		}
		if (level < level1 || level > level2)
		{
			//			send_user(who,"%c%s",':',me->get_name()+":\n    你队伍中有人的等级跟队伍的等级段不一致,不能报名！\n"ESC"Rời khỏi");
			send_user(who, "%c%s", ':', me->get_name() + ":\n    Thành viên trong nhóm của ngươi " HIR + player->get_name() + NOR " cùng những thành viên trong đội cấp bậc chênh lệch quá cao.\n" ESC "Rời khỏi");
			return;
		}
		if (check_valid_user(player))
		{
			//			send_user(who,"%c%s",':',me->get_name()+":\n    你队伍中有人已经报名了！\n"ESC"Rời khỏi");
			send_user(who, "%c%s", ':', me->get_name() + ":\n    Thành viên trong nhóm của ngươi " HIR + player->get_name() + NOR " đã báo danh rồi, khi khác hãy đến.\n" ESC "Rời khỏi");
			return;
		}
		if ((sec = gone_time(player->get_2("changping.abort"))) < 5)
		{
			send_user(player, "%c%s", '!', sprintf("Muốn đăng kí lại phải đợi thời gian %d giây", 5 - sec));
			send_user(who, "%c%s", ':', me->get_name() + ":\n    Thành viên trong nhóm của ngươi " HIR + player->get_name() + NOR " tạm thời không thể vào Chiến Trường, khi khác hãy đến.\n" ESC "Rời khỏi");
			return;
		}
	}
	level = level2;
	wId = get_war_id(level);
	nMem1 = get_2(sprintf("%d.%d.Tần Quốc", level, wId));
	nMem2 = get_2(sprintf("%d.%d.Triệu Quốc", level, wId));
	if (!arrayp(nMem1))
		nMem1 = ({});
	if (!arrayp(nMem2))
		nMem2 = ({});
	if (sizeof(nMem1) < sizeof(nMem2))
	{
		nMem = nMem1;
		cTmp = "Tần Quốc";
	}
	else if (sizeof(nMem1) > sizeof(nMem2))
	{
		nMem = nMem2;
		cTmp = "Triệu Quốc";
	}
	else if (random(2))
	{
		nMem = nMem1;
		cTmp = "Tần Quốc";
	}
	else
	{
		nMem = nMem2;
		cTmp = "Triệu Quốc";
	}
	if (sizeof(nMem) > (MAX_SIZE - sizeof(nTeam)))
	{
		send_user(who, "%c%s", '!', "Chiến Trường đã đầy người rồi ! hãy đợi đến lượt sau rồi báo danh");
		return;
	}
	for (i = 0; i < size; i++)
	{
		player = nTeam[i];
		nMem += ({player->get_number()});
		player->set_2("changping.level", level);
		player->set_2("changping.country", cTmp);
		player->set_2("changping.warid", wId);
		player->delete_2("changping.start");
		send_user(player, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Lão Tiên đã an bài cho ngươi tới Chiến Trường cấp " HIR "%d " NOR "số " HIR "%d " NOR " phe " HIR "%s " NOR ". Hiện tại Chiến Trường đã có " HIR "%d " NOR "người tham gia báo danh..\n" ESC "Rời khỏi", me->get_name(), level, wId, cTmp, sizeof(nMem1 + nMem2) + size));
	}
	set_2(sprintf("%d.%d.%s", level, wId, cTmp), nMem);
	//	send_user(who,"%c%s",';',"你的队伍报名加入长平之战！");
	check_war_begin(level, wId);
}
//检查是否开战
void check_war_begin(int level, int wId)
{
	int *nMem1, *nMem2, z, d = 903, i;
	object player, npc, map;
	mapping mpTmp, mpTmp1;
	string name1, name2;

	if (get_2(sprintf("%d.%d.z", level, wId))) //已经开战了
		return;
	nMem1 = get_2(sprintf("%d.%d.Tần Quốc", level, wId));
	nMem2 = get_2(sprintf("%d.%d.Triệu Quốc", level, wId));
	if (sizeof(nMem1) < MIN_SIZE || sizeof(nMem2) < MIN_SIZE)
		return;
	//开战
	if ((z = find_map_flag(1000, 2999, 0)) <= 0)
		return;
	init_virtual_map(z, d);
	// map = new ("/inh/std/changping");
	// if (level == 60)
	// {
	map = new ("/inh/std/changping2");

	map->set_war_attack("Tần Quốc");
	map->set_war_defense("Triệu Quốc"); // 记录战争双方
	map->set_heart_sec(0);				// 校正时钟
	map->set_war(WAR_READY_2);			// 记录战争准备
	map->set_starttime(1);
	// NPC_BATTLE_D->war_ready_notice(map);
	// }
	map->set_client_id(d);
	map->set("warid", wId);
	map->set("warlevel", level);
	map->set("warbegin", time());
	set_map_object(map, map->set_id(z));
	set_2(sprintf("%d.%d.z", level, wId), z);
	name1 = map->get_war_attack();
	name2 = map->get_war_defense();
	"sys/npc/changping2"->war_begin_count_down_notice(map);
	//生成NPC
	//小精怪
	npc = new ("/npc/88/8801");
	npc->set_city_name("Tần Quốc");
	npc->add_to_scene(z, 40, 51, 8);
	npc = new ("/npc/88/8801");
	npc->set_city_name("Triệu Quốc");
	npc->add_to_scene(z, 201, 149, 4);
	// Tần Quốc
	mpTmp1 = mpNpc["Tần Quốc"];
	for (i = 1; i <= 5; i++)
	{
		mpTmp = mpTmp1[i];
		npc = new (mpTmp["file"]);
		npc->set_level(level);
		init_npc(npc, level);
		npc->set_2("nPos", mpTmp["nPos"]);
		npc->set("warid", wId);
		npc->set_name_color(HIR);
		if (i == 1)
		{
			npc->set_city_name(name1);
			npc->set_front(1);
			npc->set_manager(npc);
			map->set_manager(npc);
		}
		npc->add_to_scene(z, mpTmp["nPos"][0], mpTmp["nPos"][1], 3);
		map->set(sprintf("qin%d", i), npc);
	}
	// Triệu Quốc
	mpTmp1 = mpNpc["Triệu Quốc"];
	for (i = 1; i <= 5; i++)
	{
		mpTmp = mpTmp1[i];
		npc = new (mpTmp["file"]);
		npc->set_level(level);
		init_npc(npc, level);
		npc->set_2("nPos", mpTmp["nPos"]);
		npc->set("warid", wId);
		npc->set_name_color(HIB);

		if (i == 1)
		{
			npc->set_city_name(name2);
			npc->set_front(2);
			npc->set_manager(npc);
			map->set_manager_2(npc);
		}
		npc->add_to_scene(z, mpTmp["nPos"][0], mpTmp["nPos"][1], 3);
		map->set(sprintf("zhao%d", i), npc);
	}

	//公告
	nMem1 += nMem2;
	for (i = 0, z = sizeof(nMem1); i < z; i++)
	{
		player = find_char(sprintf("%d", nMem1[i]));
		if (!objectp(player))
			continue;
		send_user(player, "%c%c%w%s", ':', 3, 0, sprintf("Hiện giờ đã có thể tiến vào Trận Chiến Trường Bình số %d, ngươi thuộc phe %s, ngươi có muốn lập tức tiến vào? (Vượt quá 60 giây xem như bỏ cuộc)\n" ESC "Tiến vào Chiến Trường\ndesc changping yes\n"
														 // ESC "Bạn đã sử dụng 1 Kim Bảo (Tham gia Trường Bình sẽ nhận được gấp đôi Chiến Tích)\ndesc changping yes2\n"
														 ESC "Bỏ cuộc\ndesc changping no\n",
														 player->get_2("changping.warid"), player->get_2("changping.country")));
		player->set_2("changping.start", time());
	}
	map->check_fighter(60);
}

//清除报名
void delete_sign_up(object who)
{
	int id, level, *nMem, wId;
	string cTmp;

	id = who->get_number();
	level = who->get_2("changping.level");
	cTmp = who->get_2("changping.country");
	wId = who->get_2("changping.warid");
	if (!level)
		return;
	who->delete_2("changping");
	// who->set_save("nhandoict", 0);
	nMem = get_2(sprintf("%d.%d.%s", level, wId, cTmp));
	if (!sizeof(nMem))
		return;
	if (member_array(id, nMem) == -1)
		return;
	nMem -= ({id});
	set_2(sprintf("%d.%d.%s", level, wId, cTmp), nMem);
}

int init_npc(object npc, int level)
{
	string cTmp;
	int *nTmp;

	npc->set_level(level);
	cTmp = sprintf("%s%d", npc->get_name(), level);
	if (!arrayp(nTmp = mpInfo[cTmp]))
	{
		log_file("changping.txt", sprintf("%s %s yêu cầu đẳng cấp %d\n", short_time(), npc->get_name(), level));
		return;
	}
	npc->set_max_hp(nTmp[0]);
	npc->set_max_mp(nTmp[1]);
	npc->set_ap(nTmp[2]);
	npc->set_dp(nTmp[3]);
	npc->set_cp(nTmp[4]);
	npc->set_pp(nTmp[5]);
	npc->set_sp(nTmp[6]);
	return 1;
}
//发送最终报表
void send_war_report(object who, object map)
{
	int i, size, pos, score, win, lose, *nTmp, id;
	string cTmp, cCountry, cName;
	mapping mpTmp, mpTmp1;

	mpTmp = map->get_2("player_info");
	if (!mapp(mpTmp))
		return;
	cCountry = who->get_2("changping.country");
	if (!stringp(cCountry))
		return;
	if (who->get_2("changping.warid") != map->get("warid"))
		return;
	id = who->get_number();
	if (cCountry == map->get_2("win_country"))
	{
		cTmp = "   Với sự chiến đấu anh dũng của các bằng hữu, quân ta đã giành thắng lợi. Mong rằng từ nay trở đi mọi người sẽ gặt hái được nhiều thành quả thắng lợi hơn nữa.";
		cName = "|" + sprintf(HIY "WIN - CHIẾN THẮNG！");
	}
	else
	{
		cTmp = "   Mặc dù các bạn đã anh dũng chiến đấu, nhưng quân ta vẫn bại trận. Hi vọng từ nay về sau mọi người hãy cố gắng hơn nữa.";
		cName = "|" + sprintf(HIY "LOSE - BẠI TRẬN！");
	}
	cTmp += "|" + map->get_2("win_country") + "|Triệu Quốc|Tần Quốc";
	send_user(who, "%c%c%s", 0xA5, 1, cName);
	if (cCountry == "Tần Quốc")
	{
		win = map->get_2("qin_score");
		lose = map->get_2("zhao_score");
	}
	else
	{
		win = map->get_2("zhao_score");
		lose = map->get_2("qin_score");
	}
	if (mapp(mpTmp[id]))
		score = mpTmp[id]["score"];
	send_user(who, "%c%c%d%d%d%d%s", 0xA5, 6,
			  map->get_2("total_player"), win, lose, score, cTmp);
	nTmp = map->get_2("sort_player");
	size = sizeof(nTmp);
	if (!size)
		return;
	pos = member_array(id, nTmp);
	if (size > 10)
		size = 10;
	for (i = 0; i < size; i++)
	{
		mpTmp1 = mpTmp[nTmp[i]];
		send_user(who, "%c%c%d%d%d%s", 0xA5, 7,
				  i + 1, mpTmp1["kill"], mpTmp1["die"],
				  mpTmp1["name"] + "|" + mpTmp1["country"] + "|" + mpTmp1["family"]);
	}
	if (pos >= 10)
	{
		mpTmp1 = mpTmp[id];
		send_user(who, "%c%c%d%d%d%s", 0xA5, 7,
				  pos + 1, mpTmp1["kill"], mpTmp1["die"],
				  mpTmp1["name"] + "|" + mpTmp1["country"] + "|" + mpTmp1["family"]);
	}
}
//活动结束
void game_over(object map, string cWin)
{
	int i, size, iTime, score, total, *nTmp = ({});
	object who, *nPlayer;
	mapping mpTmp = ([]);
	mixed *mixTime;
	iTime = time();
	mixTime = localtime(iTime);

	nPlayer = map->get_all_user();
	map->set("finish", 1);
	map->set("win", cWin);
	map->game_over();
	delete_2(sprintf("%d.%d", map->get("warlevel"), map->get("warid")));
	//计算队伍得分
	map->add_2("totalscore.Tần Quốc", 450);
	map->add_2("totalscore.Triệu Quốc", 450);
	for (i = 0, size = sizeof(nPlayer); i < size; i++)
	{
		who = nPlayer[i];
		if (!objectp(who))
			continue;
		if (who->get_2("changping.warid") != map->get("warid"))
			continue;
		if (who->get_2("changping.country") == cWin)
			who->add_save_2("changping.win", 1);
		else
			who->add_save_2("changping.lose", 1);
		score = map->get_2(sprintf("score.%d", who->get_number()));
		score += 450;
		if (score < 0)
			score = 0;
		score = change_score(score); //转换成战绩
		score += kill_score(who, map);
		if (mixTime[TIME_WDAY] == 6 || mixTime[TIME_WDAY] == 0)
		{
			// if ((mixTime[TIME_WDAY] == 2 && (mixTime[TIME_HOUR] >= 14 && mixTime[TIME_HOUR] < 16)) ||
			// 	(mixTime[TIME_WDAY] == 2 && (mixTime[TIME_HOUR] >= 19 && mixTime[TIME_HOUR] < 22)) ||
			// 	(mixTime[TIME_WDAY] == 4 && (mixTime[TIME_HOUR] >= 14 && mixTime[TIME_HOUR] < 16)) ||
			// 	(mixTime[TIME_WDAY] == 4 && (mixTime[TIME_HOUR] >= 19 && mixTime[TIME_HOUR] < 22)) ||
			// 	(mixTime[TIME_WDAY] == 6 && (mixTime[TIME_HOUR] >= 14 && mixTime[TIME_HOUR] < 16)) ||
			// 	(mixTime[TIME_WDAY] == 6 && (mixTime[TIME_HOUR] >= 19 && mixTime[TIME_HOUR] < 22)) ||
			// 	(mixTime[TIME_WDAY] == 0 && (mixTime[TIME_HOUR] >= 14 && mixTime[TIME_HOUR] < 16)) ||
			// 	(mixTime[TIME_WDAY] == 0 && (mixTime[TIME_HOUR] >= 19 && mixTime[TIME_HOUR] < 22)))
			// {
			// 	who->add_save_2("changping.score", score * 4);
			// 	"sys/sys/test_db"->add_yuanbao(who, 1);
			// 	who->add_save_2("changping.totalscore", score * 4);
			// 	send_user(who, "%c%s", ';', sprintf("Chiến Tích của bạn ở trong Chiến Trường là %d Chiến tích", score * 4));
			// 	log_file("changping.txt", sprintf("%s %d Tổng quát %d giết %d chiến tích người 1 %d chiến tích 2 %d Tổng chiến tích %d \n", short_time(), who->get_number(), map->get_2(sprintf("score.%d", who->get_number())) + 450, map->get_2(sprintf("kill.%d", who->get_number())), score * 4 - kill_score(who, map), kill_score(who, map), score * 4));
			// 	mpTmp[who->get_number()] = (["name":who->get_name(),
			// 							   "family":who->get_fam_name(),
			// 							  "country":who->get_2("changping.country"),
			// 								 "kill":map->get_2(sprintf("kill.%d", who->get_number())),
			// 								  "die":map->get_2(sprintf("killed.%d", who->get_number())),
			// 								"score":score * 4,
			// 	]);
			// 	total++;
			// 	nTmp += ({who->get_number()});
			// }
			// else
			// {
			// 	who->add_save_2("changping.score", score * 2);
			// 	"sys/sys/test_db"->add_yuanbao(who, 1);
			// 	who->add_save_2("changping.totalscore", score * 2);
			// 	send_user(who, "%c%s", ';', sprintf("Chiến Tích của bạn ở trong Chiến Trường là %d Chiến tích", score * 2));
			// 	log_file("changping.txt", sprintf("%s %d Tổng quát %d giết %d chiến tích người 1 %d chiến tích 2 %d Tổng chiến tích %d \n", short_time(), who->get_number(), map->get_2(sprintf("score.%d", who->get_number())) + 450, map->get_2(sprintf("kill.%d", who->get_number())), score * 2 - kill_score(who, map), kill_score(who, map), score * 2));
			// 	mpTmp[who->get_number()] = (["name":who->get_name(),
			// 							   "family":who->get_fam_name(),
			// 							  "country":who->get_2("changping.country"),
			// 								 "kill":map->get_2(sprintf("kill.%d", who->get_number())),
			// 								  "die":map->get_2(sprintf("killed.%d", who->get_number())),
			// 								"score":score * 2,
			// 	]);
			// 	total++;
			// 	nTmp += ({who->get_number()});
			// }
			who->add_save_2("changping.score", score * 8);
			"sys/sys/test_db"->add_yuanbao(who, 1);
			who->add_save_2("changping.totalscore", score * 8);
			send_user(who, "%c%s", ';', sprintf("Chiến Tích của bạn ở trong Chiến Trường là %d Chiến tích", score * 4));
			log_file("changping.txt", sprintf("%s %d Tổng quát %d giết %d chiến tích người 1 %d chiến tích 2 %d Tổng chiến tích %d \n", short_time(), who->get_number(), map->get_2(sprintf("score.%d", who->get_number())) + 450, map->get_2(sprintf("kill.%d", who->get_number())), score * 4 - kill_score(who, map), kill_score(who, map), score * 4));
			mpTmp[who->get_number()] = (["name":who->get_name(),
									   "family":who->get_fam_name(),
									  "country":who->get_2("changping.country"),
										 "kill":map->get_2(sprintf("kill.%d", who->get_number())),
										  "die":map->get_2(sprintf("killed.%d", who->get_number())),
										"score":score * 8,
			]);
			total++;
			nTmp += ({who->get_number()});
		}
		else
		{
			who->add_save_2("changping.score", score * 4);
			"sys/sys/test_db"->add_yuanbao(who, 1);
			who->add_save_2("changping.totalscore", score * 4);
			send_user(who, "%c%s", ';', sprintf("Chiến Tích của bạn ở trong Chiến Trường là %d Chiến tích", score * 2));
			log_file("changping.txt", sprintf("%s %d Tổng quát %d giết %d chiến tích người 1 %d chiến tích 2 %d Tổng chiến tích %d \n", short_time(), who->get_number(), map->get_2(sprintf("score.%d", who->get_number())) + 450, map->get_2(sprintf("kill.%d", who->get_number())), score * 2 - kill_score(who, map), kill_score(who, map), score * 2));
			mpTmp[who->get_number()] = (["name":who->get_name(),
									   "family":who->get_fam_name(),
									  "country":who->get_2("changping.country"),
										 "kill":map->get_2(sprintf("kill.%d", who->get_number())),
										  "die":map->get_2(sprintf("killed.%d", who->get_number())),
										"score":score * 4,
			]);
			total++;
			nTmp += ({who->get_number()});
			// if ((mixTime[TIME_WDAY] == 2 && (mixTime[TIME_HOUR] >= 14 && mixTime[TIME_HOUR] < 16)) ||
			// 	(mixTime[TIME_WDAY] == 2 && (mixTime[TIME_HOUR] >= 19 && mixTime[TIME_HOUR] < 22)) ||
			// 	(mixTime[TIME_WDAY] == 4 && (mixTime[TIME_HOUR] >= 14 && mixTime[TIME_HOUR] < 16)) ||
			// 	(mixTime[TIME_WDAY] == 4 && (mixTime[TIME_HOUR] >= 19 && mixTime[TIME_HOUR] < 22)) ||
			// 	(mixTime[TIME_WDAY] == 6 && (mixTime[TIME_HOUR] >= 14 && mixTime[TIME_HOUR] < 16)) ||
			// 	(mixTime[TIME_WDAY] == 6 && (mixTime[TIME_HOUR] >= 19 && mixTime[TIME_HOUR] < 22)) ||
			// 	(mixTime[TIME_WDAY] == 0 && (mixTime[TIME_HOUR] >= 14 && mixTime[TIME_HOUR] < 16)) ||
			// 	(mixTime[TIME_WDAY] == 0 && (mixTime[TIME_HOUR] >= 19 && mixTime[TIME_HOUR] < 22)))
			// {
			// 	who->add_save_2("changping.score", score * 8);
			// 	"sys/sys/test_db"->add_yuanbao(who, 1);
			// 	who->add_save_2("changping.totalscore", score * 8);
			// 	send_user(who, "%c%s", ';', sprintf("Chiến Tích của bạn ở trong Chiến Trường là %d Chiến tích", score * 8));
			// 	//log_file("changping.txt", sprintf("%s %d Tổng quát %d giết %d chiến tích người 1 %d chiến tích 2 %d Tổng chiến tích %d \n", short_time(), who->get_number(), map->get_2(sprintf("score.%d", who->get_number())) + 450, map->get_2(sprintf("kill.%d", who->get_number())), score * 8 - kill_score(who, map), kill_score(who, map), score * 8));
			// 	who->set_save("nhandoict", 0);
			// 	mpTmp[who->get_number()] = (["name":who->get_name(),
			// 							   "family":who->get_fam_name(),
			// 							  "country":who->get_2("changping.country"),
			// 								 "kill":map->get_2(sprintf("kill.%d", who->get_number())),
			// 								  "die":map->get_2(sprintf("killed.%d", who->get_number())),
			// 								"score":score * 8,
			// 	]);
			// 	total++;
			// 	nTmp += ({who->get_number()});
			// }
			// else
			// {
			// 	who->add_save_2("changping.score", score * 4);
			// 	"sys/sys/test_db"->add_yuanbao(who, 1);
			// 	who->add_save_2("changping.totalscore", score * 4);
			// 	send_user(who, "%c%s", ';', sprintf("Chiến Tích của bạn ở trong Chiến Trường là %d Chiến tích", score * 4));
			// 	//	log_file("changping.txt", sprintf("%s %d Tổng quát %d giết %d chiến tích người 1 %d chiến tích 2 %d Tổng chiến tích %d \n", short_time(), who->get_number(), map->get_2(sprintf("score.%d", who->get_number())) + 450, map->get_2(sprintf("kill.%d", who->get_number())), score * 4 - kill_score(who, map), kill_score(who, map), score * 4));
			// 	who->set_save("nhandoict", 0);
			// 	mpTmp[who->get_number()] = (["name":who->get_name(),
			// 							   "family":who->get_fam_name(),
			// 							  "country":who->get_2("changping.country"),
			// 								 "kill":map->get_2(sprintf("kill.%d", who->get_number())),
			// 								  "die":map->get_2(sprintf("killed.%d", who->get_number())),
			// 								"score":score * 4,
			// 	]);
			// 	total++;
			// 	nTmp += ({who->get_number()});
			// }
		}
	}
	map->set_2("player_info", mpTmp);
	map->set_2("win_country", cWin);
	map->set_2("total_player", total);
	map->set_2("attack_country", "Tần Quốc");
	map->set_2("defend_country", "Triệu Quốc");
	map->set_2("qin_score", map->get_2("totalscore.Tần Quốc") * 10000 / 2050);
	map->set_2("zhao_score", map->get_2("totalscore.Triệu Quốc") * 10000 / 2050);
	if (sizeof(mpTmp))
	{
		nTmp = sort_array(nTmp, "sort_cmp", map);
		map->set_2("sort_player", nTmp);
	}
	for (i = 0, size = sizeof(nPlayer); i < size; i++)
	{
		who = nPlayer[i];
		if (!objectp(who))
			continue;
		if (who->get_2("changping.warid") != map->get("warid"))
			continue;
		send_war_report(who, map);
	}
}

//杀死NPC的奖励和惩罚
void win_bonus(object me, object who)
{
	int iRank, iAdd, iSub, i, size, z;
	object *nPlayer, map, owner;
	string cCountry1, cCountry2, cTmp, cName, cWin;

	if (!who->is_user())
		return;
	owner = who->get_owner();
	if (owner && owner->is_user())
		who = owner;
	iRank = me->get("rank");
	//	if ( who->get_save("nhandoict") < 1 )
	//	{
	if (iRank >= 1 && iRank < 6)
		iAdd = 1;
	//	}
	//	else
	//	{
	//		if ( iRank >= 1 && iRank < 6 )
	//		iAdd = 10;
	//	}

	/*	if ( iRank == 1 )
		iAdd = 500;
	else if ( iRank == 2 )
	{
		iAdd = 200;
		iSub = -80;
	}
	else if ( iRank >2 && iRank < 6 )
	{
		iAdd = 300;
		iSub = -120;
	}*/
	cCountry1 = who->get_2("changping.country");
	cCountry2 = me->get_city_name();
	cName = me->get_name();
	z = get_z(me);
	map = get_map_object(z);
	if (!map)
		return;
	nPlayer = map->get_all_user();
	if (!stringp(cCountry1))
		cCountry1 = "";
	if (!stringp(cCountry2))
		cCountry2 = "";
	nPlayer -= ({0});
	for (i = 0, size = sizeof(nPlayer); i < size; i++)
	{
		who = nPlayer[i];
		if (!objectp(who))
			continue;
		if ((cTmp = who->get_2("changping.country")) && cTmp == cCountry1) //同一方的
			map->add_2(sprintf("score.%d", who->get_number()), iAdd * who->get_online_rate() / 100);
		else if ((cTmp = who->get_2("changping.country")) && cTmp == cCountry2) //对方的
			map->add_2(sprintf("score.%d", who->get_number()), iSub);
	}
	//计算队伍得分
	map->add_2(sprintf("totalscore.%s", cCountry1), iAdd);
	map->add_2(sprintf("totalscore.%s", cCountry2), iSub);
	map->set("success", 1);
	if (cName == "Bạch Khởi")
	{
		cWin = "Triệu Quốc";
		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, HIR "Chủ tướng Bạch Khởi quân Tần đã bị quân Triệu đánh bại! Trận chiến Trường Bình kết thúc với thắng lợi của quân Triệu, sau 1 phút mọi người sẽ trở về nước Chu.");
	}
	else if (cName == "Liêm Pha")
	{
		cWin = "Tần Quốc";
		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, HIR "Chủ tướng Liêm Pha quân Tần đã bị quân Triệu đánh bại! Trận chiến Trường Bình kết thúc với thắng lợi của quân Triệu, sau 1 phút mọi người sẽ trở về nước Chu.");
	}
	else if (cName == "Vương Ngật")
		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, "Tần quân Phó Tướng Vương Ngật đã bị quân Triệu đánh bại !");
	else if (cName == "Triệu Quát")
		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, "Triệu quân Phó Tướng Triệu Quát đã bị quân Tần đánh bại !");
	else if (cName == "Tư Mã Thác")
		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, "Tần quân Tư Mã Thác đã bị quân Triệu đánh bại !");
	else if (cName == "Phùng Đình")
		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, "Triệu quân Phùng Đinh đã bị quân Tần đánh bại !");
	else if (cName == "Vương Lăng")
		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, "Tần quân Tả Tiên Phong Vương Lăng đã bị quân Triệu đánh bại !");
	else if (cName == "Lạc Thừa")
		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, "Triệu quân Tả Tiên Phong Lạc Thừa đã bị quân Tần đánh bại !");
	else if (cName == "Mông Ngạo")
		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, "Tần quân Hữu Tiên Phong Mông Ngạo đã bị quân Triệu đánh bại !");
	else if (cName == "Quách Khai")
		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, "Triệu quân Hữu Tiên Phong Quách Khai đã bị quân Tần đánh bại !");
	if (stringp(cWin) && !map->get("finish"))
	{
		game_over(map, cWin);
	}
}

int can_fight(object me, object who)
{
	object owner, map;
	string leader, id;

	if (!who)
		return 0;

	if (who->is_die())
	{
		me->set_enemy(0);
		return 0;
	}

	// if (who->is_npc() && objectp(owner = who->get_owner()))
	// 	who = owner;

	// if (who->is_npc())
	// {
	// 	me->set_enemy(0);
	// 	return 0;
	// }

	if (me->get_city_name() == who->get_2("changping.country"))
		return 0;
	if (me->get_city_name() == who->get_city_name())
		return 0;
	// if (me->get("warid") != who->get_2("changping.warid"))
	// 	return 0;

	map = get_map_object(get_z(me));
	if (!map)
		return 0;

	if (map->get("finish"))
		return 0;

	return 1;
}

int can_be_fighted(object me, object who)
{
	int i, size, p;
	object owner, map, *nPlayer, npc;
	string leader, id, cTmp, cTmp1;

	if (!who)
		return 0;

	// if (who->is_npc() && objectp(owner = who->get_owner()))
	// 	who = owner;
	// if (who->is_npc())
	// {
	// 	me->set_enemy(0);
	// 	return 0;
	// }

	if (me->get_city_name() == who->get_2("changping.country"))
		return 0;
	if (me->get_city_name() == who->get_city_name())
		return 0;

	// if (me->get("warid") != who->get_2("changping.warid"))
	// 	return 0;

	map = get_map_object(get_z(me));
	if (!map)
		return;

	if (map->get("finish"))
		return 0;

	if (gone_time(me->get("relax")) > 15)
	{
		if (!map)
			return;
		nPlayer = map->get_all_user();
		nPlayer -= ({0});
		if (who->get_2("changping.country") == "Tần Quốc")
		{
			cTmp = "Quân Tần";
			cTmp1 = "Quân Triệu";
		}
		else if (who->get_2("changping.country") == "Triệu Quốc")
		{
			cTmp1 = "Quân Tần";
			cTmp = "Quân Triệu";
		}
		// send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, sprintf("Đai anh hùng %s của quân %s đã tấn công tướng quân %s ", cTmp, cTmp1, me->get_name()));
		if (me->get_name() == "Bạch Khởi")
			npc = map->get("qin2");
		else if (me->get_name() == "Liêm Pha")
			npc = map->get("zhao2");
		if (npc)
		{
			p = get_valid_xy(get_z(me), get_x(me) + random(10) - 5, get_y(me) + random(10) - 5, IS_CHAR_BLOCK);
			if (p)
			{
				npc->set_2("nPos", ({p / 1000, p % 1000}));
				npc->add_to_scene(get_z(me), p / 1000, p % 1000, 3, 9413);
			}
		}
	}

	me->set("relax", time());
	// if (me->get("lowhp") == 0)
	// {
	// 	if (me->get_hp() < me->get_max_hp() / 2)
	// 	{
	// 		if (who->get_2("changping.country") == "Tần Quốc")
	// 		{
	// 			cTmp = "Quân Tần";
	// 			cTmp1 = "Quân Triệu";
	// 		}
	// 		else if (who->get_2("changping.country") == "Triệu Quốc")
	// 		{
	// 			cTmp1 = "Quân Tần";
	// 			cTmp = "Quân Triệu";
	// 		}
	// 		nPlayer = map->get_all_user();
	// 		nPlayer -= ({0});
	// 		me->set("lowhp", 1);
	// 		send_user(nPlayer, "%c%c%d%s", 0x43, 10, 0, sprintf("Bởi vì %s mãnh liệt tấn công,%s %s Tướng quân rơi vào khổ chiến, %s binh sĩ hãy nhanh nhanh trợ giúp.", cTmp, cTmp1, me->get_name(), cTmp1));
	// 	}
	// }

	return 1;
}

void before_destruct()
{
	"npc/88/8801"->set_2("database", get_dbase_2());
	"npc/88/8801"->set_2("warid", WarId);
}
//杀死对方玩家的奖励
void kill_player_bonus(object me, object who)
{
	int exp;
	object owner, map;
	if (!who->is_user())
		return;
	owner = me->get_owner();
	if (owner)
		me = who;
	write_user(who, HIR "Bạn bị %s tiêu diệt rồi!", me->get_name());
	if (!me->is_user())
		return;
	me->add_exp(exp = 100 + random(50));
	write_user(me, HIR "Bạn đã giết chết %s", who->get_name());
	map = get_map_object(get_z(me));
	if (map && map->is_changping())
	{
		if (me->get_online_rate() == 100)
		{
			map->add_2(sprintf("kill.%d", me->get_number()), 1);
			me->add_save_2("changping.kill", 1);
		}
		if (who->get_online_rate() == 100)
		{
			map->add_2(sprintf("killed.%d", who->get_number()), 1);
			who->add_save_2("changping.killed", 1);
		}
	}
}

void summon_guard(object me)
{
	int i, size, x, y, z, count, p, level, level1;
	object npc;

	x = get_x(me);
	y = get_y(me);
	z = get_z(me);
	level = me->get_level();
	for (i = 0, size = 8; i < size; i++)
	{
		if (objectp(get(sprintf("guard%d", i))))
			continue;
		p = get_valid_xy(z, x + random(10) - 5, y + random(10) - 5, IS_CHAR_BLOCK);
		if (!p)
			continue;
		npc = new ("npc/88/0001");
		if (!npc)
			break;
		level1 = level - (10 + random(6));
		NPC_ENERGY_D->init_level(npc, level1);
		set(sprintf("guard%d", i), npc);
		if (me->get_city_name() == "Tần Quốc")
		{
			npc->set_char_picid(9967);
			npc->set_name(HIR + me->get_city_name() + "Binh Sĩ");
		}
		else
		{
			npc->set_char_picid(9960);
			npc->set_name(HIB + me->get_city_name() + "Binh Sĩ");
		}
		npc->add_to_scene(z, p / 1000, p % 1000);
		npc->set_owner(me);
		NPC_SLAVE_D->find_enemy(npc); // 寻找敌人
		send_user(get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc),
				  41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE);
	}
}
//进入长平战场
void enter_changping(object who)
{
	string name1, name2;
	int level, wId, z, x, y, p;
	object map;
	if (localtime(time())[2] >= 0 && localtime(time())[2] <= 7)
	{
		send_user(who, "%c%s", '!', "Chiến Trường chỉ hoạt động từ 7 giờ đến 24 giờ");
	}
	level = who->get_2("changping.level");
	wId = who->get_2("changping.warid");

	if (!level)
	{
		send_user(who, "%c%s", '!', "Ngươi đã huỷ bỏ vào Chiến Trường, hãy báo danh lại !");
		return;
	}
	z = get_2(sprintf("%d.%d.z", level, wId));
	if (!z || !(map = get_map_object(z)))
	{
		send_user(who, "%c%s", '!', "Chiến Trường mới chưa mở ra, vui lòng đợi !");
		return;
	}
	if (who->get_2("changping.country") == "Triệu Quốc")
	{
		name1 = who->get_2("changping.country");
		x = 196;
		y = 152;
	}
	else
	{
		name1 = who->get_2("changping.country");
		x = 52;
		y = 48;
	}

	if (name1 == map->get_war_attack())
	{

		if (p = get_jumpin(z, 1))
		{
			x = p / 1000;
			y = p % 1000;

			who->set_manager(map->get_manager());
			who->add_to_scene(z, x, y, 3, 40971, 0, 40971, 0);
			map->add_user(who);
			CHAR_CHAR_D->init_loop_perform(who);
			send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9005, 1, OVER_BODY, PF_LOOP);

			map->show_to_user(who);
			map->show_to_scene(who);
			send_user(who, "%c%c", 0x95, 255);

			// switch (who->get_level()) // 设置玩家种类
			// {
			// case 0..9:
			// 	USER_D->sub_level_a_user(who);
			// 	break;
			// case 10..29:
			// 	USER_D->sub_level_b_user(who);
			// 	break;
			// default:
			// 	USER_D->sub_level_c_user(who);
			// 	break;
			// }
			// USER_D->add_battle_user(who);
		}
	}
	else if (name1 == map->get_war_defense())
	{

		if (p = get_jumpin(z, 2))
		{
			x = p / 1000;
			y = p % 1000;

			who->set_manager(map->get_manager_2());
			who->add_to_scene(z, x, y, 3, 40971, 0, 40971, 0);
			map->add_user_2(who);
			CHAR_CHAR_D->init_loop_perform(who);
			send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9006, 1, OVER_BODY, PF_LOOP);

			map->show_to_user(who);
			map->show_to_scene(who);
			send_user(who, "%c%c", 0x95, 255);

			// switch (who->get_level()) // 设置玩家种类
			// {
			// case 0..9:
			// 	USER_D->sub_level_a_user(who);
			// 	break;
			// case 10..29:
			// 	USER_D->sub_level_b_user(who);
			// 	break;
			// default:
			// 	USER_D->sub_level_c_user(who);
			// 	break;
			// }
			// USER_D->add_battle_user(who);
		}
	}
	if (p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
	{
		if (who->get_leader()) //踢出队伍
			TEAM_D->remove_member(who->get_leader(), who);
		// x = p / 1000, y = p % 1000;
		// who->add_to_scene(z, x, y, 3);
		// CHAR_CHAR_D->init_loop_perform(who);
		// if (who->get_2("changping.country") == "Tần Quốc")
		// {
		// 	send_user(who, "%c%s", ';', sprintf("Chiến Trường này đã bắt đầu " HIR "%d phút " NOR ", tiêu diệt quân địch " HIR " Chủ tướng Liêm Pha" NOR " , vinh quang thắng lợi sẽ thuộc về các bạn.", gone_time(map->get("warbegin")) / 60 + 1));
		// 	send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9005, 1, OVER_BODY, PF_LOOP);
		// }
		// else
		// {
		// 	send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9006, 1, OVER_BODY, PF_LOOP);
		// 	send_user(who, "%c%s", ';', sprintf("Chiến Trường này đã bắt đầu " HIR "%d phút " NOR ", tiêu diệt quân địch " HIR " Chủ tướng Bạch Khởi" NOR " , vinh quang thắng lợi sẽ thuộc về các bạn.", gone_time(map->get("warbegin")) / 60 + 1));
		// }
	}
}

//放弃进入战场
void refuse_changping(object who)
{
	int level, wId, z, x, y, p;

	level = who->get_2("changping.level");
	wId = who->get_2("changping.warid");
	if (!level)
		return;
	z = get_2(sprintf("%d.%d.z", level, wId));
	if (z && z == get_z(who)) //已经进入战场
		return;
	delete_sign_up(who);
}
//检查是否已经报名
int check_valid_user(object who)
{
	int level, wId, *nMem;
	string cTmp;

	level = who->get_2("changping.level");
	if (!level)
		return 0;
	wId = who->get_2("changping.warid");
	cTmp = who->get_2("changping.country");
	nMem = get_2(sprintf("%d.%d.%s", level, wId, cTmp));
	if (!sizeof(nMem))
		return 0;
	if (member_array(who->get_number(), nMem) == -1)
		return 0;
	return 1;
}
//计算报名人数
int count_sign_up(int level, int wId)
{
	return sizeof(get_2(sprintf("%d.%d.Tần Quốc", level, wId))) + sizeof(get_2(sprintf("%d.%d.Triệu Quốc", level, wId)));
}
//放弃
void abort_changping(object who)
{
	int level, wId, z, x, y, p;

	level = who->get_2("changping.level");
	wId = who->get_2("changping.warid");
	if (!level)
		return;
	z = get_2(sprintf("%d.%d.z", level, wId));
	if (z && z == get_z(who)) //已经进入战场
		return;
	delete_sign_up(who);
	who->set_2("changping.abort", time());
	send_user(who, "%c%s", '!', "Hủy tham dự Trận Chiến Trường Bình!");
}
//按积分转换成战绩
int change_score(int score)
{
	if (score < 451)
		score = 10;
	else if (score < 452)
		score = 15;
	else if (score < 453)
		score = 21;
	else if (score < 454)
		score = 28;
	else if (score < 455)
		score = 36;
	else if (score < 456)
		score = 45;
	else if (score < 460)
		score = 21;
	else if (score < 470)
		score = 31;
	else if (score < 480)
		score = 43;
	else if (score < 490)
		score = 57;
	else if (score < 500)
		score = 73;
	else
		score = 91;

	return score;
}
//杀玩家的战绩兑换
int kill_score(object who, object map)
{
	int i;

	if (!map)
		return 0;
	i = map->get_2(sprintf("kill.%d", who->get_number()));
	if (i < 4)
		i = 1;
	else if (i < 9)
		i = 3;
	else if (i < 15)
		i = 6;
	else if (i < 22)
		i = 10;
	else if (i < 30)
		i = 15;
	else if (i < 39)
		i = 21;
	else if (i < 51)
		i = 28;
	else
		i = 36;
	return i;
}
//给予战场称谓
void give_title(object me, object who, int iFlag)
{
	int iRank, iScore;
	string cTitle, cName, cTitle1, cName1;

	iRank = who->get_save_2("changping.rank");
	if (iRank >= 11)
	{
		send_user(who, "%c%s", '!', "Hiện tại chưa có danh hiệu mới hơn !");
		return;
	}
	iScore = nRankScore[iRank];
	cTitle1 = "P" + sprintf("%03d", iRank);
	iRank++;
	cTitle = "P" + sprintf("%03d", iRank);
	cName = TITLE_D->get_titlename(cTitle);
	cName1 = TITLE_D->get_titlename(cTitle1);
	if (cName == "")
		return;
	if (iFlag == 0)
	{
		if (iRank == 1)
			send_user(who, "%c%s", ':', sprintf("%s:\n    Trước đây ngươi chưa từng nhận qua Danh Hiệu Chiến Trường nào, nhận Danh Hiệu Chiến Trường đầu tiên sẽ là " HIR "“Tân binh chiến quốc”" NOR " cần " HIR " 25 điểm Chiến Tích (không trừ Chiến Tích) " NOR ", ngươi có muốn nhận Danh Hiệu này không?\n" ESC "Đồng ý\ntalk %x# welcome.8\n" ESC "Suy nghĩ lại", me->get_name(), getoid(me)));
		else if (iRank > 1 & who->get_save_2("changping.score") < iScore)
			send_user(who, "%c%s", ':', sprintf("Danh Hiệu Chiến Trường của bạn là " HIR "%s" NOR ", bạn không bị trừ điểm chiến tích khi nhận được Danh Hiệu này. Hãy cố gắng đạt nhiều điểm chiến tích hơn để có Danh Hiệu cao hơn nhé.\n" ESC "Thoát", cName1));
		else
			send_user(who, "%c%s", ':', sprintf("%s:\n    Ngươi đã có Danh Hiệu " HIR "%s" NOR ", có thể nhận tiếp Danh Hiệu Chiến Trường mới là " HIR "%s" NOR ", nhưng Chiến Tích phải đạt đến " HIR "%d điểm (không mất điểm Chiến Tích) " NOR ", Ngươi muốn nhận Danh Hiệu này không?\n" ESC "Đồng ý\ntalk %x# welcome.8\n" ESC "Suy nghĩ lại", me->get_name(), cName1, cName, iScore, getoid(me)));
		return;
	}
	if (who->get_save_2("changping.score") < iScore)
	{
		send_user(who, "%c%s", ':', sprintf("%s:\n    Chiến tích của ngươi không đủ, hãy cố gắng đi Chiến Trường để kiếm điểm Chiến Tích cho nhiều rồi hãy đến tìm ta !\n" ESC "Rời khỏi", me->get_name()));
		return;
	}
	//	who->add_save_2("changping.score",-iScore) ;
	who->set_save_2("changping.rank", iRank);
	who->set_save_2("changping.ranktime", time() + (3600 * 24 * 30));
	who->delete_title(cTitle1);
	who->add_title(cTitle);
	send_user(who, "%c%s", '!', "Bạn đã nhận được Danh Hiệu mới " + HIR + cName);
	MAILBOX->sys_mail(who->get_id(), who->get_number(), "Chúc mừng bạn nhận được " + HIR + cName + " Danh Hiệu Chiến Trường, thời hạn 1 tháng(30 Ngày) .");
}

void leave_changping(object who)
{
	int p, z;
	object map;
	if (!who->get_2("changping"))
		return;
	z = get_z(who);
	map = get_map_object(z);
	if (map->is_changping() && map->get("success"))
	{
		who->delete_2("changping");
		//	who->set_save("nhandoict", 0);
		if (p = get_valid_xy(80, 243, 156, IS_CHAR_BLOCK))
		{
			CHAR_CHAR_D->init_loop_perform(who);
			who->add_to_scene(80, p / 1000, p % 1000);
		}
		else
		{
			CHAR_CHAR_D->init_loop_perform(who);
			MAP_D->add_to_void(who);
		}
	}
	return;
}

void do_nhanthuong(string arg)
{
	object me = this_object();
	__FILE__->do_nhanthuong2(me, arg);
}

void do_nhanthuong2(object me, string arg)
{
	int flag, id, p;
	object who, item;

	who = this_player();
	id = getoid(me);
	flag = to_int(arg);
	who->set_time("talk", 0);
	switch (flag)
	{
	case 1:
		break;
	case 2:
		send_user(who, "%c%s", ':', sprintf(get_name() + ":\n  Ngươi đã anh dũng chiến đấu giờ muốn đổi thưởng gì ???\n"
												//	ESC"500 Điểm đổi Đuôi đặc biệt\ntalk %x# nhanthuong.3\n"
												ESC "1000 Điểm đổi Vũ khí nguyên liệu\ntalk %x# nhanthuong.4\n" ESC "5000 Điểm đổi Huân Chương Sự Kiện\ntalk %x# nhanthuong.5\n" ESC "Thoát\n",
											id, id, id, id, id, id, id));
		break;
	case 3:
		send_user(who, "%c%s", ':', sprintf(get_name() + ":\n  Ngươi đã anh dũng chiến đấu giờ muốn đổi thưởng gì ???\n" ESC "500 Điểm đổi Thiên Thần Trị Thương\ntalk %x# bonus.1\n" ESC "500 Điểm đổi Tinh Nghịch Phi Phong\ntalk %x# bonus.2\n" ESC "500 Điểm đổi Ác Quỷ Hậu\ntalk %x# bonus.3\n" ESC "500 Điểm đổi Chong Chóng Hậu\ntalk %x# bonus.4\n" ESC "500 Điểm đổi Tarzan Hậu\ntalk %x# bonus.5\n" ESC "500 Điểm đổi Tinh Linh Hậu\ntalk %x# bonus.6\n" ESC "500 Điểm đổi Cờ Quật Khởi\ntalk %x# bonus.7\n" ESC "500 Điểm đổi Bia Mộ\ntalk %x# bonus.8\n" ESC "Thoát\n", id, id, id, id, id, id, id, id, id));
		break;
	case 4:
		send_user(who, "%c%s", ':', sprintf(get_name() + ":\n  Hãy chọn vũ khí phù hợp đi nào!!!\n" ESC "1000 Điểm đổi vũ khí Quyền Thủ\ntalk %x# bonus.9\n" ESC "1000 Điểm đổi vũ khí Ám Khí\ntalk %x# bonus.10\n" ESC "1000 Điểm đổi vũ khí Đao\ntalk %x# bonus.11\n" ESC "1000 Điểm đổi vũ khí Kiếm\ntalk %x# bonus.12\n" ESC "1000 Điểm đổi vũ khí Thương\ntalk %x# bonus.13\n" ESC "1000 Điểm đổi vũ khí Côn\ntalk %x# bonus.14\n" ESC "Thoát\n", id, id, id, id, id, id, id, id, id));
		break;
	case 5:
		send_user(who, "%c%s", ':', sprintf(get_name() + ":\n  Ngươi thật sự muốn đổi chứ?\n"
												// ESC"200 Điểm đổi Đá Tương Uyên\ntalk %x# bonus.15\n"
												ESC "Đồng ý\ntalk %x# bonus.16\n"
												// ESC"400 Điểm đổi Đá Càn Khôn\ntalk %x# bonus.17\n"
												ESC "Thoát\n",
											id, id, id, id, id, id, id, id, id));
		break;
	}
}
void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_object(), arg);
}

void do_bonus_2(object me, string arg)
{
	int flag, point, i, id, p;
	object who, item;
	string cTmp, cFile;
	who = this_player();
	flag = to_int(arg);

	return;
	// switch (flag)
	// {
	// case 1:
	// 	if (who->get_save_2("changping.score") < 500)
	// 	{
	// 		notify("Không đủ 500 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/ppvacanh/duoi/1");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -500);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được phần thưởng hậu hĩnh !!! ", who->get_name()));
	// 	break;
	// case 2:
	// 	if (who->get_save_2("changping.score") < 500)
	// 	{
	// 		notify("Không đủ 500 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/ppvacanh/duoi/2");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -500);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được phần thưởng hậu hĩnh !!! ", who->get_name()));
	// 	break;
	// case 3:
	// 	if (who->get_save_2("changping.score") < 500)
	// 	{
	// 		notify("Không đủ 500 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/ppvacanh/duoi/3");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -500);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được phần thưởng hậu hĩnh !!! ", who->get_name()));
	// 	break;
	// case 4:
	// 	if (who->get_save_2("changping.score") < 500)
	// 	{
	// 		notify("Không đủ 500 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/ppvacanh/duoi/4");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -500);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được phần thưởng hậu hĩnh !!! ", who->get_name()));
	// 	break;

	// case 5:
	// 	if (who->get_save_2("changping.score") < 500)
	// 	{
	// 		notify("Không đủ 500 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/ppvacanh/duoi/5");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -500);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được phần thưởng hậu hĩnh !!! ", who->get_name()));
	// 	break;
	// case 6:
	// 	if (who->get_save_2("changping.score") < 500)
	// 	{
	// 		notify("Không đủ 500 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/ppvacanh/duoi/6");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -500);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được phần thưởng hậu hĩnh !!! ", who->get_name()));
	// 	break;
	// case 7:
	// 	if (who->get_save_2("changping.score") < 500)
	// 	{
	// 		notify("Không đủ 500 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/ppvacanh/duoi/7");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -500);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được phần thưởng hậu hĩnh !!! ", who->get_name()));
	// 	break;
	// case 8:
	// 	if (who->get_save_2("changping.score") < 500)
	// 	{
	// 		notify("Không đủ 500 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/ppvacanh/duoi/8");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -500);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được phần thưởng hậu hĩnh !!! ", who->get_name()));
	// 	break;
	// case 9:
	// 	if (who->get_save_2("changping.score") < 1000)
	// 	{
	// 		notify("Không đủ 1000 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/70/1075");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -1000);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được vũ khí nguyên liệu.!!! ", who->get_name()));

	// 	break;
	// case 10:
	// 	if (who->get_save_2("changping.score") < 1000)
	// 	{
	// 		notify("Không đủ 1000 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/71/1075");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -1000);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được vũ khí nguyên liệu.!!! ", who->get_name()));
	// 	break;
	// case 11:
	// 	if (who->get_save_2("changping.score") < 1000)
	// 	{
	// 		notify("Không đủ 1000 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/72/1075");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -1000);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được vũ khí nguyên liệu.!!! ", who->get_name()));
	// 	break;
	// case 12:
	// 	if (who->get_save_2("changping.score") < 1000)
	// 	{
	// 		notify("Không đủ 1000 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/73/1075");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -1000);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được vũ khí nguyên liệu.!!! ", who->get_name()));
	// 	break;
	// case 13:
	// 	if (who->get_save_2("changping.score") < 1000)
	// 	{
	// 		notify("Không đủ 1000 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/74/1075");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -1000);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được vũ khí nguyên liệu.!!! ", who->get_name()));
	// 	break;
	// case 14:
	// 	if (who->get_save_2("changping.score") < 1000)
	// 	{
	// 		notify("Không đủ 1000 điểm");
	// 		return;
	// 	}
	// 	item = new ("item/75/1075");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -1000);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được vũ khí nguyên liệu.!!! ", who->get_name()));
	// 	break;
	// case 15:
	// 	if (who->get_save_2("changping.score") < 200)
	// 	{
	// 		notify("Không đủ 200 điểm");
	// 		return;
	// 	}
	// 	//item = new("item/ppvacanh/duoi/1");
	// 	//"/item/test/dacankhon",
	// 	item = new ("item/test/datuonguyen");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -200);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được phần thưởng hậu hĩnh !!! ", who->get_name()));
	// 	break;
	// case 16:
	// 	if (who->get_save_2("changping.score") < 5000)
	// 	{
	// 		notify("Không đủ 5000 điểm");
	// 		return;
	// 	}
	// 	//	item = new("item/ppvacanh/duoi/1");
	// 	item = new ("item/04/0438");
	// 	i = item->move(who, -1);
	// 	item->add_to_user(i);
	// 	who->add_save_2("changping.score", -5000);
	// 	USER_D->user_channel(sprintf(HIG "Với nhiều trận chiến anh dũng trên chiến trường " HIY "%s" HIG " đã đổi được phần thưởng hậu hĩnh !!! ", who->get_name()));
	// 	break;
	// }
}
