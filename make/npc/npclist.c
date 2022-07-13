
// 函数：获取物品文件
string get_npc_type( string type )
{
                switch( type )
                {
          case "王爷" : type = "KING";  break;
          case "大臣" : type = "MINISTER";  break;
          case "捕头" : case "衙役" : 
                        type = "CAPTOR";  break;
          case "将帅" : type = "MARSHAL";  break;
          case "军官" : type = "GENERAL";  break;
          case "士兵" : type = "SOLDIER";  break;
          case "富人" : case "富商" : 
                        type = "RICH_MAN";  break;
      case "富家公子" : type = "RICH_YOUNG";  break;
      case "富家男孩" : type = "RICH_BOY";  break;
          case "老板" : type = "SELLER";  break;
          case "书生" : type = "SCHOLAR";  break;
      case "穷家男孩" : type = "BOY";  break;
          case "游侠" : type = "PALADIN";  break;
          case "守卫" : type = "GUARD";  break;
          case "打手" : type = "WARRIOR";  break;
          case "樵夫" : case "猎户" : 
                        type = "WOODMAN";  break;
          case "小二" : case "渔夫" : 
                        type = "WAITER";  break;
          case "流氓" : case "无赖" : 
                        type = "ROGUE";  break;
          case "农民" : type = "FARMER";  break;

          case "贵妇" : type = "RICH_WOMAN";  break;
      case "富家小姐" : type = "RICH_LADY";  break;
      case "富家女孩" : type = "RICH_GIRL";  break;
          case "丫鬟" : type = "SERVANT_GIRL";  break;
          case "村妇" : type = "FARM_WOMAN";  break;
          case "村姑" : type = "FARM_LADY";  break;
      case "穷家女孩" : type = "GIRL";  break;

          case "僵尸" : type = "ZOMBIE";  break;

              default : type = "";  break;
                        }

        return type;
}
