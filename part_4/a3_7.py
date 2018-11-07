from pyspark import SparkContext, SparkConf
import csv

sc = SparkContext.getOrCreate()


# Unicode reader

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
g = sc.textFile("hdfs:///user/simmhan/ml/full/genome-scores.csv")
gs = g.map(lambda l: tuple(unicode_csv_reader([l,]))[0]).filter(lambda l: l[0] != u'movieId').cache()

# Computation
a = gs.filter(lambda l: l[0] == '79132')
b = gs.filter(lambda l: l[0] != '79132')
c = a.map(lambda l: (l[1], float(l[2])))
d = b.map(lambda l: (l[1], (l[0], float(l[2]))))
e = c.join(d)
f = e.flatMap(lambda kv: [(i[0], abs(i[1]*i[1] - kv[1][0]*kv[1][0])) for i in kv[1][1:]])
h = f.reduceByKey(lambda a, b: a+b)
i = mu.map(lambda l: (l[0], l[1]))
j = h.join(i)
k = j.map(lambda kvp: (kvp[1][0], kvp[1][1]))
l = k.sortByKey().take(10)


# Print results

for x in l:
    print x[1]
