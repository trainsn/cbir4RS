#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;
const int img_num = 36707;
const int DIM = 128;
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

struct CmpSimi1{ //from small to big
    bool operator()(const SimiStruct& first, const SimiStruct& second) const{
        if (first.simi < second.simi)
            return true;
        return false;
    }
};

float getDistance(const std::vector<float>& lhs, const std::vector<float>& rhs);

int main()
{
    freopen("/home/cad/disk/linux/cbir/RSI-CB128/img_feature.txt", "r", stdin);
    freopen("bovw_simi.txt", "w", stdout);
    string file = "/home/cad/disk/linux/cbir/RSI-CB128/filename.txt";
    fstream fin(file.c_str());
    string imgfilename;
    std::vector<string> imgfilenames;
    std::vector<int> truths;

    std::vector< std::vector <float> > img_features;
    img_features.resize(img_num, std::vector<float>(DIM));
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

        int label;
        cin >> label;
        for (int i = 0; i < DIM ;i++)
        {
            cin >> img_features[imgcount][i];
            //cout << img_features[imgcount][i] << " " ;
        }
        //cout << endl;
        imgcount++;
    }

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
            tempSimi.simi = getDistance(img_features[i], img_features[j]);
            simires.push_back(tempSimi);
        }

        std::sort(simires.begin(), simires.end(), CmpSimi1());

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
      std::cout << "map" << topk[i] << " " << map[i]/(topk[i]*img_num) << std::endl;
    return 0;
}

float getDistance(const std::vector<float>& lhs, const std::vector<float>& rhs){
    int n = lhs.size();
    float tmp = 0.0;
    for (int i = 0; i < n; i++)
        tmp += (lhs[i]-rhs[i]) * (lhs[i]-rhs[i]);
    return sqrt(tmp);
}
