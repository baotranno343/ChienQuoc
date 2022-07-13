
#include <ansi.h>

#define EMOTE           INI_DIR "emote.ini"

private mapping Emote = ([ ]);

private void load_emote();

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：构造处理
private void create() { load_emote(); }

// 函数：读取动作资料
private void load_emote()
{
        string *line, lemma, content, verb;
        int i, size;

        // 读出动作资料
        line = explode( read_file( EMOTE ), "\n" );

        // 历遍动作资料
        size = sizeof(line);
        for( i = 0, verb = ""; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( line[i][<1] <= ' ' ) line[i] = line[i][0..<2];    // UNIX 格式
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( !sscanf( line[i], "%s : %s", lemma, content ) ) 
                {
                        log_file( ERROR, sprintf( "错误: " EMOTE " 第 %d 行动作定义错。\n", i + 1 ) );
                        continue;
                }
                if( lemma == "ACT" ) 
                {
                        verb = content;
                        Emote[verb] = ([ ]);
                        Emote[verb]["none"] = "";
                        Emote[verb]["who"] = "";
                        Emote[verb]["self"] = "";
                        Emote[verb]["note"] = "";
                }
                else if( verb != "" ) switch( lemma ) 
                {
           case "ALL" : Emote[verb]["none"] = content;  break;
           case "WHO" : Emote[verb]["who"] = content;  break;
           case ">ME" : Emote[verb]["self"] = content;  break;
          case "NOTE" : Emote[verb]["note"] = content;  break;
                }
        }
}

// 函数：查询所有动作
string *get_all_emote() { return sort_array( keys(Emote), 1 ); }

// 函数：查询单个动作
mapping get_emote( string verb ) { return undefinedp( Emote[verb] ) ? ([ ]) : Emote[verb]; }

// 函数：查询动作说明
string get_emote_note( string verb ) { return undefinedp( Emote[verb] ) ? "" : Emote[verb]["note"]; }

// -------------------------------------------------------------

// 函数：返回自己尊称
string get_self_respect( object me )    // (Cha), 
{
        switch( me->get_gender() )
        {
      default : return "Bổn công công";
       case 1 : switch( me->get_fam_name() )
                {
              default : return "Bổn đại gia";
        case "Đào Hoa Nguyên" : return "Bổn tiền bối";
          case "Thục Sơn" : return "Bổn đại hiệp";
        case "Cấm Vệ Quân" : return "Bổn tướng quân";
          case "Đường Môn" : return "Bổn đại hiệp";
          case "Mao Sơn" : return "Bổn đạo trưởng";    // 本道
        case "Côn Luân" : return "Bổn tiên trưởng";    // 本仙
        case "Vân Mộng Cốc" : return "Bổn đại sư";
                }
       case 2 : switch( me->get_fam_name() )
                {
              default : return "Bổn cô nương";
        case "Đào Hoa Nguyên" : return "Bổn cô nương";
          case "Thục Sơn" : return "Bổn nữ hiệp";
        case "Cấm Vệ Quân" : return "Nữ tướng quân ta";
          case "Đường Môn" : return "Bổn nữ hiệp";
          case "Mao Sơn" : return "Bổn đạo cô";
        case "Côn Luân" : return "Bổn tiên cô";
        case "Vân Mộng Cốc" : return "Nữ đại sư ta";
                }
        }
}

// 函数：返回对方尊称
string get_respect( object who )    // (Ngài), 这位(Ngài), 
{
        switch( who->get_gender() )
        {
      default : return "Công công";
       case 1 : switch( who->get_fam_name() )
                {
              default : return "Đại gia";
        case "Đào Hoa Nguyên" : return "Tráng sĩ";
          case "Thục Sơn" : return "Đại hiệp";
        case "Cấm Vệ Quân" : return "Tướng quân";
          case "Đường Môn" : return "Đại hiệp";
          case "Mao Sơn" : return "Đạo trưởng";    // 道兄
        case "Côn Luân" : return "Tiên trưởng";    // 仙兄
        case "Vân Mộng Cốc" : return "Đại sư";
                }
       case 2 : switch( who->get_fam_name() )
                {
              default : return "Cô nương";
        case "Đào Hoa Nguyên" : return "Cô nương";
          case "Thục Sơn" : return "Nữ hiệp";
        case "Cấm Vệ Quân" : return "Nữ tướng quân";
          case "Đường Môn" : return "Nữ hiệp";
          case "Mao Sơn" : return "Đạo cô";
        case "Côn Luân" : return "Tiên cô";
        case "Vân Mộng Cốc" : return "Nữ đại sư";
                }
        }
}

// 函数：返回对方贬称
string get_disrespect( object who )    // (Tiểu tử), Ngươi这(Tiểu tử), 
{
        switch( who->get_gender() )
        {
      default : return "Tử thái giám";
       case 1 : switch( who->get_fam_name() )
                {
              default : return "Vương bát đản";
        case "Đào Hoa Nguyên" : return "Vương bát đản";
          case "Thục Sơn" : return "Tử xú tặc";
        case "Cấm Vệ Quân" : return "Tử xú tặc";
          case "Đường Môn" : return "Tử xú tặc";
          case "Mao Sơn" : return "Tử yêu đạo";    // 死牛鼻子, 死贼道
        case "Côn Luân" : return "Tử yêu quái";
        case "Vân Mộng Cốc" : return "Lão thất phu";
                }
       case 2 : switch( who->get_fam_name() )
                {
              default : return "Tử tiện nhân";
        case "Đào Hoa Nguyên" : return "Tử tiện nhân";
          case "Thục Sơn" : return "Tặc bà nương";
        case "Cấm Vệ Quân" : return "Tặc bà nương";
          case "Đường Môn" : return "Tặc bà nương";
          case "Mao Sơn" : return "Xú yêu nữ";
        case "Côn Luân" : return "Xú yêu quái";
        case "Vân Mộng Cốc" : return "Xú bà nương";
                }
        }
}

// 函数：处理表情动作
string do_emote( object me, string name, string verb, object who )
{
        string result;

        // 禁止非法动作
        if( !verb || !mapp(Emote) || undefinedp( Emote[verb] ) ) return 0;

        // 判断动作对象
        if( !objectp(who) )
        {
                if( !stringp( result = Emote[verb]["none"] ) ) return 0;
                result = replace_string(result, "(Ta)", HIC+name+NOR );
                result = replace_string(result, "(Cha)", get_self_respect(me) );
        }
        else 
        {
                if( me == who )
                {
                        if( !stringp( result = Emote[verb]["self"] ) ) return 0;
                        result = replace_string(result, "(Ta)", HIC+name+NOR );
                        result = replace_string(result, "(Cha)", get_self_respect(me) );
                }
                else
                {
                        if( !stringp( result = Emote[verb]["who"] ) ) return 0;
                        result = replace_string(result, "(Ta)", HIC+name+NOR );
                        result = replace_string(result, "(Cha)", get_self_respect(me) );
                        result = replace_string(result, "(Ngươi)", HIC+ who->get_name() + NOR );
                        result = replace_string(result, "(Ngài)", get_respect(who) );
                        result = replace_string(result, "(Tiểu tử)", get_disrespect(who) );
                }
        }

        return result;
}
