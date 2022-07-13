
private mapping mpFly = ([ ]);                  // 瞬移数据集

private mapping mpMascot = ([ ]);               // 福缘数据集(永久)

private mapping mpChBlk = ([ ]);                // 阻止数据集(频道)

private mapping mpLOG = ([ ]);                  // 日志数据集

// =============================================================

// 函数：获取瞬移数据集
mapping get_fly_dbase() { return copy(mpFly); }

// 函数：获取瞬移数据集大小
int sizeof_fly_dbase() { return sizeof(mpFly); }

// 函数：初始瞬移数据集
void init_fly_dbase() { mpFly = ([ ]); }

// -------------------------------------------------------------

// 函数：获取瞬移数据集
mixed get_fly( string key ) { return mpFly[key]; }

// 函数：设置瞬移数据集
mixed set_fly( string key, mixed value ) { return mpFly[key] = value; }

// 函数：添加瞬移数据集
mixed add_fly( string key, mixed value )
{
        mixed old;

        if( !( old = get_fly(key) ) ) 
                return set_fly(key, value);
        else    return set_fly(key, old + value);
}

// 函数：删除瞬移数据集
void delete_fly( string key ) { map_delete(mpFly, key); }

// =============================================================

// 函数：获取福缘数据集
mapping get_mascot_dbase() { return copy(mpMascot); }

// 函数：获取福缘数据集大小
int sizeof_mascot_dbase() { return sizeof(mpMascot); }

// 函数：初始福缘数据集
void init_mascot_dbase() { mpMascot = ([ ]); }

// -------------------------------------------------------------

// 函数：获取福缘数据集
mixed get_mascot( string key ) { return mpMascot[key]; }

// 函数：设置福缘数据集
mixed set_mascot( string key, mixed value ) { return mpMascot[key] = value; }

// 函数：添加福缘数据集
mixed add_mascot( string key, mixed value )
{
        mixed old;

        if( !( old = get_mascot(key) ) ) 
                return set_mascot(key, value);
        else    return set_mascot(key, old + value);
}

// 函数：删除福缘数据集
void delete_mascot( string key ) { map_delete(mpMascot, key); }

// =============================================================

// 函数：获取阻止数据集
mapping get_chblk_dbase() { return copy(mpChBlk); }

// 函数：获取阻止数据集大小
int sizeof_chblk_dbase() { return sizeof(mpChBlk); }

// 函数：初始阻止数据集
void init_chblk_dbase() { mpChBlk = ([ ]); }

// -------------------------------------------------------------

// 函数：获取阻止数据集
mixed get_chblk( string key ) { return mpChBlk[key]; }

// 函数：设置阻止数据集
mixed set_chblk( string key, mixed value ) { return mpChBlk[key] = value; }

// 函数：添加阻止数据集
mixed add_chblk( string key, mixed value )
{
        mixed old;

        if( !( old = get_chblk(key) ) ) 
                return set_chblk(key, value);
        else    return set_chblk(key, old + value);
}

// 函数：删除阻止数据集
void delete_chblk( string key ) { map_delete(mpChBlk, key); }

// =============================================================

// 函数：获取日志数据集
mapping get_log_dbase() { return copy(mpLOG); }

// 函数：获取日志数据集大小
int sizeof_log_dbase() { return sizeof(mpLOG); }

// 函数：初始日志数据集
void init_log_dbase() { mpLOG = ([ ]); }

// -------------------------------------------------------------

// 函数：获取日志数据集
mixed get_log( string key ) { return mpLOG[key]; }

// 函数：设置日志数据集
mixed set_log( string key, mixed value ) { return mpLOG[key] = value; }

// 函数：添加日志数据集
mixed add_log( string key, mixed value )
{
        mixed old;

        if( !( old = get_log(key) ) ) 
                return set_log(key, value);
        else    return set_log(key, old + value);
}

// 函数：删除日志数据集
void delete_log( string key ) { map_delete(mpLOG, key); }

// 函数：添加金钱日志
void add_gold_log( string key, int gold )
{
        string keyH, keyL;
        int oldH, oldL;

        switch( key )
        {
          case "drop" : keyH = "$drop$H";  keyL= "$drop$L";  break;    // 丢地上的钱
           case "get" : keyH = "$get$H";  keyL= "$get$L";  break;    // 拣地上的钱
          case "give" : keyH = "$give$H";  keyL= "$give$L";  break;    // 给别人的钱
         case "give2" : keyH = "$give2$H";  keyL= "$give2$L";  break;    // 别人给的钱
      case "exchange" : keyH = "$exchange$H";  keyL= "$exchange$L";  break;    // 交易给的钱
     case "exchange2" : keyH = "$exchange2$H";  keyL= "$exchange2$L";  break;    // 交易收的钱
           case "buy" : keyH = "$buy$H";  keyL= "$buy$L";  break;    // 买东西的钱
          case "sell" : keyH = "$sell$H";  keyL= "$sell$L";  break;    // 卖东西的钱
          case "buy2" : keyH = "$buy2$H";  keyL= "$buy2$L";  break;    // 买东西的钱(摆摊)
         case "sell2" : keyH = "$sell2$H";  keyL= "$sell2$L";  break;    // 卖东西的钱(摆摊)
          case "date" : keyH = "$date$H";  keyL= "$date$L";  break;    // 活动得的钱(节日)
          case "task" : keyH = "$task$H";  keyL= "$task$L";  break;    // 任务得的钱
         case "trade" : keyH = "$trade$H";  keyL= "$trade$L";  break;    // 经商赚的钱
          case "biao" : keyH = "$biao$H";  keyL= "$biao$L";  break;    // 运镖赚的钱
        case "repair" : keyH = "$repair$H";  keyL= "$repair$L";  break;    // 修理用的钱
          case "make" : keyH = "$make$H";  keyL= "$make$L";  break;    // 合成用的钱
           case "org" : keyH = "$org$H";  keyL= "$org$L";  break;    // 捐给帮的钱
         case "learn" : keyH = "$learn$H";  keyL= "$learn$L";  break;    // 学习花的钱
           case "pay" : keyH = "$pay$H";  keyL= "$pay$L";  break;    // 给系统的钱：任务，入城....
              default : keyH = "$????$H";  keyL= "$????$L";  break;    // ????
        }

        oldH = get_log(keyH);  oldL = get_log(keyL);

        if( oldH == 0 )
        {
                oldL += gold;
        }
        else if( oldH > 0 )
        {
                if( gold > 0 )
                {
                        oldL += gold % BILLION_NUMBER;
                }
                else if( gold < 0 )
                {
                        oldL += gold % BILLION_NUMBER + BILLION_NUMBER;
                        oldH --;
                }
        }
        else
        {
                if( gold < 0 )
                {
                        oldL += gold % BILLION_NUMBER;
                }
                else if( gold > 0 )
                {
                        oldL += gold % BILLION_NUMBER - BILLION_NUMBER;
                        oldH ++;
                }
        }
        
        oldH += oldL / BILLION_NUMBER;
        oldL = oldL % BILLION_NUMBER;

        set_log(keyH, oldH);  set_log(keyL, oldL);
}
