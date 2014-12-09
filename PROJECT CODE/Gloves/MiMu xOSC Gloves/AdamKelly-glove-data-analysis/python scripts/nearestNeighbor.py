import pickle
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from pylab import *
from mpl_toolkits.mplot3d import Axes3D


def NN_test(dataset,sensors,numTraining=-1):

	"""
	if (numSensors != 2):
		data_X = dataset['observations'][:,:numSensors]
	else:
		data_X = np.vstack((dataset['observations'][:,3],dataset['observations'][:,3])).T
	"""
	data_X = dataset['observations'][:,sensors[0]]


	for i in range(1,len(sensors)):
		data_X = np.vstack((data_X,dataset['observations'][:,sensors[i]]))

	data_X = data_X.T

	#print data_X

	data_Y = dataset['classifications']

	np.random.seed(0)
	indices = np.random.permutation(data_X.shape[0])

	if (numTraining < 1):
		v = np.int(np.floor(data_X.shape[0]/2.))
	else:
		v = data_X.shape[0]-numTraining

	data_X_train = data_X[indices[:-1*v]]
	data_Y_train = data_Y[indices[:-1*v]]
	data_X_test = data_X[indices[-1*v:]]
	data_Y_test = data_Y[indices[-1*v:]]

	knn = KNeighborsClassifier()

	knn.fit(data_X_train, data_Y_train)

	predictions = knn.predict(data_X_test)

	diff = abs(data_Y_test - predictions)
	perc = ((1-(diff[diff != 0].size / float(diff.size)))*100.)
	print len(sensors), "sensors - ",sensors,": ", "%.2f" % ((1-(diff[diff != 0].size / float(diff.size)))*100.),"% from ",predictions.size,"tests"

	if (True):
		if (len(sensors) == 2):
			xlim(-0.05,1.05)
			ylim(-0.05,1.05)
			title("user: " + dataset['user'] + "    sensors: " + str(sensors) + "     score: " + ("%.2f" % perc) + "%")
			scatter(data_X_test[:,0][data_Y_test == 0],data_X_test[:,1][data_Y_test == 0],c='r')
			hold(True)
			scatter(data_X_test[:,0][data_Y_test == 1],data_X_test[:,1][data_Y_test == 1],c='b')
			hold(True)
			scatter(data_X_test[:,0][data_Y_test == 2],data_X_test[:,1][data_Y_test == 2],c='g')
			hold(True)
			scatter(data_X_test[:,0][data_Y_test == 3],data_X_test[:,1][data_Y_test == 3],c='c')
			hold(True)
			scatter(data_X_test[:,0][data_Y_test == 4],data_X_test[:,1][data_Y_test == 4],c='m')
			hold(True)
			scatter(data_X_test[:,0][data_Y_test == 5],data_X_test[:,1][data_Y_test == 5],c='y')
			hold(True)
			scatter(data_X_test[:,0][data_Y_test == 6],data_X_test[:,1][data_Y_test == 6],c='k')
			show()

		if (len(sensors) == 3):
			#title("sensors: " + str(sensors) + "     score: " + ("%.2f" % perc) + "%")
			fig=figure()

			ax = Axes3D(fig)
			#ax.title("hi")

			pos = 0
			ax.scatter(data_X_test[:,0][data_Y_test == pos], data_X_test[:,1][data_Y_test == pos],data_X_test[:,2][data_Y_test == pos],c='r')
			hold(True)
			pos = 1
			ax.scatter(data_X_test[:,0][data_Y_test == pos], data_X_test[:,1][data_Y_test == pos],data_X_test[:,2][data_Y_test == pos],c='b')
			hold(True)
			pos = 2
			ax.scatter(data_X_test[:,0][data_Y_test == pos], data_X_test[:,1][data_Y_test == pos],data_X_test[:,2][data_Y_test == pos],c='g')
			hold(True)
			pos = 3
			ax.scatter(data_X_test[:,0][data_Y_test == pos], data_X_test[:,1][data_Y_test == pos],data_X_test[:,2][data_Y_test == pos],c='c')
			hold(True)
			pos = 4
			ax.scatter(data_X_test[:,0][data_Y_test == pos], data_X_test[:,1][data_Y_test == pos],data_X_test[:,2][data_Y_test == pos],c='m')
			hold(True)
			pos = 5
			ax.scatter(data_X_test[:,0][data_Y_test == pos], data_X_test[:,1][data_Y_test == pos],data_X_test[:,2][data_Y_test == pos],c='y')
			hold(True)
			pos = 6
			ax.scatter(data_X_test[:,0][data_Y_test == pos], data_X_test[:,1][data_Y_test == pos],data_X_test[:,2][data_Y_test == pos],c='k')
			show()

# 'fist' - red
# 'openHand' - blue
# 'puppetHand' - green
# 'oneFingerPoint' - cyan
# 'twoFingerPoint' - magenta
# 'threeFingerPoint' - yellow
# 'thumbsUp' - black

# set the path
path = "/Users/adamstark/Documents/Code/The Gloves/Glove Data Analysis/data/python_pickles/"

adamData = pickle.load(open(path + "adam_yellowWorkshop.gloveDataset"))
kellyData = pickle.load(open(path + "kelly_yellowWorkshop.gloveDataset"))

postures = adamData['classes']

numSensors = 4
numTrainingExamples = 50

print " "
print numTrainingExamples,"training examples"

print "Adam:"
NN_test(adamData,[0,1,2,3],numTrainingExamples)
NN_test(adamData,[0,1,2],numTrainingExamples)
NN_test(adamData,[0,1,3],numTrainingExamples)
NN_test(adamData,[0,2,3],numTrainingExamples)
NN_test(adamData,[1,2,3],numTrainingExamples)
NN_test(adamData,[0,1],numTrainingExamples)
NN_test(adamData,[0,2],numTrainingExamples)
NN_test(adamData,[0,3],numTrainingExamples)
NN_test(adamData,[1,2],numTrainingExamples)
NN_test(adamData,[1,3],numTrainingExamples)
NN_test(adamData,[2,3],numTrainingExamples)

print "----"
print "Kelly:"
NN_test(kellyData,[0,1,2,3],numTrainingExamples)
NN_test(kellyData,[0,1,2],numTrainingExamples)
NN_test(kellyData,[0,1,3],numTrainingExamples)
NN_test(kellyData,[0,2,3],numTrainingExamples)
NN_test(kellyData,[1,2,3],numTrainingExamples)
NN_test(kellyData,[0,1],numTrainingExamples)
NN_test(kellyData,[0,2],numTrainingExamples)
NN_test(kellyData,[0,3],numTrainingExamples)
NN_test(kellyData,[1,2],numTrainingExamples)
NN_test(kellyData,[1,3],numTrainingExamples)
NN_test(kellyData,[2,3],numTrainingExamples)
