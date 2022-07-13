#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>
#include <time.h>

int main(object me, string arg)
{

	int p, cap, exist, exist2, i, size, iTime, iDay;
	string result, arg2, arg3, arg4, *line, *data, username;
	object item, item1, who, *objs, target,map;
	mixed *mixTime;
	iTime = time();
	mixTime = localtime(iTime);
	iDay = mixTime[TIME_YDAY];
	if (!me->have_title("Z888"))
		return 1;
	if (!arg)
		return 1;
	if (arg == 0)
		return 1;
	if (sscanf(arg, "+ %s", arg2) == 1)
	{
		if (arg2 && !(who = find_any_char(arg2)))
		{
			write_user(me, ECHO "Không tìm thấy người này !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nKhông thể tìm thấy người này, hãy chắc chắn rằng người đó đang trực tuyến ! \n" ESC "Xác nhận");
			return 1;
		}
		if (who == me)
		{
			write_user(me, ECHO "Không thể tự Phong bế kênh Chat của chính mình !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nKhông thể tự Phong bế kênh Chat của chính mình ! \n" ESC "Xác nhận");
			return 1;
		}
		if (!who->is_user())
		{
			write_user(me, ECHO "Đối phương không phải là người chơi !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nĐối phương hoàn toàn không phải là người chơi ! \n" ESC "Xác nhận");
			return 1;
		}
		if ("/sys/party/vstfix"->checkctmk() == 1)
		{
			write_user(me, ECHO "Hôm nay không thể sử dụng !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nHôm nay là ngày công chiến Vô Song Thành, không thể sử dụng ! \n" ESC "Xác nhận");
			return 1;
		}
		if ("sys/party/vst4"->check_revive(me))
		{
			"sys/party/vst4"->add_revive(me, 1);
			who->set_chblk("chat", 15 * 60);
			who->set_chblk("rumor", 15 * 60);
			who->set_chblk("family", 15 * 60);
			who->set_chblk("say", 15 * 60);
			who->set_chblk("city", 15 * 60);
			who->set_chblk("vipchat", 15 * 60);
			who->set_chblk("ft", 15 * 60);
			who->set_chblk("et", 15 * 60);
			who->set_chblk("ot", 15 * 60);
			who->set_chblk("org", 15 * 60);
			who->set_chblk("tell", 15 * 60);
			who->set_chblk("time", time());
			who->set_save("nomail", time() + 15 * 60);
			send_user(me, "%c%s", ';', sprintf("%s (%d) đã bị Phong bế kênh Chat 15 phút", who->get_name(), who->get_number()));
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nNgười chơi " + who->get_name() + " (" + who->get_number() + ") đã bị bạn Phong bế kênh Chat 15 phút ! \n" ESC "Xác nhận");
			CHAT_D->rumor_channel(0, CHAT + sprintf(HIM "Bằng hữu %s (%d) đã bị Vô Song Thành Chủ phong bế kênh chat 15 phút !!", who->get_name(), who->get_number()));
			return 1;
		}
		else
		{
			write_user(me, ECHO "Hôm nay đã sử dụng 3 lần rồi !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nHôm nay đã sử dụng chức năng này 3 lần rồi ! \n" ESC "Xác nhận");
			return 1;
		}
	}
	else if (sscanf(arg, "- %s", arg2) == 1)
	{
		if (arg2 && !(who = find_any_char(arg2)))
		{
			write_user(me, ECHO "Không tìm thấy người này !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nKhông thể tìm thấy người này, hãy chắc chắn rằng người đó đang trực tuyến ! \n" ESC "Xác nhận");
			return 1;
		}
		if (who == me)
		{
			write_user(me, ECHO "Không thể tự Nhốt tù chính mình !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nKhông thể tự nhốt chính mình vào Tù ! \n" ESC "Xác nhận");
			return 1;
		}
		if (!who->is_user())
		{
			write_user(me, ECHO "Đối phương không phải là người chơi !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nĐối phương hoàn toàn không phải là người chơi ! \n" ESC "Xác nhận");
			return 1;
		}
		if (!who->is_user())
		{
			write_user(me, ECHO "Đối phương không phải là người chơi !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nĐối phương hoàn toàn không phải là người chơi ! \n" ESC "Xác nhận");
			return 1;
		}
		if (objectp(map = get_map_object(get_z(who))) && map->is_ken_map())
		{
	        write_user(me, ECHO "Đối phương đang trong Phá Thiên Tháp !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nĐối phương đang trong Phá Thiên Tháp ! \n" ESC "Xác nhận");
			return 1;
		}
		
		if (who->get_save("vstc_nhottu") == iDay)
		{
			write_user(me, ECHO "Hôm nay bạn đã nhốt người này rồi!");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nHôm nay bạn đã nhốt người này rồi ! \n" ESC "Xác nhận");
			return 1;
		}
		if ("/sys/party/vstfix"->checkctmk() == 1)
		{
			write_user(me, ECHO "Hôm nay không thể sử dụng !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nHôm nay là ngày công chiến Vô Song Thành, không thể sử dụng ! \n" ESC "Xác nhận");
			return 1;
		}
		if ("sys/party/vst4"->check_revive2(me))
		{
			if (gone_time(me->get("timentuben")) < 900)
			{
				write_user(me, ECHO "Quyền nhốt tù chưa được hồi phục !");
				send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nBạn vừa nhốt Tù một người nào đó, xin chờ vài phút để có lại quyền nhốt tù ! \n" ESC "Xác nhận");
				return 1;
			}
			if (get_z(who) != 704)
			{
				me->set("timentuben", time());
				"sys/party/vst4"->add_revive2(me, 1);
				who->set_save("gietnguoi", 1);
				who->set_save("vaotu", 900);
				who->set_save("vstc_nhottu", iDay);
				who->set_login_flag(2);
				set_invisible(who, 1);
				set_effect(who, EFFECT_USER_LOGIN, 4);
				who->add_to_scene(704, 35, 25);
				send_user(who, "%c%c%w%s", ':', 3, 9963, "Giám Ngục Quan :\nNgươi đã bị Vô Song Thành Chủ nhốt vào tù trong thời gian 15 phút !\n" ESC "Xác nhận\nCLOSE\n");
				send_user(me, "%c%s", ';', sprintf("%s (%d) đã bị Nhốt vào tù 15 phút", who->get_name(), who->get_number()));
				send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nNgười chơi " + who->get_name() + " (" + who->get_number() + ") đã bị bạn Nhốt vào tù 15 phút ! \n" ESC "Xác nhận");
				CHAT_D->rumor_channel(0, CHAT + sprintf(HIM "Bằng hữu %s (%d) đã bị Vô Song Thành Chủ nhốt vào tù 15 phút !!", who->get_name(), who->get_number()));
				return 1;
			}
			else
			{
				write_user(me, ECHO "Đối phương đang ở trong Nhà ngục !");
				send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nĐối phương vẫn đang còn ở trong Nhà ngục ! \n" ESC "Xác nhận");
				return 1;
			}
		}
		else
		{
			write_user(me, ECHO "Hôm nay đã sử dụng 3 lần rồi !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nHôm nay đã sử dụng chức năng này 3 lần rồi ! \n" ESC "Xác nhận");
			return 1;
		}
	}
	else if (sscanf(arg, "@ %s", arg2) == 1)
	{
		if ("sys/party/vst4"->check_revive3(me))
		{
			"sys/party/vst4"->add_revive3(me, 1);
			username = sprintf("%c+%d,%s=%d%c-", '\t', 0xff0202, "Vô Song Thành Chủ", me->get_number(), '\t');
			USER_D->user_channel(sprintf(HIR "%s : " NOR "%s", username, arg2));
			return 1;
		}
		else
		{
			write_user(me, ECHO "Hôm nay đã sử dụng 10 lần rồi !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nHôm nay đã sử dụng chức năng này 10 lần rồi ! \n" ESC "Xác nhận");
			return 1;
		}
	}
	else if (sscanf(arg, "? %s", arg2) == 1)
	{
		if (arg2 && !(who = find_any_char(arg2)))
		{
			write_user(me, ECHO "Không tìm thấy người này !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nKhông thể tìm thấy người này, hãy chắc chắn rằng người đó đang trực tuyến ! \n" ESC "Xác nhận");
			return 1;
		}
		if (who == me)
		{
			write_user(me, ECHO "Không thể tự giải Phong bế kênh Chat của chính mình !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nKhông thể tự giải Phong bế kênh Chat của chính mình ! \n" ESC "Xác nhận");
			return 1;
		}
		if (!who->is_user())
		{
			write_user(me, ECHO "Đối phương không phải là người chơi !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nĐối phương hoàn toàn không phải là người chơi ! \n" ESC "Xác nhận");
			return 1;
		}
		if ("/sys/party/vstfix"->checkctmk() == 1)
		{
			write_user(me, ECHO "Hôm nay không thể sử dụng !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nHôm nay là ngày công chiến Vô Song Thành, không thể sử dụng ! \n" ESC "Xác nhận");
			return 1;
		}
		if (!who->get_chblk("vipchat"))
		{
			write_user(me, ECHO "Đối phương không bị Phong bế kênh Chat !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nĐối phương không bị Phong bế kênh Chat, không cần Mở chat ! \n" ESC "Xác nhận");
			return 1;
		}
		if ("sys/party/vst4"->check_revive4(me))
		{
			"sys/party/vst4"->add_revive4(me, 1);
			who->delete_chblk("chat");
			who->delete_chblk("rumor");
			who->delete_chblk("say");
			who->delete_chblk("city");
			who->delete_chblk("family");
			who->delete_chblk("vipchat");
			who->delete_chblk("time");
			who->delete_chblk("ft");
			who->delete_chblk("et");
			who->delete_chblk("tell");
			who->delete_chblk("org");
			who->delete_chblk("ot");
			who->set_save("nomail", 0);
			send_user(me, "%c%s", ';', sprintf("%s (%d) đã được giải phong bế kênh Chat", who->get_name(), who->get_number()));
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nNgười chơi " + who->get_name() + " (" + who->get_number() + ") đã được bạn giải phong bế kênh Chat ! \n" ESC "Xác nhận");
			CHAT_D->rumor_channel(0, CHAT + sprintf(HIM "Bằng hữu %s (%d) đã được Vô Song Thành Chủ ân xá giải phong bế kênh chat !!", who->get_name(), who->get_number()));
			return 1;
		}
		else
		{
			write_user(me, ECHO "Hôm nay đã sử dụng 3 lần rồi !");
			send_user(me, "%c%c%w%s", ':', 3, 5502, "Đặc quyền Vô Song : \nHôm nay đã sử dụng chức năng này 3 lần rồi ! \n" ESC "Xác nhận");
			return 1;
		}
	}
	return 1;
}