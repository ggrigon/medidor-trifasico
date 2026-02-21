// Utilitario para configurar enderecos Modbus dos PZEMs
//
// IMPORTANTE: Conecte apenas UM PZEM por vez ao barramento Serial2!
// O PZEM de fabrica vem com endereco 0xF8 (broadcast).
// Este programa troca para o endereco desejado.
//
// Uso:
//   1. Conecte apenas o PZEM que deseja configurar
//   2. Defina TARGET_ADDRESS abaixo (0x01, 0x02 ou 0x03)
//   3. Compile e faca upload: pio run -e set_pzem_addr -t upload
//   4. Abra o monitor serial: pio device monitor
//   5. Repita para cada PZEM

#include <Arduino.h>
#include <PZEM004Tv30.h>

#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17

// ========================================
// ALTERE AQUI O ENDERECO DESEJADO
// ========================================
#define TARGET_ADDRESS 0x01  // 0x01 = L1, 0x02 = L2, 0x03 = L3

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n==================================");
    Serial.println(" PZEM-004T - Configurador de Endereco");
    Serial.println("==================================\n");

    HardwareSerial pzemSerial(2);

    // Conecta usando endereco geral (0xF8 = broadcast para PZEM novo)
    PZEM004Tv30 pzem(pzemSerial, PZEM_RX_PIN, PZEM_TX_PIN, 0xF8);
    delay(500);

    // Le endereco atual
    uint8_t currentAddr = pzem.getAddress();
    Serial.printf("Endereco atual: 0x%02X\n", currentAddr);

    // Tenta ler tensao para confirmar comunicacao
    float v = pzem.voltage();
    if (isnan(v)) {
        Serial.println("AVISO: Nao foi possivel ler tensao (PZEM desconectado ou sem carga)");
        Serial.println("Tentando configurar mesmo assim...\n");
    } else {
        Serial.printf("Tensao lida: %.1fV - Comunicacao OK!\n\n", v);
    }

    // Configura novo endereco
    Serial.printf("Configurando novo endereco: 0x%02X ...\n", TARGET_ADDRESS);
    if (pzem.setAddress(TARGET_ADDRESS)) {
        Serial.println("SUCESSO! Endereco configurado.");

        // Verifica lendo com novo endereco
        PZEM004Tv30 pzemNew(pzemSerial, PZEM_RX_PIN, PZEM_TX_PIN, TARGET_ADDRESS);
        delay(500);
        float vNew = pzemNew.voltage();
        if (!isnan(vNew)) {
            Serial.printf("Verificacao: Tensao = %.1fV no novo endereco 0x%02X\n", vNew, TARGET_ADDRESS);
        } else {
            Serial.println("Verificacao: Nao foi possivel ler com novo endereco (pode ser normal sem carga)");
        }
    } else {
        Serial.println("FALHA ao configurar endereco!");
    }

    Serial.println("\n----------------------------------");
    Serial.println("Desconecte este PZEM e conecte o proximo.");
    Serial.println("Altere TARGET_ADDRESS e repita o processo.");
    Serial.println("----------------------------------");
}

void loop() {
    // Nada a fazer - utilitario de configuracao unica
    delay(10000);
}
