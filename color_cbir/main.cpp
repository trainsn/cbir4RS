#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include "cv.h"
#include "highgui.h"

using namespace std;
using namespace cv;
const int SCALE = 4;
const int SIZE = SCALE*SCALE*SCALE*SCALE;
const int img_num = 24747;
const int EVAL_NUM = 5;

struct SimiStruct{
    int idx;
    float simi;
};

struct CmpSimi{ //from big to small
    bool operator()(const SimiStruct& first, const SimiStruct& second) const{
        if (first.simi > second.simi)
            return true;
        return false;
    }
};

float getSimilarity(const std::vector<float>& lhs, const std::vector<float>& rhs);

int main()
{
    Mat img,hsvImg;
    char key;
    string file = "/home/cad/disk/linux/cbir/RSI-CB256/filename.txt";
    fstream fin(file.c_str());
    string imgfilename;
    std::vector<string> imgfilenames;
    std::vector<int> truths;
    freopen("img_feature.txt", "w", stdout);

    std::vector< std::vector <float> > img_features;
    img_features.resize(img_num, std::vector<float>(SIZE));
    int imgcount = 0;

    while (getline(fin, imgfilename)){
        int pos = imgfilename.find(" ");
        int truth;
        if (pos != -1)
            truth = atoi(imgfilename.substr(pos+1, 5).c_str());
        else
            truth = 0;
        imgfilename = imgfilename.substr(0,pos);
        //std::cout << imgfilename << std::endl;
        img = imread(imgfilename.c_str());
        imgfilenames.push_back(imgfilename);
        truths.push_back(truth);

        cvtColor(img, hsvImg, CV_BGR2HSV);
        uchar* hsvDataPtr = hsvImg.data;
        int hist[SIZE] = {0};

        //exatracting featrues
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                const int hi = i*img.cols*3 + j*3;
                float tempH = (float)hsvDataPtr[hi] * 2;
                float tempS = (float)hsvDataPtr[hi+1] / 255.0;
                float tempV = (float)hsvDataPtr[hi+2] / 255.0;
                //cout << tempH << " " << tempS << " " << tempV << endl;
                int H, S, V, L;
                if (tempH <= 15 || tempH > 345 )
                    H = 0;
                else if (tempH <= 25)
                    H = 1;
                else if (tempH <= 45)
                    H = 2;
                else if (tempH <= 50)
                    H = 3;
                else if (tempH <= 80)
                    H = 4;
                else if (tempH <= 108)
                    H = 5;
                else if (tempH <= 140)
                    H = 6;
                else if (tempH <= 165)
                    H = 7;
                else if (tempH <= 190)
                    H = 8;
                else if (tempH <= 220)
                    H = 9;
                else if (tempH <= 255)
                    H = 10;
                else if (tempH <= 275)
                    H = 11;
                else if (tempH <= 290)
                    H = 12;
                else if (tempH <= 316)
                    H = 13;
                else if (tempH <= 330)
                    H = 14;
                else if (tempH <= 345)
                    H = 15;

                if (tempS <= 0.15)
                    S = 0;
                else if (tempS <= 0.4)
                    S = 1;
                else if (tempS <= 0.75)
                    S = 2;
                else
                    S = 3;

                if (tempV <= 0.15)
                    V = 0;
                else if (tempV <= 0.4)
                    V = 1;
                else if (tempV <= 0.75)
                    V = 2;
                else
                    V = 3;
                L = H * SCALE * SCALE + S * SCALE + V;
                hist[L]++;
            }
        }
        for (int i = 0; i < SIZE; i++ ){
            //cout << hist[i] << " ";
            img_features[imgcount][i] = hist[i] / 65536.0;
        }
        imgcount++;
    }

    //search
    int topk[5] = {5, 10, 50, 100, 200};
    float map[5] = {0};
    std::vector<SimiStruct> simires;
    for (int i = 0; i < img_num; i++){
        int acc = 0;
        simires.clear();
        std::cout <<  imgfilenames[i] << std::endl;
        for (int j = 0; j < img_num; j++){
            SimiStruct tempSimi;
            tempSimi.idx = j;
            tempSimi.simi = getSimilarity(img_features[i], img_features[j]);
            simires.push_back(tempSimi);
        }

        std::sort(simires.begin(), simires.end(), CmpSimi());

        for (size_t j = 0; j < EVAL_NUM; j++)
        {
            acc = 0;
            for (size_t k = 1; k <= topk[j]; k++)
            {
               if (!j)
                  std::cout << "  simi" << k << " " << imgfilenames[simires[k].idx] << " " << simires[k].simi << std::endl;
               if (truths[simires[k].idx] == truths[i])
                   acc++;
            }
            map[j]+=acc;
            std::cout << "acc: " << topk[j] << " " << (float)acc/topk[j] << std::endl;
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < EVAL_NUM; i++)
      std::cout << "map" << topk[i] << " " << map[i]/(topk[i]*img_num) << std::endl;
    return 0;
}

float getSimilarity(const std::vector<float>& lhs, const std::vector<float>& rhs){
    int n = lhs.size();
    assert(n == rhs.size());
    float simi = 0;
    for (int i = 0; i < n; i++)
        simi += min(lhs[i], rhs[i]);
    return simi;
}
