import math
CrackMultiplier = 48.4220808
# CrackMultiplier = 47.8836025
SortMultiplier = 21.54876923
ScanUnsortedMultiplier = 31.0328112
ScanSortedMultiplier = 104.5911996
crackThreshold = 100000
StartSize = 1000000000
arraysizes = []
crackedarraysizes = []
sortedarraysizes = []
crackSizes = []
sortSizes = []
timeToCrack = []
timeToSort = []
scanTimes = []
arraysizes.append(StartSize)
scanTimes.append(StartSize*ScanUnsortedMultiplier)
while not len(arraysizes) == 0:
	arraysizes.sort(reverse = True)
	a = arraysizes[0]
	arraysizes = arraysizes[1:]
	if a <= crackThreshold:
		crackedarraysizes.append(a)
		continue
	crackSizes.append(a)
	timeToCrack.append(a*CrackMultiplier)
	newA = int(a*0.75)
	newB = a - newA
	if newA > crackThreshold:
		arraysizes.append(newA)
	else:
		crackedarraysizes.append(newA)
	if newB > crackThreshold:
		arraysizes.append(newB)
	else:
		crackedarraysizes.append(newB)
	TotalScanTime = 0
	for x in arraysizes:
		TotalScanTime = TotalScanTime + (x*x*ScanUnsortedMultiplier)
	for x in crackedarraysizes:
		TotalScanTime = TotalScanTime + (x*x*ScanUnsortedMultiplier)
	averageScanTime = TotalScanTime/StartSize
	scanTimes.append(averageScanTime)
# print 'c\t0\t0\t'+str(int(scanTimes[0]))
print 'c\t0\t'+str(int(StartSize*ScanUnsortedMultiplier))
scanTimes = scanTimes[1:]
for i in range(0,len(crackSizes)):
	# print 'c\t'+str(crackSizes[i])+'\t'+str(int(timeToCrack[i]))+'\t'+str(int(scanTimes[i]))
	print 'c\t'+str(int(timeToCrack[i]))+'\t'+str(int(scanTimes[i]))
crackedarraysizes.sort(reverse = True)
scanTimes2 = []
while not len(crackedarraysizes) == 0:
	a = crackedarraysizes[0]
	crackedarraysizes = crackedarraysizes[1:]
	sortSizes.append(a)
	timeToSort.append(a*math.log(a,2)*SortMultiplier)
	sortedarraysizes.append(a)
	TotalScanTime = 0
	for x in crackedarraysizes:
		TotalScanTime = TotalScanTime + (x*x*ScanUnsortedMultiplier)
	for x in sortedarraysizes:
		TotalScanTime = TotalScanTime + (x*math.log(x,2)*ScanSortedMultiplier)
	averageScanTime = TotalScanTime/StartSize
	scanTimes2.append(averageScanTime)
for i in range(0,len(sortSizes)):
	# print 's\t'+str(sortSizes[i])+'\t'+str(int(timeToSort[i]))+'\t'+str(int(scanTimes2[i]))
	print 's\t'+str(int(timeToSort[i]))+'\t'+str(int(scanTimes2[i]))
		
