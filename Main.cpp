#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

int main(int argc, const char** argv)
{
	VideoCapture capture;
	Mat image, image2;

	Mat image1, image3;
	image1 = imread("C:/Users/ricar/Documents/image3.jpg", IMREAD_COLOR);

	int R = 0;
	int G = 177;
	int B = 64;

	int toleranciaR = 20;
	int toleranciaG = 40;
	int toleranciaB = 40;

	bool Calibration = false;


	capture.open(1);
	if (capture.isOpened())
	{
		while (1)
		{
			

			if (!Calibration)
			{
				for (int i = 0; i < image.cols; i++)
				{
					for (int j = 0; j < image.rows; j++)
					{
						if (image.at<Vec3b>(j, i)[2] < 80 && image.at<Vec3b>(j, i)[1] < 177 + 100 && image.at<Vec3b>(j, i)[1] > 177 - 100 && image.at<Vec3b>(j, i)[0] < 64 + 100 && image.at<Vec3b>(j, i)[0] > 64 - 100)
						{
							B = image.at<Vec3b>(j, i)[0];
							G = image.at<Vec3b>(j, i)[1];
							R = image.at<Vec3b>(j, i)[2];
							Calibration = true;
						}

					}
				}

			}
			capture >> image;
			/*	cout << " 2-"; cout << (int)(image.at<Vec3b>(image.rows / 2, image.cols / 2)[2]);
				cout << " 1-"; cout << (int)(image.at<Vec3b>(image.rows / 2, image.cols / 2)[1]);
				cout << " 0-"; cout << (int)(image.at<Vec3b>(image.rows / 2, image.cols / 2)[0]);*/

			cv::resize(image1, image2, image.size());
			
			//LOAD IMAGE


			imshow("imagem BGR", image);



			//cvtColor(image, image2, COLOR_BGR2GRAY);
			for (int i = 0; i < image.cols; i++)
			{
				for (int j = 0; j < image.rows; j++)
				{
					if (image.at<Vec3b>(j, i)[2] < R + toleranciaR && image.at<Vec3b>(j, i)[1] < G + toleranciaG && image.at<Vec3b>(j, i)[1] > G - toleranciaG && image.at<Vec3b>(j, i)[0] < B + toleranciaB && image.at<Vec3b>(j, i)[0] > B - toleranciaB)
					//if (image.at<Vec3b>(j, i)[2] < 80 && image.at<Vec3b>(j, i)[1] < 177 + 100 && image.at<Vec3b>(j, i)[1] > 177 - 100 && image.at<Vec3b>(j, i)[0] < 64 + 100 && image.at<Vec3b>(j, i)[0] > 64 - 100)
					{
						image.at<Vec3b>(j, i)[0] = image1.at<Vec3b>(j, i)[0];
						image.at<Vec3b>(j, i)[1] = image1.at<Vec3b>(j, i)[1];
						image.at<Vec3b>(j, i)[2] = image1.at<Vec3b>(j, i)[2];
					}
					/*	else
						{
							image.at<Vec3b>(j, i)[0] = 0;
							image.at<Vec3b>(j, i)[1] = 0;
							image.at<Vec3b>(j, i)[2] = 0;
						}*/
				}
			}


			imshow("imagem BGR2", image);
			//cv::resize(image, image2, cv::Size(), 0.25, 0.25);


			//imshow("imagem BGR processada", image2);


			if (image.empty())
				break;

			char c = (char)waitKey(1);
			if (c == 's' || c == 'S')
				break;

			if (c == 't' || c == 'T')
			{

				cout << "R: ";
				cin >> toleranciaR;
				cout << "G: ";
				cin >> toleranciaG;
				cout << "B: ";
				cin >> toleranciaB;
			}



		}
	}
	else
		cout << "WebCam não encontrada";
	return 0;

}