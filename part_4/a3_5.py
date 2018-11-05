from pyspark import SparkContext, SparkConf

sc = SparkContext.getOrCreate()

# Read csv file
t = sc.textFile("hdfs:///user/simmhan/ml/small/tags.csv").filter(lambda l: l.split(',')[0] != 'userId')


# Get max. and min. tags

s = t.map(lambda l: (l.split(',')[2], 1)).reduceByKey(lambda a, b: a+b)
max_c = s.map(lambda kv: kv[1]).max()
min_c = s.map(lambda kv: kv[1]).min()
max_t = s.filter(lambda kv: kv[1] == max_c).collect()
min_t = s.filter(lambda kv: kv[1] == min_c).collect()

# print

for i in max_t:
    print i[0]
for i in min_t:
    print i[0]




