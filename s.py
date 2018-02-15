import socket
import MySQLdb
import time

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.bind(('localhost', 9090))

db = MySQLdb.connect(host="localhost", user="root", passwd="", db="botnet")
while True:
	sock.listen(1)
	conn, addr = sock.accept()
	print 'connected:', addr
	cursor = db.cursor()

	s = []
	while True:
		data = conn.recv(1024)
		print data
		if not data:
			break
		s.append(data)

	conn.send(b'Hello\n')
	print len(s), s
	sql = """INSERT INTO data(BOT_ID, FLAG, BUFF)
        VALUES ('%(BOT_ID)s', '%(FLAG)s', '%(BUFF)s')
        """%{"BOT_ID":s[0], "FLAG":s[1], "BUFF":addr[0]}
	print sql
	cursor.execute(sql)

	db.commit()

db.close()
conn.close()