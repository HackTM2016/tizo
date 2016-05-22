from flask import Flask
from pololu_drv8835_rpi import motors, MAX_SPEED

app = Flask(__name__)

@app.route('/lights/red/')
def red():
    motors.setSpeeds(0, -480)
    return 'RED'

@app.route('/lights/green/')
def green():
    motors.setSpeeds(-480, 0)
    return 'GREEN'

if __name__ == '__main__':
    app.run("0.0.0.0", "80")
