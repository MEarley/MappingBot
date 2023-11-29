import serial
import csv

COMPORT = "COM3"
CSV_FILE = r"C:\Users\livid\Documents\GitHub\MappingBot\Visual_Display\VSCode\locationdata.csv"

def saveData():
    
    # Send data to CSV file
    field_names = ["x","y"] 
    with open(CSV_FILE, 'w') as csvfile: 
        writer = csv.DictWriter(csvfile, fieldnames = field_names) 
        writer.writeheader() 
        writer.writerows(topCoins) 
    print('Saved data')
    return

def readSerial():
     ser = serial.Serial(COMPORT, 115200)
     while True:
          cc=str(ser.readline())
          if(cc[2:][:-5] == "Done."):
               saveData()
               break
          print(cc[2:][:-5])

def main():
     print("Connecting to serial " + COMPORT)
     readSerial()
     return

main()
