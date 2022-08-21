#include <iostream>
#include "Person.h"
#include <algorithm>

using namespace std;
int main()
{

  




cout << "Testing Person class" << endl;
  Person p1= Person(Person::MALE, "A");
  Person p2 = Person(Person::MALE, "B");
  Person p3 = Person(Person::MALE, "C");
  Person p4 = Person(Person::MALE, "D");
  Person p5 = Person(Person::FEMALE, "E");
  Person p6 = Person(Person::MALE, "F");
  
  Person p7 = Person(Person::MALE, "G");
  Person p8 = Person(Person::MALE, "H");
  Person p9 = Person(Person::MALE, "I");
  Person p10 = Person(Person::FEMALE, "J");
  Person p11 = Person(Person::MALE, "K");
  Person p12 = Person(Person::MALE, "L");


p2.setFather(&p11);
p12.setFather(&p9);


p3.setFather(&p1);
p4.setFather(&p1);
p4.setMother(&p10);


p5.setFather(&p2);
p6.setFather(&p2);
p7.setFather(&p3);
p8.setFather(&p4);
p8.setMother(&p5);
p9.setFather(&p6);




  

 
  People results = People();
  People results2 = People();

  
  
  results2.push_back(&p1);
  
   p8.getCousins(results);
  
  

  for (auto it = results.begin(); it != results.end(); ++it) {
   

      cout<<(*it)->name<<endl;
      


   }

 


}
