import RPi.GPIO as GPIO
import time
import socket

HOST = ""
PORT = 8888
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Socket created')
s.bind((HOST, PORT))
print('Socket bind complete')
s.listen(1)
print('Socket now listening')



def do_some_HIGH_with_input(input_string):
    motor_in1 = 20 # IN1
    motor_in2 = 21 # IN2
    motor_en = 16 # pwm
    linear_in1 = 24
    linear_in2 = 23
    linear_en = 25  
    
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)

    GPIO.setup(linear_in1,GPIO.OUT)
    GPIO.setup(linear_in2,GPIO.OUT)
    GPIO.setup(linear_en,GPIO.OUT)
    
    linear_p=GPIO.PWM(linear_en,1000)
    linear_p.start(100)
    
    if input_string == "OPERATE":
        try:
            GPIO.setup(motor_in1, GPIO.OUT)
            GPIO.setup(motor_in2, GPIO.OUT)
            GPIO.setup(motor_en, GPIO.OUT)
            GPIO.output(motor_in1,True)
            GPIO.output(motor_in2,False)
            GPIO.output(motor_en, True)
        except:
            GPIO.cleanup()
    
    elif input_string == "STOP":
        GPIO.cleanup()
    
    elif input_string == "HIGH":
        input_string = "set high"
        while(True):
            GPIO.output(linear_in1,GPIO.LOW)
            GPIO.output(linear_in2,GPIO.HIGH)           
            print("forward_high")
            
            
            time.sleep(0.5)
            
            print('HIGH DONE')            
            GPIO.cleanup()            
            break
        

    elif input_string == "LOW":
        input_string = "set low"
        while(True):
            GPIO.output(linear_in1,GPIO.HIGH)
            GPIO.output(linear_in2,GPIO.LOW)           
            print("forward_low")
            time.sleep(0.5)   
                
            print('LOW DONE')            
            GPIO.cleanup()            
            break
        
    elif input_string == "RESET":
        input_string = "reset"
        while(True):
            GPIO.output(linear_in1,GPIO.LOW)
            GPIO.output(linear_in2,GPIO.HIGH)           
            print("RESET START")
            print("LOADING")
            time.sleep(14)
            print('RESET DONE')            
            GPIO.cleanup()            
            break
        
    else :
        input_string = input_string + "없는 명령어 입니다."


while True:
    conn, addr = s.accept()
    print("Connected by ", addr)
    data = conn.recv(1024)
    data = data.decode("utf8").strip()
    if not data: break
    print("Received: " + data)
    
    do_some_HIGH_with_input(data)
    
    conn.close()
s.close()