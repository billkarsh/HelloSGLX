import subprocess

HelloSGLX = r"C:/Users/labadmin/Desktop/HelloSGLX-win/HelloSGLX.exe"
args = "-host=127.0.0.1 -cmd=getVersion"

ret = subprocess.run(HelloSGLX+" "+args,capture_output=True,shell=True)
print(ret.stdout)


