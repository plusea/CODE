import numpy as np 
import csv
import pickle

path = "/Users/adamstark/Documents/Code/The Gloves/Glove Data Analysis/data/txt/Adam_Yellow_Workshop_Gloves/"


#======================================================================
def importData(filename):
    #The next step is to open and create the reader object:
    my_csv = csv.reader(open(filename))

    data = []

    f = open(filename, 'rb') # opens the csv file
    try:
        reader = csv.reader(f)  # creates the reader object
        for row in reader:      # iterates the rows of the file in orders
            data.append(row)       # prints each row
    finally:
        f.close()           # closing

    out = np.zeros((len(data),len(data[0])))

    for i in range(len(data)):
        for j in range(len(data[0])):
            out[i][j] = np.float(data[i][j])

    return np.array(out)


#======================================================================

fist = importData(path + "fistR.txt")
openHand = importData(path + "openHandR.txt")
puppetHand = importData(path + "puppetHandR.txt")
oneFingerPoint = importData(path + "oneFingerPointR.txt")
twoFingerPoint = importData(path + "twoFingerPointR.txt")
threeFingerPoint = importData(path + "threeFingerPointR.txt")
thumbsUp = importData(path + "thumbsUpR.txt")


#print openHand.shape
#print openHand

X = {}

# store the metadata
X['gloves'] = "Yellow Workshop Gloves"
X['hand'] = "Right Hand"
X['user'] = "Adam Stark"
X['date'] = "18th April 2013"


# store the data
obs = fist
obs = np.vstack((obs,openHand))
obs = np.vstack((obs,puppetHand))
obs = np.vstack((obs,oneFingerPoint))
obs = np.vstack((obs,twoFingerPoint))
obs = np.vstack((obs,threeFingerPoint))
obs = np.vstack((obs,thumbsUp))

#print obs.shape
#print obs

classes = np.ones(fist.shape[0])*0
classes = np.append(classes,np.ones(openHand.shape[0])*1)
classes = np.append(classes,np.ones(puppetHand.shape[0])*2)
classes = np.append(classes,np.ones(oneFingerPoint.shape[0])*3)
classes = np.append(classes,np.ones(twoFingerPoint.shape[0])*4)
classes = np.append(classes,np.ones(threeFingerPoint.shape[0])*5)
classes = np.append(classes,np.ones(thumbsUp.shape[0])*6)
classes = np.array(classes,'int')

#print classes.shape[0]
#print classes

X['observations'] = obs
X['classifications'] = classes
X['classes'] = ['fist','openHand','puppetHand','oneFingerPoint','twoFingerPoint','threeFingerPoint','thumbsUp']

pickle.dump(X,open('adam_yellowWorkshop.gloveDataset','wb'))
