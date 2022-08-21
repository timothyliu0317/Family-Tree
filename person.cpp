#include "Person.h"
#include <algorithm>
#include <vector>

using namespace std;

const char* Person::getAuthor()
{
  return "Chia-Chuan Liu";
}

Person::Person(Sex sex, const std::string& name)
  : sex(sex), name(name)
{
  father = NULL;
  mother = NULL;
  children = People();
}

Person::~Person()
{
}

bool Person::setFather(Person* p)
{
  assert(p->sex == MALE);
  if (father == NULL){
    father = p;
    p->addChild(this);
  }
  else
  {
    father->removeChild(this);
    father = p;
    p->addChild(this);
  }
  return true;
}

bool Person::setMother(Person* p)
{
  assert(p->sex == FEMALE);
  if (mother == NULL){
    mother = p;
    p->addChild(this);
  }
  else
  {
    mother->removeChild(this);
    mother = p;
    p->addChild(this);
  }
  return true;
}

bool Person::hasChild(const Person* p) const
{
  return std::find(children.begin(), children.end(), p) != children.end();
}

bool Person::addChild(Person* p)
{
  children.push_back(p);
  //TODO: Catch bac_alloc exeption?
  return true;
}

bool Person::removeChild(Person* p)
{
  children.erase(std::remove(children.begin(), children.end(), p), children.end());
  switch(p->sex) {
  case MALE:
    p->father = NULL;
    break;
  case FEMALE:
    p->mother = NULL;
    break;
  }
  return true;
}

void Person::removeAllChildren()
{
  for (auto it= children.begin();it!=children.end();)
  {
    switch(sex) {
    case MALE:
      (*it)->father = NULL;
      break;
    case FEMALE:
      (*it)->mother = NULL;
      break;
    }
    it = children.erase(it);
  }
}

void Person::getAncestors(People& results) const
{
  results.clear();
  addAncestors(results);
  //remove duplicated people
  sort(results.begin(),results.end());
  results.erase(unique(results.begin(),results.end()),results.end());
}

void Person::addAncestors(People& results) const
{
  if (father != NULL)
    {
      results.push_back(father);
      father->addAncestors(results);
    }
  if (mother != NULL)
    {
      results.push_back(mother);
      mother->addAncestors(results);
    }
}

void Person::getDescendants(People& results) const
{
  results.clear();
  addDescendants(results);
  //remove duplicated people
  sort(results.begin(),results.end());
  results.erase(unique(results.begin(),results.end()),results.end());
}

void Person::getSiblings(People& results) const
{
  results.insert( results.end(), father->children.begin(), father->children.end() );
  results.insert( results.end(), mother->children.begin(), mother->children.end() );
  sort( results.begin(), results.end() );
  results.erase( unique( results.begin(), results.end() ), results.end() );
  //remove self
  results.erase(std::remove(results.begin(), results.end(), this), results.end());
}

void Person::addDescendants(People& results) const
{
  for (auto it= children.begin();it!=children.end(); ++it)
    {
      (*it)->addDescendants(results);
    }
}

void Person::getCousins(People& results) const
{
  // find all decendents with no parents
  People root_ancestors = People();
  std::vector<int> ancestors_gen;
  int gen = 0;
  getRootAncestors(root_ancestors, ancestors_gen, gen);

  for (auto it = root_ancestors.begin(); it != root_ancestors.end(); it++)
    {
      People temp = People();
      auto i = std::distance(root_ancestors.begin(), it);
      (*it)->getDecendentsgen(temp, ancestors_gen[(int)i]);
      results.insert( results.end(), temp.begin(), temp.end() );
    }
  //remove duplitcate items
  sort( results.begin(), results.end() );
  results.erase( unique( results.begin(), results.end() ), results.end() );
  //remove self
  results.erase(std::remove(results.begin(), results.end(), this), results.end());
  //remove siblings
  People siblings = People();
  getSiblings(siblings);
  for (auto it = siblings.begin(); it != siblings.end(); it++)
    {
      results.erase(std::remove(results.begin(), results.end(), (*it)), results.end());
    }
}

void Person::getRootAncestors(People& results, std::vector<int>& gen_vec, int gen) const
{
  if (father != NULL)
    {
      father->getRootAncestors(results, gen_vec, gen+1);
    }
  if (mother != NULL)
    {
      mother->getRootAncestors(results, gen_vec, gen+1);
    }
  if ((father == NULL) and (mother == NULL))
    {
      results.push_back((Person*) this);
      gen_vec.push_back(gen);
    }
}

void Person::getDecendentsgen(People& results, int gen) const
{
  if (gen == 0)
    {
      results.push_back((Person*) this);
    }
  else
    {
      for (auto it= children.begin();it!=children.end(); ++it)
        {
          (*it)->getDecendentsgen(results, gen-1);
        }
    }
}

People::iterator Person::findChild(const Person* p)
{
  return std::find(children.begin(), children.end(), p);
}

People::const_iterator Person::findChild(const Person* p) const
{
  return std::find(children.begin(), children.end(), p);
}

void Person::addSelfToPeople(People& result) const
{
  result.push_back((Person*)this);
}

void Person::printAllChildrenNames() const
{
  std::cout << "children of " << name << ": " << std::endl;
  for (auto it = children.begin(); it != children.end(); ++it) {
    std::cout << (*it)->name << std::endl;
  }
  std::cout << std::endl;
}
