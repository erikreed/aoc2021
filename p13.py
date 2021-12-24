import numpy as np

with open('p13.txt') as f:
    nums = []
    for line in f:
        line = line.strip()
        if not line:
            break
        nums.append(tuple(map(int, line.split(','))))
    folds = []
    for line in f:
        line = line.strip()
        axis, value = line.split('fold along ')[1].split('=')
        folds.append((axis, int(value)))

dims = max(max(yx) + 1 for yx in nums)
grid = np.zeros((dims, dims), dtype=bool)

for y,x in nums:
    grid[x, y] = 1

print(grid)
assert grid.sum() == len(nums)
print(folds)

# x = left
# y = top

for axis, value in folds:
    print('folding', axis, value)
    if axis == 'x':
        folded_grid = grid[:, :value]

        folded_grid[:, -value:] |= grid[:, value+1:][:, ::-1]
        print('folded_grid.sum()', folded_grid.sum())
    else:
        folded_grid = grid[:value, :]

        subgrid = grid[value+1:, :]
        subgrid = subgrid[:folded_grid.shape[0], :folded_grid.shape[1]]

        folded_grid[-value:, :] |= subgrid[::-1, :]
        print('folded_grid.sum()', folded_grid.sum())
    grid = folded_grid

print(folded_grid.astype(int))
for row in folded_grid:
    for char in row:
        print('X' if char else ' ', end='')
    print()
