int main(int argc, char const *argv[])
{
    const int *p1 = new int(1);
    int *const p2 = new int(2);
    // *p1 = 11;                    // p1指向常量整数(常量指针)
    p1 = new int(2);                  
    // p2 = p1;                     // p2是指针常量
    *p2 = 22; 
    return 0;
}
