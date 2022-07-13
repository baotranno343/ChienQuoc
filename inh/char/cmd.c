
#include <npc.h>
#include <skill.h>
#include <effect.h>
#define MAX_TIMES 50 // 每秒命令限制

// 命令计数限制
private
static int ThisTime = time(); // 同时用于断线僵尸
private
static int InputCmds;
// 可用命令等级
private
static string CmdsLevel;

// 函数：获取发呆时间
int get_idle_time() { return gone_time(ThisTime); }

// 函数：获取可用命令
mixed *get_commands() { return commands(); }

// 函数：命令输入处理
string process_input(string cmd)
{
        // 空命令、无生命则返回
        if (!cmd || !living(this_object()))
        {
                send_user(this_object(), "%c%d", 0x74, time2()); // 动作时钟(2.x 分钟校正)
                return "";
        }

        // 每秒命令限制
        if (time() != ThisTime)
        {
                ThisTime = time();
                InputCmds = 0;
        }
        else if (++InputCmds > MAX_TIMES) // && is_player(me)
        {
                return "";
        }
        return cmd;
}

// 函数：命令处理
int command_hook(string arg)
{

        object me, snooper;
        string verb, file, luusnoop;

        me = this_object();
        verb = get_verb(); // 获取命令动词

        if (is_god(me))
                send_user(me, "%c%s", '>', sprintf("g> %s %s", verb, arg ? arg : ""));
        //if(verb!="go"&&verb!="desc"&&verb!="tips"&&verb!="kill"&&verb!="use"&&verb!="pf"&&verb!="pf2"&&verb!="remove"&&verb!="drop"&&verb!="say"&&verb!="chat"&&verb!="vipchat"&&verb!="et"&&verb!="ct"&&verb!="ft"&&verb!="ot"&&verb!="tt"&&verb!="rumor")
        //"cmd/debug/kenl"->main(me, verb, arg);

        // Lưu snoop - Start
        // luusnoop = sprintf("snoop_%02d%02d%d.txt", mxTime[TIME_MDAY], mxTime[TIME_MON] + 1, mxTime[TIME_YEAR]);
        // write_file(sprintf("data/%c/%c/%c/%s/%s", me->get_id()[0], me->get_id()[1], me->get_id()[2], me->get_id(), luusnoop),
        //            sprintf("%s : %s: %d> %s %s\n", short_time(time()), me->get_name(), me->get_number(), verb, arg ? arg : ""));
        // Lưu snoop - End
        if (objectp(snooper = me->get_snooper()) && is_god(snooper))
                tell_user(snooper, "%d> %s %s", me->get_number(), verb, arg ? arg : "");

        if (me->is_die())
                file = USER_CMD_D->find_command_die(verb, CmdsLevel);
        else
                file = USER_CMD_D->find_command(verb, CmdsLevel);

        if (me->get_login_flag() < 3) // 与 effect/user/login 同步
        {
                set_effect(me, EFFECT_USER_LOGIN, 0);

                me->set_login_flag(3);
                //              me->set_char_type(PLAYER_TYPE_2);
                me->add_pk(0); // 显示ＰＫ状态
                if (!get_effect(me, EFFECT_CHAR_INVISIBLE))
                        set_invisible(me, 0); // 没有隐身时
                if (gone_time(me->get_login_time()) < 20)
                        USER_TASK_D->auto_give_task(me); // 只在登录时
        }
        if (file == "")
        {
                "/sys/sys/count"->add_command("无指令", strlen(verb) + strlen(arg) + 1);
                return 1; // 无命令
        }
        if (!call_other(file, "main", me, arg))
        {
                "/sys/sys/count"->add_command("无效", strlen(verb) + strlen(arg) + 1);
                return 1; // 无效命令
        }
        else
                "/sys/sys/count"->add_command(verb, strlen(verb) + strlen(arg) + 1);

        return 1;
}

// 函数：强迫执行命令
int force_me(string cmd)
{
        string result;

        //      if( previous_object() != this_object() ) return 0;
        result = process_input(cmd);
        return result != "" ? command(result) : 0;
}

// 函数：使能接收命令
void enable_player()
{
        object me = this_object();

        set_living_name(me->get_char_id()); // 涉及太广，禁止改动
        enable_commands();
        add_action("command_hook", "", 1);

        me->set_security_class();
        CmdsLevel = get_class(me);
}

// -------------------------------------------------------------

// 函数：登录命令处理
int logon_cmds_process(string arg)
{
        string id, name, code;
        int gender, order, photo, hair;
        object me = this_object();

        if (!arg || arg == "")
                return 1;
        if (sscanf(arg, "%s %s %s %d %d %d %d", id, code, name, gender, photo, hair, order) == 7)
        {
                me->set_photo(photo);
                me->set_hair(hair);
                LOGIN_0_D->new_login_2(this_object(), id, code, name, gender, order);
        }
        else if (sscanf(arg, "%s %s %s %d %d", id, code, name, gender, order) == 5)
        {
                LOGIN_0_D->new_login_2(this_object(), id, code, name, gender, order);
        }
        else if (sscanf(arg, "%s %s %s %d", id, code, name, gender) == 4)
        {
                LOGIN_0_D->new_login_2(this_object(), id, code, name, gender, 1);
        }
        else if (sscanf(arg, "\"%s\" \"%s\" %d", id, code, order) == 3 || sscanf(arg, "%s %s %d", id, code, order) == 3)
        {
                LOGIN_D->connect(this_object(), id, code, order);
        }
        else if (sscanf(arg, "\"%s\" \"%s\"", id, code) == 2 || sscanf(arg, "%s %s", id, code) == 2)
        {
                LOGIN_D->connect(this_object(), id, code, 0);
        }
        return 1;
}

// 函数：登录命令处理
int logon_cmds_process2(string arg)
{
        string id, name, code;
        int gender, order, hair, photo;
        object me = this_object();

        if (!arg || arg == "")
                return 1;
        if (sscanf(arg, "%s %s %d %d %d %d", id, name, gender, photo, hair, order) == 6)
        {
                me->set_photo(photo);
                me->set_hair(hair);
                LOGIN_0_D->new_login_2(this_object(), id, "", name, gender, order);
        }
        else if (sscanf(arg, "%s %s %d %d", id, name, gender, order) == 4)
        {
                LOGIN_0_D->new_login_2(this_object(), id, "", name, gender, order);
        }
        else if (sscanf(arg, "%s %s %d", id, name, gender) == 3)
        {
                LOGIN_0_D->new_login_2(this_object(), id, "", name, gender, 1);
        }
        else if (sscanf(arg, "\"%s\" %d", id, order) == 2 || sscanf(arg, "%s %d", id, order) == 2)
        {
                LOGIN_D->connect(this_object(), id, "", order);
        }
        else if (sscanf(arg, "\"%s\"", id) == 1 || sscanf(arg, "%s", id) == 1)
        {
                LOGIN_D->connect(this_object(), id, "", 0);
        }
        return 1;
}

// 函数：使能接收登录命令
void enable_logon_cmds()
{
        enable_commands();
        add_action("logon_cmds_process", "LOGIN", 1);
        add_action("logon_cmds_process2", "LOGIN2", 1);
        add_action("logon_cmds_process", "LOGIN3", 1);
}

// 函数：使能接收登录命令
void disable_logon_cmds()
{
        remove_action("logon_cmds_process", "LOGIN");
        remove_action("logon_cmds_process2", "LOGIN2");
        remove_action("logon_cmds_process", "LOGIN3");
}