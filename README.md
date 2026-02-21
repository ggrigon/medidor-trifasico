# Medidor de Tensao Trifasico - ESP32 + PZEM-004T

Medidor trifasico DIY para monitoramento de sistema 220/380V em tempo real. Le tensao, corrente, potencia, energia, frequencia e fator de potencia das 3 fases com interface web, display OLED, historico em SD card e integracao MQTT.

**Custo estimado:** ~US$ 70-80 (vs US$ 129+ de solucoes comerciais como Shelly Pro 3EM)

## Lista de Materiais

| # | Componente | Qtd | Funcao | Custo aprox |
|---|---|---|---|---|
| 1 | ESP32 DevKit V1 (30 pinos) | 1 | Microcontrolador principal - WiFi + Bluetooth | US$ 10 |
| 2 | PZEM-004T v3.0 (100A) com TC | 3 | Medidor de energia por fase (Modbus RTU) | US$ 42 (3x US$14) |
| 3 | Display OLED SSD1306 128x64 I2C | 1 | Display local para leituras | US$ 4 |
| 4 | Modulo SD Card SPI | 1 | Armazenamento de historico CSV | US$ 3 |
| 5 | Cartao microSD (qualquer, 4GB+) | 1 | Midia de armazenamento | US$ 3 |
| 6 | Buzzer passivo 5V | 1 | Alarme sonoro | US$ 1 |
| 7 | Protoboard ou placa perfurada | 1 | Montagem dos componentes | US$ 3 |
| 8 | Fios jumper (M-M, M-F) | ~20 | Conexoes entre componentes | US$ 3 |
| 9 | Caixa plastica/projeto | 1 | Gabinete de protecao | US$ 5-10 |
| 10 | Fonte 5V 1A (USB ou HLK-PM01) | 1 | Alimentacao do ESP32 | US$ 3-5 |

**Total: ~US$ 77-84**

### Onde comprar
- AliExpress: melhor preco, entrega 15-40 dias
- Amazon: entrega rapida, preco um pouco maior
- Mercado Livre (BR): preco em reais, entrega rapida

## Funcionalidades

- **Leitura das 3 fases:** tensao, corrente, potencia, energia, frequencia, fator de potencia
- **Display OLED:** 5 paginas auto-rotativas (overview + detalhe de cada fase + alarmes)
- **Dashboard Web:** interface responsiva com graficos em tempo real via WebSocket
- **Historico SD Card:** log CSV diario (~1.5 MB/dia), cartao de 32GB = ~58 anos
- **MQTT:** integracao com Home Assistant, Grafana (via Telegraf + InfluxDB)
- **Alarmes:** sobretensao (>253V) e subtensao (<197V) com buzzer, LED e notificacao web

## Pinagem

```
ESP32 GPIO 16 (RX2) ──┬── PZEM #1 (L1, addr 0x01) TX
                       ├── PZEM #2 (L2, addr 0x02) TX
                       └── PZEM #3 (L3, addr 0x03) TX

ESP32 GPIO 17 (TX2) ──┬── PZEM #1 RX
                       ├── PZEM #2 RX
                       └── PZEM #3 RX

GPIO 21 (SDA) ── OLED SDA
GPIO 22 (SCL) ── OLED SCL
GPIO 23 (MOSI) ── SD MOSI
GPIO 19 (MISO) ── SD MISO
GPIO 18 (SCK)  ── SD SCK
GPIO  5 (CS)   ── SD CS
GPIO  4        ── Buzzer
GPIO  2        ── LED status (built-in)
```

## Estrutura do Projeto

```
medidor-trifasico/
├── platformio.ini              # Configuracao PlatformIO
├── partitions.csv              # Tabela de particoes customizada
├── src/
│   ├── main.cpp                # Setup/loop, orquestracao
│   ├── config.h                # Pinos, constantes, structs
│   ├── pzem_reader.h/.cpp      # Leitura dos 3 PZEMs
│   ├── display_manager.h/.cpp  # OLED SSD1306
│   ├── web_server.h/.cpp       # AsyncWebServer + WebSocket
│   ├── mqtt_client.h/.cpp      # Publicacao MQTT
│   ├── sd_logger.h/.cpp        # Log CSV no SD card
│   ├── alarm_manager.h/.cpp    # Alarmes sub/sobretensao
│   ├── wifi_manager.h/.cpp     # WiFi STA + fallback AP
│   └── ntp_time.h/.cpp         # Sincronizacao NTP
├── data/                        # LittleFS -> dashboard web
│   ├── index.html
│   ├── style.css
│   ├── app.js
│   └── chart.min.js.gz
└── tools/
    └── set_pzem_addresses.cpp   # Utilitario config enderecos PZEM
```

## Instalacao

### Pre-requisitos
- [PlatformIO CLI](https://platformio.org/install/cli) ou PlatformIO IDE (VS Code)
- Cabo USB para o ESP32

### 1. Configurar enderecos dos PZEMs

Cada PZEM precisa de um endereco Modbus unico. De fabrica, todos vem com 0xF8. Configure um por vez:

```bash
# Conecte apenas 1 PZEM ao ESP32
# Edite tools/set_pzem_addresses.cpp -> TARGET_ADDRESS = 0x01 (L1)
pio run -e set_pzem_addr -t upload
pio device monitor
# Repita para 0x02 (L2) e 0x03 (L3)
```

### 2. Configurar WiFi e MQTT

Edite `src/config.h`:
```cpp
#define WIFI_SSID       "SuaRedeWiFi"
#define WIFI_PASSWORD   "SuaSenha"
#define MQTT_SERVER     "192.168.1.100"
```

### 3. Compilar e fazer upload

```bash
# Firmware
pio run -e esp32 -t upload

# Filesystem (dashboard web)
pio run -e esp32 -t uploadfs
```

### 4. Verificar

```bash
# Monitor serial
pio device monitor

# Acesse o dashboard web pelo IP mostrado no OLED/serial
```

## Dashboard Web

Acesse `http://IP_DO_ESP32` no navegador. O dashboard mostra:
- 3 cards com leituras de cada fase em tempo real
- Grafico de potencia dos ultimos 5 minutos
- Barra de alarme quando ha sub/sobretensao

## Integracao MQTT

Topics publicados:
```
medidor/L1/voltage    medidor/L2/voltage    medidor/L3/voltage
medidor/L1/current    medidor/L2/current    medidor/L3/current
medidor/L1/power      medidor/L2/power      medidor/L3/power
medidor/L1/energy     medidor/L2/energy     medidor/L3/energy
medidor/L1/frequency  medidor/L2/frequency  medidor/L3/frequency
medidor/L1/pf         medidor/L2/pf         medidor/L3/pf
medidor/data          (JSON completo)
medidor/status        (online/offline - LWT)
medidor/alarm         (alertas com retain)
```

## Seguranca

Os modulos PZEM-004T conectam-se a tensao de rede (220/380V). A instalacao **deve ser feita por alguem confortavel com eletricidade de rede**, dentro de um gabinete apropriado com espacamento adequado. Sempre desligue a energia antes de fazer conexoes.

## Licenca

Este projeto e de uso pessoal/hobby. Use por sua conta e risco.
