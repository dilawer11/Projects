#Lists Of Lists for CSV Data
import csv
with open('winequality-red.csv','r') as f:
    wines = list(csv.reader(f, delimiter=';'))
    print(wines[:3])
qualities = [float(item[-1]) for item in wines[1:]]

#Numpy 2-Dimensional Arrays
import numpy as np
print(sum(qualities)/len(qualities))
wines = np.array(wines[1:], dtype=np.float)
print(wines)
print(wines.shape)

#Alternative NumPy Array Creation Methods

empty_array = np.zeros((3,4))
print(empty_array)
print(np.random.rand(3,4))

#Using NumPy To Read In Files
wines = np.genfromtxt("winequality-red.csv", delimiter=";", skip_header=1)
print(wines)

#Indexing NumPy Arrays
print(wines[2,3])

#Slicing NumPy Arrays
print(wines[0:3,3])
print(wines[:3,3])
print(wines[:,3])
print(wines[3,:])
print(wines[:,:])

#Assigning Values to NumPy Arrays

#wines[1,5] = 10
#wines[:,10] = 50
print(wines)

#1-Dimensional Numpy Arrays
third_wine = wines[3,:]
print(third_wine)
print(third_wine[1])
print(np.random.rand(3))

#N-Dimensional NumPy Arrays

year_one = [
    [500,505,490],
    [810,450,678],
    [234,897,430],
    [560,1023,640]
]
earnings = [
            [
                [500,505,490],
                [810,450,678],
                [234,897,430],
                [560,1023,640]
            ],
            [
                [600,605,490],
                [345,900,1000],
                [780,730,710],
                [670,540,324]
            ]
          ]
earnings = np.array(earnings)
print(earnings[0,0,0])
print(earnings.shape)
print(earnings[:,0,:])

#NumPy Data Types
print(wines.dtype)

#Converting Data Types
print(wines.astype(int))
int_wines = wines.astype(int)
print(int_wines.dtype.name)
print(wines.astype(np.int32))

#NumPy Array Operations
#Single Array Math
print(wines[:,11] + 10)
#wines[:,11] += 10
print(wines[:,11])
print(wines[:,11] * 2)

#Multiple Array Math
print(wines[:,11] + wines[:,11])
print(wines[:,10] * wines[:,11])

#Broadcasting
#print(wines * np.array([1,2]))
array_one = np.array(
        [
            [1,2],
            [3,4]
        ] 
)
array_two = np.array([4,5])
rand_array = np.random.rand(12)
print(wines+rand_array)
print(array_one + array_two)

#NumPy Array Methods
print(wines[:11].sum())
print(wines.sum(axis=0))
print(wines.sum(axis=0).shape)
print(wines.sum(axis=1))

#NumPy Array Comparisons
print(wines[:,11] > 5)
print(wines[:,11] == 10)

#Subsetting
high_quality = wines[:,11] > 7
print(wines[high_quality,:][:3,:])
high_quality_and_alcohol = (wines[:,10] > 10) & (wines[:,11] > 7)
print(wines[high_quality_and_alcohol,10:])

#Reshaping NumPy Arrays
print(np.transpose(wines).shape)
print(wines.ravel())
array_one = np.array(
    [
        [1,2,3,4],
        [5,6,7,8]
    ]
)
print(array_one.ravel())
print(wines[1,:].reshape((2,6)))

#Combining NumPy Arrays
white_wines = np.genfromtxt("winequality-white.csv", delimiter=";", skip_header=1)
print(white_wines.shape)
all_wines = np.vstack((wines, white_wines))
print(all_wines.shape)
print(np.concatenate((wines,white_wines),axis=0))


