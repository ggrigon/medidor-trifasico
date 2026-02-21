# Medidor de Tensao Trifasico - ESP32 + PZEM-004T

Medidor trifasico DIY para monitoramento de sistema 220/380V em tempo real. Le tensao, corrente, potencia, energia, frequencia e fator de potencia das 3 fases com interface web, display OLED, historico em SD card e integracao MQTT.

**Custo estimado:** ~R$ 310-390 (vs R$ 700+ de solucoes comerciais como Shelly Pro 3EM)

## Funcionalidades

- **Leitura das 3 fases:** tensao, corrente, potencia, energia, frequencia, fator de potencia
- **Display OLED:** 5 paginas auto-rotativas (overview + detalhe de cada fase + alarmes)
- **Dashboard Web:** interface responsiva com graficos em tempo real via WebSocket
- **Historico SD Card:** log CSV diario (~1.5 MB/dia), cartao de 32GB = ~58 anos
- **MQTT:** integracao com Home Assistant, Grafana (via Telegraf + InfluxDB)
- **Alarmes:** sobretensao (>253V) e subtensao (<197V) com buzzer, LED e notificacao web
- **OTA:** atualizacao de firmware via Wi-Fi

## Lista de Materiais

| # | Componente | Qtd | Funcao |
|---|---|---|---|
| 1 | ESP32 DevKit V1 (30 pinos, CP2102) | 1 | Microcontrolador principal - WiFi + Bluetooth |
| 2 | PZEM-004T v3.0 com TC split-core 100A | 3 | Medidor de energia por fase (Modbus RTU) |
| 3 | Display OLED SSD1306 128x64 I2C | 1 | Display local para leituras |
| 4 | Modulo SD Card SPI | 1 | Armazenamento de historico CSV |
| 5 | Cartao microSD (4GB+ classe 10) | 1 | Midia de armazenamento |
| 6 | Buzzer passivo 5V (BP18) | 1 | Alarme sonoro |
| 7 | Placa perfurada dupla face | 1 | Montagem dos componentes |
| 8 | Fios jumper Dupont (M-M, M-F) | ~40 | Conexoes entre componentes |
| 9 | Resistor 4.7k 1/4W | 2 | Pull-up I2C (SDA/SCL) |
| 10 | Resistor 330R 1/4W | 1 | Limitador LED status |
| 11 | Capacitor eletrolitico 100uF 16V | 1 | Desacoplamento 5V |
| 12 | Capacitor ceramico 100nF 50V | 1 | Filtro 3.3V |
| 13 | LED verde 3mm | 1 | Indicador de status |
| 14 | Borne KRE 2 vias | 1-6 | Conexoes parafusadas |
| 15 | Barras de pinos macho/femea | 3 | Soquetes e conectores |
| 16 | Fonte 5V 1A (USB ou HLK-PM01) | 1 | Alimentacao do ESP32 |

> **IMPORTANTE:** Os PZEMs devem ter CT tipo **split-core** (aberto, tipo grampo). NAO comprar com CT fechado (closed loop). Ver detalhes completos em [`LISTA_MATERIAIS.md`](LISTA_MATERIAIS.md).

## Pinagem

```
ESP32 GPIO16 (RX2) ──bus──> 3x PZEM TX   (Modbus RTU, addr 0x01/0x02/0x03)
ESP32 GPIO17 (TX2) ──bus──> 3x PZEM RX
ESP32 GPIO21 (SDA) ──────> OLED SDA      (pull-up 4.7k para 3.3V)
ESP32 GPIO22 (SCL) ──────> OLED SCL      (pull-up 4.7k para 3.3V)
ESP32 GPIO23 (MOSI) ─────> SD MOSI
ESP32 GPIO19 (MISO) ─────> SD MISO
ESP32 GPIO18 (SCK) ──────> SD SCK
ESP32 GPIO5  (CS) ───────> SD CS
ESP32 GPIO4  ────────────> Buzzer passivo
ESP32 GPIO2  ── R 330R ──> LED verde
```

Ver esquematico completo em [`hardware/schematic.pdf`](hardware/schematic.pdf) ou [`hardware/schematic.txt`](hardware/schematic.txt).

## Estrutura do Projeto

```
medidor-trifasico/
├── platformio.ini              # Configuracao PlatformIO
├── partitions.csv              # Tabela de particoes customizada (1.87MB app + 2.06MB LittleFS)
├── LISTA_MATERIAIS.md          # Lista detalhada com precos e links de compra (BR)
├── STATUS.md                   # Andamento do projeto
├── src/
│   ├── main.cpp                # Setup/loop, orquestracao cooperativa com millis()
│   ├── config.h                # Pinos, constantes, structs (PhaseData, MeterData)
│   ├── pzem_reader.h/.cpp      # Leitura dos 3 PZEMs via Modbus RTU
│   ├── display_manager.h/.cpp  # OLED SSD1306 (5 paginas rotativas)
│   ├── web_server.h/.cpp       # AsyncWebServer + WebSocket (tempo real)
│   ├── mqtt_client.h/.cpp      # Publicacao MQTT (Home Assistant / Grafana)
│   ├── sd_logger.h/.cpp        # Log CSV no SD card (rotacao diaria)
│   ├── alarm_manager.h/.cpp    # Alarmes sub/sobretensao com buzzer
│   ├── wifi_manager.h/.cpp     # WiFi STA + fallback AP
│   ├── ntp_time.h/.cpp         # Sincronizacao NTP
│   └── ota_manager.h/.cpp      # Atualizacao OTA via Wi-Fi
├── data/                        # LittleFS -> dashboard web
│   ├── index.html
│   ├── style.css
│   ├── app.js
│   └── chart.min.js.gz
├── hardware/                    # Projeto PCB KiCad 7 (90x80mm, 2 camadas)
│   ├── medidor-trifasico.kicad_pro
│   ├── medidor-trifasico.kicad_sch
│   ├── medidor-trifasico.kicad_pcb
│   ├── schematic.pdf
│   └── schematic.txt
└── tools/
    └── set_pzem_addresses.cpp   # Utilitario config enderecos PZEM
```

## Instalacao

### Pre-requisitos
- [PlatformIO CLI](https://platformio.org/install/cli) ou PlatformIO IDE (VS Code)
- Cabo USB-C para o ESP32

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

## PCB Customizada (opcional)

Projeto KiCad 7 pronto em `hardware/` para fabricacao na JLCPCB:
- PCB carrier board 90x80mm, 2 camadas
- Todos os modulos encaixam via pin header (ESP32, PZEMs, OLED, SD, buzzer)
- Resistores e capacitores em SMD 0805
- Plano de terra em ambas as camadas
- Furos de montagem M3 nos 4 cantos

## Seguranca

Os modulos PZEM-004T conectam-se a tensao de rede (220/380V). A instalacao **deve ser feita por alguem confortavel com eletricidade de rede**, dentro de um gabinete apropriado com espacamento adequado. Sempre desligue a energia antes de fazer conexoes. Os CTs split-core podem ser instalados com a rede energizada, mas tome cuidado com os fios de tensao do PZEM.

## Licenca

Este projeto e de uso pessoal/hobby. Use por sua conta e risco.
