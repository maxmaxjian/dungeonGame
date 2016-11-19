#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

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
      std::vector<int> temp;
      std::transform(path.begin(), path.end(), std::inserter(temp, temp.begin()),
		     [&](const pos & ps){
		       return dungeon[ps.first][ps.second];
		     });
      std::partial_sum(temp.begin(), temp.end(), temp.begin());
      std::copy(temp.begin(), temp.end(), std::ostream_iterator<int>(std::cout, " "));
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
				 std::partial_sum(v1.begin(), v1.end(), v1.begin());
				 std::partial_sum(v2.begin(), v2.end(), v2.begin());
				 return *std::min_element(v1.begin(), v1.end()) > *std::min_element(v2.begin(), v2.end());
			       });

    std::cout << "The optimal path is:\n";
    std::copy(it->begin(), it->end(), std::ostream_iterator<pos>(std::cout, " "));
    std::cout << std::endl;
    std::vector<int> vec;
    std::transform(it->begin(), it->end(),
		   std::inserter(vec, vec.begin()),
		   [&](const pos & p){
		     return dungeon[p.first][p.second];
		   });
    std::partial_sum(vec.begin(), vec.end(), vec.begin());
    return *std::min_element(vec.begin(), vec.end());
  }

private:
  std::vector<std::vector<pos>> getPaths(const std::vector<std::vector<int>> & dungeon, const std::vector<pos> & curr) {
    std::vector<std::vector<pos>> result;
    if (curr.back() == std::make_pair(dungeon.size()-1, dungeon[0].size()-1))
      result.push_back(curr);
    else {
      std::vector<pos> next = getNext(dungeon, curr);
      for (auto nx : next) {
	auto cpy = curr;
	cpy.push_back(nx);
	auto temp = getPaths(dungeon, cpy);
	std::copy(temp.begin(), temp.end(), std::inserter(result,result.end()));
      }
    }
    return result;
  }

  std::vector<pos> getNext(const std::vector<std::vector<int>> & dungeon, const std::vector<pos> & curr) {
    std::vector<pos> next;
    if (curr.back().first < dungeon.size()-1)
      next.push_back(std::make_pair(curr.back().first+1, curr.back().second));
    if (curr.back().second < dungeon[0].size()-1)
      next.push_back(std::make_pair(curr.back().first, curr.back().second+1));
    return next;
  }
};

int main() {
  std::vector<std::vector<int>> dungeon{
    {-2,-3,3},
      {-5,-10,1},
	{10,30,-5}
  };

  solution soln;
  int minHP = soln.calculateMinHP(dungeon);
  std::cout << "The minimum HP required is:\n"
	    << minHP << std::endl;
}
