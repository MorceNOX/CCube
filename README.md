# CCube
<img width="1035" height="962" alt="logo" src="https://github.com/user-attachments/assets/8928eaf8-4664-4b71-8546-b81200c473d9" />

This is a complete and robust terminal-based and very accurate scrambles generator and timer for your Rubik's Cube practicing. Scrambles and timers are shown in very big letters. It also shows your times and the averages according to the WCA rules.

This is NOT the official scramble program, but it is very good for practicing. 

It is the only application which gives you the 15 seconds regressive timer after the scramble, so you can analyze your cube the same way it happens in the competitions! After this, the game really begins. You will see the changes in the screen and will hear the sound indication.

Written in C, this application is extremely fast, small and does the task. It runs everything the way a Speedcuber needs, with very big letters and without complication. Of course we put some colors, animations and sound effects to make the things more pleasant and enjoyable.

## Requirements
You can install `libao` to runs the timer and the pre-timer with sounds.
We provide commands to install it if you runs under any Linux system or MacOS.

### For Ubuntu/Debian:
```bash
make install-libao-debian
```

### For Fedora/RHEL/CentOS:
```bash
make install-libao-redhat
```

### For MacOS:
```bash
make install-libao-macos
```

## Instalation
Just clone this repository, enter the directory and runs the following commands:

```bash
make
make install
```

## How the application works?

Here are a few screenshots showing the features and the simplicity.

### The generated scramble:
<img width="2560" height="1539" alt="001-generated-scramble" src="https://github.com/user-attachments/assets/b1744d60-6ed6-4368-977a-d0fd928c3b6b" />

### The 15 seconds pre-timer:
<img width="2560" height="1539" alt="002-15secs-counter" src="https://github.com/user-attachments/assets/061a92ee-dc4f-42ff-ba30-5becb3b5c9bd" />

### The Timer:
<img width="2560" height="1539" alt="003-timer" src="https://github.com/user-attachments/assets/4f2ce748-4261-4d43-87d0-c3c9beac5321" />

### The Averages and the possibility to cancel the current scramble and its time:
<img width="2560" height="1539" alt="005-averages" src="https://github.com/user-attachments/assets/1378cc57-de93-49d7-a1ad-af9a213a2662" />

### Your last times and scrambles in the current session:
<img width="2560" height="1539" alt="006-last-times-list" src="https://github.com/user-attachments/assets/a4ccfc06-bf2d-48d2-84c6-fbfef76b2d0e" />

### Closing the Session
<img width="2560" height="1539" alt="007-closed-session" src="https://github.com/user-attachments/assets/56a8f555-132b-42ce-ab45-6d0a76d4cf99" />

Enjoy your CCube!

