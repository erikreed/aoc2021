import functools

lines = open('p3.txt').read().split()
digits = [0] * len(lines[0])

for line in lines:
    for i, c in enumerate(line):
        digits[i] += int(c)
        
assert len(lines) == 1000

digits = [d / len(lines) for d in digits]
GAMMA = [round(d) for d in digits]
EPSILON = [int(d <= .5) for d in digits]


output = ''.join([str(d) for d in GAMMA])
def print_int_product(bits_1, bits_2):
    print(int(bits_1, base=2) * int(bits_2, base=2))

output_number = int(output, base=2)
print(output_number, 0xfff ^ output_number)
print(output_number * (0xfff ^ output_number))


def get_rating(bit_number, reference):
    """determines how many initial digits of the bit number
    match the reference"""
    rating = 0
    for index, val in enumerate(bit_number):
        if int(val) ^ reference[index]:
            break
        rating += 1

    return rating
        

o2_rating = ("", 0)
co2_rating = ("", 0)
for line in lines:
    gamma_rating, epsilon_rating = get_rating(line, GAMMA), get_rating(line, EPSILON)
    if gamma_rating > o2_rating[1]:
        o2_rating = (line, gamma_rating)
    if epsilon_rating > co2_rating[1]:
        co2_rating = (line, epsilon_rating)

print("life support product:")
print_int_product(o2_rating[0], co2_rating[0])