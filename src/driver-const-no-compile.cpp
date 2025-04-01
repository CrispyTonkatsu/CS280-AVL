#include <random>
#include <algorithm>
#include "avl-map.h"
#include <iostream>
#include <vector>
#include <numeric>

void simple_inserts(
  CS280::AVLmap<int, int>& map,
  const std::vector<int>& data
) {
  // insert (using index operator) and perform sanity check each time
  for (const int& key: data) {
    map[key] = key * key; // value is not important
    // if you have the method below, uncomment next line
    if (!map.sanityCheck()) {
      std::cout << "Error\n";
    }
  }
}

int main() {
  int N = 100;
  CS280::AVLmap<int, int> map;
  std::vector<int> data(N); // data to insert
  std::iota(data.begin(), data.end(), 1);
  std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});

  simple_inserts(map, data);

  // now copy to constant map
  const CS280::AVLmap<int, int> map2(map);

  // use no-const iterator on const container - error
  CS280::AVLmap<int, int>::iterator it = map2.begin();
  CS280::AVLmap<int, int>::iterator it_e = map2.end();
}
