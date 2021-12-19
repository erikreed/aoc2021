import numpy as np
data = [int(r) for r in open('p1.txt').read().split()]
data = np.array(data)
print((data.diff() > 0).sum())

