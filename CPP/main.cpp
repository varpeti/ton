#include <iostream>
#include "Ton/Ton.h"

int main()
{
    
    Ton* test = Ton::parseFromFile("../tests/test.ton");
    Ton* ae = test->at("Creature")->at("Animal")->at("Ground")->at("Mammal")->at("Anthropoid")->at("Human")->at("Male")->at("Albert Einstein");
    
    ae->insert("Theory of relativity");
    ae->insert("Description","German physicist");
    ae->insert("Lived","1879");
    ae->insert("Lived","1955");
    std::cout << test->toString() << "\n";

    delete test;

    /*test = new Ton("l0");
    test->insert("l2","l3");
    std::cout << test->toString() << "\n";*/
    
    std::string a = "t1\n    t2v1\n   t2v2\n   t2v3\n    t2v4";
/*
t1
    t2v1
   t2v2 //ignored
   t2v3 //ignored
   	t2v4
*/
    test = Ton::parseFromString(a);
    std::cout << test->toString() << "\n";

   
    return 0;
}