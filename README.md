# Research on Image Retrieval Method Based on Feature Fusion and Deep Learning
Created by Shi Neng from Zhejiang University.

### Introduction 
This work is for Zhejiang University Geographic Information Science. We  uses the deep learning framework Caffe to train the CNN and use CNN to extract features. A large-scale remote sensing dataset RSI-CB is used as a training sample, and the current most popular networks in the industry including AlexNet, VGGNet, and GoogLeNet are used for training. The similarity judgment is performed using the high-dimensional vectors provided by the last hidden layer of the network. At the same time, we fine-tuned the network structure, added latent layers to represent potential concepts, learned compact binary codes, and achieved rough judgments of remote sensing retrieval through the Hamming distance. 

### Files Introduction
- caffe - caffe forked from https://github.com/upcAutoLang/Blog/issues/1
- model - prototxt and sovler files for caffemodel
- feat_extra - prototxt files used for feature extracting
- cmp - traditional remote sensing image retreivial methods 
    - bovw - Bag of visual words, forked from https://github.com/shackenberg/Minimal-Bag-of-Visual-Words-Image-Classifier
    - color_cbir - RGb->HSV and performs non-equal interval quantization,  calculate the L histogram as a color feature
    - glcm - Gray-level Co-occurrence Matrix, forked from https://github.com/upcAutoLang/GLCM-OpenCV
- class_xx.txt - class name for each dataset
- train_command.txt - specific train comands 

### Extracting features and Image Serching 
We experiment on three datasets, RSI-CB128, RSI-CB256 and UC-Merced. In the path `feat_extra`, there are three subdirs. You can use the Caffe tool  `extract_features.bin`, which is already modified by us to fit our task. The comand is like this:

    ./build/tools/extract_features.bin /home/cad/disk/linux/cbir/model/RSI-CB128/AlexNet_iter_100000.caffemodel /home/cad/disk/linux/cbir/feat_extra/RSI-CB128/class_val_alex.prototxt fc7 feat_extra 36707 /home/cad/disk/linux/cbir/feat_extra/rs_simi_alex_10.txt GPU 0
    
The results will be saved in `rs_simi_xxx.txt`.

### Train your own model for Image Searching 
The caffe prototxt file are stored in the path `feat_extra`, there are three subdirs which represent three datasets.  There are two types of train_val prototxt files. The ones ends with "hash" are for the caffemodel with latenthash layer, the others are for the ordinary caffemodel. You can finetune the caffemodel with latent hash layer by the command:

    nohup ./build/tools/caffe test --model=/home/cad/disk/linux/cbir/model/RSI-CB128/AlexNet_hash.prototxt -weights /home/cad/disk/linux/cbir/model/RSI-CB128/AlexNet_hash_48.caffemodel -gpu 0 -iterations 12 > output_alex_test.log 2>&1 &
    
The result caffemodel will be temporarily saved in `caffe`.

