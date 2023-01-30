// https://www.freesion.com/article/81831251448/

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>

#include <NumCpp.hpp>
#include <magic_enum.hpp>

using std::vector;
using std::string;
using std::endl;
using std::cout;
using std::map;
using std::set;

// 对应书表3-1
struct data
{
	int featNum;                    //样本ID
	vector<char> features;          //样本数据特征
	string label;                   //标签
};
vector<data> dataset;               //数据集


double calcShannonEnt(vector<data> myData)
{
	size_t numEntries = myData.size();
	map<string,size_t> labelCounts;
	for (auto it = myData.begin(); it != myData.end();it++)
	{
		string currentLabel = it->label;
		if (labelCounts.count(currentLabel) == 0)
		{
			labelCounts[currentLabel] = 0;
		}
		labelCounts[currentLabel] += 1;
	}
	double shannonEnt = 0.0;
	for (auto it_map = labelCounts.begin(); it_map != labelCounts.end(); it_map++)
	{
		double prob = (double)(it_map->second) / (double)numEntries;
		shannonEnt -= prob * log2(prob);
	}
	return shannonEnt;
}

vector<data> splitDataSet(vector<data> myData, int axis, char value)
{
	vector<data> retDataSet;
	for (auto it = myData.begin(); it != myData.end(); it++)
	{
		auto it_feat = it->features.begin();
		auto it_axis = it_feat + axis;
 
		data d;
		d.featNum = it->featNum - 1;
 
		if (*(it_axis) == value)
		{
			for (; it_feat != it->features.end(); it_feat++)
			{
				if (it_feat == it_axis)
					continue;
				bool temp = *(it_feat);
				d.features.push_back(temp);
			}
			d.label = it->label;
			retDataSet.push_back(d);
		}
	}
	return retDataSet;
}

size_t chooseBestFeatureToSplit(vector<data> myData)
//找出最好的数据集划分方式，即找出最合适的特征用于分类
//myData:数据集
{
 
	double baseEntropy = calcShannonEnt(myData);               //计算原始数据集的香农熵
	double bestInfoGain = 0.0;                                 //信息增益的最大值
	size_t bestFeature = -1;                                   //最“好”的特征
//	auto it_feat = myData.begin()->features.begin();
	for (int i = 0; i < myData.begin()->featNum;i++)
	{
		auto it = myData.begin();
		set<bool> featSet;
		for (; it != myData.end(); it++)
		{
			featSet.insert(it->features[i]);
		}
		double newEntory = 0;
		for (auto it_feat = featSet.begin(); it_feat != featSet.end(); it_feat++)  //计算每种划分方式的香农熵
		{
			vector<data> subDataSet = splitDataSet(dataset, i, *(it_feat));
			double prob = (double)subDataSet.size() / (double)dataset.size();
			newEntory += prob*calcShannonEnt(subDataSet);
 
		}
		double infoGain = baseEntropy - newEntory;
		if (infoGain > bestInfoGain)                              //计算最好的信息增益
		{
			bestInfoGain = infoGain;
			bestFeature = i;
		}
	}
	return bestFeature;                                         //返回最好的特征
}

int main() {
  // 构建数据集
  //
  dataset.push_back({1, {1, 1, 1}, "yes"});
  dataset.push_back({2, {1, 1, 1}, "yes"});
  dataset.push_back({3, {1, 0, 0}, "no"});
  dataset.push_back({4, {0, 1, 0}, "no"});
  dataset.push_back({5, {0, 1, 0}, "no"});

  //
  cout << calcShannonEnt(dataset) << endl;

  // 手动选取一个特征和特征值进行分类
  // 分类的目的是判断生物是否是海洋生物
  // 0和1表示选取第0个特征，也就是不浮出水面是否可以生存，1为特征值
  // （简单来说就是以可以浮出水面分类样本）
  vector<data> retData = splitDataSet(dataset, 0, 1);

  cout << calcShannonEnt(retData) << endl;

  cout << chooseBestFeatureToSplit(dataset) << endl;

  return 0;
}

