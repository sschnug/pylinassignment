from pylinassignment import linear_assignment
from scipy.optimize import linear_sum_assignment
import numpy as np
from time import perf_counter
np.random.seed(1)

# scipy smalle example
print('\nscipy small example\n')
cost = np.array([[4, 1, 3], [2, 0, 5], [3, 2, 2]])

row_ind, col_ind = linear_sum_assignment(cost)
print('scipy: ', cost[row_ind, col_ind].sum())

lemon = linear_assignment(cost)
print('lemon: ', lemon)

# random example
print('\nRandom example\n')
cost = np.random.randint(-1e4, 1e4, size=(750,750))

s_t = perf_counter()
row_ind, col_ind = linear_sum_assignment(cost)
e_t = perf_counter()
print('scipy: ', cost[row_ind, col_ind].sum(), ' -> ', str(e_t - s_t) + ' secs')

s_t = perf_counter()
lemon = linear_assignment(cost)
e_t = perf_counter()

print('lemon: ', lemon, '-> ', str(e_t - s_t) + ' secs')
