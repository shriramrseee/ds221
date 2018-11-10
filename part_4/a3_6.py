from pyspark import SparkContext, SparkConf
import csv

sc = SparkContext.getOrCreate()


# Unicode reader
# Reference: https://docs.python.org/2/library/csv.html#examples

def unicode_csv_reader(unicode_csv_data, dialect=csv.excel, **kwargs):
    # csv.py doesn't do Unicode; encode temporarily as UTF-8:
    csv_reader = csv.reader(utf_8_encoder(unicode_csv_data),
                            dialect=dialect, **kwargs)
    for row in csv_reader:
        # decode UTF-8 back to Unicode, cell by cell:
        yield [unicode(cell, 'utf-8') for cell in row]

def utf_8_encoder(unicode_csv_data):
    for line in unicode_csv_data:
        yield line.encode('utf-8')


# Read csv file
m = sc.textFile("hdfs:///user/simmhan/ml/full/movies.csv")
mu = m.map(lambda l: tuple(unicode_csv_reader([l,]))[0]).filter(lambda l: l[0] != u'movieId').cache()


# Computation

a =  mu.map(lambda l: (l[0], l[2]))

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
    print i[0],
for i in min_v.collect():
    print i[0],
