### Write to Board

```
sudo chown root:admn /dev/ttyUSB0
```

### how to save git credentials:

- Generate passcode from github from `Settings -> Developer Settings`

```
git config --global credential.helper store
```

### Servo

- Move `AntiClock` pulse for `95` milliseconds write`writeMicroseconds(1540)`
- Move `AntiClock` pulse for `85` milliseconds write`writeMicroseconds(1460)`
- Making 60 Pulses will complete 360 degree
