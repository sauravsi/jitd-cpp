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
	y = []
	x.append(0)
	for line in lines:
		nums = line.split()
		xi = int(nums[1])+x[-1]
		x.append(xi)
		x.append(xi)
		y.append(1.0/int(nums[2]))
		y.append(y[-1])
	x.pop(0)
	y.pop(-1)
	y.insert(0,y[0])
	plt.semilogy(x,y, 'o-', ms=2, label = inFile)

plt.xlabel('runtime (ns)')
plt.ylabel('throughput (scans/ns)')
plt.legend()
plt.show()