#include <iostream>
#include <map>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>


// two data structures store all of the information for efficiency
typedef std::map<std::string, std::vector<std::string> > LIBRARY_TYPE;
typedef std::map<std::string, std::map<std::string, int> > PEOPLE_TYPE;


// prototypes for the helper functions
void addItem(std::istream &istr, LIBRARY_TYPE& library);
void checkoutItem(std::istream &istr, LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void returnItems(std::istream &istr, LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void lookup(std::istream &istr, LIBRARY_TYPE& library);
void printPeople(PEOPLE_TYPE& people);


int main(int argc, char* argv[]) {
  LIBRARY_TYPE library;
  PEOPLE_TYPE people;
  char c;
  std::ifstream istr(argv[1]);
  while (istr >> c) {
    if (c == 'a') {
      addItem(istr, library);
    } else if (c == 'c') {
      checkoutItem(istr, library, people);
    } else if (c == 'r') {
      returnItems(istr, library, people);
    } else if (c == 'l') {
      lookup(istr, library);
    } else if (c == 'p') {
      printPeople(people);
    } else {
      std::cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }
}


void addItem(std::istream &istr, LIBRARY_TYPE& library) {
  std::string title;
  int num;
  istr >> num >> title;
  library.insert(std::make_pair(title,std::vector<std::string>()));
  for (unsigned int i=0; i< num; i++){
    library[title].push_back(" ");
  }
  std::cout << num << " copies of " << title << " is added to the library"<<std::endl;
}


void checkoutItem(std::istream &istr, LIBRARY_TYPE& library, PEOPLE_TYPE& people) {
  std::string name;
  std::string title;
  istr >> name >> title;
  people[name];
  LIBRARY_TYPE::iterator p=library.find(title);
  if (p!=library.end()){
    if (people[name].find(title)==people[name].end() && library[title][library[title].size()-1]==" "){
      for (unsigned int i=0; i<library[title].size(); i++){
        if (library[title][i] == " "){
          library[title][i]=name;
          i=library[title].size();
          people[name].insert(std::make_pair(title, people[name].size()));
          std::cout << name << " check out "<< title<< std::endl;
        }
      }
    }
    else if (people[name].find(title)!=people[name].end())
      std::cout << name <<" already has " << title;
    else
      std::cout << "all of " << title << " is out.";
  }
  else
    std::cout << "do not have this book in the library.";

  std::cout<<std::endl;
}


void returnItems(std::istream &istr, LIBRARY_TYPE& library, PEOPLE_TYPE& people) {
  std::string name;
  istr >> name;
  std::cout << people[name].size() << " books are returned by "<< name <<std::endl;
  std::map<std::string, int>::iterator p;
  for (p=people[name].begin(); p!=people[name].end();p++){
    for (unsigned int i=0; i<library[p->first].size(); i++){
      if (library[p->first][i]!=" "){
        std::cout<< name << " returned "<< p->first << std::endl;
        library[p->first][i]=" ";
        i=library[p->first].size();
      }
    }
  }
  people[name].erase(people[name].begin(), people[name].end());
  people.erase(name);

}


void lookup(std::istream &istr, LIBRARY_TYPE& library) {

  std::string title;
  istr >> title;
  std::cout << "there are a total of "<< library[title].size() << " copies of "<< title <<" available."<<std::endl;
  std::cout << "the patrons are: ";
  for (unsigned int i=0; i<library[title].size(); i++){
    if (library[title][i]!=" "){
      std::cout << library[title][i] << " ";
    }
  }
  std::cout << std::endl;
}


void printPeople(PEOPLE_TYPE& people) {
  std::map<std::string, int>::iterator q;
  for(PEOPLE_TYPE::iterator p=people.begin(); p!=people.end(); p++){
    std::cout << p->first << " has the following items: "<<std::endl;
    for (int i=0; i<p->second.size(); i++){
      for (q=p->second.begin();q!=p->second.end();q++){
         if (i==q->second)
          std::cout << q->first << std::endl;
      }
    }
  }

}
