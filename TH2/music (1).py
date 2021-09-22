import serial
import msvcrt

ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM6'
ser.close()  # trước tiên đóng cổng để đảm bảo cổng đang không bị chiếm
ser.open()

while(True):
    #    char = getch.getche()
    #    char = input()
    #    char = input()[0]
    char = msvcrt.getch()  # Nhận kí tự từ bàn phím
    char = char.decode('ASCII')  # tiến hành decode kí tự về chuỗi ASCII
    # Gửi đi kí tự dưới dạng byte dưới định dạng utf8
    ser.write(bytes(char, 'utf-8'))

    # print(char)
    print(ser.read())  # In ra màn hình console giá trị đã ghi ra cổng COM
    if(char == '\x03'):
        break  # Nếu là nhập vào ctrl + C thì thoát vòng lặp dừng chương trình
