import copy
import collections

graph = collections.defaultdict(list)
for line in open('p12.txt'):
    origin, dest = line.strip().split('-')
    if dest != 'start':
        graph[origin].append(dest)
    if origin != 'start':
        graph[dest].append(origin)

target = 'end'
route = ('start',)
traversed = collections.defaultdict(int)

def find_path(route: list, traversed: set):
    current = route[-1]
    if current == target:
        yield route
        return

    twice = any(v == 2 for k,v in traversed.items() if k.lower() == k)

    neighbors = graph[current]
    for neighbor in neighbors:
        if traversed[neighbor] < (1 if twice else 2):
            retraversable = neighbor.upper() == neighbor
            if retraversable:
                next_traversable_set = traversed
            else:    
                next_traversable_set = copy.copy(traversed)
                next_traversable_set[neighbor] += 1
            yield from find_path(route + (neighbor,), next_traversable_set)            


all_paths = set()
def validate_path(path):
    h = hash(path)
    assert h not in all_paths
    all_paths.add(h)
    assert path[0] == 'start'
    assert path[-1] == 'end'
    counts = collections.Counter(path)
    assert counts['start'] == 1
    assert counts['end'] == 1
    twice = False
    for k, v in counts.items():
        if k.lower() == k and v == 2:
            assert not twice
            twice = True
        if v > 2:
            assert k == k.upper()
            


for i, path in enumerate(find_path(route, traversed), start=1):
    validate_path(path)

# 68191325 too high
# 34095662 too high
# 3679 too low
print(i)
