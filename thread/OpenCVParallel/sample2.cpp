#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Parallel_process : public cv::ParallelLoopBody
{

private:
  cv::Mat img;
  cv::Mat& retVal;
  int size;
  int diff;

public:
  Parallel_process(cv::Mat inputImgage, cv::Mat& outImage, 
		   int sizeVal, int diffVal)
    : img(inputImgage), retVal(outImage), 
      size(sizeVal), diff(diffVal){}

  virtual void operator()(const cv::Range& range) const
  {
    for(int i = range.start; i < range.end; i++)
      {
	/* divide image in 'diff' number 
	   of parts and process simultaneously */

	cv::Mat in(img, cv::Rect(0, (img.rows/diff)*i, 
				 img.cols, img.rows/diff));
	cv::Mat out(retVal, cv::Rect(0, (retVal.rows/diff)*i, 
				     retVal.cols, retVal.rows/diff));
	cv::GaussianBlur(in, out, cv::Size(size, size), 0);
      }
  }
};

int main(int argc, char* argv[])
{
  cv::Mat img, out;
  img = cv::imread(argv[1]);
  out = cv::Mat::zeros(img.size(), CV_8UC3);

  double f = 1000.0f / cv::getTickFrequency();
  // create 8 threads and use TBB

  int64 start = cv::getTickCount();
  cv::parallel_for_(cv::Range(0, 8), Parallel_process(img, out, 5, 8));
  int64 end = cv::getTickCount();

  std::cout << (end - start) * f << " [ms]" << std::endl;

  cv::imshow("image", img);
  cv::imshow("blur", out);
  cv::waitKey(0);

  return(1);
}
