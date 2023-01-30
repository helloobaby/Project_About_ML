#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <unordered_map>

#include <NumCpp.hpp>
#include <magic_enum.hpp>


enum class MovieType {
    aiqingpian,
    dongzuopian,
    invalid,
};

// 训练数据集(书中表2-1)
// California Man   (3,104) 爱情片
// He's Not Really into Dudes   (2,100) 爱情片
// Beautiful Woman  (1,81)  爱情片
// Kevin Longblade (101,10) 动作片
// Robo Slayer 3000 (99,5) 动作片
// Amped II (98,2) 动作片

// 测试数据集
// ? (18,90) -> 分类结果应该是爱情片

struct DataAndLabel {
  nc::Vec2 d;
  MovieType l;
};
struct DistanceAndLabel {
  double dis;
  MovieType l;
};
std::vector<DataAndLabel> kTrainDataSet{
    {{3, 104}, MovieType::aiqingpian}, {{2, 100}, MovieType::aiqingpian},
    {{1, 81}, MovieType::aiqingpian},  {{101, 10}, MovieType::dongzuopian},
    {{99, 5}, MovieType::dongzuopian}, {{98, 2}, MovieType::dongzuopian}};

// 计算测试点与已知数据点的距离
double GetDistance(nc::Vec2 a, nc::Vec2 b) {
  auto x1 = a.x;
  auto y1 = a.y;
  auto x2 = b.x;
  auto y2 = b.y;
  return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

std::string_view Classification(int k,nc::Vec2 test_data) {

    MovieType val = MovieType::invalid;

    // 计算所有点与测试点的距离
    std::vector<DistanceAndLabel> all_distance;

    for (const auto& data_and_label : kTrainDataSet) {
      auto v = data_and_label.d;
      all_distance.push_back({GetDistance(v, test_data), data_and_label.l});
    }

    // 排序
    std::sort(all_distance.begin(), all_distance.end(),
              [](const DistanceAndLabel& a,const DistanceAndLabel& b) {
                if (a.dis < b.dis)
                  return true;
                else
                  return false;
        });

    for (auto& dis : all_distance) {
      std::cout << "距离 : " << dis.dis << "  标签 : " << magic_enum::enum_name(dis.l) << std::endl;
    }

    std::unordered_map<MovieType, int> main_class;

    // 不能让k大于总坐标数量了
    if (k > all_distance.size()) k = all_distance.size();
    
    // 确定前k个距离最小元素所在的主要分类
    for (int i = 0; i < k; i++) {
        main_class[all_distance[i].l]++;
    }

    return magic_enum::enum_name(std::max_element(main_class.begin(), main_class.end())->first);
}


int main() {
  // 测试
  assert(GetDistance({0, 0}, {0, 5}) == 5.0);
  assert(GetDistance({0, 8}, {6, 0}) == 10.0);

  // 分类失败，K太大
    std::cout << "-----------------------------分类测试一----------------------"
            << std::endl;
  std::cout << Classification(4, {18, 90}) << std::endl;
  std::cout << Classification(4, {90, 18}) << std::endl;

  //
  std::cout << "-----------------------------分类测试二----------------------"
            << std::endl;
    std::cout << Classification(1, {18, 90}) << std::endl;
  std::cout << Classification(1, {90, 18}) << std::endl;

  return 0;
}


