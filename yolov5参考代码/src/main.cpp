#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <pthread.h>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <thread>
#include <ctime>
#include "httplib.h"
#include "json.hpp"

#include "TS_YoloClassification.h"
#include "jni_types.h"
float DETECTSCORE = 0.4;
float confidence = 0.4;
float xiaodouyuzhi = 2;
std::string *labels = new std::string[1000];
std::vector<output> last_result = {};
std::vector<output> result = {};
cv::VideoCapture cap;
cv::Mat frame;
int peopleCount = 0;
int lastpeople = 0;
int renliuliang = 0;
long int timecount = 0;
long int lastMinute = -1;     // 上一次保存的分钟数
std::ofstream logFile;        // 日志文件流
bool stopProcessing = false;  // 停止处理标志
bool stopProcessing2 = false; // 停止处理标志
std::string dthing = "person";

// 定义颜色映射
std::map<int, cv::Scalar> labelColors;
void startServer();

void initializeLabelColors()
{
    // 循环初始化颜色映射
    for (int i = 0; i <= 1000; ++i)
    {
        // 生成随机颜色
        cv::Scalar color(rand() % 256, rand() % 256, rand() % 256);
        labelColors[i] = color;
    }
}

void saveMinuteResult()
{
    // 获取当前分钟数
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *tm_info = std::localtime(&currentTime);
    int currentMinute = tm_info->tm_min;

    // 如果当前分钟数不等于上一次保存的分钟数，表示新的一分钟开始
    if (currentMinute != lastMinute)
    {
        // 记录上一分钟的人流量
        logFile << "Minute " << lastMinute << ": " << renliuliang << dthing << std::endl;

        // 重置人流量计数
        renliuliang = 0;

        // 更新上一次保存的分钟数
        lastMinute = currentMinute;
    }
}

void displayThread()
{
    while (1)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        // 如果用户按ESC键，退出循环
        if (cv::waitKey(5) == 27)
        {
            // 关闭日志文件
            logFile.close();
            // 设置停止处理标志
            stopProcessing2 = true;
            return;
        }

        // 读取摄像头帧
        cap.read(frame);
        // 如果帧为空，输出消息
        if (frame.empty())
        {
            std::cout << "空帧" << std::endl;
            continue;
        }

        // 显示图像
        cv::Mat frame_copy = frame;
        cv::putText(frame_copy, "Now Current:" + std::to_string(renliuliang),
                    cv::Point(0, 40),
                    cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
        cv::putText(frame_copy, ctime(&currentTime),
                    cv::Point(0, 20),
                    cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
        cv::putText(frame_copy, "detecting object:" + dthing,
                    cv::Point(300, 20),
                    cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
        cv::putText(frame_copy, "confidence:" + std::to_string(confidence),
                    cv::Point(180, 40),
                    cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
        cv::putText(frame_copy, "detectscore:" + std::to_string(DETECTSCORE),
                    cv::Point(180, 60),
                    cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
        cv::putText(frame_copy, "debounceparam:" + std::to_string(xiaodouyuzhi),
                    cv::Point(0, 80),
                    cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
        cv::putText(frame_copy, stopProcessing ? "paused" : "detecting",
                    cv::Point(0, 60),
                    cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
        if (!result.empty())
        {
            for (int i = 0; i < result.size() && result[i].m_score > DETECTSCORE; i++)
            {
                // 调整矩形框和文本位置的缩放系数
                cv::putText(frame_copy, labels[result[i].m_label],
                            cv::Point(static_cast<int>(result[i].m_x) * 1.6, static_cast<int>(result[i].m_y) * 1.0),
                            cv::FONT_HERSHEY_COMPLEX, 0.8, labelColors[result[i].m_label], 2, cv::LINE_8);
                cv::putText(frame_copy, std::to_string(result[i].m_score),
                            cv::Point(static_cast<int>(result[i].m_x) * 1.6 + 140, static_cast<int>(result[i].m_y) * 1.0),
                            cv::FONT_HERSHEY_COMPLEX, 0.8, labelColors[result[i].m_label], 2, cv::LINE_8);
                // 调整矩形框的坐标系数
                cv::rectangle(frame_copy,
                              cv::Point(static_cast<int>(result[i].m_x) * 1.55, static_cast<int>(result[i].m_y) - 30),
                              cv::Point(static_cast<int>(result[i].m_x + result[i].m_w) * 1.6,
                                        static_cast<int>(result[i].m_y + result[i].m_h) * 1.35),
                              labelColors[result[i].m_label], 2, cv::LINE_8);
            }
        }
        cv::imshow("实时画面", frame_copy);
    }
}

void thread_loop_doDetect()
{
    std::ifstream in("../models/labels.txt");
    std::string line;
    int count = 0;
    YoloClassification *detector = new YoloClassification();
    detector->init(0);
    detector->setConfidence(confidence);
    while (getline(in, line))
    {
        labels[count] = line;
        count++;
    }
    int Count = 0;
    while (!stopProcessing2)
    {
        if (stopProcessing)
        {
            result = {};
            continue;
        }
        timecount++;
        std::cout << timecount << std::endl;

        if (frame.empty())
        {
            std::cout << "empty" << std::endl;
            continue;
        }

        // 每分钟执行一次保存人流量统计结果
        saveMinuteResult();

        result = detector->doDetect(frame);

        last_result = result;
        std::cout << "Yolov5 detect out size: " << result.size() << std::endl;
        if (result.size() > 0)
        {
            Count = 0;
            for (int i = 0; i < result.size(); i++)
            {
                if (result[i].m_score > DETECTSCORE)
                {
                    std::cout << "name : " << labels[result[i].m_label] << std::endl;
                    std::cout << "score : " << result[i].m_score << std::endl;
                    std::cout << "position(x, y, width, height):" << std::endl;
                    std::cout << "x:" << result[i].m_x << std::endl;
                    std::cout << "y:" << result[i].m_y << std::endl;
                    std::cout << "width:" << result[i].m_w << std::endl;
                    std::cout << "height:" << result[i].m_h << std::endl;
                    if (labels[result[i].m_label] == dthing)
                    {
                        // If a person is detected, increment people count
                        Count++;
                    }
                }
            }
            peopleCount = Count;
            if (peopleCount - lastpeople < 0 && timecount >= xiaodouyuzhi)
            {
                timecount = 0;
                renliuliang = renliuliang + abs(peopleCount - lastpeople);
            }
            lastpeople = peopleCount;
        }
    }
}

int main()
{
    // 打开日志文件，准备记录人流量统计结果
    logFile.open("result.log", std::ios::app);

    int deviceID = 0; // 使用 0 为默认摄像头，如果需要调整，则修改此值
    cap.open(deviceID);
    // 设置摄像头帧宽度
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    // // 设置摄像头帧高度
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    if (!cap.isOpened())
    {
        std::cerr << "ERROR! 无法打开摄像头\n";
        return -1;
    }

    initializeLabelColors();

    std::cout << "按ESC键退出程序" << std::endl;

    // 启动目标检测线程
    std::thread detection_thread(thread_loop_doDetect);
    // 启动显示图像线程
    std::thread display_thread(displayThread);
    // 启动Web服务器线程
    std::thread web_thread(startServer);

    // 等待目标检测线程和显示图像线程结束
    detection_thread.join();
    display_thread.join();
    // 关闭日志文件
    logFile.close();
    // 停止Web服务器线程
    web_thread.detach();

    return 0;
}

void startServer()
{
    httplib::Server svr;

    svr.Get("/video", [](const httplib::Request &req, httplib::Response &res)
            {
        res.set_header("Access-Control-Allow-Origin", "*");  // 允许所有来源
        // 在这里返回图像数据，例如JPEG格式
        std::vector<uchar> img_buffer;
        cv::imencode(".jpg", frame, img_buffer);
        res.set_content(std::string(img_buffer.begin(), img_buffer.end()), "image/jpeg"); });

    svr.Get("/init", [](const httplib::Request &req, httplib::Response &res)
            {
        res.set_header("Access-Control-Allow-Origin", "*");  // 允许所有来源
            nlohmann::json response_json = {
            {"pauseparam",stopProcessing},
            {"detectscore", DETECTSCORE},
            {"confidence", confidence},
            {"detectobject",dthing },
            {"debounce",xiaodouyuzhi}

        };
        res.set_header("Content-Type", "application/json");
        std::string response_str = response_json.dump();

        res.set_content((response_str), "application/json"); 
        });

    svr.Post("/control", [](const httplib::Request &req, httplib::Response &res)
             {
        res.set_header("Access-Control-Allow-Origin", "*");  // 允许所有来源
        auto action = req.get_param_value("action");
        if (action == "start")
        {
            // 启动处理
            stopProcessing = false;
            res.set_content("Processing started", "text/plain");
        }
        else if (action == "stop")
        {
            // 停止处理
            stopProcessing = true;
            res.set_content("Processing stopped", "text/plain");
        }
        else
        {
            res.set_content("Unknown action", "text/plain");
        } });
    svr.Post("/change", [](const httplib::Request &req, httplib::Response &res)
             {
        res.set_header("Access-Control-Allow-Origin", "*");  // 允许所有来源

        auto detectscoreparam = req.get_param_value("detectscore");
        DETECTSCORE=std::stof(detectscoreparam);
        auto detectobjectparam = req.get_param_value("detectobject");
        dthing=detectobjectparam;
        auto debounceparam = req.get_param_value("debounce");
        xiaodouyuzhi=std::stof(debounceparam);
        renliuliang=0;
             });
        svr.Get("/logdownload", [](const httplib::Request &req, httplib::Response &res)
            {
        res.set_header("Access-Control-Allow-Origin", "*");  // 允许所有来源

        // 打开日志文件
        std::ifstream logFileStream("result.log", std::ios::binary);
        if (!logFileStream.is_open())
        {
            res.status = 500;
            res.set_content("Internal Server Error: Unable to open log file", "text/plain");
            return;
        }

        // 读取文件内容
        std::string logContent((std::istreambuf_iterator<char>(logFileStream)), std::istreambuf_iterator<char>());

        // 设置响应头，指定文件名和内容类型
        res.set_header("Content-Disposition", "attachment; filename=result.log");
        res.set_content(logContent, "text/plain");
    });

    svr.set_mount_point("/", "../dist");

    svr.listen("localhost", 8081);
}