#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void addMat(const cv::Mat& src1, const cv::Mat&src2, cv::Mat& dst)
{
#pragma omp parallel for
  for (int i = 0; i < src1.rows; i++)
    for (int j = 0; j < src1.cols; j++)
      dst.ptr<uchar>(i)[j] = src1.ptr<uchar>(i)[j] + src2.ptr<uchar>(i)[j];
}

class addInvorker: public cv::ParallelLoopBody
{
private:
  cv::Mat im1, im2;
  cv::Mat &dst;
  int diff;

public:
  addInvorker(const cv::Mat& src1, const cv::Mat& src2, cv::Mat& dst, const int diff) :
    im1(src1), im2(src2), dst(dst), diff(diff) {}

  virtual void operator() (const cv::Range &range) const
  {

    for (int r = range.start; r < range.end; r++)
      {
	cv::Mat in1(im1, cv::Rect(0, (im1.rows/diff)*r,
				   im1.cols, im1.rows/diff));
	cv::Mat in2(im2, cv::Rect(0, (im2.rows/diff)*r,
				   im2.cols, im2.rows/diff));
	cv::Mat out(dst, cv::Rect(0, (dst.rows/diff)*r,
				 dst.cols, dst.rows/diff));
	addMat(in1, in2, out);
      }
  }
};

void addParallelOpenCV(cv::Mat& src1, cv::Mat& src2, cv::Mat& dst)
{
  addInvorker  body(src1, src2, dst, 8);
  cv::parallel_for_(cv::Range(0, 8), body);
}

int main()
{
  cv::Mat src1(cv::Size(5000, 5000), CV_8UC1, cv::Scalar(200));
  cv::Mat src2(cv::Size(5000, 5000), CV_8UC1, cv::Scalar(55));
  cv::Mat dst = cv::Mat::zeros(src1.size(), src1.type());

  double f = 1000.0f / cv::getTickFrequency();

  int64 start = cv::getTickCount();
  addParallelOpenCV(src1, src2, dst);
  int64 end = cv::getTickCount();
  std::cout << "time for parallel calculation: " <<
    (end - start) * f << " [ms]" << std::endl;

  start = cv::getTickCount();


  addMat(src1, src2, dst);
  end = cv::getTickCount();
  std::cout << "time for naive calculation: " <<
    (end - start) * f << " [ms]" << std::endl;

  cv::imshow("dst", dst);
  cv::waitKey(0);

  return 0;
}
