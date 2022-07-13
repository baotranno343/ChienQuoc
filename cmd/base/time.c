#include <public.h>
#include <ansi.h>
#include <time.h>

private
int truybatdaopham;
private
int sugia;
private
int aptieu;
private
int nguyenlieu;
private
int phitac;
private
int doatbaomatac;
private
int baohop;
private
int tapkich;
private
int hkty;
private
int gumu;
private
int bonboss;
private
int vancotmalong;
private
int amlinhdaotruong;

int set_truybatdaopham(int i) { return truybatdaopham = i; }
int set_sugia(int i) { return sugia = i; }
int set_aptieu(int i) { return aptieu = i; }
int set_nguyenlieu(int i) { return nguyenlieu = i; }
int set_phitac(int i) { return phitac = i; }
int set_doatbaomatac(int i) { return doatbaomatac = i; }
int set_baohop(int i) { return baohop = i; }
int set_tapkich(int i) { return tapkich = i; }
int set_hkty(int i) { return hkty = i; }
int set_gumu(int i) { return gumu = i; }
int set_4boss(int i) { return bonboss = i; }
int set_vancotmalong(int i) { return vancotmalong = i; }
int set_amlinhdaotruong(int i) { return amlinhdaotruong = i; }
string time_string(int time);

// 函数:命令处理
int main(object me, string arg)
{
        string x2time = "";
        int iTime;
        mixed *mixTime;
        iTime = time();
        mixTime = localtime(iTime);
        tell_user(me, HIY "Bạn đang ở Kênh %d", MAIN_D->get_kenh());
        tell_user(me, "Thời gian hiện tại: %s.", short_time(time()));
        // tell_user( me, GAME_NAME " đã chạy được %s.", time_string( uptime() ) );
        // tell_user( me, "Hiện tại " GAME_NAME " đang hoàn thành: %s, thời gian trực tuyến: %s.",
        //         time_string( me->game_time() + time ), time_string( me->online_time() ) );
        // if (me->double_time()-time-me->game_time()>0)
        // 	tell_user( me, "Thời gian nhân đôi kinh nghiệm đóng băng còn %d giây",  me->double_time()-time-me->game_time() );
        // tell_user( me, "Sinh nhật của bạn: %s." ,short_time( me->birthday() ) );
        tell_user(me, "Thời gian ở " HIG "Cự Thú Đảo" NOR " của bạn: %s.", time_string(me->get_cuthudaotime()));
        tell_user(me, "------------------------------Các Event Hiện đang mở");
        x2time += truybatdaopham ? "\n" HIG "Truy Bắt Đạo Phạm:" NOR " Đang Tăng Phần Thưởng" : "";
        x2time += sugia ? "\n" HIG "Sư Gia:" NOR " Đang Tăng Phần Thưởng" : "";
        x2time += aptieu ? "\n" HIG "Áp Tiêu:" NOR " Đang Tăng Phần Thưởng" : "";
        x2time += nguyenlieu ? "\n" HIG "Thương Gia Nguyên Liệu:" NOR " Đã Xuất Hiện" : "";
        x2time += phitac ? "\n" HIG "Phỉ Tặc:" NOR " Đã Bắt Đầu" : "";
        x2time += doatbaomatac ? "\n" HIG "Đoạt Bảo Mã Tặc:" NOR " Đã Bắt Đầu" : "";
        x2time += baohop ? "\n" HIG "Bảo Hộp:" NOR " Đã Bắt Đầu" : "";
        x2time += tapkich ? "\n" HIG "Tập Kích Môn Phái:" NOR " Đã Bắt Đầu" : "";
        x2time += hkty ? "\n" HIG "Hoàng Kim Thánh Y:" NOR " Đã Bắt Đầu" : "";
        x2time += gumu ? "\n" HIG "Cổ Mộ:" NOR " Đã Bắt Đầu" : "";
        x2time += bonboss ? "\n" HIG "Bốn Boss Thần Binh:" NOR " Đã Xuất Hiện" : "";
        x2time += vancotmalong ? "\n" HIG "Vạn Cốt Ma Long:" NOR " Đã Xuất Hiện" : "";
        x2time += amlinhdaotruong ? "\n" HIG "Âm Linh Đạo Trưởng:" NOR " Đã Xuất Hiện" : "";
        x2time += me->get_save("diemdanh.day") != mixTime[TIME_YDAY] ? "\n" HIG "Hôm nay bạn chưa nhận điểm danh hằng ngày" : "";
        x2time += me->get_save("lsk") != mixTime[TIME_YDAY] ? "\n" HIG "Hôm nay bạn chưa tham gia Loạn Sơn Kê" : "";
        if (mixTime[TIME_WDAY] == 0 || mixTime[TIME_WDAY] == 6)
                x2time += me->get_save("gtt.day") != mixTime[TIME_YDAY] ? "\n" HIG "Hôm nay bạn chưa tham gia Thật Giả Hổ Vương" : "";
        x2time += me->get_save_2("banditi.solan") < 10 ? "\n" HIG "Hôm nay bạn chưa làm đủ 10 nhiệm vụ hằng ngày Trị An" : "";

        tell_user(me, "%s", x2time);
        if (x2time == "")
        {
                tell_user(me, "Hiện không có event nào");
        }
        // tell_user(me, "------------------------------\nThời gian ra Event và Boss mỗi ngày" HIR " Lưu Ý:" NOR " nên cập nhật thêm ở trên fanpage,website, và theo dõi thông báo khi boss xuất hiện");
        // partytime += "\nHoàng Kim Thánh Y - Tập Kích Môn Phái: 10h-10h30 và 6h-6h30";
        // partytime += "\nTruy Bắt Đạo Phạm 11h45-12h và 19h45 đến 20h";
        // partytime += "\nÁp tiêu: 12h-12h30 và 20h-20h30";
        // partytime += "\nCổ Mộ: Hằng Ngày lúc 20h30-22h";
        // partytime += "\nSư Gia: 12h45-13h và 20h30-21h";
        // partytime += "\nThương Gia Nguyên Liệu 13h45-14h và 21h45 đến 22h";
        // partytime += "\nBoss Thần Binh: Hằng Ngày lúc 20h";
        // partytime += "\nÂm Linh Đạo Trưởng: Chủ Nhật lúc 22h";
        // partytime += "\nVạn Cốt Ma Long: Hằng Ngày lúc 22h";
        // tell_user(me, "%s", partytime);
        return 1;
}

// 函数:获取时间字串
string time_string(int time)
{
        int day, hour, min, sec;
        string result = "";

        time = abs(time);

        sec = time % 60;
        time /= 60;
        min = time % 60;
        time /= 60;
        hour = time % 24;
        time /= 24;
        day = time;

        if (day)
                result += sprintf(" %d Ngày", day);
        if (hour)
                result += sprintf(" %d Giờ", hour);
        if (min)
                result += sprintf(" %d Phút", min);
        result += sprintf(" %d Giây", sec);

        return result;
}

// 函数:获取时间字串(简短)
string time_string_2(int time)
{
        int min, sec;
        string result = "";

        time = abs(time);

        sec = time % 60;
        time /= 60;
        min = time % 60;

        if (min)
                result += sprintf(" %d Phút", min);
        result += sprintf(" %d Giây", sec);

        return result;
}
