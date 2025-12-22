## External GUI for AI Voice Assistant (ESP32)  
A small DIY device that mirrors the current state of a voice assistant, visible both when the MacBook screen is on **and** when it is off.

### Purpose
Displays the assistant’s state (*listening / thinking(loading or processing) / speaking / sleeping*) via an OLED display showing anime-tyan face emotions.  
The key benefit is continuous visibility: even with the MacBook screen turned off, it’s immediately clear what the current state is.

### Hardware
- ESP32  
- 0.96" OLED (I2C)  
- WS2812B (1 LED for status/accent)

### How It Works
- Always connected to Wi‑Fi  
- Receives status commands over the network from the client
- Powered via USB‑C  
- Nightly automatic Wi‑Fi restart for long‑term stability

### UX Details
- Expressive OLED graphics matching the current state  
  (a single LED would be sufficient, but visuals improve readability and add personality)  
- Instant, glanceable feedback regardless of the main display state  
- Designed as a status mirror without exposing internal assistant logic

### Case & Assembly
- Disassemblable case (repair / reuse / upgrades)  
- PCB secured with four screws, suitable for frequent USB‑C interaction  
- Ventilation holes for passive airflow
- The LED light diffuser was hand‑shaped using a needle file, made from an old compact disc case

### Performance  
- Code is optimized for near‑instant response, enabling real‑time status indication  

### Architecture Advantage
The assistant core runs on a MacBook Pro, while this device acts purely as an external GUI and status mirror.

### Benefits
- Leverages the MacBook Pro’s processing power to run AI logic and local scripts  
- Assistant performance automatically improves with Mac hardware upgrades  
- The GUI device remains unchanged over time; only the core evolves  
- No need to rebuild or replace the hardware UI when updating the assistant  
- Fits naturally into an existing workflow where the Mac is already a primary tool

![0](https://github.com/user-attachments/assets/3798beed-ea9f-4c9b-a82a-88520f0b4b75)
![1](https://github.com/user-attachments/assets/860f56a9-a52f-44d5-ab8b-a56533c1e211)
![2](https://github.com/user-attachments/assets/d0059396-b980-4d71-b79d-4e2b049a75ff)
![3](https://github.com/user-attachments/assets/87b11408-1773-4d03-bd46-2371550b0ea9)
![4](https://github.com/user-attachments/assets/1418d08f-af80-4c5d-8995-1582423fe2bd)
![5](https://github.com/user-attachments/assets/db6d2984-5e7f-481d-8a8e-3c897bee5dec)
![6](https://github.com/user-attachments/assets/5d931ac9-cc4a-4e0f-a17f-0da6ecd29bf1)
![7](https://github.com/user-attachments/assets/07fe6376-ff25-4386-b7d1-6e6b30585218)
![8](https://github.com/user-attachments/assets/7ab77e41-aee0-4542-9f83-d9f7f709cd3a)

## License

MIT

## Support

If you find this project useful:

TON: UQCQclFDQnQkHI4bJETisvn4QAZevjMWx5mjC3AErZaXvhlU  
USDT: TSiRAGH2apuygsgYP7Q9mS48WN4gDS6D5o  
BTC: 1HCZ7KsmVoiDrvPpnZ5jLQPp7mi7xWR7fi
