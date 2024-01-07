//
// Created by liqing on 18-12-3.
//

#include "TS_YoloClassification.h"
#include "MyUdlLayers.h"
#include "snpe_udl_layers.h"

#include <DlContainer/IDlContainer.hpp>
#include <DlSystem/String.hpp>
#include <DlSystem/DlError.hpp>
#include <DlSystem/ITensor.hpp>
#include <DlSystem/ITensorFactory.hpp>
#include <DlSystem/ITensorFactory.hpp>
#include <DlSystem/IUserBufferFactory.hpp>
#include <DlSystem/TensorShape.hpp>
#include <SNPE/SNPEFactory.hpp>
#include <SNPE/SNPEBuilder.hpp>


#include "TimeUtil.h"

//#define USE_ITENSOR
#define USE_MODEL_FILE

#ifdef USE_MODEL_FILE
//#define MODEL_PATH "../models/yolov5_client_8_3s_quantized_hta.dlc"
//#define MODEL_PATH "../models/yolov5s_3_bk_quantize.dlc"

#define MODEL_PATH "../models/yolov5s_3_416_quantized_hta.dlc"
#define OUT_NODE0 "Sigmoid_246"
#define OUT_NODE1 "Sigmoid_295"
#define OUT_NODE2 "Sigmoid_344"
#define OUT_TENSOR0 "379"
#define OUT_TENSOR1 "440"
#define OUT_TENSOR2 "501"

#endif

inline float sigmoid(float x) {
    return (1 / (1 + exp(-x)));
}

output::output()
{

}

output::output(float x, float y, float w, float h, float score, int label)
{
    // get top-left position
    m_x = x - w / 2 ;
    if (m_x <= 0)
	    m_x = 0;
    m_y = y - h / 2;
    if (m_y <= 0)
	    m_y = 0;

    m_w = w;
    m_h = h;
    m_score = score;
    m_label = label;
}

output::~output()
{

}

/** @brief calculate the rectangle iou */
inline float IoU(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
    int xOverlap = std::max(0.0f,
                            std::min(x1 + w1 - 1, x2 + w2 - 1)
                            - std::max(x1, x2) + 1);
    int yOverlap = std::max(0.0f,
                            std::min(y1 + h1 - 1, y2 + h2 - 1)
                            - std::max(y1, y2) + 1);
    int intersection = xOverlap * yOverlap;
    int unio = w1 * h1 + w2 * h2 - intersection;
    return float(intersection) / unio;
}

YoloClassification::YoloClassification():mConfidenceThreshold(0.7f), input_data(NULL),
    outPtr1(NULL), outPtr2(NULL) {
    //outShape1 = {1,20,20,3*MODEL_OUTPUT_CHANNEL};
    //outShape2 = {1,40,40,3*MODEL_OUTPUT_CHANNEL};
    //outShape3 = {1,80,80,3*MODEL_OUTPUT_CHANNEL};
    outShape1 = {1,13,13,3*MODEL_OUTPUT_CHANNEL};
    outShape2 = {1,26,26,3*MODEL_OUTPUT_CHANNEL};
    outShape3 = {1,52,52,3*MODEL_OUTPUT_CHANNEL};
}

YoloClassification::~YoloClassification() {
    deInit();
}

state_t YoloClassification::init(int device) {
    std::unique_ptr<zdl::DlContainer::IDlContainer> container;
#ifdef USE_MODEL_FILE
    container = zdl::DlContainer::IDlContainer::open(zdl::DlSystem::String(MODEL_PATH));
#else
    const std::vector<uint8_t> buffer(&_np_detect_buf[0], &_np_detect_buf[0] + sizeof(_np_detect_buf));
    container = zdl::DlContainer::IDlContainer::open(buffer);
#endif
    zdl::SNPE::SNPEBuilder snpeBuilder(container.get());
#if 1
    outputLayers.append(OUT_NODE2); // 1x13x13x255
    outputLayers.append(OUT_NODE1); // 1x26x26x255
    outputLayers.append(OUT_NODE0); // 1x52x52x255
#else
    outputLayers.append("BoxPredictor_0/Reshape:0");
    outputLayers.append("BoxPredictor_0/Reshape_1:0");
    outputLayers.append("BoxPredictor_1/Reshape:0");
    outputLayers.append("BoxPredictor_1/Reshape_1:0");
    outputLayers.append("BoxPredictor_2/Reshape:0");
    outputLayers.append("BoxPredictor_2/Reshape_1:0");
    outputLayers.append("BoxPredictor_3/Reshape:0");
    outputLayers.append("BoxPredictor_3/Reshape_1:0");
    outputLayers.append("BoxPredictor_4/Reshape:0");
    outputLayers.append("BoxPredictor_4/Reshape_1:0");
    outputLayers.append("BoxPredictor_5/Reshape:0");
    outputLayers.append("BoxPredictor_5/Reshape_1:0");
#endif
    zdl::DlSystem::Runtime_t runtime;
    switch (device) {
        case CPU: runtime = zdl::DlSystem::Runtime_t::CPU;
            std::cout<<"CPU"<<std::endl;
            break;
        case GPU: runtime = zdl::DlSystem::Runtime_t::GPU;
            std::cout<<"GPU"<<std::endl;
            break;
        case GPU_16: runtime = zdl::DlSystem::Runtime_t::GPU_FLOAT16;
            std::cout<<"GPU_16"<<std::endl;
            break;
        case DSP: runtime = zdl::DlSystem::Runtime_t::DSP;
            std::cout<<"DSP"<<std::endl;
            break;
        case AIP: runtime = zdl::DlSystem::Runtime_t::AIP_FIXED8_TF;
            std::cout<<"AIP"<<std::endl;
            d_device_id = 4;
            break;
        default:  runtime = zdl::DlSystem::Runtime_t::GPU;break;
    }

//    zdl::DlSystem::UDLBundle udlBundle;
//    udlBundle.cookie = (void*) 0xdeadbeaf;
//    udlBundle.func = MyUDLFactory;

    zdl::DlSystem::PerformanceProfile_t profile = zdl::DlSystem::PerformanceProfile_t::BURST;

#ifdef USE_ITENSOR
    snpe = snpeBuilder.setOutputLayers(outputLayers)
            .setRuntimeProcessor(runtime)
            .setCPUFallbackMode(true)
            .setPerformanceProfile(profile)
          //.setUdlBundle(udlBundle)
          //.setInputDimensions(inputDimensionsMap)
            .build();
#else
    snpe = snpeBuilder.setOutputLayers(outputLayers)
            .setRuntimeProcessor(runtime)
          //  .setCPUFallbackMode(true)
            .setPerformanceProfile(profile)
          //.setUdlBundle(udlBundle)
            .setUseUserSuppliedBuffers(true)
            //.setInputDimensions(inputDimensionsMap)
            .build();
#endif
    if(NULL == snpe) {
        const char* const err = zdl::DlSystem::getLastErrorString();
        std::cout<<"error code first %s"<< err <<std::endl;
    } else {
        const auto strList = snpe->getInputTensorNames();
        auto inputDims = snpe->getInputDimensions((*strList).at(0));
        const zdl::DlSystem::TensorShape& inputShape = *inputDims;
        size_t rank = inputShape.rank();
        input_shape.clear();
        int input_size = 1;
        for (size_t i=0; i<rank; i++) {
            input_size *= inputShape[i];
            input_shape.push_back(inputShape[i]);
            std::cout<<"input shape"<<i<<" "<<inputShape[i]<<std::endl;
        }

        inTensor = zdl::SNPE::SNPEFactory::getTensorFactory().createTensor(
                inputDims
        );
        inMap.add((*strList).at(0), inTensor.get());

        userBuf = createUserBuffer(inputShape, input_data);
        outBuf1 = createUserBuffer(outShape1, outPtr1);
        int out1_size = outShape1[0] * outShape1[1] * outShape1[2] * outShape1[3];
        outTensor1 = zdl::SNPE::SNPEFactory::getTensorFactory().createTensor(
                outShape1, (unsigned char *) outPtr1, out1_size * sizeof(float));

        outBuf2 = createUserBuffer(outShape2, outPtr2);
        int out2_size = outShape2[0] * outShape2[1] * outShape2[2] * outShape2[3];
        outTensor2 = zdl::SNPE::SNPEFactory::getTensorFactory().createTensor(
                outShape2, (unsigned char *) outPtr2, out2_size * sizeof(float));

        int out3_size = outShape3[0] * outShape3[1] * outShape3[2] * outShape3[3];
        outBuf3 = createUserBuffer(outShape3, outPtr3);
        outTensor3 = zdl::SNPE::SNPEFactory::getTensorFactory().createTensor(
                outShape3, (unsigned char *) outPtr3, out3_size * sizeof(float));

        inUBMap.add((*strList).at(0), userBuf.get());

        outUBMap.add(OUT_TENSOR2, outBuf1.get()); // 1x13x13x255
        outUBMap.add(OUT_TENSOR1, outBuf2.get()); // 1x26x26x255
        outUBMap.add(OUT_TENSOR0, outBuf3.get()); // 1x52x52x255

        auto outTensorNames = snpe->getOutputTensorNames();
        std::string name = "";
        for (size_t i = 0; i < (*outTensorNames).size(); i++) {
            name = (*outTensorNames).at(i);
            std::cout<<"output node"<<name.c_str()<<std::endl;
        }

	//outPtr_output = new float[25200*MODEL_OUTPUT_CHANNEL];
	outPtr_output = new float[10647*MODEL_OUTPUT_CHANNEL];

        zdl::DlSystem::Version_t Version = zdl::SNPE::SNPEFactory::getLibraryVersion();
        std::cout<<"version:"<<Version.toString().c_str()<<std::endl;
    }
    return NO_ERROR;
}

state_t YoloClassification::deInit() {
    if (nullptr != snpe) {
        snpe.reset(nullptr);
    }
    if (input_data != NULL) {
        delete[] input_data;
        input_data = nullptr;
    }
    if (outPtr1 != nullptr) {
        delete[] outPtr1;
        outPtr1 = nullptr;
    }
    if (outPtr2 != nullptr) {
        delete[] outPtr2;
        outPtr2 = nullptr;
    }
    return NO_ERROR;
}

void YoloClassification::setConfidence(float value) {
    mConfidenceThreshold = value > 1.0f ? 1.0f : (value < 0.0f ? 0.0f : value);
}

std::vector<output> YoloClassification::doDetect(cv::Mat img) {
    std::vector<output> m_output;
    if (NULL == snpe) {
        std::cout<<"Can not init."<<std::endl;
        return m_output;
    }
    cv::Mat rgb_mat;
    cv::cvtColor(img, rgb_mat, CV_BGR2RGB);
#if 0
    img = cv::imread("/sdcard/Download/person.jpg");
    cv::cvtColor(img, rgb_mat, CV_BGR2RGB);  // real is bgra to bgr
#else
    // cv::cvtColor(img, rgb_mat, CV_BGRA2RGB);  // real is bgra to bgr
//    cv::imwrite("/sdcard/Download/dump.jpg", img);
#endif
    long pre_start = getCurrentTime_ms();
    // int img_w = img.cols;
    // int img_h = img.rows;
    int img_w = rgb_mat.cols;
    int img_h = rgb_mat.rows;
    float scale = std::min(MODEL_INPUT_W/(float)img_w, MODEL_INPUT_H/(float)img_h);
    int new_w = img_w * scale;
    int new_h = img_h * scale;
//    long convert_rgb = getCurrentTime_ms();
//    long con_time = getCurrentTime_ms();
//    TS_LOGD("convert rgb cost time=%ld", con_time - convert_rgb);

    int x_offset = (MODEL_INPUT_W - new_w) / 2;
    int y_offset = (MODEL_INPUT_H - new_h) / 2;
    cv::Mat in_mat(MODEL_INPUT_H, MODEL_INPUT_W, CV_8UC3, cv::Scalar(128, 128, 128));
    cv::Mat roi_mat(in_mat, cv::Rect(x_offset, y_offset, new_w, new_h));
    cv::resize(rgb_mat, roi_mat, cv::Size(new_w, new_h), cv::INTER_CUBIC);

    cv::Mat input(MODEL_INPUT_H, MODEL_INPUT_W, CV_32FC3, input_data);
    in_mat.convertTo(input, CV_32FC3);
    input /= 255.0f;

#ifdef USE_ITENSOR
    const auto strList = snpe->getInputTensorNames();
    zdl::DlSystem::ITensorItr<false> tensorIt = inTensor->begin();
    zdl::DlSystem::ITensorItr<false> tensorItEnd = inTensor->end();
    int width = input.cols;
    int height = input.rows;
    int channel = input.channels();
    float* ptr = (float*) inTensor.get();
    for (int i=0; i<height; i++) {
        const float *matData = input.ptr<float>(i);
        std::copy(matData, matData + width * channel, tensorIt);
        tensorIt += width * channel;
    }
#endif
    long pre_diff = getCurrentTime_ms() - pre_start;
    // std::cout<<"pre process cost time="<<pre_diff<<std::endl;

    long start = getCurrentTime_ms();
    zdl::DlSystem::ITensor* out1 = nullptr;
#ifdef USE_ITENSOR
    //inMap.add((*strList).at(0), inTensor.get());
    bool ret = snpe->execute(inMap, outMap);
#else
    bool ret = snpe->execute(inUBMap, outUBMap);
#endif
    long diff = getCurrentTime_ms() - start;
    // std::cout<<"execute cost time="<<diff<<std::endl;
    if (!ret) {
        const char* const err = zdl::DlSystem::getLastErrorString();
        std::cout<<"error code:"<<err<<std::endl;
        return m_output;
    }
    uint64_t avg_time = m_time_analyzer.update(diff);
    // std::cout<<"LQ-TEST inference time: avg:"<<diff<<avg_time<<std::endl;
    // post process
    long post_start = getCurrentTime_ms();

    // merge outPtr1 outPtr2 outPtr3
    {
        //long merge_start = getCurrentTime_ms();
        const int output_class_num = MODEL_OUTPUT_CHANNEL;
        //int size_list[] = {20, 40, 80};
	int size_list[] = {13, 26, 52};
        float *output_ptr_lst[] = {outPtr1, outPtr2, outPtr3}; // 20, 40, 80

        float anchor_grid[][6] = {
            {116, 90, 156, 198, 373, 326}, //# P5/32
            {30, 61, 62, 45, 59, 119},     //# P4/16
            {10, 13, 16, 30, 33, 23},      //# P3/8
        };
        float stride[] = {32, 16, 8};

        float *out_ptr = outPtr_output;
        for (int i = 0; i < 3; i++)
        {
            int size = size_list[i];
            float *src_ptr = output_ptr_lst[i];
            // 1x20x20x3x8
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    int anchor_index = 0;
                    for (int l = 0; l < 3; l++)
                    {
                        for (int m = 0; m < output_class_num; m++)
                        {
                            if (m < 2)
                            {
                                float value = *src_ptr;
                                float grid_value = m == 0 ? k : j;
                                *out_ptr = (value * 2 - 0.5 + grid_value) * stride[i];
                            }
                            else if (m < 4)
                            {
                                float value = *src_ptr;
                                *out_ptr = value * value * 4 * anchor_grid[i][anchor_index++];
                            }
                            else
                            {
                                *out_ptr = *src_ptr;
                            }
                            out_ptr++;
                            src_ptr++;
                        }
                    }
                }
            }
        }
    }

    //int data_size_25200 = 25200 * MODEL_OUTPUT_CHANNEL;
    int data_size_25200 = 10647 * MODEL_OUTPUT_CHANNEL;

    //NMS get the result
    {
        std::vector<int> idx_vec;
        std::vector<float> conf_vec;
        std::deque<output> data;

        for (unsigned int i = 0; i < 10647; i++) {
            float conf = outPtr_output[i * MODEL_OUTPUT_CHANNEL + 4];
            if (conf > 0.001) {
                idx_vec.push_back(i);
                conf_vec.push_back(conf);
            }
        }

        float cur_max_score = 0.0;
        float cur_min_score = 0.0;

        for (unsigned int i = 0; i < idx_vec.size(); i++) {
            int cur_idx = idx_vec.at(i);
            float cur_conf = conf_vec.at(i);

            // Mark as modification
            for (unsigned j = 5; j < MODEL_OUTPUT_CHANNEL; j++) {
                float score = cur_conf * outPtr_output[cur_idx*MODEL_OUTPUT_CHANNEL+j];
                if (score > 0.25) {
                    output tmp(outPtr_output[cur_idx*MODEL_OUTPUT_CHANNEL], outPtr_output[cur_idx*MODEL_OUTPUT_CHANNEL+1], 
				        outPtr_output[cur_idx*MODEL_OUTPUT_CHANNEL+2], outPtr_output[cur_idx*MODEL_OUTPUT_CHANNEL+3], score, j-5);
                    if (data.size() == 0) {
                        data.push_back(tmp);
                        cur_max_score = score;
                        cur_min_score = score;
                    } else {
                        if (score >= cur_max_score) {
                            data.push_front(tmp);
                            cur_max_score = score;
                        } else {
                            data.push_back(tmp);
                            cur_min_score = score;
                        }
                    }
                }
            }
        }

        // NMS
        for(unsigned int i = 0; i < data.size(); i++) {
            output data1, data2;
            bool isInsert = true;
            data1 = data.at(i);
            for (unsigned int j = 0; j < m_output.size(); j++) {
                data2 = m_output.at(j);
                float iou = IoU(data1.m_x, data1.m_y, data1.m_w, data1.m_h, data2.m_x, data2.m_y, data2.m_w, data2.m_h);
                if (iou > 0.45 || m_output.size() > 50) {
                    isInsert = false;
                }
            }
            if (isInsert) {
                m_output.push_back(data1);
            }
        }
    }

    long post_diff = getCurrentTime_ms() - post_start;
    long sum_diff = getCurrentTime_ms() - pre_start;
    // std::cout<<"post cost time="<<post_diff<<std::endl;
    std::cout<<"one frame cost time="<<sum_diff<<std::endl;
    return m_output;
}

std::unique_ptr<zdl::DlSystem::IUserBuffer> YoloClassification::createUserBuffer(
        zdl::DlSystem::TensorShape shape, float*& data) {
    int buf_size = shape[0] * shape[1] * shape[2] * shape[3];
    std::vector<size_t> strides(shape.rank());
    strides[strides.size() - 1] = sizeof(float);
    size_t stride = strides[strides.size() - 1];
    for (size_t i = shape.rank() - 1; i > 0; i--) {
        stride *= shape[i];
        strides[i - 1] = stride;
    }

    int bufSize = buf_size * sizeof(float);
    float* buffer = new float[buf_size];
    data = (float*) buffer;
    // user buffer
    zdl::DlSystem::UserBufferEncodingFloat userBufferEncodingFloat;
    // create SNPE user buffer from the user-backed buffer
    zdl::DlSystem::IUserBufferFactory &ubFactory = zdl::SNPE::SNPEFactory::getUserBufferFactory();
    return ubFactory.createUserBuffer(data, bufSize, strides,
                                      &userBufferEncodingFloat);
}

