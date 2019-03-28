#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp> 
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>

#include<iostream>
#include<conio.h>
#include<math.h>
#include<stdio.h>
#include <algorithm>
#include <stdlib.h> 

using namespace std;
using namespace cv;

Mat AddRest(Mat img1, Mat img2);
Mat Add255(Mat img1, Mat img2);
Mat AddNormalized(Mat img1, Mat img2);
Mat Sub0(Mat img1, Mat img2);
Mat SubNormalized(Mat img1, Mat img2);
Mat Multi(Mat img, float scale);
Mat Div(Mat img1, Mat img2);
Mat AverageFilter(Mat img, int window);
float normalizRange(float max, float min, float maxTarget, float minTarget, float value);

int main() {
	while (true) {
		int operation;
		cout << "1 - Adicao" << endl;
		cout << "2 - Subtracao" << endl;
		cout << "3 - Multiplicacao" << endl;
		cout << "4 - Divisao" << endl;
		cout << "5 - Filtro da Media" << endl;
		cout << "6 - Sair" << endl;
		cout << "Opcao: ";
		cin >> operation;
		switch (operation) {
			case 1: // Add
			{
				Mat img1 = imread("Images/lenna.png", CV_LOAD_IMAGE_COLOR);
				if (img1.empty()) {
					cout << "Nao foi possivel acessar o caminho da imagem especificado.\n\n";
					_getch();
					return(0);
				}

				Mat img2 = imread("Images/lenno.jpg", CV_LOAD_IMAGE_COLOR);
				if (img2.empty()) {
					cout << "Nao foi possivel acessar o caminho da imagem especificado.\n\n";
					_getch();
					return(0);
				}

				Mat add255_img = Add255(img1, img2);
				namedWindow("Add255", CV_WINDOW_AUTOSIZE);
				imshow("Add255", add255_img);

				Mat addRest_img = AddRest(img1, img2);
				namedWindow("AddRest", CV_WINDOW_AUTOSIZE);
				imshow("AddRest", addRest_img);

				Mat addNormalized_img = AddNormalized(img1, img2);
				namedWindow("AddNormalized", CV_WINDOW_AUTOSIZE);
				imshow("AddNormalized", addNormalized_img);

				waitKey(0);

				destroyAllWindows();
				system("cls");
				break;
			}
			case 2: // Subtration
			{
				Mat img1 = imread("Images/lenna.png", CV_LOAD_IMAGE_COLOR);
				if (img1.empty()) {
					cout << "Nao foi possivel acessar o caminho da imagem especificado.\n\n";
					_getch();
					return(0);
				}

				Mat img2 = imread("Images/lenno.jpg", CV_LOAD_IMAGE_COLOR);
				if (img2.empty()) {
					cout << "Nao foi possivel acessar o caminho da imagem especificado.\n\n";
					_getch();
					return(0);
				}

				Mat sub0_img = Sub0(img1, img2);
				namedWindow("Sub0", CV_WINDOW_AUTOSIZE);
				imshow("Sub0", sub0_img);

				Mat subNormalized_img = SubNormalized(img1, img2);
				namedWindow("SubNormalized", CV_WINDOW_AUTOSIZE);
				imshow("SubNormalized", subNormalized_img);

				waitKey(0);

				destroyAllWindows();
				system("cls");
				break;
			}
			case 3: // Multiplication
			{
				Mat img = imread("Images/lenna.png", CV_LOAD_IMAGE_COLOR);
				if (img.empty()) {
					cout << "Nao foi possivel acessar o caminho da imagem especificado.\n\n";
					_getch();
					return(0);
				}

				Mat multi_img = Multi(img, 5.5);
				namedWindow("Multi", CV_WINDOW_AUTOSIZE);
				imshow("Multi", multi_img);

				waitKey(0);

				destroyAllWindows();
				system("cls");
				break;
			}
			case 4: // Divide
			{
				Mat img1 = imread("Images/lenna.png", CV_LOAD_IMAGE_COLOR);
				if (img1.empty()) {
					cout << "Nao foi possivel acessar o caminho da imagem especificado.\n\n";
					_getch();
					return(0);
				}

				Mat img2 = imread("Images/lenno.jpg", CV_LOAD_IMAGE_COLOR);
				if (img2.empty()) {
					cout << "Nao foi possivel acessar o caminho da imagem especificado.\n\n";
					_getch();
					return(0);
				}

				Mat div_img = Div(img1, img2);
				namedWindow("Div", CV_WINDOW_AUTOSIZE);
				imshow("Div", div_img);

				waitKey(0);

				destroyAllWindows();
				system("cls");
				break;
			}
			case 5: // Divide
			{
				Mat img = imread("Images/lenna.png", CV_LOAD_IMAGE_COLOR);
				if (img.empty()) {
					cout << "Nao foi possivel acessar o caminho da imagem especificado.\n\n";
					_getch();
					return(0);
				}

				Mat avg_img = AverageFilter(img, 3);
				namedWindow("Div", CV_WINDOW_AUTOSIZE);
				imshow("Div", avg_img);

				waitKey(0);

				destroyAllWindows();
				system("cls");
				break;
			}
			case 6:
			{
				return(0);
			}
			default:
				system("cls");

				cout << "Opcao invalida." << endl;

				system("pause");
				system("cls");
				break;
		}
	}

	return(0);
}

// When the sum is higher than 255 the pixel value is set to 255
Mat Add255(Mat img1, Mat img2) {
	Mat result_img(img1.rows, img1.cols, img1.type());

	for (int i = 0; i < img1.rows; i++) { // Rows
		for (int j = 0; j < img1.cols; j++) { // Columns
			try {

				Vec3b pixel1 = img1.at<Vec3b>(Point(j, i));
				uchar blue1 = pixel1.val[0];
				uchar green1 = pixel1.val[1];
				uchar red1 = pixel1.val[2];

				Vec3b pixel2 = img2.at<Vec3b>(Point(j, i));
				uchar blue2 = pixel2.val[0];
				uchar green2 = pixel2.val[1];
				uchar red2 = pixel2.val[2];

				int r = (uchar) red1 + (uchar) red2;
				int g = (uchar) green1 + (uchar) green2;
				int b = (uchar) blue1 + (uchar) blue2;

				if (r > 255) r = 255;
				if (g > 255) g = 255;
				if (b > 255) b = 255;

				Vec3b pixel;
				pixel.val[0] = (uchar) b;
				pixel.val[1] = (uchar) g;
				pixel.val[2] = (uchar) r;

				result_img.at<Vec3b>(Point(j, i)) = pixel;

			} catch (Exception & e) {
				cerr << e.msg << endl;
			}
		}
	}

	return result_img;
}

// When the sum is higher than 255 the pixel value is set to 255
Mat AddRest(Mat img1, Mat img2) {

	Mat result_img(img1.rows, img1.cols, img1.type());

	for (int i = 0; i < img1.rows; i++) { // Rows
		for (int j = 0; j < img1.cols; j++) { // Columns
			try {

				Vec3b pixel1 = img1.at<Vec3b>(Point(j, i));
				uchar blue1 = pixel1.val[0];
				uchar green1 = pixel1.val[1];
				uchar red1 = pixel1.val[2];

				Vec3b pixel2 = img2.at<Vec3b>(Point(j, i));
				uchar blue2 = pixel2.val[0];
				uchar green2 = pixel2.val[1];
				uchar red2 = pixel2.val[2];

				int r = (uchar) red1 + (uchar) red2;
				int g = (uchar) green1 + (uchar) green2;
				int b = (uchar) blue1 + (uchar) blue2;

				if (r > 255) {
					int diff = r - 255;
					r = diff;
				}
				if (g > 255) {
					int diff = g - 255;
					g = diff;
				}
				if (b > 255) {
					int diff = b - 255;
					b = diff;
				}

				Vec3b pixel;
				pixel.val[0] = (uchar) b;
				pixel.val[1] = (uchar) g;
				pixel.val[2] = (uchar) r;

				result_img.at<Vec3b>(Point(j, i)) = pixel;

			} catch (Exception & e) {
				cerr << e.msg << endl;
			}
		}
	}

	return result_img;
}

Mat AddNormalized(Mat img1, Mat img2) {

	Mat result_img = img1.clone();

	int maxR = -1, maxG = -1, maxB = -1;
	int minR = 255, minG = -1, minB = 255;

	int **auxR = (int**) calloc(img1.rows, sizeof(int*));
	int **auxG = (int**) calloc(img1.rows, sizeof(int*));
	int **auxB = (int**) calloc(img1.rows, sizeof(int*));
	for (int i = 0; i < img1.rows; i++) {
		auxR[i] = (int*) calloc(img1.cols, sizeof(int));
		auxG[i] = (int*) calloc(img1.cols, sizeof(int));
		auxB[i] = (int*) calloc(img1.cols, sizeof(int));
	}

	for (int i = 0; i < img1.rows; i++) { // Rows
		for (int j = 0; j < img1.cols; j++) { // Columns
			try {

				Vec3b pixel1 = img1.at<Vec3b>(Point(j, i));
				uchar blue1 = pixel1.val[0];
				uchar green1 = pixel1.val[1];
				uchar red1 = pixel1.val[2];

				Vec3b pixel2 = img2.at<Vec3b>(Point(j, i));
				uchar blue2 = pixel2.val[0];
				uchar green2 = pixel2.val[1];
				uchar red2 = pixel2.val[2];

				// Sum 
				int r = (uchar) red1 + (uchar) red2;
				int g = (uchar) green1 + (uchar) green2;
				int b = (uchar) blue1 + (uchar) blue2;

				//Finding new global maximun value to each channel
				if (r > maxR) maxR = r;
				if (g > maxG) maxG = g;
				if (b > maxB) maxB = b;

				//Finding new global minimun value to each channel
				if (r < minR) minR = r;
				if (g < minG) minG = g;
				if (b < minB) minB = b;

				auxR[i][j] = r;
				auxG[i][j] = g;
				auxB[i][j] = b;

			} catch (Exception & e) {
				cerr << e.msg << endl;
			}
		}
	}

	for (int i = 0; i < result_img.rows; i++) { // Rows
		for (int j = 0; j < result_img.cols; j++) { // Columns
			try {

				if (auxR[i][j] > maxR) maxR = auxR[i][j];
				if (auxG[i][j] > maxG) maxG = auxG[i][j];
				if (auxB[i][j] > maxB) maxB = auxB[i][j];

				Vec3b finalPixel;
				finalPixel.val[0] = (uchar) normalizRange(maxB, minB, 255, 0, auxB[i][j]);
				finalPixel.val[1] = (uchar) normalizRange(maxG, minG, 255, 0, auxG[i][j]);
				finalPixel.val[2] = (uchar) normalizRange(maxR, minR, 255, 0, auxR[i][j]);

				result_img.at<Vec3b>(Point(j, i)) = finalPixel;

			} catch (Exception & e) {
				cerr << e.msg << endl;
			}
		}
	}

	return result_img;
}

float normalizRange(float max, float min, float maxTarget, float minTarget, float value) {
	return ((value - min) / (max - min)) * (maxTarget - minTarget) + minTarget;
}

// When the sum is lower than 0 the pixel value is set to 0
Mat Sub0(Mat img1, Mat img2) {
	Mat result_img(img1.rows, img1.cols, img1.type());

	for (int i = 0; i < img1.rows; i++) { // Rows
		for (int j = 0; j < img1.cols; j++) { // Columns
			try {

				Vec3b pixel1 = img1.at<Vec3b>(Point(j, i));
				uchar blue1 = pixel1.val[0];
				uchar green1 = pixel1.val[1];
				uchar red1 = pixel1.val[2];

				Vec3b pixel2 = img2.at<Vec3b>(Point(j, i));
				uchar blue2 = pixel2.val[0];
				uchar green2 = pixel2.val[1];
				uchar red2 = pixel2.val[2];

				int r = (uchar) red1 - (uchar) red2;
				int g = (uchar) green1 - (uchar) green2;
				int b = (uchar) blue1 - (uchar) blue2;

				if (r < 0) r = 0;
				if (g < 0) g = 0;
				if (b < 0) b = 0;

				Vec3b pixel;
				pixel.val[0] = (uchar) b;
				pixel.val[1] = (uchar) g;
				pixel.val[2] = (uchar) r;

				result_img.at<Vec3b>(Point(j, i)) = pixel;

			} catch (Exception & e) {
				cerr << e.msg << endl;
			}
		}
	}

	return result_img;
}

Mat SubNormalized(Mat img1, Mat img2) {

	Mat result_img = img1.clone();

	int maxR = -1, maxG = -1, maxB = -1;
	int minR = 255, minG = -1, minB = 255;

	int **auxR = (int**) calloc(img1.rows, sizeof(int*));
	int **auxG = (int**) calloc(img1.rows, sizeof(int*));
	int **auxB = (int**) calloc(img1.rows, sizeof(int*));
	for (int i = 0; i < img1.rows; i++) {
		auxR[i] = (int*) calloc(img1.cols, sizeof(int));
		auxG[i] = (int*) calloc(img1.cols, sizeof(int));
		auxB[i] = (int*) calloc(img1.cols, sizeof(int));
	}

	for (int i = 0; i < img1.rows; i++) { // Rows
		for (int j = 0; j < img1.cols; j++) { // Columns
			try {

				Vec3b pixel1 = img1.at<Vec3b>(Point(j, i));
				uchar blue1 = pixel1.val[0];
				uchar green1 = pixel1.val[1];
				uchar red1 = pixel1.val[2];

				Vec3b pixel2 = img2.at<Vec3b>(Point(j, i));
				uchar blue2 = pixel2.val[0];
				uchar green2 = pixel2.val[1];
				uchar red2 = pixel2.val[2];

				// Sum 
				int r = (uchar) red1 - (uchar) red2;
				int g = (uchar) green1 - (uchar) green2;
				int b = (uchar) blue1 - (uchar) blue2;

				//Finding new global maximun value to each channel
				if (r > maxR) maxR = r;
				if (g > maxG) maxG = g;
				if (b > maxB) maxB = b;

				//Finding new global minimun value to each channel
				if (r < minR) minR = r;
				if (g < minG) minG = g;
				if (b < minB) minB = b;

				auxR[i][j] = r;
				auxG[i][j] = g;
				auxB[i][j] = b;

			} catch (Exception & e) {
				cerr << e.msg << endl;
			}
		}
	}

	for (int i = 0; i < result_img.rows; i++) { // Rows
		for (int j = 0; j < result_img.cols; j++) { // Columns
			try {

				if (auxR[i][j] > maxR) maxR = auxR[i][j];
				if (auxG[i][j] > maxG) maxG = auxG[i][j];
				if (auxB[i][j] > maxB) maxB = auxB[i][j];

				Vec3b finalPixel;
				finalPixel.val[0] = (uchar) normalizRange(maxB, minB, 255, 0, auxB[i][j]);
				finalPixel.val[1] = (uchar) normalizRange(maxG, minG, 255, 0, auxG[i][j]);
				finalPixel.val[2] = (uchar) normalizRange(maxR, minR, 255, 0, auxR[i][j]);

				result_img.at<Vec3b>(Point(j, i)) = finalPixel;

			} catch (Exception & e) {
				cerr << e.msg << endl;
			}
		}
	}

	return result_img;
}

// When the sum is higher than 255 the pixel value is set to 255
Mat Multi(Mat img, float scale) {
	Mat result_img(img.rows, img.cols, img.type());

	for (int i = 0; i < img.rows; i++) { // Rows
		for (int j = 0; j < img.cols; j++) { // Columns
			try {

				Vec3b pixel = img.at<Vec3b>(Point(j, i));
				uchar blue = pixel.val[0];
				uchar green = pixel.val[1];
				uchar red = pixel.val[2];

				int r = (uchar) red * scale;
				int g = (uchar) green * scale;
				int b = (uchar) blue * scale;

				if (r > 255) r = 255;
				if (g > 255) g = 255;
				if (b > 255) b = 255;

				Vec3b finalPixel;
				finalPixel.val[0] = (uchar) b;
				finalPixel.val[1] = (uchar) g;
				finalPixel.val[2] = (uchar) r;

				result_img.at<Vec3b>(Point(j, i)) = finalPixel;

			} catch (Exception & e) {
				cerr << e.msg << endl;
			}
		}
	}

	return result_img;
}

// When the sum is lower than 0 the pixel value is set to 0
Mat Div(Mat img1, Mat img2) {
	Mat result_img(img1.rows, img1.cols, img1.type());

	for (int i = 0; i < img1.rows; i++) { // Rows
		for (int j = 0; j < img1.cols; j++) { // Columns
			try {

				Vec3b pixel1 = img1.at<Vec3b>(Point(j, i));
				uchar blue1 = pixel1.val[0];
				uchar green1 = pixel1.val[1];
				uchar red1 = pixel1.val[2];

				Vec3b pixel2 = img2.at<Vec3b>(Point(j, i));
				uchar blue2 = pixel2.val[0];
				uchar green2 = pixel2.val[1];
				uchar red2 = pixel2.val[2];

				int r = red2 != 0 ? (uchar) red1 / (uchar) red2 : 0;
				int g = green2 != 0 ? (uchar) green1 / (uchar) green2 : 0;
				int b = blue2 != 0 ? (uchar) blue1 / (uchar) blue2 : 0;

				Vec3b pixel;
				pixel.val[0] = (uchar) b;
				pixel.val[1] = (uchar) g;
				pixel.val[2] = (uchar) r;

				result_img.at<Vec3b>(Point(j, i)) = pixel;

			} catch (Exception & e) {
				cerr << e.msg << endl;
			}
		}
	}

	return result_img;
}

// Low Pass Filters
Mat AverageFilter(Mat img, int window) {

	if (window % 2 != 1) return img;

	Mat result_img(img.rows, img.cols, img.type(), Scalar(0, 0, 0));

	int n = int(window / 2);

	for (int i = n; i < img.rows - n; i++) { // Rows
		for (int j = n; j < img.cols - n; j++) { // Columns
			float r = 0, g = 0, b = 0;
			for (int x = 0; x < window; x++) { //windows rows
				for (int y = 0; y < window; y++) { // windows cols
					try {
						Vec3b pixel = img.at<Vec3b>(Point(j - n + y, i - n + x));
						uchar blue = pixel.val[0];
						uchar green = pixel.val[1];
						uchar red = pixel.val[2];

						r += (uchar) red;
						g += (uchar) green;
						b += (uchar) blue;

					} catch (Exception & e) {
						cerr << e.msg << endl;
					}
				}
			}
			Vec3b finalPixel;
			finalPixel.val[0] = (uchar) round((b * 1.0) / (pow(window, 2)));
			finalPixel.val[1] = (uchar) round((g * 1.0) / (pow(window, 2)));
			finalPixel.val[2] = (uchar) round((r * 1.0) / (pow(window, 2)));

			result_img.at<Vec3b>(Point(j, i)) = finalPixel;
		}
	}
	return result_img;
}

