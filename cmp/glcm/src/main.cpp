/*=================================================================
 * Calculate GLCM(Gray-level Co-occurrence Matrix) By OpenCV.
 *
 * Copyright (C) 2017 Chandler Geng. All rights reserved.
 *
 *     This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *     You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place, Suite 330, Boston, MA 02111-1307 USA
===================================================================
*/

/*=================================================
 * Version:
 * v1.0: 完成了单个GLCM的计算；
 * v1.1: 完成了矩阵归一化、图像纹理特征计算的功能；
 * v1.2: 完成了矩阵边界部分的计算；
 * v1.3: 完成了获取单一通道、灰度图量化为4/8/16等级的功能；
 * v1.4: 完成了整幅图像纹理特征的计算；
 * v1.5: 完成了对纹理特征图像的调整功能，并显示；
 * v1.7: 添加了计算整幅图像的特征值函数；
===================================================
 */

#include "glcm.h"
#include <fstream>

// 示例程序
// Example Program
int main()
{
    char key;
    Mat img;
    GLCM glcm;
    TextureEValues EValues;

    // 程序运行时间统计变量
    // the Time Statistical Variable of Program Running Time
    double time;
    double start;

    // 纹理特征值矩阵
    // the Matrixs of Texture Features
    Mat imgEnergy, imgContrast, imgHomogenity, imgEntropy;

    // 读取图像
    // Read a Image
    string file = "/home/cad/disk/linux/cbir/RSI-CB128/filename.txt";
    fstream fin(file.c_str());
    string imgfilename;
    freopen("img_feature.txt", "w", stdout);

    while (getline(fin, imgfilename)){
        int pos = imgfilename.find(" ");
        int truth;
        if (pos != -1)
            truth = atoi(imgfilename.substr(pos+1, 5).c_str());
        else
            truth = 0;
        imgfilename = imgfilename.substr(0,pos);
        std::cout << imgfilename << std::endl;
        //img = imread("/home/cad/disk/linux/cbir/RSI-CB256/construction_land/city_building/city_building(1).bmp");
        img = imread(imgfilename);

        Mat dstChannel;
        glcm.getOneChannel(img, dstChannel, CHANNEL_B);

        // 灰度量化，并统计运算时间
        // Magnitude Gray Image, and calculate program running time
        start = static_cast<double>(getTickCount());
        glcm.GrayMagnitude(dstChannel, dstChannel, GRAY_8);
        time = ((double)getTickCount() - start) / getTickFrequency() * 1000;
        //cout << "Time of Magnitude Gray Image: " << time << "ms" <<endl<<endl;

        // 计算整幅图像的纹理特征值图像，并统计运算时间
        // Calculate Texture Features of the whole Image, and calculate program running time
        start = static_cast<double>(getTickCount());
        glcm.CalcuTextureImages(dstChannel, imgEnergy, imgContrast, imgHomogenity, imgEntropy, 5, GRAY_8, true);
        time = ((double)getTickCount() - start) / getTickFrequency() * 1000;
        //cout << "Time of Generate the whole Image's Calculate Texture Features Image: " << time << "ms" << endl<<endl;

        start = static_cast<double>(getTickCount());
        glcm.CalcuTextureEValue(dstChannel, EValues, 5, GRAY_8);
        time = ((double)getTickCount() - start) / getTickFrequency() * 1000;
        //cout << "Time of Calculate Texture Features of the whole Image: " << time << "ms" << endl<<endl;

        cout <<EValues.contrastMean<<" ";
        cout <<EValues.energyMean<<" ";
        cout<<EValues.entropyMean<<" ";
        cout<<EValues.homogenityMean<<" ";
        cout<<EValues.contrastStd<<" ";
        cout<<EValues.energyStd<<" ";
        cout<<EValues.entropyStd<<" ";
        cout<<EValues.homogenityStd<<endl;
    }


    key = (char) cvWaitKey(0);

    return 0;
}
