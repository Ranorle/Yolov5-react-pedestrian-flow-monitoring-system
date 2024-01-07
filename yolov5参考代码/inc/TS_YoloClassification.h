//
// Created by liqing on 18-12-3.
//

#ifndef NIKEDEMO_NIKESHOESRECOGNITION_H
#define NIKEDEMO_NIKESHOESRECOGNITION_H

#include "jni_types.h"
#include <iostream>
#include <math.h>
#include <SNPE/SNPE.hpp>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>

#include "time_utility.hpp"

#define MODEL_INPUT_BATCH 1
#define MODEL_INPUT_W 416
#define MODEL_INPUT_H 416
#define MODEL_OUTPUT_CHANNEL 85
#define MODEL_INPUT_CHANNEL 3
#define MODEL_OUTPUT_BATCH 1
#define MODEL_OUTPUT_W MODEL_INPUT_W/16
#define MODEL_OUTPUT_H MODEL_INPUT_H/16
#define MODEL_OUTPUT_C 255

class output {
public:
    output();
    output(float x, float y, float w, float h, float score, int label);
    ~output();
    float m_x, m_y, m_w, m_h;
    float m_score;
    int m_label;
};

class YoloClassification {
public:
    explicit YoloClassification();
    virtual ~YoloClassification();

    state_t init(int device);
    state_t deInit();
    std::vector<output> doDetect(cv::Mat img);
    std::vector<output> doDetect(std::shared_ptr<cv::Mat>& img);
    void setConfidence(float value);

private:
    std::unique_ptr<zdl::DlSystem::IUserBuffer> createUserBuffer(
            zdl::DlSystem::TensorShape shape,
            float*& data);

    std::unique_ptr<zdl::SNPE::SNPE> snpe;
    zdl::DlSystem::StringList outputLayers;
    std::shared_ptr<zdl::DlSystem::ITensor> inTensor;
    std::shared_ptr<zdl::DlSystem::ITensor> outTensor1;
    std::shared_ptr<zdl::DlSystem::ITensor> outTensor2;
    std::shared_ptr<zdl::DlSystem::ITensor> outTensor3;
    zdl::DlSystem::TensorMap inMap;
    zdl::DlSystem::TensorMap outMap;
    float* input_data;
    float* outPtr1;
    float* outPtr2;
    float* outPtr3;
    float* outPtr_output;
    std::unique_ptr<zdl::DlSystem::IUserBuffer> userBuf;
    std::unique_ptr<zdl::DlSystem::IUserBuffer> outBuf1;
    std::unique_ptr<zdl::DlSystem::IUserBuffer> outBuf2;
    std::unique_ptr<zdl::DlSystem::IUserBuffer> outBuf3;
    zdl::DlSystem::UserBufferMap inUBMap;
    zdl::DlSystem::UserBufferMap outUBMap;
    std::vector<int> input_shape;
    zdl::DlSystem::TensorShape outShape1;
    zdl::DlSystem::TensorShape outShape2;
    zdl::DlSystem::TensorShape outShape3;
    float mConfidenceThreshold;

    std::vector<pairInt> anchors;
    std::vector<std::vector<int>> anchor_mask;
    int grid_xy1[MODEL_OUTPUT_W/2][MODEL_OUTPUT_H/2][2];
    int grid_xy2[MODEL_OUTPUT_W][MODEL_OUTPUT_H][2];
    int grid_xy3[MODEL_OUTPUT_W*2][MODEL_OUTPUT_H*2][2];

    // debug
    ts::TimeAnalyzer<uint64_t> m_time_analyzer;
    int d_device_id = 0;
};

extern std::vector<output>  yolov5_detection(std::shared_ptr<cv::Mat>& img, YoloClassification* detector);

#endif //NIKEDEMO_NIKESHOESRECOGNITION_H
