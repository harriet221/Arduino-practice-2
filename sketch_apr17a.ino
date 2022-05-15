// 아두이노 마스터 / COM8 (Arduino Uno)

#include <SoftwareSerial.h>
SoftwareSerial s(2,3);  // 2:RX, 3:TX

int pin_switch = 13; // button 입력 핀
int pin_LED1 = 8; // LED1 출력 핀
int pin_LED2 = 9; // LED2 출력 핀

boolean buttonState = false; // 버튼 상태 초기화 = 풀다운 저항 (0V LOW / 5V HIGH)
boolean buttonSwitch_state_old = LOW; // 버튼 이전 상태
boolean buttonSwitch_state_new = LOW; // 버튼 현재 상태
boolean statusLED = LOW; // LED 상태 (정확히는 LED1 상태에 가까움)

void setup() {
  Serial.begin(9600); // 데스크톱과의 시리얼 통신
  s.begin(9600); // 장치간 시리얼 통신
  pinMode(pin_LED1, OUTPUT); // LED1 출력
  pinMode(pin_LED2, OUTPUT); // LED2 출력
  digitalWrite(pin_LED1, LOW); // LED1 초기화:꺼짐 - 버튼 누르면 작동되고 있음을 알리는 의미로 켜질 예정
  digitalWrite(pin_LED2, LOW); // LED2 초기화:꺼짐 - 조도센서가 일정 이상 빛 감지하면 켜질 예정
  pinMode(pin_switch, INPUT); // 버튼 입력
}

void loop() {
  if(s.available()) { // 시리얼 통신 입력이 있으면 실행
    char data = s.read(); // 시리얼 통신을 통해 읽은 값 문자로
    if(data == 'c') { // c일 경우 실행
      digitalWrite(pin_LED2, HIGH); delay(2000); // LED2 2초간 켜졌다가
      digitalWrite(pin_LED2, LOW); // 다시 꺼짐
    }
  }
  buttonSwitch_state_new = digitalRead(pin_switch); // 버튼 상태 읽기
  delay(1);  // 채터링 방지
  if(buttonSwitch_state_new != buttonSwitch_state_old) { // 버튼 상태 달라졌으면 실행
    if(buttonSwitch_state_new == HIGH) { // 버튼 현재 상태가 high (누름)이면 실행
      if(statusLED == LOW) { // LED(1) 상태가 LOW면 (꺼져있음) 실행 
        s.write(1); // 1 송신 ((조도센서 값 읽어라))
        digitalWrite(pin_LED1, HIGH); // LED1 켜짐
        statusLED = HIGH; // LED(1) 상태 HIGH로
      }
      else { // LED(1) 상태가 HIGH면 (켜져있음) 실행
        //s.write(2); // b 송신 ((읽을 필요 없다))
        digitalWrite(pin_LED1, LOW); // LED1 끄기
        statusLED = LOW; // LED(1) 상태 LOW로
      }
    }
    else { // 버튼 현재 상태가 low (안 누름)이면 실행
      s.write(2); // b 송신 ((읽을 필요 없다))
    }
    buttonSwitch_state_old = buttonSwitch_state_new; // 버튼 상태 갱신
  }
}
