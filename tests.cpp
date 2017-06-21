//
// Created by orerez on 20/06/2017.
//

/* #include "List.h"
#include <iostream>
using namespace std;

#define ASSERT_TEST(b) do { \
        if (!(b)) { \
                printf("\nAssertion failed at %s:%d %s\n",__FILE__,__LINE__,#b); \
                return false; \
        } \
} while (0)

ListTests(){
    string juha="juhatit";
    node<string> k(juha);
    string c=k.getInfo();
    ASSERT_TEST(c==juha);
    node<string> l(&k, NULL, false,"Stringo");
    ASSERT_TEST(l.getNext()->getInfo()==k.getInfo());
    ASSERT_TEST(!l.isEnd());
    ASSERT_TEST(l.getInfo()=="Stringo");
    node<string> m(l.getNext(),&k,true,"try");
    ASSERT_TEST(m.isEnd());
    node<string> p(m.getPrevious(),m.getPrevious(), false,"humus");
    node<string> s("hamaya");
    ASSERT_TEST(s.getNext()== nullptr);
    p.setEnd(true);
    ASSERT_TEST(p.isEnd());
    p.setNext(&m);
    ASSERT_TEST(p.getNext()->getInfo()==m.getInfo());
    p.setPrevious(&m);
    ASSERT_TEST(p.getNext()->getInfo()==m.getInfo());
} */