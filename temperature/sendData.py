from datetime import date, datetime
import MySQLdb
conn = MySQLdb.connect(host= "localhost",
				  user="root",
				  passwd="pokemon",
				  db="temperature")
x = conn.cursor()

try:

	add_temp = ("INSERT INTO tb_temperature"
				  "(Value) "
				  "VALUES (%(Value)s)")

	# Insert salary information
	data_temp = {
		'Value': 18.888,
	}
	
	x.execute(add_temp,data_temp)
	
	conn.commit()

except:
	print("exception!")
	conn.rollback()


conn.close()