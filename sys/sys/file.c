
// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：获取绝对路径
string resolve_path(string cwd, string path)
{
        object me = this_player();
        string s, *p;
        int i;
        if (!cwd)
                cwd = "/";
        if (!path || path == ".")
                return cwd;
        if (path == "here" && me)
                return get_object_name(environment(me)) + ".c";
        if (path[0] != '/')
                path = cwd + (cwd[ < 1] != '/' ? "/" : "") + path;

        p = explode(path, "/");
        for (i = 0; i < sizeof(p); i++)
                if (p[i] == "..")
                {
                        if (sizeof(p) > 2)
                        {
                                p = p[0..i - 2] + p[i + 1.. < 1];
                                i -= 2;
                        }
                        else
                        {
                                p = p[2..< 1];
                                i = 0;
                        }
                }
        path = "/" + implode(p, "/");

        return (path == "/"
                        "/")
                   ? "/"
                   : path;
}
