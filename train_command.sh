#RSI-CB256
#classification
nohup  ./build/examples/cpp_classification/classification.bin /home/cad/disk/linux/cbir/model/RSI-CB256/AlexNet_deploy.prototxt /home/cad/disk/linux/cbir/model/RSI-CB256/AlexNet_iter_100000.caffemodel /home/cad/disk/linux/cbir/model/RSI-CB256/mean.binaryproto /home/cad/disk/linux/cbir/class.txt /home/cad/disk/linux/cbir/RSI-CB256/filename.txt > cla_res.txt 2>&1 &

nohup  ./build/examples/cpp_classification/classification.bin /home/cad/disk/linux/cbir/model/RSI-CB256/AlexNet_deploy.prototxt /home/cad/disk/linux/cbir/model/RSI-CB256/AlexNet_iter_100000.caffemodel /home/cad/disk/linux/cbir/model/RSI-CB256/mean.binaryproto /home/cad/disk/linux/cbir/class.txt /home/cad/disk/linux/cbir/RSI-CB256/filename.txt > cla_res.txt 2>&1 &

#extracting features 
./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB256/AlexNet_iter_100000.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB256/class_val_alex.prototxt fc7 feat_extra 24747 /home/cad/disk/linux/cbir/feat_extra/rs_simi_alex.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB256/VGG16_iter_100000.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB256/class_val_vgg16.prototxt fc7 feat_extra 24747 /home/cad/disk/linux/cbir/feat_extra/rs_simi_vgg16.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB256/VGG_ILSVRC_16_layers.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB256/class_val_vgg16.prototxt fc6 feat_extra 24747 /home/cad/disk/linux/cbir/feat_extra/rs_simi_vgg16_pretrain.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB256/Alexnet_hash_128.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB256/class_val_alex_hash.prototxt fc8_hash_encode feat_extra 24747 /home/cad/disk/linux/cbir/feat_extra/rs_simi_alex_hash128_10.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB256/VGG16_hash_48.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB256/class_val_vgg16_hash.prototxt fc8_hash_encode feat_extra 24747 /home/cad/disk/linux/cbir/feat_extra/rs_simi_vgg16_hash48.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB256/GoogleNet_iter_100000.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB256/class_val_googlenet.prototxt pool5/7x7_s1 feat_extra 24747 /home/cad/disk/linux/cbir/feat_extra/rs_simi_googlenet.txt GPU 0 

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB256/GoogleNet_hash_48.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB256/class_val_googlenet_hash.prototxt fc_hash_encode feat_extra 24747 /home/cad/disk/linux/cbir/feat_extra/rs_simi_googlenet_hash48.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB256/ResNet_hash_128.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB256/class_val_resnet_hash.prototxt fc_hash_encode feat_extra 24747 /home/cad/disk/linux/cbir/feat_extra/rs_simi_resnet_hash128.txt GPU 0

#finetune for hash codes 
nohup ./build/tools/caffe train --solver=/home/cad/disk/linux/cbir/model/RSI-CB256/solver_AlexNet.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB256/AlexNet_iter_100000.caffemodel > output.log 2>&1 &

nohup ./build/tools/caffe train --solver=/home/cad/disk/linux/cbir/model/RSI-CB256/solver_VGG16.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB256/VGG16_iter_100000.caffemodel > output.log 2>&1 &

nohup ./build/tools/caffe train --solver=/home/cad/disk/linux/cbir/model/RSI-CB256/solver_ResNet.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB256/ResNet_iter_100000.caffemodel > output.log 2>&1 &

nohup ./build/tools/caffe train --solver=/home/cad/disk/linux/cbir/model/RSI-CB256/solver_GoogleNet.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB256/GoogleNet_iter_100000.caffemodel > output.log 2>&1 &

nohup ./build/tools/caffe train --solver=/home/shineng/Elements/cbir/solver_ResNet.prototxt -weight /home/shineng/Elements/cbir/ResNet_hash_128_iter_4800.caffemodel --gpu 1 > output.log 2>&1 &


#test
nohup ./build/tools/caffe test --model=/home/cad/disk/linux/cbir/model/RSI-CB256/AlexNet_train.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB256/AlexNet_iter_100000.caffemodel -gpu 0 -iterations 10 > output_alex_test.log 2>&1 &

nohup ./build/tools/caffe test --model=/home/cad/disk/linux/cbir/model/RSI-CB256/VGG16_train.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB256/VGG16_iter_100000.caffemodel -gpu 0 -iterations 10 > output_vgg16_test.log 2>&1 &

nohup ./build/tools/caffe test --model=/home/cad/disk/linux/cbir/model/RSI-CB256/VGG16_hash.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB256/VGG16_hash_48.caffemodel -gpu 0 -iterations 156 > output_vgg16_test.log 2>&1 &

nohup ./build/tools/caffe test --model=/home/cad/disk/linux/cbir/model/RSI-CB256/GoogleNet_train.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB256/GoogleNet_iter_100000.caffemodel -gpu 0 -iterations 58 > output_googlenet_test.log 2>&1 &

nohup ./build/tools/caffe test --model=/home/cad/disk/linux/cbir/model/RSI-CB256/GoogleNet_hash.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB256/GoogleNet_hash_48.caffemodel -gpu 0 -iterations 58 > output_googlenet_test.log 2>&1 &

nohup ./build/tools/caffe test --model=/home/cad/disk/linux/cbir/model/RSI-CB256/ResNet_hash.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB256/ResNet_hash_128.caffemodel -gpu 0 -iterations 156 > output_resnet_test.log 2>&1 &




#RSI-CB128
#classification
nohup  ./build/examples/cpp_classification/classification.bin /home/cad/disk/linux/cbir/model/RSI-CB128/AlexNet_deploy.prototxt /home/cad/disk/linux/cbir/model/RSI-CB128/AlexNet_iter_100000.caffemodel /home/cad/disk/linux/cbir/model/RSI-CB128/mean.binaryproto /home/cad/disk/linux/cbir/class_128.txt /home/cad/disk/linux/cbir/RSI-CB128/filename.txt > cla_res.txt 2>&1 &

nohup  ./build/examples/cpp_classification/classification.bin /home/cad/disk/linux/cbir/model/RSI-CB128/GoogleNet_deploy.prototxt /home/cad/disk/linux/cbir/model/RSI-CB128/GoogleNet_iter_100000.caffemodel /home/cad/disk/linux/cbir/model/RSI-CB128/mean.binaryproto /home/cad/disk/linux/cbir/class_128.txt /home/cad/disk/linux/cbir/RSI-CB128/filename.txt > cla_res.txt 2>&1 &

#extracting features 
./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB128/AlexNet_iter_100000.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB128/class_val_alex.prototxt fc7 feat_extra 36707 /home/cad/disk/linux/cbir/feat_extra/rs_simi_alex_10.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB128/VGG16_iter_400.caffemodel  /home/cad/disk/linux/cbir/feat_extra/RSI-CB128/class_val_vgg16.prototxt fc7 feat_extra 36707 /home/cad/disk/linux/cbir/feat_extra/RSI-CB128/rs_simi_vgg16.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB256/VGG_ILSVRC_16_layers.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB128/class_val_vgg16.prototxt fc6 feat_extra 9233 /home/cad/disk/linux/cbir/feat_extra/RSI-CB128/rs_simi_vgg16_pretrain.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB128/AlexNet_hash_48.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB128/class_val_alex_hash.prototxt fc8_hash_encode feat_extra 36707 /home/cad/disk/linux/cbir/feat_extra/rs_simi_alex_hash48_10.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB128/VGG16_hash_128.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB128/class_val_vgg16_hash.prototxt fc8_hash_encode feat_extra 36707 /home/cad/disk/linux/cbir/feat_extra/RSI-CB128/rs_simi_vgg16_hash128.txt GPU 0

#test
nohup ./build/tools/caffe test --model=/home/cad/disk/linux/cbir/model/RSI-CB128/AlexNet_hash.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB128/AlexNet_hash_48.caffemodel -gpu 0 -iterations 12 > output_alex_test.log 2>&1 &

nohup ./build/tools/caffe test --model=/home/cad/disk/linux/cbir/model/RSI-CB128/VGG16_hash.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB128/VGG16_hash_128.caffemodel -gpu 0 -iterations 125 > output_vgg16_test.log 2>&1 &

nohup ./build/tools/caffe test --model=/home/cad/disk/linux/cbir/model/RSI-CB128/GoogleNet_train.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB128/GoogleNet_iter_100000.caffemodel -gpu 0 -iterations 125 > output_googlenet_test.log 2>&1 &

#finetune for hash codes 
nohup ./build/tools/caffe train --solver=/home/cad/disk/linux/cbir/model/RSI-CB128/solver_AlexNet.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB128/AlexNet_iter_100000.caffemodel > output.log 2>&1 &

nohup ./build/tools/caffe train --solver=/home/cad/disk/linux/cbir/model/RSI-CB128/solver_VGG16.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB128/VGG16_iter_400.caffemodel > output.log 2>&1 &

nohup ./build/tools/caffe train --solver=/home/cad/disk/linux/cbir/model/RSI-CB128/solver_GoogleNet.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB128/GoogleNet_iter_100000.caffemodel > output.log 2>&1 &

#common-12
#classification
nohup  ./build/examples/cpp_classification/classification.bin /home/cad/disk/linux/cbir/model/common-12/VGG16_deploy.prototxt /home/cad/disk/linux/cbir/model/common-12/VGG16_hash_128.caffemodel /home/cad/disk/linux/cbir/model/RSI-CB256/mean.binaryproto /home/cad/disk/linux/cbir/class_common12.txt /home/cad/disk/linux/cbir/common-12/filename_test_UCM.txt > cla_res.txt 2>&1 &

#finetune for hash codes
nohup ./build/tools/caffe train --solver=/home/cad/disk/linux/cbir/model/common-12/solver_VGG16.prototxt -weights /home/cad/disk/linux/cbir/model/common-12/VGG16_hash_128.caffemodel > output.log 2>&1 &

#extracting features
./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/common-12/VGG16_hash_128.caffemodel /home/cad/disk/linux/cbir/feat_extra/common-12/class_val_vgg16_hash.prototxt fc6 feat_extra 9233 /home/cad/disk/linux/cbir/feat_extra/common-12/rs_simi_vgg16_hash128.txt GPU 0

./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB256/VGG_ILSVRC_16_layers.caffemodel /home/cad/disk/linux/cbir/feat_extra/common-12/class_val_vgg16.prototxt fc6 feat_extra 9233 /home/cad/disk/linux/cbir/feat_extra/common-12/rs_simi_vgg16_pretrain.txt GPU 0
