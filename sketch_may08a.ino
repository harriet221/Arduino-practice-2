// 아두이노 슬레이브 / COM9

#include <SoftwareSerial.h>
SoftwareSerial m(2,3);  // 2:RX, 3:TX
int data;
int cds = A0; // 조도센서(CDS) 입력 핀

void setup() {
  Serial.begin(9600); // 데스크톱과의 시리얼 통신
  m.begin(9600); // 장치간 시리얼 통신
}

void loop() {
  if(m.available()) { // 시리얼 통신 입력이 있으면 실행
    data = m.read(); // 시리얼 통신을 통해 읽은 값 정수로
    if(data == 1) { // 수신한 값이 1이면 실행
      int cdsValue = analogRead(cds); // 조도센서 읽기
      delay(1); // 값 읽고 반응할 시간 위한 짧은 딜레이
      if(cdsValue > 200) { // 조도센서 값이 200보다 크면 실행 (손전등을 가까이 한 정도)
        m.write('c'); // c 송신 ((충분히 밝으니까 LED2 켜라))
      }
      else { // 200보다 작거나 같으면
        m.write('f'); // f 송신
      }
    }
  }
}
