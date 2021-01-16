//
//  hw085.cpp
//  CF.Homework085
//
//  Created by Alan Sampson on 1/14/21.
//

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <vector>

//  MARK: - Definitions.
//  =================================================================
/*
 *  MARK: Class Node
 */
class Node {
public:
  Node() : link(nullptr) {};  //  default constructor
  Node(Node const &) = delete;
  Node(Node const &&) = delete;
  Node & operator=(Node const &) = delete;
  Node & operator=(Node const &&) = delete;
  virtual ~Node() = default;

  std::string const toString(bool compact = false) const;

  std::string code;
  std::string subj;
  int hour;
  float mark;
//  std::string del;
  Node * link;
};

//  =================================================================
/*
 *  MARK: Class mainNode
 */
class mainNode {
private:
  Node * head = NULL;
  size_t node_ct;

public:
  mainNode() : head(nullptr), node_ct(0) {} //  default constructor
  mainNode(mainNode const &) = delete;
  mainNode(mainNode const &&) = delete;
  mainNode & operator=(mainNode const &) = delete;
  mainNode & operator=(mainNode const &&) = delete;
  virtual ~mainNode();

  void deleteCode(std::string code);
  void display(void);
  void addNode(Node * nnode);
  void sort(void);

};

//  =================================================================
/*
 *  MARK: Enumeration Menu
 */
enum Menu {
  STOP, ADD, DELETE, DISPLAY, SORT, OTHERS,
};

Node * mainAdd(void);
void sample_data(mainNode & obj);

//  MARK: - Implementation.
/*
 *  MARK: main()
 */
int main(int argc, char ** argv) {
  mainNode obj;
  uint32_t choice;
  bool exit_p(true);

#ifdef AS_DEBUG
  {
    std::string tg("some characters");
    std::cout << tg << ' ';
    std::transform(tg.begin(), tg.end(), tg.begin(), ::toupper);
    std::cout << tg << std::endl;
  }
#endif

  std::cout << "CGPA System. Designed by JOS"
            << std::endl;

  do {
    std::cout << "\nMain Menu"      << '\n';
    std::cout << "\n  [" << ADD     << "] Add Subject"
              << "\n  [" << DELETE  << "] Delete Subject"
              << "\n  [" << DISPLAY << "] Display Subject"
              << "\n  [" << SORT    << "] Sort"
              << "\n  [" << OTHERS  << "] Others"
              << "\n  [" << STOP    << "] Stop"
              << std::endl;
    std::cout << "\nEnter your choice: ";
    std::cout.flush();
    std::cin >> choice;

    Node * nnode(nullptr);
    std::string del;

    switch (choice) {
    case ADD:
      nnode = mainAdd();
      obj.addNode(nnode);
      break;

    case DELETE:
      std::cout << "\nEnter subject code to delete ";
      std::cout.flush();
      std::cin >> del;
      std::transform(del.begin(), del.end(), del.begin(), ::toupper);
      obj.deleteCode(del);
      break;

    case DISPLAY:
      obj.display();
      break;
 
    case SORT:
      obj.sort();
      break;
 
    case OTHERS:
      sample_data(obj);
      break;;

    case STOP:
      exit_p = false;
      break;

    default:
      break;
    }
  }
  while (exit_p);

  return 0;
}

/*
 *  MARK: mainAdd()
 */
Node * mainAdd(void) {
  std::string subj;
  std::string code;
  int hour;
  float mark;

  Node * nnode = new Node;
  std::cout << "Enter subject name ";
  std::cout.flush();
  std::cin >> subj;
  //getline(cin, subj);
  nnode->subj = subj;

  std::cout << "Enter subject code ";
  std::cout.flush();
  std::cin >> code;
  std::transform(code.begin(), code.end(),
                  code.begin(), ::toupper);
  //getline(cin, code);
  nnode->code = code;

  std::cout << "Enter subject credit hour ";
  std::cout.flush();
  std::cin >> hour;
  nnode->hour = hour;

  std::cout << "Enter subject mark ";
  std::cout.flush();
  std::cin >> mark;
  nnode->mark = mark;

  return nnode;
}

/*
 *  MARK: Node::toString()
 */
std::string const Node::toString(bool compact) const {
  std::ostringstream ts;
  if (compact) {
    ts << std::setw(20) << subj << ','
       << std::setw( 4) << code << ','
       << std::setw( 4) << hour << ','
       << std::setw( 8) << mark << ','
       << std::setw(18) << this << ','
       << std::setw(18) << link
       << std::ends;
  }
  else {
    ts << "Name: " << subj
       << ", Code: " << code
       << ", Credit hour: " << std::setw(4) << hour
       << ", Mark: " << std::setw(8) << mark
       << "\nthis: " << std::setw(18) << this
       << "\nlink: " << std::setw(18) << link
       << std::ends;
  }

  return ts.str();
}

/*
 *  MARK: mainNode::deleteCode()
 */
void mainNode::deleteCode(std::string code) {
  std::cout << code << std::endl;

  Node ** chain = &head;
  Node * cnode = head;
  Node * lnode = nullptr;
  while (cnode != nullptr) {
    std::cout << "Crnt " << std::setw(10) << cnode << ' '
              << "Last " << std::setw(10) << lnode << ' '
              << "Next " << std::setw(10) << cnode->link << ' '
              << "HPtr " << std::setw(10) << *chain << '\n';
    std::cout << "Ncode " << cnode->code << ' '
              << "Ucode " << code << '\n';
    if (cnode->code == code) {
      Node * dnode = cnode; // node to delete
      cnode = cnode->link;  // update current node
      if (lnode != nullptr) {
        lnode->link = cnode;
      }
      else {
        head = cnode;
        lnode = nullptr;
      }
      delete dnode;
      node_ct -= node_ct > 0 ? 1 : 0;
      break;  // done!
    }
    else {
      lnode = cnode;
      cnode = cnode->link;
    }
  }
}

/*
 *  MARK: mainNode::display()
 */
void mainNode::display() {
  Node * temp = head;
  //system("color f0");
  if (node_ct > 0) {
    std::cout << "\nList of Subject " << std::endl;
    while (temp != nullptr) {

//      std::cout << "Name: " << temp->subj
//                << ", Code: " << temp->code
//                << ", Credit hour: " << std::setw(4) << temp->hour
//                << ", Mark: " << std::setw(8) << temp->mark
//                << "\nthis: " << std::setw(18) << temp
//                << "\nlink: " << std::setw(18) << temp->link
//                << std::endl;

      std::cout << temp->toString() << std::endl;
//      std::cout << "temp: " << std::setw(18) << temp << std::endl;
      temp = temp->link;
    }
  }
  else {
    std::cout << "Empty list" << std::endl;
  }
}

/*
 *  MARK: mainNode::addNode()
 */
void mainNode::addNode(Node * nnode) {
  node_ct++;
  if (head != nullptr) {
    Node * cnode = head;
    while (cnode->link != nullptr) {
      cnode = cnode->link;
    }
    cnode->link = nnode;
  }
  else {
    head = nnode;
  }
}

/*
 *  MARK: mainNode::sort()
 */
void mainNode::sort(void) {
  if (head != nullptr) {
    Node * lnode;
    Node * rnode;

#ifdef AS_DEBUG
    bool s_debug(true);
#else
    bool s_debug(false);
#endif
    if (s_debug) {
      auto disp = [](auto & codes, auto & msg) {
        size_t constexpr cc_max(5);
        size_t cc;
        auto pa = [&](auto n_) {
          std::cout << std::setw(6) << n_
                    << ((++cc % cc_max == 0) ? "\n" : "");
        };
        cc = 0;
        std::cout << std::setw(8) << msg;
        std::for_each(codes.cbegin(), codes.cend(), pa);
        std::cout << std::endl;
      };

      lnode = head;
      std::vector<std::string> codes(node_ct);
      for (size_t c_ = 0; c_ < node_ct; ++c_) {
        codes[c_] = lnode->code;
        lnode = lnode->link;
      }

      bool swapped(true);
      disp(codes, "Before:");
      for (size_t i_ = 0; swapped || i_ < codes.size() - 1; ++i_ ) {
        swapped = false;
        for (size_t j_ = 0; j_ < codes.size() - i_ - 1; ++j_) {
          if (codes[j_] > codes[j_ + 1]) {
            std::string save = codes[j_];
            codes[j_] = codes[j_ + 1];
            codes[j_ + 1] = save;
            swapped = true;
          }
        }
      }
      disp(codes, "After:");
    }

    bool swap;
    for (size_t i_ = 0; i_ < node_ct - 1; ++i_ ) {
      Node ** root(&head);
      lnode = head;
      for (size_t j_ = 0; j_ < node_ct - i_ - 1; ++j_) {
        rnode = lnode->link;
        if (rnode && lnode->code > rnode->code) {
          swap = true;
        }
        else {
          swap = false;
        }
        std::ostringstream swappy;
        swappy << std::boolalpha << swap;

        std::cout << '.' << std::setw(18) << root << " ."
                  << std::setw(4) << i_
                  << std::setw(4) << j_
                  << std::setw(4) << node_ct
                  << std::setw(6) << lnode->code
                  << std::setw(6) << (rnode ? rnode->code : "null")
                  << " . "
                  << std::setw(6) << swappy.str()
                  << std::endl;
        if (swap) {
//          Node * save = lnode;
          std::cout << std::setw(18) << &root
                    << std::setw(18) << root
                    << std::setw(18) << *root;
          *root = rnode;
          std::cout << std::setw(18) << *root << std::endl;
          std::cout << "L: " << lnode->toString(true) << std::endl;
          std::cout << "R: " << rnode->toString(true) << std::endl;

          lnode->link = rnode->link;
          rnode->link = lnode;
          lnode = rnode;
          rnode = lnode->link;

          std::cout << "L: " << lnode->toString(true) << std::endl;
          std::cout << "R: " << rnode->toString(true) << std::endl;
        }
        root = &lnode->link;
        lnode = rnode;
      }
      Node * xptr = head;
      while (xptr != nullptr) {
        std::cout << std::setw(3) << xptr->code;
        xptr = xptr->link;
      }
      std::cout << std::endl;
    }
  }
  else {
    std::cout << "Empty list" << std::endl;
  }
}

/*
 *  MARK: mainNode::~mainNode() destructor
 */
mainNode::~mainNode() {
  while (head != nullptr) {
    Node * next = head->link;
//    std::cout << std::setw(10) << head->code << ' '
//              << "Head " << std::setw(18) << head << ' '
//              << "Next " << std::setw(18) << next
//              << std::endl;
    std::cout << head->toString(true) << std::endl;
    delete head;
    head = next;
  }
}

/*
 *  MARK: sample_data()
 */
void sample_data(mainNode & obj) {
  std::cout << "adding sample data" << std::endl;
  struct SNode {
  public:
    std::string subj;
    std::string code;
    int hour;
    float mark;
  };

  std::vector<SNode> sample {
    { "Toy", "T1", 66, 66.6, },
    { "Cat", "C1", 33, 33.3, },
    { "Boy", "B1", 11, 11.1, },
    { "Add", "A1", 88, 88.8, },
    { "Bat", "B2", 22, 22.2, },
  };

  Node * node;
  for (auto snode : sample) {
    node = new Node;
    node->subj = snode.subj;
    node->code = snode.code;
    node->hour = snode.hour;
    node->mark = snode.mark;

    obj.addNode(node);
  }
}

/*
1 Toy t1 66 66.6 1 Cat c1 33 33.3 1 Boy b1 11 11.1 1 Add a1 88 88.8 1 Bat b2 22 22.2
*/
