# Lista de Materiais - Medidor Trifasico ESP32

## Componentes Principais

| # | Componente | Qtd | Especificacao | Preco PIX (R$) | Onde comprar |
|---|---|---|---|---|---|
| 1 | **ESP32 DevKit V1** | 1 | 30 pinos, CP2102, USB-C, 4MB flash | R$ 66,36 | [Usinainfo](https://www.usinainfo.com.br/nodemcu/esp32-nodemcu-iot-com-wifi-e-bluetooth-30-pinos-com-cp2102-5147.html) |
| 2 | **PZEM-004T v3.0** com TC **split-core** 100A | 3 | Modbus RTU, medidor AC, **CT aberto obrigatorio** | R$ 55-80/un | [Mercado Livre](https://lista.mercadolivre.com.br/pzem-004) ou [AliExpress](https://www.aliexpress.com/item/32907139707.html) |
| 3 | **Display OLED SSD1306** | 1 | 0.96", 128x64, I2C (4 pinos), branco | R$ 25,46 | [Usinainfo](https://www.usinainfo.com.br/display-arduino/display-oled-096-i2c-128x64-branco-para-arduino-5366.html) |
| 4 | **Modulo SD Card** | 1 | SPI, slot micro SD, 3.3V/5V | R$ 7,89 | [Usinainfo](https://www.usinainfo.com.br/outros-modulos-arduino/sd-card-para-arduino-leitor-micro-sd-card-2637.html) |
| 5 | **Cartao micro SD** | 1 | 4GB+ classe 10 (SanDisk/Kingston) | R$ 20-30 | Qualquer papelaria ou [Mercado Livre](https://lista.mercadolivre.com.br/cartao-micro-sd-16gb-classe-10) |
| 6 | **Buzzer passivo BP18** | 1 | 5V, acionamento GND Low | R$ 6,94 | [Usinainfo](https://www.usinainfo.com.br/buzzer-arduino/buzzer-passivo-modulo-transdutor-bp18-acionamento-gnd-low-4708.html) |

> **IMPORTANTE sobre PZEM-004T:** Exigir CT **split-core (aberto)** que abre como grampo para abracar o cabo sem desconectar. NAO comprar com CT fechado (closed loop). Na Usinainfo tem o V4.0 a R$78,38 mas vem com CT fechado. Preferir Mercado Livre ou AliExpress com split-core.

## Alimentacao

| # | Componente | Qtd | Especificacao | Preco PIX (R$) | Onde comprar |
|---|---|---|---|---|---|
| 7 | **Fonte HLK-PM01** (opcao A) | 1 | AC 220V -> DC 5V 600mA, embutida | R$ 18-35 | [ML](https://lista.mercadolivre.com.br/hlk-pm01-5v) ou [AliExpress](https://www.aliexpress.com/wholesale?SearchText=HLK-PM01+AC-DC+5V+600mA) |
| 8 | **Carregador USB 5V** (opcao B) | 1 | Qualquer carregador de celular + cabo USB | R$ 0 (reaproveitar) | - |

## Montagem em Placa Perfurada

| # | Componente | Qtd | Especificacao | Preco PIX (R$) | Onde comprar |
|---|---|---|---|---|---|
| 9 | **Placa perfurada dupla face 5x7cm** | 1 | 432 furos, passo 2.54mm, fibra de vidro | R$ 4,99 | [Usinainfo #06403](https://www.usinainfo.com.br/placa-de-fibra-de-vidro/placa-de-circuito-impresso-ilhada-universal-432-furos-dupla-face-5x7cm-3126.html) |
| 9b | **Placa perfurada dupla face 8x12cm** (alternativa maior) | 1 | 1260 furos, passo 2.54mm, fibra de vidro | R$ 8,31 | [Usinainfo #06820](https://www.usinainfo.com.br/placa-de-fibra-de-vidro/placa-de-circuito-impresso-ilhada-1260-furos-dupla-face-8x12cm-3521.html) |
| 10 | **Barra de pinos femea 20p** | 2 | 2.54mm, empilhavel (soquete ESP32 - cortar 2x15) | R$ 2,27/un | [Usinainfo #07279](https://www.usinainfo.com.br/barras-de-pinos/barra-de-20-pinos-254mm-femea-conector-empilhavel-para-pci-3964.html) |
| 11 | **Barra de pinos macho 1x40** | 1 | 2.54mm, 180 graus (cortar no tamanho) | R$ 1,89 | [Usinainfo #06017](https://www.usinainfo.com.br/barras-de-pinos/barra-de-pinos-macho-1x40-vias-com-passo-de-254mm-180-preto-2748.html) |
| 12 | **Jumper M-M 20cm** kit 20pcs | 1 | Dupont Premium, 24 AWG, 10 cores | R$ 5,89 | [Usinainfo #05861](https://www.usinainfo.com.br/jumper/jumper-premium-para-protoboard-macho-macho-20cm-kit-c-20-pecas-2611.html) |
| 12b | **Jumper M-F 20cm** kit 20pcs | 1 | Dupont Premium, 24 AWG, 10 cores | R$ 5,51 | [Usinainfo #05632](https://www.usinainfo.com.br/jumper/jumper-premium-para-protoboard-macho-femea-20cm-kit-c-20-pecas-2314.html) |
| 13 | **Borne KRE 2 vias** | 1-6 | 12mm, passo 5.08mm, max 10A | R$ 1,88/un | [Usinainfo](https://www.usinainfo.com.br/borne-kre-e-xt60/conector-borne-kre-12mm-2-vias-azul-3077.html) |

## Componentes Passivos

| # | Componente | Qtd | Especificacao | Preco PIX (R$) | Onde comprar |
|---|---|---|---|---|---|
| 14 | **Resistor 4.7k** kit 10un | 1 kit | 1/4W THT, CR25, +/-5% - pull-up I2C | R$ 1,62 | [Usinainfo #07085](https://www.usinainfo.com.br/resistor-14-watt/resistor-4k7-14w-kit-com-10-unidades-3773.html) |
| 15 | **Resistor 330R** kit 10un | 1 kit | 1/4W THT, CR25, +/-5% - limitador LED | R$ 2,00 | [Usinainfo #06254](https://www.usinainfo.com.br/resistor-14-watt/resistor-330r-14w-kit-com-10-unidades-2977.html) |
| 16 | **Capacitor eletrolitico 100uF 16V** kit 10un | 1 kit | Radial, polarizado - desacoplamento 5V | R$ 3,33 | [Usinainfo](https://www.usinainfo.com.br/capacitor-eletrolitico/capacitor-eletrolitico-100uf-16v-kit-com-10-unidades-3053.html) |
| 17 | **Capacitor ceramico 100nF 50V** | 1 | Codigo 104 - filtro 3.3V | ~R$ 0,50 | **Indisponivel na Usinainfo** - comprar no [ML](https://lista.mercadolivre.com.br/capacitor-ceramico-100nf) ou [AliExpress](https://www.aliexpress.com/wholesale?SearchText=ceramic+capacitor+100nF+104+50V) |
| 18 | **LED verde 3mm difuso** kit 10un | 1 kit | LV3MD, 2~2.2V, 20mA max | R$ 3,40 | [Usinainfo #07323](https://www.usinainfo.com.br/led-difuso/led-verde-3mm-difuso-kit-com-10-unidades-4008.html) |

## Caixa e Acabamento

| # | Componente | Qtd | Especificacao | Preco PIX (R$) | Onde comprar |
|---|---|---|---|---|---|
| 19 | **Caixa Patola PB-114** | 1 | 55x97x148mm, com tampa | R$ 31,92 | [Usinainfo](https://www.usinainfo.com.br/caixas-patola/caixa-patola-case-para-montagem-55-x-97-x-148-mm-pb-114-3880.html) |
| 19b | **Caixa Patola PB-112** (alternativa menor) | 1 | 53x85x124mm, com tampa | R$ 24,70 | [Usinainfo](https://www.usinainfo.com.br/caixas-patola/caixa-patola-case-para-montagem-53-x-85-x-124-mm-pb-112-3879.html) |
| 19c | **Case SZOMK Trilho DIN** (alternativa quadro) | 1 | 145x90x40mm, com bornes, trilho DIN | R$ 66,68 | [Usinainfo](https://www.usinainfo.com.br/caixas-patola/case-szomk-para-montagem-145x90x40mm-gabinete-para-trilho-din-bornes-5027.html) |
| 20 | **Prensa-cabo PG7** | 3-4 | IP67, nylon, para cabo 3.5-6.5mm | R$ 2,76/un | [Usinainfo](https://www.usinainfo.com.br/conectores-e-adaptadores/prensa-cabo-pg7-ip67-14-para-condutor-de-35-a-65mm-5043.html) |

## Ferramentas Necessarias (se nao tiver)

| Ferramenta | Observacao |
|---|---|
| Ferro de solda + estanho | Para montar na placa perfurada |
| Multimetro | Para verificar conexoes |
| Chave phillips pequena | Para os bornes |
| Alicate de corte | Para fios |

## Resumo de Custo (R$ PIX - Fev/2026)

### Opcao 1: Tudo na Usinainfo (exceto PZEM e cap 100nF)

| # | Item | Preco PIX |
|---|---|---|
| 1 | ESP32 DevKit V1 | R$ 66,36 |
| 2 | Display OLED SSD1306 | R$ 25,46 |
| 3 | Modulo SD Card | R$ 7,89 |
| 4 | Buzzer Passivo BP18 | R$ 6,94 |
| 5 | Placa perfurada 8x12cm dupla face | R$ 8,31 |
| 6 | 2x Barra pinos femea 20p | R$ 4,54 |
| 7 | Barra pinos macho 1x40 | R$ 1,89 |
| 8 | Jumper M-M 20cm x20 | R$ 5,89 |
| 9 | Jumper M-F 20cm x20 | R$ 5,51 |
| 10 | 2x Borne KRE 2 vias | R$ 3,76 |
| 11 | Resistor 4.7k kit 10un | R$ 1,62 |
| 12 | Resistor 330R kit 10un | R$ 2,00 |
| 13 | Capacitor 100uF 16V kit 10un | R$ 3,33 |
| 14 | LED verde 3mm kit 10un | R$ 3,40 |
| 15 | Caixa Patola PB-114 | R$ 31,92 |
| 16 | 4x Prensa-cabo PG7 | R$ 11,04 |
| | **Subtotal Usinainfo** | **R$ 189,86** |
| 17 | 3x PZEM-004T split-core (ML) | ~R$ 165-240 |
| 18 | Cartao micro SD 16GB (ML) | ~R$ 20 |
| 19 | Capacitor ceramico 100nF (ML) | ~R$ 2 |
| | **TOTAL ESTIMADO** | **R$ 377-452** |

### Opcao 2: PZEM pelo AliExpress (economica, demora 30-60 dias)

| Categoria | Custo |
|---|---|
| Usinainfo (buscar, sem frete) | R$ 189,86 |
| 3x PZEM-004T AliExpress | ~R$ 96-168 |
| Cartao SD + cap 100nF (ML) | ~R$ 22 |
| **Total estimado** | **R$ 308-380** |

## Dicas de Compra

### PZEM-004T (item mais critico)
- **OBRIGATORIO**: CT tipo **split-core** (abre como grampo). NAO comprar CT fechado (closed loop)
- Versao **v3.0 ou v4.0** - ambas usam Modbus RTU e sao compativeis com a biblioteca
- Confirmar que vem com TC de 100A incluso na embalagem
- Comprar 3 unidades do mesmo vendedor para garantir consistencia
- Abertura interna do CT120: ~16mm (cabe cabo ate 10mm²)
- [AliExpress - Split CT](https://www.aliexpress.com/item/32907139707.html) | [ML - Buscar](https://lista.mercadolivre.com.br/pzem-004)

### ESP32 DevKit V1
- Preferir versao com **30 pinos** (mais compacta). CH340 ou CP2102 tanto faz
- Selecionar variante **USB-C** na pagina do produto
- [Usinainfo](https://www.usinainfo.com.br/nodemcu/esp32-nodemcu-iot-com-wifi-e-bluetooth-30-pinos-com-cp2102-5147.html)

### Display OLED
- Confirmar que e **I2C** (4 pinos: VCC, GND, SDA, SCL). Existem versoes SPI com 7 pinos - NAO usar essa
- [Usinainfo](https://www.usinainfo.com.br/display-arduino/display-oled-096-i2c-128x64-branco-para-arduino-5366.html)

### Placa Perfurada
- **5x7cm** (R$ 4,99) para montagem compacta ou **8x12cm** (R$ 8,31) se quiser mais espaco
- Preferir **dupla face** (fibra de vidro) - mais resistente que fenolite

### Caixa
- **PB-114** (14.8x9.7x5.5cm, R$31,92) - tamanho ideal para o projeto
- **PB-112** (12.4x8.5x5.3cm, R$24,70) - alternativa menor e mais barata
- **Case SZOMK Trilho DIN** (14.5x9x4cm, R$66,68) - se quiser montar no quadro eletrico

### Capacitor ceramico 100nF
- Unico item **indisponivel** na Usinainfo (era outlet com defeito de medicao)
- Comprar no Mercado Livre ou em qualquer loja de eletronica - custa centavos

### HLK-PM01
- Cuidado na instalacao - entrada AC direto na rede 220V! Alternativa mais segura: usar carregador USB externo
- [AliExpress](https://www.aliexpress.com/wholesale?SearchText=HLK-PM01+AC-DC+5V+600mA)

## PCB Customizada (opcional, futura)

Arquivos KiCad 7 prontos em `hardware/` para fabricacao na JLCPCB quando quiser migrar da placa perfurada:
- `hardware/medidor-trifasico.kicad_pro` - Projeto
- `hardware/medidor-trifasico.kicad_sch` - Esquematico
- `hardware/medidor-trifasico.kicad_pcb` - Layout PCB (90x80mm, 2 camadas)
- `hardware/schematic.pdf` - PDF do esquematico
- `hardware/schematic.txt` - Diagrama ASCII de referencia
