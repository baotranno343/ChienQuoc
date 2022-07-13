#include <ansi.h>
#include <time.h>
// 函数：命令处理
int main(object me, string arg)
{
	int i;
	string result, tmp;
	string *exp_str;
	int iTime;
	mixed *mixTime;
	if (!is_gm2(me) && !is_god(me))
	{
		notify("Bạn không đủ quyền。");
		return 1;
	}
	if (arg && sscanf(arg, "%d.%s", i, tmp) != 2)
		i = to_int(arg);

	switch (i)
	{
	default:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn:\n" + sprintf(ESC "Trang kế tiếp\nparty 6666\n") + sprintf(ESC "Lễ tình nhân\nparty 1\n") + sprintf(ESC "Mùa xuân\nparty 4\n") + sprintf(ESC "Hoạt động số lần đăng nhập của bạn\nparty 100\n") + sprintf(ESC "Hoàng thành thủ vệ chiến\nparty 7\n")
					  //		+ sprintf(ESC"Hoạt động chiến quốc vương\nparty 11\n")
					  //		+ sprintf(ESC"Hệ thống bảo rương\nparty 20\n")
					  + sprintf(ESC "321 Gấp đôi kinh nghiệm sv\nparty 23\n")
					  //		+ sprintf(ESC"Hoạt động điều hành online\nparty 33\n")
					  //		+ sprintf(ESC"Phần thưởng bang phái đồng tâm\nparty 30\n")
					  //		+ sprintf(ESC"Hoạt động 51\nparty 39\n")
					  + sprintf(ESC "Phiêu vương tranh bá\nparty 43\n")
					  //		+ sprintf(ESC"Hoạt động quả cầu 4 màu\nparty 54\n")
					  //		+ sprintf(ESC"Hoạt động thuyền rồng\nparty 50\n")
					  //		+ sprintf(ESC"Dịch vụ bồi thường\nparty 200\n")
					  + sprintf(ESC "Ẩn câu chuyện\nparty 110\n") + sprintf(ESC "Chất nổ khủng khiếp\nparty 120\n") + sprintf(ESC "Bắt trộm bảo phi tặc\nparty 1220\n") + sprintf(ESC "Giết hổ vương\nparty 130\n")
					  //		+ sprintf(ESC"Tập kích môn phái (TN)\nparty 125\n")
					  //		+ sprintf(ESC"Hoàng kim vệ đội trưởng (TN)\nparty 127\n")
					  //   		+ sprintf(ESC"Hoạt động mật tịch (TN)\nparty 135\n")
					  + sprintf(ESC "Phó bản cổ mộ\nparty 5000\n")
					  //		+ sprintf(ESC"Event trung thu (TN)\nparty 138\n")
					  + sprintf(ESC "Lễ quốc khánh\nparty 151\n") + sprintf(ESC "Tết dương tiết\nparty 157\n") + sprintf(ESC "Dịch vụ bồi thường\nparty 200\n") + sprintf(ESC "Vô Song Thành\nparty 9999\n") + sprintf(ESC "4 Boss Thế Giới\nparty 789789\n")

					  + ESC "Thoát");
		break;
	case 6666:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn:\n" + sprintf(ESC "Trang trước\nparty\n") + sprintf(ESC "Tìm kiếm dodolook\nparty 12\n") + sprintf(ESC "Truy tìm duyên phận\nparty 26\n") + sprintf(ESC "Phần thưởng người mới\nparty 16\n") + sprintf(ESC "Vô song thành chiến\nparty 7000\n") + sprintf(ESC "Đoạt Ngân Phi Tặc\nparty 8000\n")

					  + ESC "Thoát");
		break;
	case 1:
		// send_user(me, "%c%c%w%s", ':',3,0,
		// 	"Mời chọn hoạt động lễ tình nhân:\n"
		// 	+ sprintf(ESC"Mở hoạt động\nparty 2\n")
		// 	+ sprintf(ESC"Định thời gian mở\nparty 214\n")
		// 	+ sprintf(ESC"Tắt\nparty 3\n")
		// 	+ ESC"Thoát"
		// );
		"sys/party/gumu_check_time"->check_time1();
		break;
	case 2:
		"sys/user/marry"->set_valentine(1, 0);
		"sys/party/valentine"->set_valentine(1, 0);
		send_user(me, "%c%s", '!', "Lễ tình nhân đã mở!");
		break;
	case 214:
		"sys/user/marry"->set_valentine(0, 0);
		"sys/party/valentine"->set_valentine(0, 0);
		"sys/party/valentine"->destruct_chocolate();
		"sys/party/valentine"->check_time();
		send_user(me, "%c%s", '!', "Lễ tình nhân hoạt động theo định sẵn đã mở!");
		break;
	case 3:
		"sys/user/marry"->set_valentine(0, 1);
		"sys/party/valentine"->set_valentine(0, 1);
		"sys/party/valentine"->destruct_chocolate();
		send_user(me, "%c%s", '!', "Lễ tình nhân đã tắt!");
		break;
	case 4:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn hoạt động mùa xuân:\n" + sprintf(ESC "Mở\nparty 5\n") + sprintf(ESC "Mở ra theo định sẵn\nparty 216\n") + sprintf(ESC "Tắt\nparty 6\n") + ESC "Thoát");
		break;
	case 5:
		"npc/00/0008"->set_newyear(1, 0);
		"sys/party/tet"->set_newyear(1, 0);
		//"sys/party/chunjie"->generate_fuwawa();
		send_user(me, "%c%s", '!', "Hoạt động mùa xuân đã mở!");
		break;
	case 7: // Hoàng thành thủ vệ chiến
		result = "Mời lựa chọn hoàng thủ vệ chiến:\n";
		if ("/sys/sys/count"->get_war_flag1())
			result += ESC "Tắt hoàng thủ vệ chiến\nparty 8\n";
		else
			result += ESC "Mở hoàng thủ vệ chiến\nparty 8\n";
		result += ESC "Lập tức khởi động hoàng thủ vệ chiến\nparty 9\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 8: // Hoàng thành thủ vệ chiến
		if ("/sys/sys/count"->get_war_flag1())
		{
			"/sys/sys/count"->set_war_flag1(0);
			send_user(me, "%c%s", '!', "Tắt Defend!");
		}
		else
		{
			"/sys/sys/count"->set_war_flag1(1);
			send_user(me, "%c%s", '!', "Mở Defend!");
		}
		break;
	case 9:
		"/sys/party/defence"->start_defence();
		break;
	case 216:
		"npc/00/0008"->set_newyear(0, 0);
		"sys/party/chunjie"->set_newyear(0, 0);
		"sys/party/chunjie"->destroy_baozhu();
		"sys/party/chunjie"->destroy_nianshou();
		"sys/party/chunjie"->destroy_fuwawa();
		"sys/party/chunjie"->check_time();
		send_user(me, "%c%s", '!', "hoạt động mùa xuân định sẵn!");
		break;
	case 6:
		"npc/00/0008"->set_newyear(0, 1);
		"sys/party/chunjie"->set_newyear(0, 1);
		"sys/party/chunjie"->destroy_baozhu();
		"sys/party/chunjie"->destroy_nianshou();
		"sys/party/chunjie"->destroy_fuwawa();
		send_user(me, "%c%s", '!', "Hoạt động mùa xuân đóng!");
		break;
	case 11:
		"npc/party/0014"->read_renwang();
		send_user(me, "%c%s", '!', "Mở chiến quốc vương!");
		break;
	case 12:
		result = "Mời lựa chọn  sự kiện tìm kiếm dodolook:\n";
		result += ESC "Mở\nparty 13\n";
		result += ESC "Tắt\nparty 14\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 13:
		send_user(me, "%c%c%d%s", '?', 16, 60, "Hoạt động bắt đầu cùng thời gian kết thúc（Ví dụ：20070315-20070430 ）：\n" ESC "party 15.%s\n");
		break;
	case 14:
		"npc/party/0022"->set_close(me);
		break;
	case 15:
		"npc/party/0022"->set_open(me, tmp);
		break;
	case 16:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn hoạt động thưởng người chơi vương mới:\n" + sprintf(ESC "Mở\nparty 17\n") + sprintf(ESC "Tắt\nparty 18\n") + ESC "Thoát");
		break;
	case 17:
		"npc/party/0023"->set_open();
		send_user(me, "%c%s", '!', "Người chơi vương mới mở！");
		break;
	case 18:
		"npc/party/0023"->set_close();
		send_user(me, "%c%s", '!', "Người chơi vương mới đóng！");
		break;
	case 20:
		result = "Mời lựa chọn hệ thống bảo rương:\n";
		if ("/sys/item/box"->get_all_stuff())
			result += ESC "Tắt hệ thống\nparty 21\n";
		else
			result += ESC "Mở hệ thống\nparty 22\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 21:
		"/sys/item/box"->del_stuff();
		send_user(me, "%c%s", '!', "Tắt hệ thống bảo rương!");
		break;
	case 22:
		"/sys/item/box"->reset_stuff();
		send_user(me, "%c%s", '!', "Mở hệ thống bảo rương!");
		break;
	case 23:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "321 nhân đôi kinh nghiệm:\n" + sprintf(ESC "Mở\nparty 24\n") + sprintf(ESC "Đóng\nparty 25\n") + ESC "Thoát");
		break;
	case 24:
		"npc/party/0026"->set_open(me);
		break;
	case 25:
		"npc/party/0026"->set_close(me);
		break;
	case 26:
		result = "Mời chọn hệ thống duyên phận:\n";
		result += ESC "Mở\nparty 27\n";
		result += ESC "Đóng\nparty 28\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 27:
		send_user(me, "%c%c%d%s", '?', 16, 60, "Mời đưa hệ thống duyên phận hoạt động（Ví dụ：20070416 ）：\n" ESC "party 29.%s\n");
		break;
	case 28:
		"npc/party/dodolook"->set_close(me);
		break;
	case 29:
		"npc/party/dodolook"->set_open(me, tmp);
		break;
	case 30:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời chọn hoạt đông bang đồng tâm:\n" + sprintf(ESC "Mở\nparty 31\n") + sprintf(ESC "Đóng\nparty 32\n") + ESC "Thoát");
		break;
	case 31:
		"npc/org/qgl_amass"->set_open2();
		send_user(me, "%c%s", '!', "Đã mở bang phái đồng tâm！");
		break;
	case 32:
		"npc/org/qgl_amass"->set_close2();
		send_user(me, "%c%s", '!', "Đã đóng bang phái đồng tâm！");
		break;
	case 33:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Thao tác đánh tuyến thượng:\n" + sprintf(ESC "Chuẩn bị trạng thái\nparty 36\n") + sprintf(ESC "Trực tiếp mở ra(Khảo nghiêm mới xài, còn chính thức thì ko xài!)\nparty 34\n") + sprintf(ESC "Thiết lập vị trí mở/Kết thúc thời gian\nparty 37\n") + sprintf(ESC "Trực tiếp tắt ra(Khảo nghiêm mới xài, còn chính thức thì ko xài!)\nparty 35\n") + ESC "Thoát");
		break;
	case 34:
		"npc/org/qgl_amass"->set_open();
		"npc/party/dodolook2"->set_open();
		"sys/npc/npc"->set_open();
		send_user(me, "%c%s", '!', "Đã mở！");
		break;
	case 35:
		"npc/org/qgl_amass"->set_close();
		"npc/party/dodolook2"->set_close();
		"sys/npc/npc"->set_close();
		send_user(me, "%c%s", '!', "Đã đóng！");
		break;
	case 36:
		"npc/org/qgl_amass"->set_prepare();
		"npc/party/dodolook2"->set_prepare();
		"sys/npc/npc"->set_prepare();
		send_user(me, "%c%s", '!', "Đang chuẩn bị！");
		break;
	case 37:
		send_user(me, "%c%c%d%s", '?', 16, 60, "Mời nhập thời gian khởi đầu và kết thúc(ví dụ：20070517-20070721 ）：\n" ESC "party 38.%s\n");
		break;
	case 38:
		"npc/party/dodolook2"->set_open_time(me, tmp);
		"npc/org/qgl_amass"->set_open_time(me, tmp);
		"sys/npc/npc"->set_open_time(me, tmp);
		break;
	case 39:
		result = "Mời lựa chọn:\n";
		result += ESC "Mở\nparty 40\n";
		result += ESC "Đóng\nparty 41\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 40:
		send_user(me, "%c%c%d%s", '?', 16, 60, "Lựa chọn thời gian mở đầu và kết thúc（Ví dụ：20070501-20070508 ）：\n" ESC "party 42.%s\n");
		break;
	case 41:
		"npc/party/0032"->set_close(me);
		break;
	case 42:
		"npc/party/0032"->set_open(me, tmp);
		break;
	case 43:
		result = "Mời lựa chọn:\n";
		result += ESC "Mở\nparty 44\n";
		result += ESC "Đóng\nparty 45\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 44:
		send_user(me, "%c%c%d%s", '?', 16, 60, "Mời nhập thời gian mở đầu hoặc kết thúc（Ví dụ：200705182000-200705182100-200705182130 ）：\n" ESC "party 46.%s\n");
		break;
	case 45:
		TASK_ESCORT_D->set_close(me);
		break;
	case 46:
		TASK_ESCORT_D->set_open(me, tmp);
		break;
	case 47:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Quả cầu 4 màu (Khảo nghiệm):\n" + sprintf(ESC "Bắt đầu khảo nghiệm\nparty 48\n") + sprintf(ESC "Kết thúc KN。Chú ý：hoạt động tiến hành trong đúng trạng thái\nparty 49\n") + ESC "Thoát");
		break;
	case 48:
		"sys/npc/npc"->test_start();
		send_user(me, "%c%s", '!', "Bắt đầu thử nghiệm quả cầu 4 màu, bắt buộc khảo nghiệm xong phải kết thúc！");
		break;
	case 49:
		"sys/npc/npc"->test_finish();
		send_user(me, "%c%s", '!', "Kết thúc thử nghiệm quả cầu 4 màu！");
		break;
	case 50:
		result = "Mời lựa chọn thao tác:\n";
		result += ESC "Mở\nparty 51\n";
		result += ESC "Đóng\nparty 52\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 51:
		send_user(me, "%c%c%d%s", '?', 16, 60, "Thời gian mở và kết thúc（ví dụ：200706190900-200706192300 ）：\n" ESC "party 53.%s\n");
		break;
	case 52:
		"sys/party/duanwujie"->set_close(me);
		"sys/party/duanwujie"->destruct_dongtingzhouzi();
		"sys/party/duanwujie"->destroy_zhongzi();
		break;
	case 53:
		"sys/party/duanwujie"->set_open(me, tmp);
		break;
	case 54:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Lựa chọn thao tác:\n" + sprintf(ESC "Quả cầu 4 màu (KN)\nparty 47\n") + sprintf(ESC "Thiết lập thời gian kết thúc hoạt động\nparty 55\n") + sprintf(ESC "Hủy bỏ thiết lập thời gian kết thúc\nparty 57\n") + ESC "Thoát");
		break;
	case 55:
		send_user(me, "%c%c%d%s", '?', 16, 60, "Thời gian bắt đầu và kết thúc(ví dụ：200707190900)：\n" ESC "party 56.%s\n");
		break;
	case 56:
		"sys/npc/npc"->set_ball_close_time(me, tmp);
		break;
	case 57:
		"sys/npc/npc"->set_ball_cancel(me);
		break;

	case 100:
		result = "Mời lựa chọn thao tác:\n";
		if ("/sys/sys/count"->get_can_gm3())
			result += ESC "Cấm số lần đăng nhập\nparty 101\n";
		else
			result += ESC "Cho phép số lần đăng nhập\nparty 102\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 101:
		"/sys/sys/count"->set_can_gm3(0);
		send_user(me, "%c%s", '!', "Đã cấm số lần đăng nhập!");
		break;
	case 102:
		"/sys/sys/count"->set_can_gm3(1);
		send_user(me, "%c%s", '!', "Đã mở số lần cho phép đăng nhập!");
		break;
	case 200:
		result = "Mời lựa chọn:\n";
		result += ESC "Tắt hoạt động bồi thường\nparty 201\n";
		result += ESC "Mở hoạt động bồi thường\nparty 202\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 201:
		"/sys/sys/count"->set_hefu_time(0);
		send_user(me, "%c%s", '!', "Tắt hoạt động bồi thường!");
		break;
	case 202:
		send_user(me, "%c%c%d%s", '?', 16, 60, "Lựa chọn thời gian(ví dụ：2 200707190900)：\n" ESC "party 203.%s\n");
		break;
	case 203:
		"sys/sys/count"->set_hefu_time2(me, tmp);
		break;
	case 110: //挖宝总动员
		result = "Lựa chọn thao tác：\n";
		result += ESC "Mở\nparty 111\n";
		result += ESC "Tắt\nparty 112\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 111:
		send_user(me, "%c%c%d%s", '?', 16, 60, "Lựa chọn khởi đầu kết thúc（Ví dụ：200706190900-200706192300 ）：\n" ESC "party 113.%s\n");
		break;
	case 112:
		"sys/party/treasure"->set_close(me);
		break;
	case 113:
		"sys/party/treasure"->set_open(me, tmp);
		break;
	case 120:
		result = "Mời lựa chọn thao tác:\n";
		result += ESC "Mở ra\nparty 121\n";
		result += ESC "Tắt đi\nparty 122\n";
		result += ESC "Thiết lập thời gian hoạt động\nparty 123\n";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 121:
		"sys/party/burst_equips"->turn_on_activity();
		break;
	case 122:
		"sys/party/burst_equips"->turn_off_activity();
		break;
	case 123:
		result = "Mời nhập thời gian hoạt động，ví dụ：\"51700-51800\" Mỗi tuần thứ năm đc 17 điểm -18 điểm lúc hoạt động bắt đầu   \n" ESC "party 124.%s\n";
		send_user(me, "%c%c%d%s", '?', 16, 60, result);
		break;
	case 124:
		exp_str = explode(tmp, "-");
		if (sizeof(exp_str) != 2)
		{
			send_user(me, "%c%s", '!', "Cách nhập sai！");
		}
		else
		{
			"sys/party/burst_equips"->set_active_time(to_int(exp_str[0]), to_int(exp_str[1]));
		}
		break;
	case 1220:
		result = "Mời lựa chọn thao tác:\n";
		result += ESC "Mở ra\nparty 1221\n";
		result += ESC "Tắt đi\nparty 1222\n";
		result += ESC "Thiết lập thời gian\nparty 1223\n";
		result += ESC "Kiểm tra thời gian\nparty 1224\n";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 1221:
		"sys/party/phitac"->check_time();
		send_user(me, "%c%s", ';', "Mở ra thành công！");
		break;
	case 1222:
		"sys/party/phitac"->turn_off_activity();
		send_user(me, "%c%s", ';', "Tắt thành công!");
		break;
	case 1223:
		result = "Mời nhập thời gian hoạt động，Như：\"1,2,3,4;9,23;2\" Mỡi tuần một，hai，ba，bốn 9 đến 23 mở ra hoạt động，mỗi lúc làm mới 2 lần \n" ESC "party 1225.%s\n";
		send_user(me, "%c%c%d%s", '?', 16, 60, result);
		break;
	case 1224:
		tell_user(me, "sys/party/phitac"->get_active_time());
		break;
	case 1225:
		if ("sys/party/phitac"->set_active_time(tmp))
		{
			send_user(me, "%c%s", ';', sprintf("Sửa đổi thời gian hoạt động thành công, đang thiết lập lại\n%s", "sys/party/phitac"->get_active_time()));
		}
		else
		{
			send_user(me, "%c%s", ';', "Cách thức sai, sửa ko thành công");
		}
		break;
	case 125:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn thời gian:\n" + sprintf(ESC "Bắt đầu thử nghiệm\nparty 126\n") + ESC "Thoát");
		break;
	case 126:
		"sys/party/sect_surprise"->generate_scum();
		break;
	case 127:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn thao tác:\n" + sprintf(ESC "Bắt đầu thử nghiệm\nparty 128\n") + ESC "Thoát");
		break;
	case 128:
		"sys/party/gold_warrior"->check_time2();
		break;
	case 130:
		result = "Mời lựa chọn thao tác:\n";
		result += ESC "Mở ra\nparty 131\n";
		result += ESC "Tắt đi\nparty 132\n";
		result += ESC "Thiết lập thời gian\nparty 133\n";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 131:
		"sys/party/guess_true_tiger"->turn_on_activity();
		break;
	case 132:
		"sys/party/guess_true_tiger"->turn_off_activity();
		break;
	case 133:
		result = "Mời nhập thời gian hoạt động，như：\"51900-60000\" con số trên là là tuần thứ 5, 19 giờ, 00 phút tới tuần thứ 6, 00h, 00 phút sẽ bắt đầu hoạt động \n" ESC "party 134.%s\n";
		send_user(me, "%c%c%d%s", '?', 16, 60, result);
		break;
	case 134:
		exp_str = explode(tmp, "-");
		if (sizeof(exp_str) != 2)
		{
			send_user(me, "%c%s", '!', "Sai cách thức！");
		}
		else
		{
			"sys/party/guess_true_tiger"->set_active_time(to_int(exp_str[0]), to_int(exp_str[1]));
		}
		break;

	//====================wg=================
	case 135:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn:\n" + sprintf(ESC "Bắt đầu thử nghiệm\nparty 136\n") + sprintf(ESC "Kết thúc\nparty 137\n") + ESC "Thoát");
		break;
	case 136:
		"sys/party/qixi"->check_time2();
		break;
	case 137:
		"sys/party/qixi"->check_time3();
		break;
	case 138:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn:\n" + sprintf(ESC "Bắt đầu thử nghiệm\nparty 139\n") + sprintf(ESC "Bắt đầu phần thưởng bắt thỏ\nparty 144\n") + sprintf(ESC "Kết thúc\nparty 143\n") + ESC "Thoát");
		break;
	case 139:
		set_party_time(2007, 9, 24, 8, 0, 0);
		"sys/party/moon1"->check_time();
		break;
	case 143:
		set_party_time(2007, 10, 3, 22, 0, 0);
		"sys/party/moon1"->check_time();
		break;
	case 144:
		set_party_time(2007, 9, 26, 22, 0, 0);
		"sys/party/moon1"->check_time();
		break;
	case 145:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn thao tác:\n" + sprintf(ESC "Mở ra\nparty 146\n") + sprintf(ESC "Điều chỉnh thời gian\nparty 147\n") + sprintf(ESC "Kiểm tra trạng thái\nparty 148\n") + sprintf(ESC "Đem trả thời gian về như cũ\nparty 149\n") + sprintf(ESC "Tắt đi\nparty 150\n") + ESC "Thoát");
		break;
	case 146:
		"sys/party/national"->set_open();
		send_user(me, "%c%s", ';', "Mở ra thành công！");
		break;
	case 147:
		set_party_time(2007, 10, 1, 8, 0, 0);
		"sys/party/national"->check_time();
		tell_user(me, "Trc mắt điều chỉnh thời gian thành：%s", short_time(get_party_time()));
		break;
	case 148:
		tell_user(me, "Trc mắt hoạt động diễn ra vào thời gian：%s", short_time(get_party_time()));
		if ("sys/party/national"->get_status() == 0)
			tell_user(me, "Trạng thái tắt");
		else
			tell_user(me, "Trang thái mở");
		break;
	case 149:
		iTime = time();
		mixTime = localtime(iTime);
		set_party_time(mixTime[TIME_YEAR], mixTime[TIME_MON] + 1, mixTime[TIME_MDAY], mixTime[TIME_HOUR], mixTime[TIME_MIN], mixTime[TIME_SEC]);
		"sys/party/national"->destruct_xigua_uncle();
		"sys/party/national"->destruct_xigua();
		"sys/party/national"->destruct_bad_npc();
		"sys/party/national"->check_time();
		tell_user(me, "Trả lại thời gian như cũ：%s", short_time(time()));
		break;
	case 150:
		"sys/party/national"->set_close();
		send_user(me, "%c%s", ';', "Tắt thành công！");
		break;

	case 151:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn thao tác:\n" + sprintf(ESC "Hoạt động dưa hấu bá bá\nparty 145\n") + sprintf(ESC "Quà tặng Quốc khánh\nparty 152\n") + ESC "Thoát");
		break;
	case 152: //国庆赠礼活动
		result = "Mời lựa chọn thao tác：\n";
		result += ESC "Mở ra\nparty 153\n";
		result += ESC "Tắt đi\nparty 154\n";
		result += ESC "Kiểm tra trạng thái\nparty 156\n";
		result += ESC "Thoát";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 153:
		send_user(me, "%c%c%d%s", '?', 16, 60, "Mời đặt khởi đầu và kết thúc（Ví dụ：200706190900-200706192300 ）：\n" ESC "party 155.%s\n");
		break;
	case 154:
		"npc/party/exchange_angel"->set_close(me);
		break;
	case 155:
		"npc/party/exchange_angel"->set_open(me, tmp);
		break;
	case 156:
		if ("npc/party/exchange_angel"->is_open())
			tell_user(me, "Trang thái mở");
		else
			tell_user(me, "Trạng thái tắt");
		break;

	case 157:
		send_user(me, "%c%c%w%s", ':', 3, 0,
				  "Mời lựa chọn hình thức:\n" + sprintf(ESC "Mở ra\nparty 158\n") + sprintf(ESC "Điều chỉnh thời gian\nparty 159\n") + sprintf(ESC "Kiểm tra trạng thái\nparty 160\n") + sprintf(ESC "Trả lại thời gian cũ\nparty 161\n") + sprintf(ESC "Tắt đi\nparty 162\n") + ESC "Thoát");
		break;
	case 158:
		"sys/party/chongyang"->set_open();
		send_user(me, "%c%s", ';', "Mở ra thành công！");
		break;
	case 159:
		set_party_time(2007, 10, 19, 9, 50, 0);
		"sys/party/chongyang"->check_time();
		tell_user(me, "Điều chỉnh thời gian thành：%s", short_time(get_party_time()));
		break;
	case 160:
		tell_user(me, "Thời gian đang hoạt động là：%s", short_time(get_party_time()));
		if ("sys/party/chongyang"->get_status() == 0)
			tell_user(me, "Trạng thái tắt");
		else
			tell_user(me, "Trạng thái mở");
		break;
	case 161:
		iTime = time();
		mixTime = localtime(iTime);
		set_party_time(mixTime[TIME_YEAR], mixTime[TIME_MON] + 1, mixTime[TIME_MDAY], mixTime[TIME_HOUR], mixTime[TIME_MIN], mixTime[TIME_SEC]);
		"sys/party/chongyang"->destruct_party_npc();
		"sys/party/chongyang"->destruct_party_item();

		"sys/party/chongyang"->check_time();
		tell_user(me, "Trc mắt trả lại thời gian như cũ là：%s", short_time(time()));
		break;
	case 162:
		"sys/party/chongyang"->set_close();
		send_user(me, "%c%s", ';', "Tắt thành công！");
		break;

		//====================end=================

		//============ TEST===========

	/************************************XXY************************************/
	case 5000:
		send_user(me, "%c%c%w%s", ':', 3, 0, "Mời lựa chọn thao tác:\n" + sprintf(ESC HIY "Bắt đầu thử nghiệm\nparty 5001\n") + sprintf(ESC HIY "Tắt TN\nparty 5002\n") + sprintf(ESC HIY "Kiểm tra trạng thái\nparty 5005\n") + sprintf(ESC HIY "Bắt đầu mở\nparty 5003\n") + sprintf(ESC HIY "Tắt hẳn\nparty 5004\n") + ESC "Thoát");
		break;
	case 5001:
		"sys/party/gumu_check_time"->set_gumu_party_open(1, 1);
		break;
	case 5002:
		"sys/party/gumu_check_time"->set_gumu_party_open(0, 1);
		break;
	case 5003:
		"sys/party/gumu_check_time"->set_gumu_party_open(1, 0);
		break;
	case 5004:
		"sys/party/gumu_check_time"->set_gumu_party_open(0, 0);
		break;
	case 5005:
		tell_user(me, sprintf(HIY "Trc mắt hoạt động diễn ra: %s", short_time(get_party_time())));
		tell_user(me, sprintf(HIY "%s", "sys/party/gumu_check_time"->get_party_statue()));
		break;
	/************************************XXY************************************/
	//====================lyt================
	/*case 7000:
		send_user(me, "%c%c%w%s", ':',3,0,
			"Mời lựa chọn thao tác:\n"
			+ sprintf(ESC"Sửa đổi thời gian hoạt động (TN)\nparty 7001\n")
			+ sprintf(ESC"HOạt động theo thời gian mở ra\nparty 7003\n")
			+ sprintf(ESC"Tắt đi\nparty 7004\n")
			+ sprintf(ESC"Kiểm tra trạng thái\nparty 7005\n")
			+ ESC"Thoát");
		break;
	case 7001:
		send_user( me, "%c%c%d%s", '?', 16, 60, "Thời gian hoạt động và kết thúc（Ví dụ：2007-9-18 19:29:30 ）：\n"ESC"party 7002.%s\n");		
		break;
	case 7002:
		WUSHUANG->set_wushuang_time(me,tmp);
		break;
	case 7003:
		WUSHUANG->set_flag(1);
		break;
	case 7004:
		WUSHUANG->set_flag(0);
		break;
	case 7005:
		WUSHUANG->get_status(me);
		break;
	case 7999:
		break; */
	case 9999:
		"/sys/party/vstfix"->set_wushuang_time(me, tmp);
		break;
	case 789789:
		"/sys/party/bonboss"->generate_scum();
		break;
	case 8000:
		result = "Mời lựa chọn thao tác:\n";
		result += ESC "Mở ra\nparty 8001\n";
		result += ESC "Tắt đi\nparty 8002\n";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		break;
	case 8001:
		"sys/party/doatbaomatac"->check_time();
		send_user(me, "%c%s", ';', "Mở ra thành công！");
		break;
	case 8002:
		"sys/party/doatngan"->turn_off_activity();
		send_user(me, "%c%s", ';', "Tắt thành công!");
		break;
		//====================end=================
	}
	return 1;
}
