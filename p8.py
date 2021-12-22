import itertools

fz = frozenset
#  7    3    4                              1   8
# bdg fdbge fcbd aecgdb dcgfe fcdgae fbage bd abdegfc ecbdfg | fcdb bd edbacg decgf
ONE =  fz(["top_right", "bottom_right"])
FOUR = fz(["top_left", "middle", "top_right", "bottom_right"])
SEVEN = fz(["top", "top_right", "bottom_right"])
EIGHT = fz()

ZERO = EIGHT.difference(fz(["middle"]))
TWO = None  # TODO
THREE = SEVEN.union(fz(["middle", "bottom"]))
SIX = EIGHT.difference(fz(["top_right"]))
NINE = FOUR.union(SEVEN)

lookup = {
    ZERO: 0,
    ONE: 1,
    fz('gcdfa'): 2,
    THREE: 3,
    FOUR: 4,
    fz('cdfbe'): 5,
    SIX: 6,
    SEVEN: 7,
    EIGHT: 8,
    NINE: 9,
}


expected_digit_mapping = {
    0: 'abcefg',
    1: 'cf',
    2: 'acdeg',
    3: 'acdfg',
    4: 'bcdf',
    5: 'abdfg',
    6: 'abdefg',
    7: 'acf',
    8: 'abcdefg',
    9: 'abcdfg'
}


# bdg fdbge fcbd aecgdb dcgfe fcdgae fbage bd abdegfc ecbdfg
def compute_mapping(samples):
    segments = 'abcdefg'
    possible_segments = set(''.join(sorted(s)) for s in expected_digit_mapping.values())

    for permutation in itertools.permutations(segments):
        mapping = {k:v for k,v in zip(segments, permutation)}
        for sample in samples:
            transformed_sample = ''.join(sorted(mapping[c] for c in sample))
            if transformed_sample not in possible_segments:
                break
        else:
            return mapping
    raise Exception('no mapping found')    


segment_to_digit = {v:k for k,v in expected_digit_mapping.items()}

total = 0
lines = open('p8.txt').read().splitlines()
for line in lines:
    segments, part = line.split('|')
    segments = segments.split()
    mapping = compute_mapping(segments)
    print('mapping:', mapping)
    
    parts = part.split()

    digit = ''
    for p in parts:
        segment = ''.join(sorted(mapping[c] for c in p))
        digit += str(segment_to_digit[segment])
    print(digit)
    total += int(digit)
print('-----')
print(total)
