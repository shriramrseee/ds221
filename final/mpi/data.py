from random import shuffle

l = [i for i in range(100000)]

shuffle(l)

for i in l:
    print i
