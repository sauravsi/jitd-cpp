import sys
import matplotlib.pyplot as plt
fig, ax = plt.subplots()
ax.set_axisbelow(True)
ax.minorticks_on()
ax.grid(which='major', linestyle='-', linewidth='0.5')
ax.grid(which='minor', linestyle=':', linewidth='0.5')
for fileNo in range(1,len(sys.argv)):
	inFile = sys.argv[fileNo]
	with open(inFile,'r') as i:
	    lines = i.readlines()
	x = []
	y1 = []
	y2 = []
	x.append(0)
	lines.pop(0)
	for line in lines:
		nums = line.split()
		x.append(x[-1]+1)
		y1.append(int(nums[0])/1000000000.0)
		y2.append(int(nums[1])/1000000000.0)
	x.pop(-1)
	plt.semilogy(x, y2, 'bo', ms=0.5, label = 'MAP')
	plt.semilogy(x, y1, 'ro', ms=0.5, label = 'JITD')
	
plt.xlabel('queries')
plt.ylabel('response time(s)')
plt.legend()
plt.show()