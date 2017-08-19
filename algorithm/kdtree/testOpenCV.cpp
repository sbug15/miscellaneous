#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{

  std::vector<cv::Point2f> pointsforSearch;
  pointsforSearch.push_back(cv::Point2f(2, 3));
  pointsforSearch.push_back(cv::Point2f(9, 4));
  pointsforSearch.push_back(cv::Point2f(5, 6));
  pointsforSearch.push_back(cv::Point2f(7, 8));
  pointsforSearch.push_back(cv::Point2f(10, 11));
  pointsforSearch.push_back(cv::Point2f(2, 4));
  
  cv::flann::KDTreeIndexParams indexParams;
  cv::flann::Index kdTree(cv::Mat(pointsforSearch).reshape(1), indexParams);

  std::vector<float> query;
  query.push_back(10);
  query.push_back(20);
  std::vector<int> indices;
  std::vector<float> dists;
  
  int numOfPoints = 3;
  float range = 100.0;
  kdTree.radiusSearch(query, indices, dists, range, numOfPoints);

  for (unsigned int i = 0; i < indices.size(); i++)
    {
      std::cout << indices[i] << " " << dists[0] << std::endl;
    }
  return 0;
}
