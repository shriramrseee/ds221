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
r = sc.textFile("hdfs:///user/simmhan/ml/full/ratings.csv")
ru = r.map(lambda l: tuple(unicode_csv_reader([l,]))[0]).filter(lambda l: l[0] != u'userId').cache()

# Get average no. of ratings

avgn = (ru.count()*1.0) / ru.map(lambda l: l[0]).distinct().count()

# Get average rating per user

avgr = ru.map(lambda l: float(l[2])).reduce(lambda a, b : a+b) / ru.count()

# Print results

print avgn, avgr
