from pyspark import SparkContext, SparkConf

sc = SparkContext.getOrCreate()

# Read csv file
t = sc.textFile("hdfs:///user/simmhan/ml/small/tags.csv").filter(lambda l: l.split(',')[0] != 'userId')


# Get max. no of tags

m = t.map(lambda l: (l.split(',')[1], 1)).reduceByKey(lambda a, b: a+b).map(lambda kv: kv[1]).max()

# Print results

print m




