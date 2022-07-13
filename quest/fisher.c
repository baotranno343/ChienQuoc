
// 变量：捕鱼地点列表

string *FisherTable01 = ({
        "010,290,190",
});

int sizeof_fisher_01 = sizeof(FisherTable01);

string *FisherTable02 = ({
        "020,290,190",
});

int sizeof_fisher_02 = sizeof(FisherTable02);

string *FisherTable03 = ({
        "030,290,190",
});

int sizeof_fisher_03 = sizeof(FisherTable03);

string *FisherTable04 = ({
        "040,290,190",
});

int sizeof_fisher_04 = sizeof(FisherTable04);

string *FisherTable05 = ({
        "050,290,190",
});

int sizeof_fisher_05 = sizeof(FisherTable05);

string *FisherTable06 = ({
        "060,290,190",
});

int sizeof_fisher_06 = sizeof(FisherTable06);

string *FisherTable07 = ({
        "070,290,190",
});

int sizeof_fisher_07 = sizeof(FisherTable07);

// 函数：获取合法坐标
int get_fisher_xy( int city, int flag )
{
        string p;
        int z, x, y;

        switch( city )
        {
      default : while( 1 )
                {
                        p = FisherTable01[ random(sizeof_fisher_01) ];
                        if( sscanf(p, "%d,%d,%d", z, x, y) != 3 ) continue;
                        return ( get_block(z, x, y) & flag ) ? 0 : z * 1000000 + x * 1000 + y;
                }
                break;

       case 2 : while( 1 )
                {
                        p = FisherTable02[ random(sizeof_fisher_02) ];
                        if( sscanf(p, "%d,%d,%d", z, x, y) != 3 ) continue;
                        return ( get_block(z, x, y) & flag ) ? 0 : z * 1000000 + x * 1000 + y;
                }
                break;

       case 3 : while( 1 )
                {
                        p = FisherTable03[ random(sizeof_fisher_03) ];
                        if( sscanf(p, "%d,%d,%d", z, x, y) != 3 ) continue;
                        return ( get_block(z, x, y) & flag ) ? 0 : z * 1000000 + x * 1000 + y;
                }
                break;

       case 4 : while( 1 )
                {
                        p = FisherTable04[ random(sizeof_fisher_04) ];
                        if( sscanf(p, "%d,%d,%d", z, x, y) != 3 ) continue;
                        return ( get_block(z, x, y) & flag ) ? 0 : z * 1000000 + x * 1000 + y;
                }
                break;

       case 5 : while( 1 )
                {
                        p = FisherTable05[ random(sizeof_fisher_05) ];
                        if( sscanf(p, "%d,%d,%d", z, x, y) != 3 ) continue;
                        return ( get_block(z, x, y) & flag ) ? 0 : z * 1000000 + x * 1000 + y;
                }
                break;

       case 6 : while( 1 )
                {
                        p = FisherTable06[ random(sizeof_fisher_06) ];
                        if( sscanf(p, "%d,%d,%d", z, x, y) != 3 ) continue;
                        return ( get_block(z, x, y) & flag ) ? 0 : z * 1000000 + x * 1000 + y;
                }
                break;

       case 7 : while( 1 )
                {
                        p = FisherTable07[ random(sizeof_fisher_07) ];
                        if( sscanf(p, "%d,%d,%d", z, x, y) != 3 ) continue;
                        return ( get_block(z, x, y) & flag ) ? 0 : z * 1000000 + x * 1000 + y;
                }
                break;
        }
}
