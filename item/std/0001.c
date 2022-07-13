
inherit ITEM;

// 函数：钱币识别
int is_cash() { return 1; }

// 函数：设置钱币数量
int set_value( int gold ) 
{
        if( gold < 1 ) gold = 1;
//        set_name( sprintf("%d金", gold) );

        switch( gold )
        {
          case 0..499 : set_picid_1(0001);
                        set_picid_2(0001);
                        break;

       case 500..1499 : set_picid_1(0002);
                        set_picid_2(0002);
                        break;

              default : set_picid_1(0003);
                        set_picid_2(0003);
                        break;
        }

        return ::set_value(gold);
}

// 函数：构造处理
void create()
{
        set_name("Tiền Tệ");
        set_picid_1(0001);
        set_picid_2(0001);
        set_unit("金");

        ::set_value(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return sprintf( " %d lượng", get_value() );
}
