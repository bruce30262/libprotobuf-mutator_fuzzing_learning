#include "test.pb.h"

#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    TEST t;
    t.set_a(101);
    t.set_b("testtest");
    cout << t.a() << endl;
    cout << t.b() << endl;   
    return 0;
}    
