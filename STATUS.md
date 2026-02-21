# Status do Projeto - Medidor Trifasico ESP32

> Atualizado em: 21/02/2026

## Resumo

Medidor trifasico DIY com ESP32 + 3x PZEM-004T para monitoramento de sistema 220/380V em tempo real. Dashboard web, display OLED, log em SD card e integracao MQTT.

---

## Firmware

| Modulo | Arquivo | Status |
|--------|---------|--------|
| Configuracao e pinos | `src/config.h` | Pronto |
| Loop principal | `src/main.cpp` | Pronto |
| Leitura PZEM (3 fases) | `src/pzem_reader.cpp/.h` | Pronto |
| Display OLED SSD1306 | `src/display_manager.cpp/.h` | Pronto |
| Web Server + WebSocket | `src/web_server.cpp/.h` | Pronto |
| Cliente MQTT | `src/mqtt_client.cpp/.h` | Pronto |
| Log CSV no SD Card | `src/sd_logger.cpp/.h` | Pronto |
| Alarmes sub/sobretensao | `src/alarm_manager.cpp/.h` | Pronto |
| WiFi STA + fallback AP | `src/wifi_manager.cpp/.h` | Pronto |
| Sincronizacao NTP | `src/ntp_time.cpp/.h` | Pronto |
| OTA (over-the-air) | `src/ota_manager.cpp/.h` | Pronto |
| Dashboard web (HTML/CSS/JS) | `data/` | Pronto |
| Utilitario enderecamento PZEM | `tools/set_pzem_addresses.cpp` | Pronto |

**Compilacao:** OK - RAM 14.4%, Flash 49.3% (bastante folga)

**Ambientes PlatformIO:**
- `esp32` - firmware principal
- `set_pzem_addr` - utilitario de configuracao Modbus

---

## Hardware

### Projeto PCB (KiCad 7)

| Arquivo | Descricao | Status |
|---------|-----------|--------|
| `hardware/medidor-trifasico.kicad_pro` | Projeto KiCad | Pronto |
| `hardware/medidor-trifasico.kicad_sch` | Esquematico | Pronto |
| `hardware/medidor-trifasico.kicad_pcb` | Layout PCB 90x80mm 2 camadas | Pronto |
| `hardware/schematic.pdf` | PDF do esquematico | Pronto |
| `hardware/schematic.txt` | Diagrama ASCII de referencia | Pronto |

> PCB pronta para fabricar na JLCPCB quando migrar da placa perfurada.

### Esquema de Conexoes

```
ESP32 GPIO16 (RX2) ──bus──> 3x PZEM TX  (Modbus RTU, addr 0x01/0x02/0x03)
ESP32 GPIO17 (TX2) ──bus──> 3x PZEM RX
ESP32 GPIO21 (SDA) ──────> OLED SDA     (pull-up 4.7k)
ESP32 GPIO22 (SCL) ──────> OLED SCL     (pull-up 4.7k)
ESP32 GPIO23 (MOSI) ─────> SD MOSI
ESP32 GPIO19 (MISO) ─────> SD MISO
ESP32 GPIO18 (SCK) ──────> SD SCK
ESP32 GPIO5  (CS) ───────> SD CS
ESP32 GPIO4  ────────────> Buzzer passivo
ESP32 GPIO2  ── R 330R ──> LED verde
```

---

## Compras

### Usinainfo (local, buscar na loja - sem frete)

| Cod | Item | Preco PIX | Status |
|-----|------|-----------|--------|
| 08240 | ESP32 NodeMCU 30 Pinos CP2102 | R$ 66,36 | No carrinho |
| 10204 | Expansor ESP32 DevKit V1 30 Pinos | R$ 23,56 | No carrinho |
| 08483 | Display OLED 0.96" I2C 128x64 Branco | R$ 25,46 | No carrinho |
| 05887 | SD Card para Arduino / Leitor Micro SD | R$ 7,89 | No carrinho |
| 06403 | Placa Ilhada 432 Furos Dupla Face 5x7cm | R$ 4,99 | No carrinho |
| 06820 | Placa Ilhada 1260 Furos Dupla Face 8x12cm | R$ 8,31 | No carrinho |
| 06017 | Barra Pinos Macho 1x40 2.54mm | R$ 1,89 | No carrinho |
| 07279 | Barra Pinos Femea 20p 2.54mm (x2) | R$ 4,54 | No carrinho |
| 05861 | Jumper Premium M-M 20cm x20 | R$ 5,89 | No carrinho |
| 05632 | Jumper Premium M-F 20cm x20 | R$ 5,51 | No carrinho |
| 06354 | Borne KRE 12mm 2 Vias (x11) | R$ 20,69 | No carrinho |
| 07085 | Resistor 4.7k 1/4W kit 10un | R$ 1,62 | No carrinho |
| 06254 | Resistor 330R 1/4W kit 10un | R$ 2,00 | No carrinho |
| 06330 | Capacitor Eletrolitico 100uF 16V kit 10un | R$ 3,33 | No carrinho |
| 07323 | LED Verde 3mm Difuso kit 10un | R$ 3,40 | No carrinho |
| 07328 | LED Amarelo 3mm Difuso kit 10un | R$ 3,03 | No carrinho |
| 06638 | LED Vermelho 3mm Difuso kit 10un | R$ 4,01 | No carrinho |
| 07768 | Buzzer Passivo BP18 GND Low | R$ 6,94 | No carrinho |
| | **Total Usinainfo (29 itens, boleto)** | **R$ 199,40** | Pronto para comprar |

### Mercado Livre

| Item | Preco | Status |
|------|-------|--------|
| Capacitor Ceramico 100nF 50V x100 pcs | ~R$ 15-20 | Comprado - chega quarta |

### AliExpress

| Item | Preco | Status |
|------|-------|--------|
| 3x PZEM-004T v3.0 com CT **split-core** 100A | ~R$ 96-168 | Comprado - 30-60 dias |

### Ja tem

| Item |
|------|
| Cartao micro SD (4GB+ classe 10) |

### Custo total estimado: **R$ 310-390**

---

## Proximos Passos

### Fase 1 - Montagem imediata (quando buscar na Usinainfo)
- [ ] Soldar barras de pinos femea na placa perfurada (soquete ESP32)
- [ ] Montar ESP32 + OLED + SD Card + Buzzer + LED na placa
- [ ] Conectar conforme esquema de pinos
- [ ] Fazer upload do firmware (`pio run -e esp32 -t upload`)
- [ ] Fazer upload do dashboard (`pio run -e esp32 -t uploadfs`)
- [ ] Testar Wi-Fi, dashboard web, display OLED, log SD, buzzer

### Fase 2 - Integracao PZEM (quando chegar do AliExpress)
- [ ] Configurar enderecos Modbus (0x01, 0x02, 0x03) um por vez
- [ ] Conectar os 3 PZEMs no barramento UART (GPIO 16/17)
- [ ] Testar leitura das 3 fases
- [ ] Instalar na caixa com prensa-cabos
- [ ] Abracar os cabos das fases com os CTs split-core

### Fase 3 - Monitoramento e ajustes
- [ ] Configurar MQTT (Home Assistant / Grafana)
- [ ] Verificar precisao das leituras vs multimetro
- [ ] Ajustar limiares de alarme se necessario
- [ ] Monitorar estabilidade por alguns dias

### Fase 4 - Melhorias futuras (opcional)
- [ ] Migrar para PCB customizada (arquivos KiCad prontos em `hardware/`)
- [ ] Implementar OTA para atualizacoes sem fio
- [ ] Adicionar medicao do neutro (4o PZEM)
- [ ] Implementar exportacao de dados (download CSV pelo dashboard)
- [ ] Notificacoes push (Telegram/WhatsApp)

---

## Limitacoes Conhecidas

- PZEM-004T nao mede potencia bidirecional (sempre positiva) - nao distingue consumo vs injecao solar
- WiFi/MQTT credentials hardcoded em `config.h` (sem portal de configuracao)
- CT split-core 100A com abertura de ~16mm (cabe cabo ate 10mm²)
- Precisao do PZEM: classe 1% para tensao, classe 2% para corrente
