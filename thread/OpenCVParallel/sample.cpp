#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

class addInvorker: public cv::ParallelLoopBody
{
private:
  cv::Mat im1, im2;
  cv::Mat &dst;

public:
  addInvorker(const cv::Mat& src1, const cv::Mat& src2, cv::Mat& dst) :
    im1(src1), im2(src2), dst(dst) {}

  virtual void operator() (const cv::Range &range) const
  {

    for (int r = range.start; r < range.end; r++)
      for (int j = 0; j < im1.cols; j++)
	dst.ptr<uchar>(r)[j] = im1.ptr<uchar>(r)[j] + im2.ptr<uchar>(r)[j];
  }
};

void addParallelOpenCV(cv::Mat& src1, cv::Mat& src2, cv::Mat& dst)
{
  addInvorker  body(src1, src2, dst);
  cv::parallel_for_(cv::Range(0, dst.rows), body);
}

int main()
{
  cv::Mat src1(cv::Size(5000, 5000), CV_8UC1, cv::Scalar(200));
  cv::Mat src2(cv::Size(5000, 5000), CV_8UC1, cv::Scalar(55));
  cv::Mat dst(src1.size(), src1.type());

  double f = 1000.0f / cv::getTickFrequency();

  int64 start = cv::getTickCount();
  addParallelOpenCV(src1, src2, dst);
  int64 end = cv::getTickCount();
  std::cout << "time for parallel calculation: " <<
    (end - start) * f << " [ms]" << std::endl;

  start = cv::getTickCount();

  #pragma omp parallel for
  for (int i = 0; i < src1.rows; i++)
    for (int j = 0; j < src1.cols; j++)
      dst.ptr<uchar>(i)[j] = src1.ptr<uchar>(i)[j] + src2.ptr<uchar>(i)[j];
  end = cv::getTickCount();
  std::cout << "time for naive calculation: " <<
    (end - start) * f << " [ms]" << std::endl;

  cv::imshow("dst", dst);
  cv::waitKey(0);

  return 0;
}
