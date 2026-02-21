# Lista de Materiais - Medidor Trifasico ESP32

## Componentes Principais

| # | Componente | Qtd | Especificacao | Preco BR (R$) | Onde comprar |
|---|---|---|---|---|---|
| 1 | **ESP32 DevKit V1** | 1 | 30 pinos, CP2102, USB-C, 4MB flash | R$ 59,80 | [Usinainfo #10357](https://www.usinainfo.com.br/index.php?route=product/product&product_id=10357) |
| 2 | **PZEM-004T v3.0** com TC **split-core** 100A | 3 | Modbus RTU, medidor AC, **CT aberto obrigatorio** | R$ 55-80/un | [Mercado Livre](https://lista.mercadolivre.com.br/pzem-004) ou [AliExpress](https://www.aliexpress.com/item/32907139707.html) |
| 3 | **Display OLED SSD1306** | 1 | 0.96", 128x64, I2C (4 pinos), branco | R$ 26,80 | [Usinainfo #08483](https://www.usinainfo.com.br/index.php?route=product/product&product_id=8483) |
| 4 | **Modulo SD Card** | 1 | SPI, slot micro SD, 3.3V/5V | R$ 6,30 | [Usinainfo #08137](https://www.usinainfo.com.br/index.php?route=product/product&product_id=8137) |
| 5 | **Cartao micro SD** | 1 | 4GB+ classe 10 (SanDisk/Kingston) | R$ 20-30 | Qualquer papelaria ou [Mercado Livre](https://lista.mercadolivre.com.br/cartao-micro-sd-16gb-classe-10) |
| 6 | **Buzzer passivo** | 1 | 5V, tipo piezo | R$ 7,30 | [Usinainfo #07768](https://www.usinainfo.com.br/index.php?route=product/product&product_id=7768) |

> **IMPORTANTE sobre PZEM-004T:** Exigir CT **split-core (aberto)** que abre como grampo para abracar o cabo sem desconectar. NAO comprar com CT fechado (closed loop). Na Usinainfo tem o V4.0 a R$78,38 mas vem com CT fechado. Preferir Mercado Livre ou AliExpress com split-core.

## Alimentacao

| # | Componente | Qtd | Especificacao | Preco BR (R$) | Onde comprar |
|---|---|---|---|---|---|
| 7 | **Fonte HLK-PM01** (opcao A) | 1 | AC 220V -> DC 5V 600mA, embutida | R$ 18-35 | [ML](https://lista.mercadolivre.com.br/hlk-pm01-5v) ou [AliExpress](https://www.aliexpress.com/wholesale?SearchText=HLK-PM01+AC-DC+5V+600mA) |
| 8 | **Carregador USB 5V** (opcao B) | 1 | Qualquer carregador de celular + cabo USB | R$ 0 (reaproveitar) | - |

## Montagem em Placa Perfurada

| # | Componente | Qtd | Especificacao | Preco BR (R$) | Onde comprar |
|---|---|---|---|---|---|
| 9 | **Placa perfurada** | 1 | 7x9cm, passo 2.54mm | ~R$ 5 | Usinainfo (balcao) |
| 10 | **Barra de pinos femea** | 2 | 1x15 pinos, 2.54mm (soquete ESP32) | ~R$ 3/par | Usinainfo (balcao) |
| 11 | **Barra de pinos macho** | 1 | 1x40 pinos, 2.54mm (cortar no tamanho) | ~R$ 2 | Usinainfo (balcao) |
| 12 | **Fios jumper** | ~20 | Dupont M-M e M-F, 10-20cm | ~R$ 8 | Usinainfo (balcao) |
| 13 | **Fio rigido 0.5mm** | 1m | Para soldas na placa perfurada | ~R$ 2 | Usinainfo (balcao) |
| 14 | **Borne KRE 2 vias** | 1-6 | Passo 5mm, para entrada/saida | R$ 1,88/un | [Usinainfo #03077](https://www.usinainfo.com.br/index.php?route=product/product&product_id=3077) |

## Componentes Passivos (para montagem ou PCB futura)

| # | Componente | Qtd | Especificacao | Preco BR (R$) | Onde comprar |
|---|---|---|---|---|---|
| 15 | **Resistor 4.7k** | 2 | 1/4W THT (ou 0805 SMD para PCB) - pull-up I2C | ~R$ 0,20/un | Usinainfo (balcao) |
| 16 | **Resistor 330R** | 1 | 1/4W THT (ou 0805 SMD) - limitador LED | ~R$ 0,20 | Usinainfo (balcao) |
| 17 | **Capacitor eletrolitico 100uF** | 1 | 16V, radial - desacoplamento 5V | ~R$ 1,50 | Usinainfo (balcao) |
| 18 | **Capacitor ceramico 100nF** | 1 | 50V - filtro 3.3V | ~R$ 0,50 | Usinainfo (balcao) |
| 19 | **LED verde 3mm** | 1 | THT, indicador de status | ~R$ 0,50 | Usinainfo (balcao) |

## Caixa e Acabamento

| # | Componente | Qtd | Especificacao | Preco BR (R$) | Onde comprar |
|---|---|---|---|---|---|
| 20 | **Caixa projeto plastica** | 1 | ~15x10x7cm, com tampa | R$ 15-40 | [ML](https://lista.mercadolivre.com.br/caixa-projeto-plastica-eletrica) ou loja eletrica |
| 21 | **Prensa-cabo PG7** | 3-4 | Para passar cabos pela caixa | R$ 2-4/un | [ML](https://lista.mercadolivre.com.br/prensa-cabo-pg7) ou loja eletrica |

## Ferramentas Necessarias (se nao tiver)

| Ferramenta | Observacao |
|---|---|
| Ferro de solda + estanho | Para montar na placa perfurada |
| Multimetro | Para verificar conexoes |
| Chave phillips pequena | Para os bornes |
| Alicate de corte | Para fios |

## Resumo de Custo (R$ - Fev/2026)

| Categoria | Onde | Custo (R$) |
|---|---|---|
| ESP32 + OLED + SD + Buzzer + Borne | Usinainfo (buscar) | ~R$ 102 |
| 3x PZEM-004T split-core | Mercado Livre | ~R$ 165-240 |
| Passivos + headers + placa perfurada | Usinainfo (balcao) | ~R$ 20 |
| Cartao SD + caixa + prensa-cabo | ML ou loja local | ~R$ 50-80 |
| **Total estimado** | | **R$ 340-440** |

> Alternativa economica: comprar PZEMs no AliExpress (~R$ 96-168 os 3) economiza ~R$100 mas demora 30-60 dias.

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
- [Usinainfo](https://www.usinainfo.com.br/index.php?route=product/product&product_id=10357)

### Display OLED
- Confirmar que e **I2C** (4 pinos: VCC, GND, SDA, SCL). Existem versoes SPI com 7 pinos - NAO usar essa
- [Usinainfo](https://www.usinainfo.com.br/index.php?route=product/product&product_id=8483)

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
