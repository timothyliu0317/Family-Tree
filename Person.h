#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

class Person;
typedef std::vector<Person*> People;




class Person
{
public:

    
    static const char* getAuthor();

    enum Sex { MALE, FEMALE };

    Person(Sex, const std::string& name = "");
    ~Person();

    /**
        Set the father of this person
    */
    bool setFather(Person*);

    /**
        Set the mother of this person
    */
    bool setMother(Person*);

    Person* getFather() const { return father; }
    Person* getMother() const { return mother; }

    /**
        Checks if this person has a given child
    */
    bool hasChild(const Person*) const;

    /**
        Adds a child to the person's child list
    */
    bool addChild(Person*);

    /**
        Remove a child from this person's children list
    */
    bool removeChild(Person*);

    People::size_type getNumChildren() const { return children.size(); }
    Person* getChild(People::size_type index) const { return children.at(index); }

    /**
        Remove all children of this person
    */
    void removeAllChildren();

    /**
        Get all ancestors of this person.
    */
    void getAncestors(People& results) const;

    /**
        Get all descendants of this person.
    */
    void getDescendants(People& results) const;

    /**
        Get all siblings of this person.
    */
    void getSiblings(People& results) const;

    /**
        Get all cousins of this person in the same generation.
    */
    void getCousins(People& results) const;
    void getRootAncestors(People& results, std::vector<int>& gen_vec, int gen) const;
    void getDecendentsgen(People & results, int gen) const;
 
    void addAncestors(People& results) const;
    void addDescendants(People& results) const;
    void printAllChildrenNames() const;
    void addSelfToPeople(People& results) const;
    const Sex sex;
    const std::string name;

private:

    People::iterator findChild(const Person*);
    People::const_iterator findChild(const Person*) const;

    Person *mother, *father;
    People children;
};

