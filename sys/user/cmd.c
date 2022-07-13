#include <time.h>
// 函数：生成二进制码
void SAVE_BINARY() {}

// 命令路径映射
private
mapping DieCmds, UserCmds;
private
mapping GmCmds, GodCmds, Gm2Cmds, Gm3Cmds;

private
void rehash(mapping mpCmds, string path);

// 函数：构造处理
private
void create()
{
        DieCmds = ([]);
        rehash(DieCmds, "/cmd/base/");

        UserCmds = ([]);
        rehash(UserCmds, "/cmd/std/");
        rehash(UserCmds, "/cmd/user/");
        rehash(UserCmds, "/cmd/base/");

        GmCmds = ([]);
        rehash(GmCmds, "/cmd/gm/");
        Gm3Cmds = copy(GmCmds);
        rehash(Gm3Cmds, "/cmd/gm3/");
        Gm2Cmds = copy(Gm3Cmds);
        rehash(Gm2Cmds, "/cmd/pro/");
        GodCmds = copy(GmCmds);
        rehash(GodCmds, "/cmd/pro/");
        rehash(GodCmds, "/cmd/gm3/");
        rehash(GodCmds, "/cmd/sys/");
        rehash(GodCmds, "/cmd/debug/");
        rehash(GodCmds, "/make/item"); // 生成程序
        rehash(GodCmds, "/make/weapon");
        rehash(GodCmds, "/make/equip");
        rehash(GodCmds, "/make/npc");
        rehash(GodCmds, "/make/std");
        rehash(GodCmds, "/make/vita");
        rehash(GodCmds, "/make/skill");
}

// 函数：命令->映照表
private
void rehash(mapping mpCmds, string path)
{
        string *cmds;
        int i, size;

        if (!stringp(path))
                return;

        // 修正命令路径
        if (path[ < 1] != '/')
                path += "/";
        if (!directory_exist(path[0.. < 2]))
                return;

        // 命令->映照表
        cmds = get_dir(path);
        for (i = 0, size = sizeof(cmds); i < size; i++)
                if (cmds[i][ < 2.. < 1] == ".c" && sscanf(cmds[i], "%s.c", cmds[i]) || cmds[i][ < 4.. < 1] == ".cpp" && sscanf(cmds[i], "%s.cpp", cmds[i]))
                        mpCmds[cmds[i]] = path + cmds[i];
}

// 函数：获取可用命令
mapping get_cmds(string level)
{
        switch (level)
        {
        default:
                return ([]);
        case PLAYER_CLASS:
                return copy(UserCmds);
        case GM_CLASS:
                return copy(UserCmds) + copy(GmCmds);
        case GM3_CLASS:
                return copy(UserCmds) + copy(Gm3Cmds);
        case GM2_CLASS:
                return copy(UserCmds) + copy(Gm2Cmds);
        case GOD_CLASS:
                return copy(UserCmds) + copy(GodCmds);
        }
}

// 函数：获取可用命令(死亡)
mapping get_cmds_die(string level)
{
        switch (level)
        {
        default:
                return ([]);
        case PLAYER_CLASS:
                return copy(DieCmds);
        case GM_CLASS:
                return copy(DieCmds) + copy(GmCmds);
        case GM3_CLASS:
                return copy(DieCmds) + copy(Gm3Cmds);
        case GM2_CLASS:
                return copy(DieCmds) + copy(Gm2Cmds);
        case GOD_CLASS:
                return copy(DieCmds) + copy(GodCmds);
        }
}

// 函数：查找命令路径
string find_command(string cmd, string level)
{
        mapping mpCmds;

        switch (level)
        {
        case PLAYER_CLASS:
                mpCmds = UserCmds;
                if (!mapp(mpCmds) || !stringp(cmd))
                        return "";
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                break;
        case GM_CLASS:
                mpCmds = UserCmds;
                if (!mapp(mpCmds) || !stringp(cmd))
                        return "";
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                mpCmds = GmCmds;
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                break;
        case GM2_CLASS:
                mpCmds = UserCmds;
                if (!mapp(mpCmds) || !stringp(cmd))
                        return "";
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                mpCmds = Gm2Cmds;
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                break;
        case GM3_CLASS:
                mpCmds = UserCmds;
                if (!mapp(mpCmds) || !stringp(cmd))
                        return "";
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                mpCmds = Gm3Cmds;
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                break;
        case GOD_CLASS:
                mpCmds = UserCmds;
                if (!mapp(mpCmds) || !stringp(cmd))
                        return "";
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                mpCmds = GodCmds;
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                break;
        }

        return "";
}

// 函数：查找命令路径(死亡)
string find_command_die(string cmd, string level)
{
        mapping mpCmds;

        switch (level)
        {
        case PLAYER_CLASS:
                mpCmds = DieCmds;
                if (!mapp(mpCmds) || !stringp(cmd))
                        return "";
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                break;
        case GM_CLASS:
                mpCmds = DieCmds;
                if (!mapp(mpCmds) || !stringp(cmd))
                        return "";
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                mpCmds = GmCmds;
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                break;
        case GM2_CLASS:
                mpCmds = DieCmds;
                if (!mapp(mpCmds) || !stringp(cmd))
                        return "";
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                mpCmds = Gm2Cmds;
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                break;
        case GM3_CLASS:
                mpCmds = DieCmds;
                if (!mapp(mpCmds) || !stringp(cmd))
                        return "";
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                mpCmds = Gm3Cmds;
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                break;
        case GOD_CLASS:
                mpCmds = DieCmds;
                if (!mapp(mpCmds) || !stringp(cmd))
                        return "";
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                mpCmds = GodCmds;
                if (!undefinedp(mpCmds[cmd]))
                        return mpCmds[cmd];
                break;
        }

        return "";
}

void log_item(string info)
{
        string file;
        int iTime;
        mixed *mxTime;
        iTime = time();
        mxTime = localtime(iTime);
        file = sprintf("item_%d%02d%02d.dat", mxTime[TIME_YEAR], mxTime[TIME_MON] + 1, mxTime[TIME_MDAY]);
        log_file(file, sprintf("%s %s\n", short_time(), info));
}