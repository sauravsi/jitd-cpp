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
	arrSizes = []
	x = []
	y = []
	m = []
	l = lines[0].split()
	x.append(float(int(l[2])/1000000000.0))
	y.append(1.0)
	m.append(float(int(l[2])/1000000000.0))
	for line in lines[1:]:
		nums = line.split()
		xi = (float(nums[1])/1000000000.0)
		x.append(x[-1] + xi)
		yi = 0.0
		if m[-1] != 0.0:
			yi = (xi/m[-1])
		y.append(y[-1] + yi)
		m.append(float(nums[2])/1000000000.0)
	xi = 1300 - x[-1]
	yi = (xi/m[-1])
	# print m
	# print x
	x.append(x[-1] + xi)
	y.append(y[-1] + yi)
	plt.semilogy(x,y, 'o-', ms=2, label = inFile)
ax.set_ylim(ymin= 0)
plt.grid(b=True, which='minor', linestyle='--')
plt.xlabel('scan time: total time - idle time (s)')
plt.ylabel('scans')
plt.legend()
plt.show()