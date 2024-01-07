export XDG_RUNTIME_DIR=/usr/bin/weston_socket
killall start1.sh start2.sh start3.sh start4.sh
ps -ef |grep AiObject-Yolov5 |awk '{print $2}'|xargs kill -9

./start1.sh &
sleep 8

./start2.sh &
sleep 8

./start3.sh &
sleep 8

./start4.sh &
sleep 8

