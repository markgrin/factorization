#/bin/python
import subprocess
import matplotlib
import matplotlib.pyplot
import random
import math
import numpy

fullLim = 10000000000
fermatLim = 10000000
polfloLim = 10 ** 80
brentLim = 10 ** 80
brentMtLim = 10 ** 80
pollardLim = 10 ** 80
maximum = 1
methods = [
#        {'full' : 'Full', 'name' : 'full', 'from' : 10, 'to' : fullLim, 'xs' : [], 'ys' : [], 'timeout' : 0},
#        {'full' : 'Fermat', 'name' : 'fermat', 'from' : 10, 'to' : fermatLim, 'xs' : [], 'ys' : [], 'timeout' : 0},
#        {'full' : 'Pollard-Floyd', 'name' : 'polflo', 'from' : 10, 'to' : polfloLim, 'xs' : [], 'ys' : [], 'timeout' : 0},
        {'full' : 'Brent', 'name' : 'brent', 'from' : 10, 'to' : brentLim, 'xs' : [], 'ys' : [], 'timeout' : 0},
        {'full' : 'Brent Multi-Thread', 'name' : 'brentmt', 'from' : 10, 'to' : brentMtLim, 'xs' : [], 'ys' : [], 'timeout' : 0},
#        {'full' : 'Pollard', 'name' : 'pollard', 'from' : 10, 'to' : pollardLim, 'xs' : [], 'ys' : [], 'timeout' : 0}
]

def getTime(method, number):
    res = subprocess.run("./factorization {} {}".format(method, number), timeout=1, shell=True, stdout=subprocess.PIPE).stdout.decode('ascii')
    res = int(res.split('\n')[0].split(':')[1])
    return res

times = 150
while times > 0:
    times = times - 1
    for method in methods:
        print('\r{}                     '.format(method['name']), end='')
        base = int(math.log(method['to'], 10))
        power = random.randint(1, base)
        number = random.randint(math.pow(10, power), math.pow(10, power + 1))
        maximum = max(number, maximum)
        try:
            result = getTime(method['name'], number)
            method['xs'].append(number)
            method['ys'].append(result)
        except Exception:
            method['timeout'] += 1

print('')

legends = []
for method in methods:
    print("method:{} timeouts:{}".format(method['name'], method['timeout']))
    legends.append(method['full'])
    matplotlib.pyplot.plot(method['xs'], method['ys'], 'p')

matplotlib.pyplot.legend(legends)
matplotlib.pyplot.xscale('log')
matplotlib.pyplot.yscale('log')
matplotlib.pyplot.ylim(1, 1000000)
matplotlib.pyplot.savefig('./res.png')



