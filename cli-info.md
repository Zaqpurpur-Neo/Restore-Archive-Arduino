# Arduino CLI Fast Docs
### Info 
dot in command can be change into folder name. For example:
```
arduino-cli compile --fqbn esp32:esp32:esp32 esp32_ps2x_receiver --verbose
```

---

## Verify (compile only, verbose)
```
arduino-cli compile --fqbn esp32:esp32:esp32 . --verbose
```

## Upload (with verbose)
```
arduino-cli upload -p COM3 --fqbn esp32:esp32:esp32 . --verbose
```

## Verify + Upload (step by step, verbose)
```
arduino-cli compile --fqbn esp32:esp32:esp32 . --verbose
arduino-cli upload -p COM3 --fqbn esp32:esp32:esp32 . --verbose
```

## Serial Monitor (verbose not needed, but here’s standard)
```
arduino-cli monitor -p COM3 -c baudrate=115200
```

---

## Another Commands

### Get Connected Board List 
```
arduino-cli board list
```

## Get All Available Board
```
arduino-cli board listall
```


```
arduino-cli board details --fqbn STMicroelectronics:stm32:GenF4

arduino-cli compile --fqbn STMicroelectronics:stm32:GenF4 stm32_compute_rotation --verbose

arduino-cli upload --fqbn STMicroelectronics:stm32:GenF4:pnum=BLACKPILL_F411CE,upload_method=dfuMethod,usb=CDCgen,xserial=generic test_stm32 --verbose
```

# LIB
``
arduino-cli lib install --zip-path ./MyModule.zip 
arduino-cli lib list
```
---

### Tips
Batch File Example:
```bat 
@echo off
arduino-cli compile --fqbn esp32:esp32:esp32 . --verbose
pause
```
