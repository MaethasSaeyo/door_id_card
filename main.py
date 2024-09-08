import serial
from mysql.connector import (connection)
import time


mydb = connection.MySQLConnection(host="localhost",user="root",password="",database="door_id_card")

SERIAL_PORT = 'COM3'
BAUD_RATE = 9600
ser = serial.Serial(SERIAL_PORT,BAUD_RATE)


if mydb.is_connected():
    print("connected Successfully")
else:
    print("Unconnected")
    
mycursor = mydb.cursor()


#


def read_and_process_data():
    line = ser.readline().decode('utf-8').strip()
    sensorValuse = line.split(', ')
    
    return sensorValuse[0]



while True:
    curr = time.ctime(time.time())
    id = read_and_process_data()
    if id == "227" or id == "131":
        name = read_and_process_data()
        print(id,name,curr)

    
    sql = "INSERT INTO user (id, name,time) VALUES ( %s,%s,%s)"
    val = (id,name,str(curr))
    mycursor.execute(sql, val)
    mydb.commit()

    print(mycursor.rowcount, "record inserted.")

    


   

    


    

    
