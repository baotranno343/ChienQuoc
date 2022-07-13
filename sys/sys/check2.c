#define FILE_ACC "taikhoan.ini"
#define BAO_TRI "baotri.txt"
#define GOD_INI "ini/god.ini"
#define USERNAME 0
#define PASSWORD 1
#define BANNED 2

int is_legal_user(object me, string id, string passwd)
{
    int i, size, size2, exist, kenh, check_god, islogin;
    object *user, *user2;
    string errstr, *line, *data, *god, baotri;
    string *list = MAIN_D->getlist();
    kenh = MAIN_D->get_kenh();
    line = explode(read_file(FILE_ACC), "\n");
    baotri = read_file(BAO_TRI);
    god = explode(read_file(GOD_INI), "\n");
    if (kenh == 0)
        return 0;
    if (baotri != "" && to_int(baotri) == 1)
    {
        if (sizeof(god) > 0)
        {
            for (i = 0, size = sizeof(god); i < size; i++)
            {
                if (id == god[i])
                {
                    check_god = 1;
                    break;
                }
            }
        }
        if (!check_god)
        {
            errstr = "Đang Bảo Trì!";
            send_user(me, "%c%s", '!', errstr);
            send_user(me, "%c%c", 0xff, 0x11);
            destruct(me);
            return 0;
        }
    }
    for (i = 0, size = sizeof(line); i < size; i++)
    {
        if (line[i] == "")
            continue;
        data = explode(line[i], " ");
        if (id == data[USERNAME])
        {
            exist = 1;
            if (passwd != data[PASSWORD])
            {
                errstr = "Mật khẩu không đúng!";
            }
            break;
        }
    }

    // Check Login Ver 1
    //  if ("sys/sys/user2"->checkid(id) != -1)
    //  {
    //      for (i = 0; i < sizeof(list); i++)
    //      {
    //          if (kenh == to_int(list[i]))
    //              continue;
    //          ghi_file(sprintf("bang/check%s.txt", list[i]), sprintf("\nlocid %s", id));
    //      }
    //      "sys/sys/user2"->locid(id);
    //      "sys/sys/user2"->sub_allnumber(id);
    //      errstr = "Vui lòng đăng nhập lại";
    //  }
    //  if ("sys/sys/user2"->checkid(id) == -1 && "sys/sys/user2"->checkid2(id))
    //  {
    //      "sys/sys/user2"->add_userid(id);
    //      rm(sprintf("isLogin/%s.dat", id));
    //      errstr = "Vui lòng đăng nhập lại";
    //  }
    // Ket Thuc Check Login

    // Check login Ver2

    if ((islogin = "sys/sys/user2"->checkid2(id)) && kenh != islogin)
    {
        //  ghi_file(sprintf("bang/check%d.txt", islogin), sprintf("\nlocid2 %s", id));
        errstr = sprintf("Tài khoản đang đăng nhập ở kênh %d", islogin);
    }
    // Check Login
    //  60 người online báo Full sv - by Ben
    if (arrayp(user2 = USER_D->get_user()))
    {
        size2 = sizeof(user2);
        if (size2 >= 60)
        {
            errstr = "Người chơi đã đầy !";
        }
    }

    user = filter_array(USER_D->get_user(), (
                                                : get_ip_name($1) == $2:),
                        get_ip_name(me));
    if (sizeof(user) >= 8)
    {
        errstr = "Chỉ có thể trực tuyến 8 Tài khoản !";
    }

    if (exist < 1)
    {
        errstr = "Tài khoản này không tồn tại!";
    }
    if (errstr)
    {
        send_user(me, "%c%s", '!', errstr);
        send_user(me, "%c%c", 0xff, 0x11);
        destruct(me);
        return 0;
    }
    return 1;
}