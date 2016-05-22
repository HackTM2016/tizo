if [[ -f "~/darknet/yolo-tiny.weights" ]];then
    echo "download the weights"
    exit
fi 
./darknet yolo demo cfg/yolo-tiny.cfg ~/darknet/yolo-tiny.weights $1
