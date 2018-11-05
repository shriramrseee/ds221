from pyspark import SparkContext, SparkConf

sc = SparkContext.getOrCreate()

# Read csv file
m = sc.textFile("hdfs:///user/simmhan/ml/small/movies.csv").filter(lambda l: l.split(',')[0] != 'movieId')


# Computation

a =  m.map(lambda l: (l.split(',')[0], l.split(',')[2]))

b = a.filter(lambda kv: len(kv[1].split('|')) > 1)

c =  b.flatMap(lambda kv: zip([kv[0]]*len(kv[1].split('|')), kv[1].split('|')))

d = c.join(c).filter(lambda kv: kv[1][0] < kv[1][1])

e = d.map(lambda kv: ('|'.join(kv[1]), 1))

f = e.reduceByKey(lambda a, b: a+b).cache()

g = f.map(lambda kv: kv[1]).cache()

max_c = g.max()

max_l = lambda kv: kv[1] == max_c

min_c = g.min()

min_l = lambda kv: kv[1] == min_c

max_v = f.filter(max_l)

min_v = f.filter(min_l)


# print

for i in max_v.collect():
    print i[0]
for i in min_v.collect():
    print i[0]
