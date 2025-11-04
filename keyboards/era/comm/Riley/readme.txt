##################################################
# 펌웨어 업데이트 방법 (Firmware Update Guide)
##################################################

[한글 설명]

■ 펌웨어 업데이트 절차

1. 아래 3가지 방법 중 하나를 선택하여 키보드를 '부트로더(Bootloader)' 모드로 진입시킵니다.
2. 부트로더 모드에 정상적으로 진입하면, 컴퓨터에 'RPI-RP2'와 같은 이름의 새로운 이동식 디스크가 나타납니다.
3. 이 디스크에 준비된 펌웨어(.uf2) 파일을 복사하여 붙여넣으면 잠시 후 자동으로 업데이트가 완료됩니다.


■ 부트로더 모드 진입 방법 (3가지)

1. 부트매직(Bootmagic) 사용
   - 키보드의 좌측 상단 키(일반적으로 Esc 키)를 누른 상태로 USB 케이블을 연결합니다.

2. 물리적 리셋(Physical Reset) 사용
   - 기판(PCB)의 리셋 버튼을 빠르게 두 번 누릅니다. (버튼이 있는 경우)
   - 또는, 기판의 'RST' 핀과 'GND' 핀을 핀셋 등으로 짧게 두 번 접촉(쇼트)시킵니다.
   - 또는, 'BOOT' 헤더 핀 두 개를 쇼트시킨 상태로 USB 케이블을 연결합니다.

3. 리셋 키코드(Reset Keycode) 사용
   - 키맵에 'QK_BOOT' 또는 'RESET'으로 미리 설정해 둔 키를 누릅니다.
   - (이 방법은 키맵에 해당 기능 키를 미리 할당한 경우에만 사용할 수 있습니다.)


======================================================================


[English Description]

■ How to Flash Firmware

1. Enter the keyboard's "Bootloader" mode using one of the three methods described below.
2. Once the keyboard is in bootloader mode, a new removable disk (e.g., "RPI-RP2") will appear on your computer.
3. Copy-paste or drag-and-drop your prepared firmware file (e.g., firmware.uf2) onto this disk. The update will complete automatically.


■ Three Ways to Enter Bootloader Mode

1. Using Bootmagic
   - Hold down the top-left key of the keyboard (usually the Esc key) while plugging in the USB cable.

2. Using Physical Reset
   - Quickly double-press the reset button on the PCB, if one exists.
   - Alternatively, use tweezers to briefly short the 'RST' and 'GND' pins on the PCB twice.
   - Alternatively, short the two 'BOOT' header pins while plugging in the USB cable.

3. Using a Reset Keycode
   - Press the key that you have assigned to 'QK_BOOT' or 'RESET' in your keymap.
   - (This method only works if you have already configured such a key in your layout.)