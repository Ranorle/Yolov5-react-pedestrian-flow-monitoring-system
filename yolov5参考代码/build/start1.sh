#!/bin/bash

while [ True ]
do
    export GST_RTSPSRC_PATH=rtsp://admin:ZKCD1234@10.0.23.227:554
    ./AiObject-Yolov5_1 > test1.log
    sleep 5
done	

