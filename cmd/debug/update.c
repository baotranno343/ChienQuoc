void update_dir(object me, string arg);
void preload(object me);
// 函数：命令处理
int main(object me, string arg)
{
        object obj;
        string file, err;

        if (is_player(me))
        {
                notify("Bạn không có đủ quyền.");
                return 1;
        }

        if (!arg)
        {
                notify("Bạn muốn cập nhật những gì?");
                return 1;
        }
        if (arg == "preload")
        {
                preload(me);
                tell_user(me, "Preload Thành Công");
                return 1;
        }
        if (file_size(arg) == -2)
        {
                log_file("updatefile.txt", short_time() + " Biên dịch thư mục: " + arg + "\n");
                update_dir(me, arg);
                tell_user(me, "Biên dịch ok");
                return 1;
        }
        if (obj = find_any_object(arg))
                file = get_file_name(obj) + ".c";
        else if (file_exist(file = absolute_path(me, arg)))
                ;
        else if (file_exist(file = absolute_path(me, arg + ".c")))
                ;
        else if (file_exist(absolute_path(me, arg + ".cpp")))
                file = absolute_path(me, arg + ".c");
        else if (arg == "cwf")
                file = me->get_cwf();
        else
        {
                notify("Bạn không thể tìm thấy đối tượng này.");
                return 1;
        }

        me->set_cwf(file); // 设置工作文件名
        tell_user(me, "Biên dịch lại: " + file);

        if (obj = find_object(file))
        {
                obj->before_destruct();
                destruct(obj);
        }

        if (obj)
        {
                tell_user(me, "Không thể xóa các chương trình cũ.");
                return 1;
        }

        if (err = catch (call_other(file, "???")))
                tell_user(me, "Đã xảy ra lỗi! \n%s", err);
        else
                tell_user(me, "hoàn thành cập nhật! ");

        return 1;
}

int update_file(object me, string arg)
{
        object obj;
        string file, err;

        if (obj = find_any_object(arg))
                file = get_file_name(obj) + ".c";
        else if (file_exist(file = absolute_path(me, arg)))
                ;
        else if (file_exist(file = absolute_path(me, arg + ".c")))
                ;
        else if (file_exist(absolute_path(me, arg + ".cpp")))
                file = absolute_path(me, arg + ".c");
        else if (arg == "cwf")
                file = me->get_cwf();
        else
        {
                log_file("updatefile.txt", sprintf("%s %s can't find obj\n", short_time(), arg));
                return 1;
        }

        log_file("updatefile.txt", "Biên dịch lại" + file + "\n");
        if (obj = find_object(file))
        {
                obj->before_destruct();
                destruct(obj);
        }

        if (obj)
        {
                tell_user(me, "Không thể xóa các chương trình cũ. ");
                return 1;
        }

        if (err = catch (call_other(file, "???")))
                log_file("updatefile.txt", err + "\n");
        return 1;
}
void preload(object me)
{
        int i, size;
        mixed *mxTmp;
        string *line;
        line = explode(read_file("ini/preload.ini"), "\n");
        //  mxTmp = get_dir(arg);
        for (i = 0, size = sizeof(line); i < size; i++)
        {
                // if (mxTmp[i] == ".svn")
                //         continue;
                // if (file_size(arg + mxTmp[i]) == -2)
                //         update_dir(me, arg + mxTmp[i] + "/");
                // if (strstr(mxTmp[i], ".c") == -1)
                //         continue;
                //		tell_user(me,"%s %s",arg,mxTmp[i]);
                update_file(me, line[i]);
        }
}
void update_dir(object me, string arg)
{
        int i, size;
        mixed *mxTmp;

        mxTmp = get_dir(arg);
        for (i = 0, size = sizeof(mxTmp); i < size; i++)
        {
                if (mxTmp[i] == ".svn")
                        continue;
                if (file_size(arg + mxTmp[i]) == -2)
                        update_dir(me, arg + mxTmp[i] + "/");
                if (strstr(mxTmp[i], ".c") == -1)
                        continue;
                //		tell_user(me,"%s %s",arg,mxTmp[i]);
                update_file(me, arg + mxTmp[i]);
        }
}