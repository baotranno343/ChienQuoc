
// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：获得对方尊称(用于小贩)
string get_respect( object who )
{
        switch( who->get_gender() )
        {
                case 1 : return "Đại gia";
                case 2 : return "Cô nương";
               default : return "Công công";
        }
}

// 函数：获得对方尊称(用于长者)
string get_respect_2( object who )
{
        switch( who->get_gender() )
        {
                case 1 : return "Tiểu huynh đệ";
                case 2 : return "Tiểu cô nương";
               default : return "Tiểu công công";
        }
}
