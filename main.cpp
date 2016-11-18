#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using pos = std::pair<size_t,size_t>;

namespace std {
    std::ostream & operator<<(std::ostream & os, const pos & p) {
        os << "(" << p.first << "," << p.second << ")";
    }
}

class solution {
  public:
    int calculateMinHP(const std::vector<std::vector<int>> & dungeon) {
        auto paths = getPaths(dungeon, std::vector<pos>{std::make_pair(0,0)});
        for (auto & path : paths) {
            std::copy(path.begin(), path.end(), std::ostream_iterator<pos>(std::cout, " "));
            std::cout << std::endl;
        }
        auto it = std::min_element(paths.begin(), paths.end(),
                                   [&](const std::vector<pos> & p1, const std::vector<pos> & p2){
                                       std::vector<int> v1, v2;
                                       std::transform(p1.begin(), p1.end(),
                                                      std::inserter(v1, v1.begin()),
                                                      [&](const pos & p){
                                                          return dungeon[p.first][p.second];
                                                      });
                                       std::transform(p2.begin(), p2.end(),
                                                      std::inserter(v2, v2.begin()),
                                                      [&](const pos & p){
                                                          return dungeon[p.first][p.second];
                                                      });
                                       std::accumulate(v1.begin(), v1.end(), 0);
                                       std::accumulate(v2.begin(), v2.end(), 0);
                                       return *std::min_element(v1.begin(), v1.end()) < *std::min_element(v2.begin(), v2.end());
                                   });
        
        std::vector<int> vec;
        std::transform(it->begin(), it->end(),
                       std::inserter(vec, vec.begin()),
                       [&](const pos & p){
                           return dungeon[p.first][p.second];
                       });
        std::accumulate(vec.begin(), vec.end(), 0);
        return *std::min_element(vec.begin(), vec.end());
    }

  private:
    std::vector<std::vector<pos>> getPaths(const std::vector<std::vector<int>> & dungeon, const std::vector<pos> & curr) {
        
    }

    std::vector<pos> getNext(const std::vector<std::vector<int>> & dungeon, const std::vector<pos> & curr) {
        
    }
};
