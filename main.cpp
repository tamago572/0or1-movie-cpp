#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std;

unsigned int sleep(unsigned int seconds);

int main(int argc, char* argv[])
{
    std::cout << "Welcome!" << std::endl;

    string videoPath = argv[1];

    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened()) {
        return 0;
    }

    int max_frame = (int)cap.get(cv::CAP_PROP_FRAME_COUNT);
    int img_h = (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int img_w = (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
    float fps = cap.get(cv::CAP_PROP_FPS);

    std::cout << "FPS: " << fps << std::endl;
    std::cout << "height: " << img_h << std::endl;
    std::cout << "width: " << img_w << std::endl;
    std::cout << "max frame: " << max_frame << std::endl;

    cv::Mat img;

    system("afplay /Users/potesala/badapple.mp3&");

    // フレームレートを設定（1/30秒）
    std::chrono::microseconds frame_duration(1000000 / (int)fps);

    for (int i = 0; i < max_frame; i++) {
        auto start = std::chrono::high_resolution_clock::now();

        std::cout << "\x1b[38;2;255;255;255m" << "current frame: " << i+1 << ", " << std::endl;
        // //1フレーム分取り出してimgに保持させる
        cap >> img;

        for (int i = 0; i < img_w * img_h; i++) {
            int x = i % img_w;
            int y = i / img_w;
            // std::cout << "x: " << x << " , y: " << y << std::endl;
            int B = img.at<cv::Vec3b>(y, x)[0];
            int G = img.at<cv::Vec3b>(y, x)[1];
            int R = img.at<cv::Vec3b>(y, x)[2];

            std::cout << "\x1b[38;2;" << R << ";" << G << ";" << B << "m" << 0;

            // 1行の描画が最後まで行った場合、改行
            if ((i + 1) % img_w == 0) {
                std::cout << std::endl;
            }

        }
        // 処理終了時間を記録
        std::cout << "\e[" << img_h+2 << "A" << std::endl;
        auto end = std::chrono::high_resolution_clock::now();
        // 処理にかかった時間を計算
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        // 次のフレームまでの待機時間を計算（処理にかかった時間を考慮）
        auto wait_time = frame_duration - elapsed;

        if(wait_time.count() < 0) {
            wait_time = std::chrono::microseconds(0);
        }

        // 次のフレームまで待機
        // std::this_thread::sleep_for(wait_time);

        usleep(33333.333);

        // std::cout << duration << "ms" << std::endl;

        // auto start2 = std::chrono::high_resolution_clock::now();



        // auto end2 = std::chrono::high_resolution_clock::now();

        // auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

        // std::cout << std::endl << duration2 << "ms" << std::endl;


        // break;
    }

    return 0;
}