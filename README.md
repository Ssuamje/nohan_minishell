# Minishell : 앵무쉘

간단(?)한 쉘 프로그램 만들기.
By Hyungnoh && Sanan
![aengm](https://user-images.githubusercontent.com/105692206/217820159-19c4363a-cde4-4086-ad2f-11657a85ac66.gif)
<br><br>
# 개요

C언어로 Bash와 유사하게 작동하는 쉘을 구현한다.
<br>
<br>
프로그램에서 파싱이 어떻게 이루어지는지, 
<br><br>
파일 입출력과 프로세스는 어떻게 연결되어서 실행되는지,
<br><br>
명령 프롬프트가 어떤 방식으로 작동하는지 이해할 수 있다.
<br><br>

# 구현사항

파싱 : Lex - Token - Parse로 이어지는 흐름을 통해 유한 상태 기계로 구문 분석을 구현했다.
<br><br>
실행부 : 주어진 실행 양식으로 파일 입출력과 프로세스 간 통신, 상태 관리와 입력에 따른 명령어 실행을 구현했다.
<br><br>
탑재 기능 : 기존의 bash가 가진 빌트인 기능(프로그램)들을 구현하고, 기존 바이너리 파일들과 원활하게 작동하도록 구현했다.
<br><br>
# 실행 흐름
![Untitled](https://user-images.githubusercontent.com/105692206/217982018-bb03d2c2-1161-4a1b-bfc5-bb45f54b75ac.png)


