# 🔐 Arduino Automatic Login System (아두이노 자동 로그인 장치)

> **High school 2nd year project archive (2019)**
>
> 주변 시선을 신경 쓰지 않고, 태그 한 번으로 빠르고 안전하게 로그인을 수행하는 아두이노 HID 시스템입니다.

## 🚀 프로젝트 소개 (Introduction)

### "주변에 사람이 너무 많을 때, 비밀번호 치기 곤란하셨나요?"

이 프로젝트는 학교나 공공장소와 같이 **주변에 사람이 많은 환경**에서 로그인을 할 때 발생할 수 있는 보안 문제와 불편함을 해결하기 위해 제작되었습니다.
매번 키보드로 비밀번호를 입력하는 번거로움과 오타로 인한 스트레스를 줄이고, **RFID 카드 태그**나 **블루투스 신호**만으로 즉시 로그인이 가능한 자동화 장치를 구현했습니다.

## ✨ 주요 기능 (Key Features)

* **⚡ RFID 퀵 로그인:** 등록된 교통카드나 RFID 태그를 리더기에 갖다 대면 미리 설정된 ID/PW가 자동으로 입력됩니다.
* **📱 블루투스 원격 제어:** HC-06 모듈을 통해 스마트폰과 통신하며, 원격으로 로그인 신호를 보낼 수 있습니다.
* **🖥️ 실시간 상태 모니터링:** I2C LCD 디스플레이를 통해 `Welcome`, `Login Completed` 등의 현재 작동 상태를 시각적으로 확인합니다.
* **⌨️ 듀얼 로그인 모드:** 카드(사용자)에 따라 서로 다른 로그인 시퀀스(탭 횟수, 대기 시간 등)를 수행하여, 일반 사이트와 입력 방식이 특이한 사이트 모두에 대응할 수 있습니다.

## 🛠️ 기술 스택 (Tech Stack)

### Hardware
* **MCU:** Arduino Leonardo - *PC가 키보드/마우스로 인식(HID)하기 위해 사용*
* **RFID:** MFRC522 모듈
* **Display:** 16x2 Character LCD
* **Communication:** HC-06 Bluetooth Module

### Software
* **IDE:** Arduino IDE
* **Libraries:** `Keyboard.h`, `Mouse.h`, `MFRC522.h`, `LiquidCrystal_I2C.h`, `SoftwareSerial.h`

## 🔌 회로 구성 및 핀맵 (Pin Configuration)

| 모듈 (Module) | 핀 (Pin) | 비고 |
| :--- | :--- | :--- |
| **Bluetooth (HC-06)** | RX: 8, TX: 7 | SoftwareSerial 사용 |
| **RFID (RC522)** | SDA(SS): 10, RST: 9 | SPI 통신 |
| **LCD (I2C)** | SDA, SCL | I2C 통신 (주소: 0x3F) |

## 💻 작동 메커니즘 (How it Works)

1.  **대기 모드:** LCD에 `Welcome to Auto Log-In System!` 문구를 띄우고 카드나 블루투스 신호를 기다립니다.
2.  **로그인 시도:**
    * **Card 1 (Standard):** ID 입력 → `Tab` 1회 → PW 입력 → `Enter` (일반적인 로그인 창)
    * **Card 2 (Complex):** ID 입력 → `Tab` 3회 → `Enter` → 대기(2.5초) → PW 입력 → `Enter` (입력 창이 분리된 사이트나 특수 환경 대응)
3.  **결과 피드백:**
    * **성공 시:** LCD에 `Login Completed!`와 인식된 카드 번호(Card 1/2)를 표시하고 카운트다운을 진행합니다.
    * **실패 시:** 등록되지 않은 카드는 `Login Failed... Unknown Card` 메시지를 출력하고 입력을 차단합니다.

## 🚀 설치 및 사용법 (Usage)

1.  **환경 설정:** 아두이노 레오나르도(또는 Micro) 보드에 코드를 업로드합니다.
2.  **계정 정보 입력:** 소스 코드(`20914ATLOGIN.ino`) 상단의 define 변수에 자신의 계정 정보를 입력합니다.
    ```cpp
    #define USERNAME "my_actual_id"  // 사용할 ID
    #define PASSWORD "my_secret_pw"  // 사용할 PW
    ```
3.  **카드 등록:** 자신의 RFID 카드 UID를 확인하여 `PICC_0` 등의 변수 값을 수정합니다.
4.  **실행:** PC USB 포트에 장치를 연결하면 자동으로 키보드/마우스 장치로 인식되며 바로 사용할 수 있습니다.

---

Copyright © 2019 Mincheol Shin. All Rights Reserved.
