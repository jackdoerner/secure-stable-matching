import sys, math, re
from matplotlib.ticker import LogLocator
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from common import *

def get_nums(f):
	res = {"x":[],"vals":[]}
	for line in open(f).readlines():
		if "ORAM" in line or "Executing" in line or "Role" in line or "Total" in line or "TCP" in line:
			continue
		line = re.findall(r'\d+', line)
		res["x"].append(int(line[0]))
		res["vals"].append(float(line[1])/1000000)

	print res
	return res

init_plotting(6,6/1.68)

fig = plt.figure()
ax = fig.add_subplot(111)

data = (get_nums("../../results/bench/summary_gs_linear.txt"), get_nums("../../results/bench/summary_gs_circuit.txt"), get_nums("../../results/bench/summary_gs_sqrt.txt"))

ax.loglog(data[0]["x"], data[0]["vals"], color=colors[0], linestyle=dashes[0], basex=2)
ax.loglog(data[1]["x"], data[1]["vals"], color=colors[2], linestyle=dashes[0], basex=2)
ax.loglog(data[2]["x"], data[2]["vals"], color=colors[3], linestyle=dashes[0], basex=2)

data = (get_nums("../../results/bench/summary_gs_textbook_linear.txt"), get_nums("../../results/bench/summary_gs_textbook_circuit.txt"), get_nums("../../results/bench/summary_gs_textbook_sqrt.txt"))

ax.loglog(data[0]["x"], data[0]["vals"], color=colors[0], linestyle=dashes[3], basex=2)
ax.loglog(data[1]["x"], data[1]["vals"], color=colors[2], linestyle=dashes[3], basex=2)
ax.loglog(data[2]["x"], data[2]["vals"], color=colors[3], linestyle=dashes[3], basex=2)

ax.set_xlabel("Number of Pairs")
ax.set_ylabel("Execution Time (seconds)")
lims = plt.xlim()
plt.xlim([lims[0]/1.1, lims[1]*1.1])

mkdir_p("../../results/graph/")
plt.savefig("../../results/graph/gs_time.pdf",bbox_inches='tight', dpi=200)
