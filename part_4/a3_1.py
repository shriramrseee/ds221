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
t = sc.textFile("hdfs:///user/simmhan/ml/full/tags.csv")
ru = r.map(lambda l: tuple(unicode_csv_reader([l,]))[0]).filter(lambda l: l[0] != u'userId')
tu = t.map(lambda l: tuple(unicode_csv_reader([l,]))[0]).filter(lambda l: l[0] != u'userId')

# Get distinct

ru = ru.map(lambda l: l[0]).distinct().cache()
tu = tu.map(lambda l: l[0]).distinct().cache()

# Print results

print ru.count(), tu.count(), ru.intersection(tu).count()




