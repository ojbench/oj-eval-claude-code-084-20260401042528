#include <iostream>

#include "src.hpp"

using std::cin, std::cout, std::endl;

int main() {
  int runForEach;
  cin >> runForEach;
  int len, method, size;
  cin >> len >> method >> size;
  LinkedHashMap map;
  map.init(len, method == 0);
  int op;
  for (int i = 0; i < size; i++) {
    cin >> op;
    if (op == 0) {
      // insert
      int key;
      string value;
      cin >> key >> value;
      // cout<<"# i "<<key<<" "<<value<<endl;
      map.insert(key, value);
    } else if (op == 1) {
      // remove
      int key;
      string value;
      cin >> key >> value;
      // cout<<"# r "<<key<<" "<<value<<endl;
      map.remove(key, value);
    } else if (op == 2) {
      // ask
      int key;
      cin >> key;
      auto ret = map.ask(key);
      // cout<<"# a "<<key<<endl;
      if (!ret.empty()) {
        for (const auto& i : ret) {
          cout << i << " ";
        }
        cout << endl;
      }
    }
  }
  // forEach
  if (runForEach) {
    auto ret = map.forEach();
    for (const auto& i : ret) {
      cout << i.key << ' ' << i.value << endl;
    }
  }

  map.clearMemory();
  return 0;
}
