import sys, math, re
from matplotlib.ticker import LogLocator
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from common import *

def get_nums(f):
	res = {"x":[],"gates":{"xor":[],"setup":[],"permutation":[],"proprej":[]},"time":{"xor":[],"setup":[],"permutation":[],"proprej":[]}}
	for line in open(f).readlines():
		if "ORAM" in line or "Executing" in line or "Role" in line or "Total" in line or "TCP" in line:
			continue
		line = re.findall(r'\d+', line)
		res["x"].append(int(line[1]))

		res["time"]["xor"].append(float(line[5])/1000000)
		res["time"]["setup"].append(float(line[7])/1000000)
		res["time"]["permutation"].append(float(line[9])/1000000)
		res["time"]["proprej"].append(float(line[11])/1000000)

		res["gates"]["xor"].append(int(line[6]))
		res["gates"]["setup"].append(int(line[8]))
		res["gates"]["permutation"].append(int(line[10]))
		res["gates"]["proprej"].append(int(line[12]))

	print res
	return res

init_plotting(3,3)

fig = plt.figure()
ax = fig.add_subplot(111)

data = get_nums("../../results/bench/samples_rp_proposer_pref_bound_sqrt.txt")

for axis in [(ax, "time")]:

	axis[0].semilogx(data["x"], data[axis[1]]["xor"], color=colors[1], basex=2)
	axis[0].fill_between(data["x"], 0, data[axis[1]]["xor"], facecolor=colors[1] , alpha=0.3)

	axis[0].semilogx(data["x"], [x[0] + x[1] for x in zip(data[axis[1]]["xor"], data[axis[1]]["setup"])], color=colors[0], basex=2)
	axis[0].fill_between(data["x"], data[axis[1]]["xor"], [x[0] + x[1] for x in zip(data[axis[1]]["xor"], data[axis[1]]["setup"])], facecolor=colors[0] , alpha=0.3)
	
	axis[0].semilogx(data["x"], [x[0] + x[1] + x[2] for x in zip(data[axis[1]]["xor"], data[axis[1]]["setup"], data[axis[1]]["permutation"])], color=colors[2], basex=2)
	axis[0].fill_between(data["x"], [x[0] + x[1] for x in zip(data[axis[1]]["xor"], data[axis[1]]["setup"])], [x[0] + x[1] + x[2] for x in zip(data[axis[1]]["xor"], data[axis[1]]["setup"], data[axis[1]]["permutation"])], facecolor=colors[2] , alpha=0.3)

	axis[0].semilogx(data["x"], [x[0] + x[1] + x[2] +x[3] for x in zip(data[axis[1]]["xor"], data[axis[1]]["setup"], data[axis[1]]["permutation"], data[axis[1]]["proprej"])], color=colors[3], basex=2)
	axis[0].fill_between(data["x"], [x[0] + x[1] + x[2] for x in zip(data[axis[1]]["xor"], data[axis[1]]["setup"], data[axis[1]]["permutation"])], [x[0] + x[1] + x[2] + x[3] for x in zip(data[axis[1]]["xor"], data[axis[1]]["setup"], data[axis[1]]["permutation"], data[axis[1]]["proprej"])], facecolor=colors[3] , alpha=0.3)

ax.set_xlabel("Proposer Preference Bound")
ax.set_ylabel("Execution Time (seconds)")

mkdir_p("../../results/graph/")
plt.savefig("../../results/graph/rp_proposer_pref_bound.pdf",bbox_inches='tight', pad_inches = 0, dpi=200)
