import serial
import csv

COMPORT = "COM6"
#CSV_FILE = r"C:\Users\livid\Documents\GitHub\MappingBot\Visual_Display\VSCode\locationdata.csv"
CSV_FILE = r"locationdata.csv"
global points
points = []

def saveData():
    
    # Send data to CSV file
    field_names = ["x","y","angle"] 
    with open(CSV_FILE, 'w') as csvfile: 
        writer = csv.DictWriter(csvfile, fieldnames = field_names) 
        writer.writeheader() 
        writer.writerows(points) 
    print('Saved data')
    return

def readSerial():
     ser = serial.Serial(COMPORT, 115200)
     start = False
     while True:
          line=str(ser.readline())
          
          # Stop recording data
          if(line[2:][:-5] == "Done."):
               print(line[2:][:-5])
               saveData()
               break

          print(line[2:][:-5])

          # Start recording data
          if(line[2:][:-5] == "Start!"):
               start = True
               continue
          if(not start):
              continue 
          
          dataPoints = line[2:][:-5].split(",")
          #print(float(dataPoints[0]))
          points.append(dict({"x": float(dataPoints[0]) , "y": float(dataPoints[1]), "angle": int(dataPoints[2])}))
          

def main():
     print("Connecting to serial " + COMPORT)
     readSerial()
     return

main()
