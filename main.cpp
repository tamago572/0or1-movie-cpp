#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;

int main(int argc, char* argv[])
{
    std::cout << "Welcome!" << std::endl;

    string imgPath = argv[1];

    int height = 36;
    int weight = 48;

    std::cout << "画像ファイル: " << imgPath << std::endl;

    // 画像を読み込む
    cv::Mat img = cv::imread(imgPath);

    cv::Mat img_bin;
    cv::cvtColor(img, img_bin, cv::COLOR_BGR2GRAY);

    // 画像を表示
    cv::imshow("IeiSenpai", img_bin);

    // 任意のキーが押されるまで待つ
    cv::waitKey(0);


    for (int i = 0; i < height; i++) {
        for (int i = 0; i < weight; i++) {
            std::cout << 0;
        }
        std::cout << std::endl;
    }

    return 0;
}