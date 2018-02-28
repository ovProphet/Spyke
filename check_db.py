import MySQLdb

db = MySQLdb.connect(host='localhost',user='root',passwd='',db='botnet')
cur = db.cursor()
cur.execute('SELECT * FROM bots')
print(cur.fetchall())