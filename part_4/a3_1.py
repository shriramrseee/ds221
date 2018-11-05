from pyspark import SparkContext, SparkConf

sc = SparkContext.getOrCreate()

# Read csv file
r = sc.textFile("hdfs:///user/simmhan/ml/small/ratings.csv")
t = sc.textFile("hdfs:///user/simmhan/ml/small/tags.csv")


# Get distinct users

ru = r.map(lambda l: l.split(',')[0]).filter(lambda u: u != 'userId').distinct()
tu = t.map(lambda l: l.split(',')[0]).filter(lambda u: u != 'userId').distinct()

# Print results

print ru.count(), tu.count(), ru.intersection(tu).count()




