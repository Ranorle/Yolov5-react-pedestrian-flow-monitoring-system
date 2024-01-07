#!/bin/bash

while [ True ]
do
    export GST_RTSPSRC_PATH=rtsp://admin:ZKCD1234@10.0.20.158:554
    ./AiObject-Yolov5_3 > test3.log
    sleep 5
done	

