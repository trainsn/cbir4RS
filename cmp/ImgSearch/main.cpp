#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;
const int DIM = 4096;
const int DIM_HASH = 128;
const int EVAL_NUM = 5;
const int coarse = 1001;
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

struct CmpSimi1{ //from small to big
    bool operator()(const SimiStruct& first, const SimiStruct& second) const{
        if (first.simi < second.simi)
            return true;
        return false;
    }
};

float getDistance(const std::vector<float>& lhs, const std::vector<float>& rhs);
float getHamming(const std::vector<int>& lhs, const std::vector<int>& rhs);
float getMold(const std::vector<float>& vec);
float getSimilarity(const std::vector<float>& lhs, const std::vector<float>& rhs);

int main()
{

    freopen("cnn_simi.txt", "w", stdout);
    string file = "/home/cad/disk/linux/cbir/common-12/filename.txt";
    fstream fin(file.c_str());
    string imgfilename;
    std::vector<string> imgfilenames;
    std::vector<int> truths;

    int imgcount = 0;

    while (getline(fin, imgfilename)){
        int pos = imgfilename.find(" ");
        int truth;
        if (pos != -1)
            truth = atoi(imgfilename.substr(pos+1, 5).c_str());
        else
            truth = 0;
        imgfilename = imgfilename.substr(0,pos);
        imgfilenames.push_back(imgfilename);
        truths.push_back(truth);

        imgcount++;
    }

    std::vector< std::vector <float> > img_features;
    img_features.resize(imgcount, std::vector<float>(DIM));
    std::vector< std::vector <int> > img_features_hash;
    img_features_hash.resize(imgcount, std::vector<int>(DIM_HASH));
    freopen("/home/cad/disk/linux/cbir/feat_extra/common-12/img_feature_fc7.txt", "r", stdin);
    for (int idx = 0; idx < imgcount; idx++)
    {
        for (int i = 0; i < DIM ;i++)
        {
            cin >> img_features[idx][i];
            //cout << img_features[idx][i] << " " ;
        }
        //cout << endl;
    }

    freopen("/home/cad/disk/linux/cbir/feat_extra/common-12/img_feature_fc8hash.txt", "r", stdin);
    for (int idx = 0; idx < imgcount; idx++)
    {
        for (int i = 0; i < DIM_HASH ;i++)
        {
            float tmp;
            cin >> tmp;
            img_features_hash[idx][i] = (int)(tmp+0.5);
            //cout << img_features_hash[idx][i] << " " ;
        }
        //cout << endl;
    }

    int topk[5] = {5, 10, 50, 100, 200};
    float map[5] = {0};
    std::vector<SimiStruct> simires;
    for (int i = 0; i < 1200; i++){
        int acc = 0;
        simires.clear();
        std::cout <<  imgfilenames[i] << std::endl;
        for (int j = 0; j < imgcount; j++){
            SimiStruct tempSimi;
            tempSimi.idx = j;
            tempSimi.simi = getHamming(img_features_hash[i], img_features_hash[j]);
            simires.push_back(tempSimi);
        }

        std::sort(simires.begin(), simires.end(), CmpSimi1());
        simires.resize(coarse);

        for (int j = 0; j <= coarse; j++){
            simires[j].simi = getSimilarity(img_features[i], img_features[simires[j].idx]);
        }
        std::sort(simires.begin(), simires.end(), CmpSimi());

        for (size_t j = 0; j < EVAL_NUM; j++)
        {
            acc = 0;
            for (size_t k = 1; k <= topk[j]; k++)
            {
               if (!j){
                  std::cout << "  simi" << k << " " << imgfilenames[simires[k].idx] << " " << simires[k].simi << std::endl;
                  //for (int l = 0; l < DIM; l++)
                  //  cout << img_features[simires[k].idx][l] <<  " " ;
                  //cout << endl;
               }
               if (truths[simires[k].idx] == truths[i])
                   acc++;
            }
            map[j]+=acc;
            std::cout << "acc: " << topk[j] << " " << (float)acc/topk[j] << std::endl;
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < EVAL_NUM; i++)
      std::cout << "map" << topk[i] << " " << map[i]/(topk[i]*1200) << std::endl;
    return 0;
}

float getDistance(const std::vector<float>& lhs, const std::vector<float>& rhs){
    int n = lhs.size();
    float tmp = 0.0;
    for (int i = 0; i < n; i++)
        tmp += (lhs[i]-rhs[i]) * (lhs[i]-rhs[i]);
    return sqrt(tmp);
}

float getHamming(const std::vector<int>& lhs, const std::vector<int>& rhs){
    int n = lhs.size();
    int tmp = 0;
    for (int i = 0; i < n; i++)
        tmp += lhs[i] ^ rhs[i];
    return tmp;
}

float getMold(const std::vector<float>& vec){   //求向量的模长
    int n = vec.size();
    float sum = 0.0;
    for (int i = 0; i < n; ++i)
        sum += vec[i] * vec[i];
    return sqrt(sum);
}

//求两个向量的余弦相似度
float getSimilarity(const std::vector<float>& lhs, const std::vector<float>& rhs){
    int n = lhs.size();
    float tmp = 0.0;  //内积
    for (int i = 0; i < n; ++i)
        tmp += lhs[i] * rhs[i];
    return tmp / (getMold(lhs)*getMold(rhs));
}
