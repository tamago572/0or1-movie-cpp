#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <time.h>
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

    // フレーム間隔をナノ秒単位で計算（1秒 = 1,000,000,000ナノ秒）
    // long frame_interval = 1000000000 / fps;

    for (int i = 0; i < max_frame; i++) {

        // フレームの開始時間を記録
        // auto start_time = std::chrono::high_resolution_clock::now();

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

            int text = 0;
            if (B > 36) {
                text = 1;
            }

            std::cout << "\x1b[38;2;" << R << ";" << G << ";" << B << "m" << text;

            // 1行の描画が最後まで行った場合、改行
            if ((i + 1) % img_w == 0) {
                std::cout << std::endl;
            }

        }
        std::cout << "\e[" << img_h+2 << "A" << std::endl;
        // 33ミリ秒止める（33000000ナノ秒）
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 23333333;
        nanosleep(&ts, NULL);


        // cv::waitKey(1/fps);
         // フレームの終了時間を記録
        // auto end_time = std::chrono::high_resolution_clock::now();

        // // 処理にかかった時間を計算（ナノ秒単位）
        // auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();

        // // 次のフレームまでの待機時間を計算（処理にかかった時間を引く）
        // long wait_time = frame_interval - elapsed_time;

        // // 計算結果が負にならないようにする
        // if(wait_time < 0) {
        //     wait_time = 0;
        // }

        // // 次のフレームまで待機（nanosleepを使用）
        // struct timespec ts;
        // ts.tv_sec = wait_time / 1000000000;
        // ts.tv_nsec = wait_time % 1000000000;
        // nanosleep(&ts, NULL);

    }
    std::cout << std::endl << "\x1b[38;2;255;255;255mご視聴ありがとうございました！" << std::endl;
    std::cout << std::endl << "是非高評価、チャンネル登録よろしくお願いします！" << std::endl;
    return 0;
}