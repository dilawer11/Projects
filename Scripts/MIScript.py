import subprocess 
import time
import csv
import sys
import os

processName = sys.argv[1]
fileExists = True
fileName = 'data0'
while(fileExists):
    if(os.path.isfile(fileName+'.csv')):
        value = int(fileName[4:])
        value = value + 1;
        fileName = fileName[:4]
        fileName = fileName+str(value)
        print(fileName)
    else:
        fileExists = False
fileName  = fileName+'.csv'
f = open(fileName,'w')
writer = csv.writer(f)
writer.writerow(['Time(ms)','TOTAL PSS'])
currentTime = 0
startTime = round(time.time()*1000)
while(currentTime<5000):
    value = subprocess.run(["adb","shell","dumpsys","meminfo",processName],capture_output=True)
    currentTime = round(time.time()*1000)-startTime
    valueList = str(value.stdout).split(' ')
    totalPSS = int(valueList[valueList.index('TOTAL')+4])
    writer.writerow([currentTime,totalPSS])

     

