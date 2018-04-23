import gzip
import pickle
import numpy as np
import matplotlib
from cycler import cycler
import urllib
import os
import sys
import pdb
from MulticoreTSNE import MulticoreTSNE as TSNE

matplotlib.use('Agg')
import matplotlib.pyplot as plt

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--n_jobs", help='Number of threads', default=1, type=int)
parser.add_argument("--n_objects", help='How many objects to use from MNIST', default=-1, type=int)
parser.add_argument("--n_components", help='T-SNE dimensionality', default=2, type=int)
args = parser.parse_args()

def get_mnist():

#    if not os.path.exists('mnist.pkl.gz'):
#        print('downloading MNIST')
#        if sys.version_info >= (3, 0):
#            urllib.request.urlretrieve(
#            'http://deeplearning.net/data/mnist/mnist.pkl.gz', 'mnist.pkl.gz')
#        else:
#            urllib.urlretrieve(
#                        'http://deeplearning.net/data/mnist/mnist.pkl.gz', 'mnist.pkl.gz')
#        print('downloaded')
#
#    f = gzip.open("mnist.pkl.gz", "rb")
#    if sys.version_info >= (3, 0):
#        train, val, test = pickle.load(f, encoding='latin1')
#    else:
#        train, val, test = pickle.load(f)
#    f.close()
#
    n = 9233
    dim = 4096
    f =  open('/home/cad/disk/linux/cbir/feat_extra/common-12/img_feature_fc7.txt'  ,'r')
    mnist = np.zeros((n, dim))
    i = 0
    for line in f.readlines():
        for j in range(dim):
            #mnist[i][j] = round(float(line.split()[j]))
            mnist[i][j] = float(line.split()[j])
        i = i+1
        if args.n_objects != -1 and i >= args.n_objects:
            break
        if (i % 10 == 0):
            print("finish reading " + str(i) + " features")            
    f =  open('/home/cad/disk/linux/cbir/common-12/filename.txt'  ,'r')
    classes = np.zeros(n)
    i = 0
    for line in f.readlines():
        classes[i] = int(line.split()[1])
        i = i+1
#    # Get all data in one array
#    _train = np.asarray(train[0], dtype=np.float64)
#    _val = np.asarray(val[0], dtype=np.float64)
#    _test = np.asarray(test[0], dtype=np.float64)
#    mnist = np.vstack((_train, _val, _test))
#
#    # Also the classes, for labels in the plot later
#    classes = np.hstack((train[1], val[1], test[1]))

    return mnist, classes

def plot(Y, classes, name):
    #pdb.set_trace()
    digits = set(classes)
    fig = plt.figure()
    colormap = plt.cm.spectral
    plt.gca().set_prop_cycle(
        cycler('color', [colormap(i) for i in np.linspace(0, 0.9, 12)]))
    ax = fig.add_subplot(111)
    labels = ['airplane', 'runway', 'buildings', 'intersection', 'forest', 'agricultural', 'freeway', 'harbor', 'parkinglot', 'mediumresidential', 'river', 'storagetanks']
    #labels= []
    for d in digits:
        idx = classes == d
        if Y.shape[1] == 1:
            ax.plot(Y[idx], np.random.randn(Y[idx].shape[0]), 'o')
        else:
            ax.plot(Y[idx, 0], Y[idx, 1], 'o')
        
        #labels.append(int(d))
    #ax.legend(labels, numpoints=1, fancybox=True)
    fig.savefig(name)
    if Y.shape[1] > 2:
        print('Warning! Plot shows only first two components!')


################################################################

mnist, classes = get_mnist()

if args.n_objects != -1:
    mnist = mnist[:args.n_objects]
    classes = classes[:args.n_objects]

tsne = TSNE(n_jobs=int(args.n_jobs), verbose=1, n_components=args.n_components, random_state=660, n_iter = 5000)
mnist_tsne = tsne.fit_transform(mnist)

filename = 'mnist_tsne_n_comp=%d.png' % args.n_components
plot(mnist_tsne, classes, filename)
print('Plot saved to %s' % filename)