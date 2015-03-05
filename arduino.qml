import QtQuick 2.0
import QtQuick.Controls 1.3
Rectangle {

    color:"black"
    //opacity:arduino.brightness / 1024;
    width: 480
    height: 400

    Column {
        x: 216
        y:307
        Text{text:"LED";color:"white"}
        Switch {
            id:led
            checked: true
            onCheckedChanged:
            {
                if (checked == true)
                {
                    arduino.turnOn(1);
                }
                else
                {
                    arduino.turnOff(1);
                }
            }
        }
        Switch {
            id:relay
            checked: true
            onCheckedChanged:
            {
                if (checked == true)
                {
                    arduino.turnOn(2);
                }
                else
                {
                    arduino.turnOff(2);
                }
            }
        }
    }

    Dial
    {
       x:10
       y:100
       value:120 - (arduino.brightness / 1024) * 120;
    }

    Dial
    {
       x:258
       y:100
       value:(arduino.volume / 1024) * 120;
    }

}

