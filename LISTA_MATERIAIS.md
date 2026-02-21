# Lista de Materiais - Medidor Trifasico ESP32

## Componentes Principais

| # | Componente | Qtd | Especificacao | Custo aprox |
|---|---|---|---|---|
| 1 | **ESP32 DevKit V1** | 1 | 30 pinos, CH340/CP2102, micro USB, 4MB flash | US$ 5-10 |
| 2 | **PZEM-004T v3.0** com TC split-core 100A | 3 | Modbus RTU, medidor AC, TC SCT-013-000 incluso | US$ 42 (3x ~US$14) |
| 3 | **Display OLED SSD1306** | 1 | 0.96", 128x64, I2C (4 pinos), cor branca ou azul | US$ 3-4 |
| 4 | **Modulo SD Card** | 1 | SPI, slot micro SD, 3.3V/5V | US$ 2-3 |
| 5 | **Cartao micro SD** | 1 | Qualquer capacidade (4GB+), classe 10 | US$ 3-5 |
| 6 | **Buzzer passivo** | 1 | 5V, tipo piezo | US$ 0.50-1 |

## Alimentacao

| # | Componente | Qtd | Especificacao | Custo aprox |
|---|---|---|---|---|
| 7 | **Fonte HLK-PM01** (opcao A) | 1 | AC 220V -> DC 5V 600mA, embutida | US$ 3-4 |
| 8 | **Carregador USB 5V** (opcao B) | 1 | Qualquer carregador de celular + cabo micro USB | US$ 0 (reaproveitar) |

## Montagem e Conexao

| # | Componente | Qtd | Especificacao | Custo aprox |
|---|---|---|---|---|
| 9 | **Placa perfurada** | 1 | 5x7cm ou 7x9cm, passo 2.54mm | US$ 1-2 |
| 10 | **Barra de pinos femea** | 2 | 1x15 pinos, 2.54mm (para encaixar o ESP32) | US$ 0.50 |
| 11 | **Fios jumper** | ~20 | Dupont M-M e M-F, 10-20cm | US$ 2-3 |
| 12 | **Fio rigido 0.5mm** | 1m | Para soldas na placa perfurada | US$ 0.50 |
| 13 | **Caixa projeto plastica** | 1 | ~15x10x5cm, com tampa | US$ 3-8 |
| 14 | **Borne/conector KF301** | 6 | 2 pinos ou 3 pinos, passo 5mm (entrada/saida fases) | US$ 1-2 |
| 15 | **Prensa-cabo (gland)** | 3-4 | PG7 ou PG9, para passar cabos pela caixa | US$ 1-2 |

## Ferramentas Necessarias (se nao tiver)

| Ferramenta | Observacao |
|---|---|
| Ferro de solda + estanho | Para montar na placa perfurada |
| Multimetro | Para verificar conexoes |
| Chave phillips pequena | Para os bornes |
| Alicate de corte | Para fios |

## Resumo de Custo

| Categoria | Custo |
|---|---|
| Componentes principais (#1-6) | US$ 55-64 |
| Alimentacao (#7 ou #8) | US$ 0-4 |
| Montagem (#9-15) | US$ 9-18 |
| **Total estimado** | **US$ 64-86** |

## Dicas de Compra no AliExpress

- **PZEM-004T v3.0**: Procure a versao que ja vem com o TC (transformador de corrente) split-core. Geralmente vendido como "PZEM-004T 100A" com o anel CT incluso. Comprar 3 unidades do mesmo vendedor.
- **ESP32 DevKit V1**: Preferir versao com 30 pinos (mais compacta). CH340 ou CP2102 tanto faz.
- **Display OLED**: Confirmar que e I2C (4 pinos: VCC, GND, SDA, SCL). Existem versoes SPI com 7 pinos - NAO usar essa.
- **Modulo SD**: Confirmar que opera em 3.3V ou que tem regulador. A maioria funciona.
- **HLK-PM01**: Cuidado na instalacao - entrada AC direto na rede! Alternativa mais segura: usar carregador USB externo.

## Busca Sugerida no AliExpress

```
1. "ESP32 DevKit V1 CH340 30pin"
2. "PZEM-004T v3.0 100A AC" (comprar 3)
3. "OLED display 0.96 I2C SSD1306 128x64"
4. "Micro SD card module SPI Arduino"
5. "Micro SD card 16GB class 10"
6. "Passive buzzer module 5V Arduino"
7. "HLK-PM01 AC-DC 5V 600mA"
8. "PCB prototype board 5x7cm"
9. "Dupont jumper wire kit 10cm"
10. "KF301 2P screw terminal 5mm"
11. "PG7 cable gland nylon"
12. "Plastic project box 150x100x50mm"
```
