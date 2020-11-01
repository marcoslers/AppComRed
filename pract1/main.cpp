#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using std::cout;
using std::endl;
int main(){
	
	Mat img=imread("img.jpg");
	Mat img1 = img.clone();
	Mat img2 = img.clone();
	Mat img3 = img.clone();

	for (int row = 0; row < img1.rows; row++){
  		for (int col = 0; col < img1.cols; col++){
        	img1.at<Vec3b>(row, col)[0] = 255;
			img2.at<Vec3b>(row, col)[1] = 255;
			img3.at<Vec3b>(row, col)[2] = 255;
   		}		
	}

	imwrite("img1.jpg",img1);
	imwrite("img2.jpg",img2);
	imwrite("img3.jpg",img3);
	
}
/*
imshow("window",img);
	waitKey(0);
	//imshow("window",img);
	//waitKey(0);
	//imwrite("img1.jpg",img);
header
https://stackoverflow.com/questions/46426249/opencv-modify-image-pixels/46426440
https://riptutorial.com/opencv/example/28276/pixel-by-pixel-modification-of-images
https://stackoverflow.com/questions/12461848/accessing-pixel-value-using-cvmatat-operator
https://www.youtube.com/watch?v=Kur8JL2GqWQ&list=PLZBN9cDu0MSlHMjJughb11ydICWbA8OBe&index=3
*/
