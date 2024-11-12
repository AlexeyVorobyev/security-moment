# Отчёт по лабораторной работе №6

## Выполненные шаги

1. Настроил облако с двумя vps, подключенными к vpc
2. Установил apache2 на 2 машину - sudo apt-get install apache2
3. Установил nmap на 1 машину - sudo apt-get install nmap

4. TCP Connect - nmap -sT 192.168.0.5

![image](images/1.png)

5. TCP-SYN - nmap -sS 192.168.0.5

![image](images/2.png)

6. Fin - nmap -sF 192.168.0.5

![image](images/3.png)

6. XmasTree - nmap -sX 192.168.0.5

![image](images/4.png)

7. NULL - nmap -sN 192.168.0.5

![image](images/5.png)

8. PROTOCOL IP - nmap -sO 192.168.0.5

![image](images/6.png)

9. ACK - nmap -sA 192.168.0.5

![image](images/7.png)

10. TCP Window - nmap -sW 192.168.0.5

![image](images/8.png)

11. RPC Сканирование - nmap -sR 192.168.0.5

![image](images/9.png)

11. Сканирование ОС - nmap -O 192.168.0.5

![image](images/9.png)
