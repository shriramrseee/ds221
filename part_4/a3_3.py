
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
r = sc.textFile("hdfs:///user/simmhan/ml/full/ratings.csv")
ru = r.map(lambda l: tuple(unicode_csv_reader([l,]))[0]).filter(lambda l: l[0] != u'userId').cache()

# Get median

length = ru.count()

rs = ru.map(lambda l: (float(l[2]), 1)).sortByKey().cache()

if length // 2:
    med = rs.zipWithIndex().filter(lambda l: l[1] == (length/2 + 1)).take(1)[0][0][0]
else:
    med = rs.zipWithIndex().filter(lambda l: l[1] == (length/2 + 1) or l[1] == length/2).take(2)
    med = (med[0][0][0] + med[1][0][0]) / 2

# Print results

print med
