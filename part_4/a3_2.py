from pyspark import SparkContext, SparkConf

sc = SparkContext.getOrCreate()

# Read csv file
r = sc.textFile("hdfs:///user/simmhan/ml/small/ratings.csv").filter(lambda l: l.split(',')[0] != 'userId')


# Get average no. of ratings

avgn = (r.count()*1.0) / r.map(lambda l: l.split(',')[0]).distinct().count()

# Get average rating per user

avgr = r.map(lambda l: float(l.split(',')[2])).reduce(lambda a, b : a+b) / r.count()

# Print results

print avgn, avgr 




