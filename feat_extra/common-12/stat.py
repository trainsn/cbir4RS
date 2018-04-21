import numpy as np

f = open('rs_simi_vgg16_level.txt'  ,'r')
idx = 0
acc = np.zeros(5)
for line in f.readlines():
    idx = idx + 1
    if (idx % 12 == 7):
        acc[0] = acc[0] + float(line.split()[2])
    if (idx % 12 == 8):
        acc[1] = acc[1] + float(line.split()[2])
    if (idx % 12 == 9):
        acc[2] = acc[2] + float(line.split()[2])
    if (idx % 12 == 10):
        acc[3] = acc[3] + float(line.split()[2])
    if (idx % 12 == 11):
        acc[4] = acc[4] + float(line.split()[2])
    if (idx % 1200 == 0):
        for i in range(5):
            print(acc[i]/100)   
        print()
        acc = np.zeros(5)
    