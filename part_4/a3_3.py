from pyspark import SparkContext, SparkConf

sc = SparkContext.getOrCreate()

# Read csv file
r = sc.textFile("hdfs:///user/simmhan/ml/small/ratings.csv").filter(lambda l: l.split(',')[0] != 'userId')


# Get median

length = r.count()

rs = r.map(lambda l: (float(l.split(',')[2]), 1)).sortByKey()

if length // 2:
    med = rs.zipWithIndex().filter(lambda l: l[1] == (length/2 + 1)).take(1)[0][0][0]
else:
    med = rs.zipWithIndex().filter(lambda l: l[1] == (length/2 + 1) or l[1] == length/2).take(2)
    med = (med[0][0][0] + med[1][0][0]) / 2

# Print results

print med




