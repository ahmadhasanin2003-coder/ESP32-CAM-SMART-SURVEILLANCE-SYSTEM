from flask import Flask,redirect,url_for,render_template,Response
import cv2 as cv
import numpy as np
import os
def resize(capture,width,height):
    return cv.resize(capture,(width,height),interpolation=cv.INTER_LINEAR)
cam=cv.VideoCapture('http://192.168.1.xx:xx/Stream')
def processed_frames():
    i=0
    old_frame=None
    while(True):
        istrue,frame=cam.read()
        if(not istrue):
            print('camera failed')
            break
        else:
            frame=cv.flip(frame,1)
            frame_new=resize(frame,1000,700)
            if(old_frame is None):
                old_frame=frame_new.copy()
                continue

            diff_matrix=cv.absdiff(old_frame,frame_new)
            old_frame=frame_new.copy()
            gray=cv.cvtColor(diff_matrix,cv.COLOR_BGR2GRAY)
            blur=cv.GaussianBlur(gray,(5,5),0)
            ret,thresh=cv.threshold(blur,50,255,cv.THRESH_BINARY)
            dilated=cv.dilate(thresh,(3,3),iterations=1)
            contours,heirerchy=cv.findContours(dilated,cv.RETR_EXTERNAL,cv.CHAIN_APPROX_SIMPLE)
            for c in contours:
                if(cv.contourArea(c)>2000):
                    i+=1
                    x,y,w,z=cv.boundingRect(c)
                    cv.rectangle(frame_new,(x,y),(w+x,z+y),(0,255,0),thickness=2)
                    break
            ret,buffer=cv.imencode('.jpg',frame_new)
            frame1=buffer.tobytes()
            yield (b'--frame\r\n'
                        b'Content-Type:image/jpeg\r\n\r\n'+frame1+b'\r\n')     
app=Flask(__name__)

@app.route('/')
def welcome():
    return render_template('index.html')
@app.route('/stream')
def stream():
    return Response(processed_frames(),mimetype='multipart/x-mixed-replace;boundary=frame')

@app.route('/capture')
def capture():
    '''with open('file_no.txt','a+',encoding='utf-8') as file:
        a=file.read()
        folder_path="output_images"
        file_name="capture_img"+str(a)+".jpg"
        os.makedirs(folder_path, exist_ok=True)
        full_path=os.path.join(folder_path,file_name)
        cv.imwrite(full_path,processed_frames())
        file.write(a)'''


    print(processed_frames())
    return "ok"

'''@app.route('/left')
def control_left():
    requests.get('http://192.168.1.34:80/control_left')
    return "okay left"

@app.route('/right')
def control_right():
    requests.get('http://192.168.1.34:80/control_right')
    return "okay right"

@app.route('/stop')
def control_stop():
    requests.get('http://192.168.1.34:80/control_stop')
    return "okay stop"'''

if __name__=='__main__':
    app.run(debug=True)
